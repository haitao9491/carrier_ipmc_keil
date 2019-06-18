/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.sycomm.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    ADC.c
** Last modified Date:      2012-1-10
** Last Version:		    1.0
** Descriptions:		    monitor 4 channel voltage
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2012-1-10
** Version:				    1.0
** Descriptions:		    无
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             zhangzongkai
** Modified Date:           2015-07-03
** Version:                 1.0
** Descriptions:
**
*********************************************************************************************************/
#include "bsp_int.h"
#include "uart.h"
#include "app_cfg.h"
#include "adc.h"

OS_EVENT  *AdcMBox;
OS_EVENT  *AdcLockSem;

/*
  ADC information struct
 */
__ADC_INFO	__ADC_INFOData;
const  __ADCP_INFO	ADC_InfoPtr = &__ADC_INFOData;


#define ADC_EDGE(x)         ((x) << 27)
#define ADC_START(x)        ((x) << 24)
#define ADC_PDN(x)          ((x) << 21)
#define ADC_CLKS(x)         ((x) << 17)
#define ADC_BURST(x)        ((x) << 16)
#define ADC_CLKDIV(x)       ((x) << 8)
#define ADC_INSEL(x)        (1 << (x))

/********************************************************************************************************
** Function name:  Adc_Start_AIN
** Descriptions:   start AD conversion
** Input:          channel num
** Output:         NONE
*********************************************************************************************************/
void Adc_Start_AIN(uint8 ch) {

	AD0CR = ADC_INSEL(ch)    |              /* chose channel*/
			((Fpclk / 3000000 - 1) << 8)|	/* CLKDIV=Fpclk/1000000-1 */
			                                /* clk is 3MHz */
			ADC_BURST(0)	|	            /* BURST=0,soft control convert */
			ADC_CLKS(0)		|               /* CLKS=0,use 11clock convert */
			ADC_PDN(1)		|               /* PDN=1,normal mode */
			ADC_START(0x01);

	AD0INTEN = ADC_INSEL(ch);
}

/********************************************************************************************************
** Function name: ADC_Read
** Descriptions:
** Input:         NONE
** Output:        NONE
*********************************************************************************************************/
void ADC_Read(void)
{
	ADC_InfoPtr->ADC_Data = ADDR(ADC_InfoPtr->ADC_Channel);	/* read ADC channel result and clear interrupt */
	ADC_InfoPtr->ADC_Data = (ADC_InfoPtr->ADC_Data >> 6) & 0x3ff;
	OSMboxPost(AdcMBox,(void *)&ADC_InfoPtr->ADC_Data);
}

/********************************************************************************************************
** Function name: ADC_Exception
** Descriptions:  ADC Interrupt
** Input:         NONE
** Output:        NONE
*********************************************************************************************************/
void ADC_Exception(void)
{
    ADC_Read();
}

void ADC_Init(void)
{
	PCONP |=1 <<12;								/* ADC Power on */

   	AD0CR = (1<<0)                  |           /* chose channel*/
			((Fpclk / 3000000 - 1) << 8)|	    /* CLKDIV=Fpclk/1000000-1 */
			                                    /* clk is 3MHz */
			(0 << 16)|	                        /* BURST=0,soft control convert */
			(0 << 17)|	                        /* CLKS=0,use 11clock convert */
			(1 << 21)|                          /* PDN=1,normal mode */
			(0 << 24);		                    /* disable ADC */

	AD0INTEN = 0x01 << 0;                       /* enable ADC channel,after convert creat interrupt */

	ADC_InfoPtr->ADC_Channel = 0;

	AdcMBox = OSMboxCreate((void *)0);
	if(AdcMBox == NULL) {
		UART0_SendStr("AdcMBox create failed\n");
		return;
	}
	AdcLockSem = OSSemCreate(1);
	if(AdcLockSem == NULL) {
		UART0_SendStr("AdcLockSem create failed\n");
		return;
	}
	BSP_IntVectSet(	(INT8U)ADC_IRQ,
						(INT8U)ADC_ISR_PRIORITY,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)ADC_Exception );
	BSP_IntEn(ADC_IRQ);
    //SetVICIRQ(ADC_IRQ, ADC_ISR_PRIORITY,(uint32)ADC_Exception);
}

/*********************************************************************************************************
** Function name:           read_ADC_Value
** Descriptions:
** Input parameters:
** 电压计算公式： 分压后的实际电压=AD读取值*参考电压/2的AD位数的次方，再根据分压电阻的比例求得实际电压值
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint8 Read_ADC_Value(uint16 *ADC_Val, uint8 *channel)
{
    uint8 err;
    uint8 i;
    uint32 Samp[8];

    OSSemPend(AdcLockSem, 0, &err);
    if(err != OS_ERR_NONE)
    	goto GetSemErr;

    for(i=0; i < ADC_CHANNEL_NUM; i++){
        ADC_InfoPtr->ADC_Channel = i;
        Adc_Start_AIN(ADC_InfoPtr->ADC_Channel);

/* waiting message box
    when message valid get and save converted result
    timeout time 1 second*/
    	Samp[i] = *(uint16 *)OSMboxPend(AdcMBox,100,&err);
	    if( *(&err) == OS_ERR_TIMEOUT)
            goto TimeOut;

    	switch(ADC_InfoPtr->ADC_Channel) {

#if	(BOARD_TYPE == BOARD_TYPE_MPCB_V2)
			case 0: /* 0.95v P0_23 */
			case 1: /* 1v P0_24 */
			case 2: /* 1.2v P0_25 */
			case 3: /* 1.8v P0_26 */
				Samp[i] = Samp[i] * 3.3 * 1000 / 1024;
				break;
			case 4: /* 2.5v P1_30 */
			case 5: /* 3.3v P1_31 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (40 / 20);
				break;
			case 6: /* 12v P0_12 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (120 / 20) ;
				break;
				
#elif (BOARD_TYPE == BOARD_TYPE_MPCB_V3)
			case 0: /* 3.3v P0_23 */
			case 1: /* 2.5v P0_24 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (40 / 20);
				break;
			case 3: /* 12v P0_26 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (120 / 20) ;
				break;
			case 2: /* 1.2v P0_25 */
			case 4: /* 1.8v P1_30 */
			case 5: /* 1.0v P1_31 */
			case 6: /* 0.95v P0_12 */
				Samp[i] = Samp[i] * 3.3 * 1000 / 1024;
				break;
				
#elif (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3)
			case 0: /* 3.3v P0_23 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (151 * 1.0 / 100);
				break;
			case 1: /* 2.5v P0_24 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (130 * 1.0 / 100);
				break;
			case 2: /* 1.2v P0_25 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (110 * 1.0 / 100);
				break;
			case 3: /* 12v P0_26 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (120 / 20) ;
				break;
				
#elif (BOARD_TYPE == BOARD_TYPE_XSCB_V2)
			case 0: /* 3.3v P0_23 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (151 * 1.0 / 100);
				break;
			case 1: /* 2.5v P0_24 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (130 * 1.0 / 100);
				break;
			case 2: /* 1.2v P0_25 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (110 * 1.0 / 100);
				break;
			case 3: /* 12v P0_26 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (120 / 20) ;
				break;
			case 4: /* VCORE P1_30 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (110 * 1.0 / 100);
				break;
				
#elif (BOARD_TYPE == BOARD_TYPE_EIPB_V2) || (BOARD_TYPE == BOARD_TYPE_EIPB_V3)
			case 0: /* 3.3v P0_23 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (151 * 1.0 / 100);
				break;
			case 1: /* 2.5v P0_24 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (130 * 1.0 / 100);
				break;
			case 2: /* 12v P0_25 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (120 / 20) ;
				break;
			case 3: /* 1.2v P0_26 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024) * (110 * 1.0 / 100);
				break;
			case 4: /* 1.8v P1_30 */
			case 5: /* 1.0v P1_31 */
				Samp[i] = (Samp[i] * 3.3 * 1000 / 1024);
				break;
#endif
			default:
				break;
		}
	}
	for (i=0; i < ADC_CHANNEL_NUM; i++) {
		ADC_Val[i] = Samp[i];
	}
	*channel = ADC_CHANNEL_NUM;
	goto AdcOK;

GetSemErr:
	UART0_SendStr("Get Adc Sem err\n");
	return 1;
TimeOut:
	UART0_SendStr("Timeout, Adc err\n");
	OSSemPost(AdcLockSem);
	return 1;
AdcOK:
	OSSemPost(AdcLockSem);
	return 0;
}

/*********************************************************************************************************
   END FILE
*********************************************************************************************************/


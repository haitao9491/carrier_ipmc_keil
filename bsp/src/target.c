/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           target.c
** Last modified Date:  2004-09-17
** Last Version:        1.0
** Descriptions:        header file of the specific codes for LPC2200 target boards
**                      Every project should include a copy of this file, user may modify it as needed
**--------------------------------------------------------------------------------------------------------
** Created by:          Chenmingji
** Created date:        2004-02-02
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         Chenmingji
** Modified date:       2004-09-17
** Version:             1.01
** Descriptions:        Renewed the template, added more compiler supports
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#define IN_TARGET
#include "config.h"
#include "app_cfg.h"
#include "uart.h"
#include "bsp_int.h"
#include "bsp_os.h"
#include "bsp_uart.h"
#include "boardinfo.h"


//extern void  BSP_CPU_Init (void);
extern void  PINSEL_Init( void );
/*********************************************************************************************************
* Function name:       sysDelayNS
* Descriptions:        长软件延时
* input parameters:    idly	延时参数，值越大，延时越久
* output parameters:   none
* Returned value:      none
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void  sysDelayNS(INT32U  uiDly)
{
    INT32U  i;
    for(; uiDly > 0; uiDly--){
        for(i = 0; i < 5000; i++);
    }
}

/*********************************************************************************************************
** Function name:           Timer0_Exception
**
** Descriptions:            Timer0 interrupt service function
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
** Created by:              Chenmingji
** Created Date:            2004/02/02
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void  Timer0_Exception (void)
{	
    T0IR = 0x01;
    OSTimeTick();	
}

/*********************************************************************************************************
** Function name:           Timer0Init
**
** Descriptions:            Initialize the Time0
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
** Created by:              Chenmingji
** Created Date:            2004/02/02
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void  Timer0Init (void)
{
    T0IR = 0xffffffff;
    T0TCR = 0x03;
    T0TC = 0;
    T0MCR = 0x03;
    T0MR0 = (Fpclk / OS_TICKS_PER_SEC);
    T0TCR = 0x01;
	BSP_IntVectSet((INT8U)BSP_INT_SRC_NBR_TMR0, 
					(INT8U)0,
					(INT8U)BSP_INT_SRC_TYPE_IRQ, 
					(OS_FNCT_VOID)Timer0_Exception);
	BSP_IntEn(BSP_INT_SRC_NBR_TMR0);
    //vicIrqFuncSet(4,0,(INT32U)Timer0_Exception);
 }

/*********************************************************************************************************
** Function name:           TargetInit
**
** Descriptions:            Initialize the target board; it is called in a necessary place, change it as
**                          needed
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
** Created by:              Chenmingji
** Created Date:            2004/02/02
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void TargetInit (void)
{
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif  
	OS_ENTER_CRITICAL();

	srand((INT32U) TargetInit);
	BSP_IntInit();   /* Initialize Interrupt controller                    */
	PINSEL_Init();	

	Timer0Init();
	UART0Init (115200);
	OS_EXIT_CRITICAL();
}
/*********************************************************************************************************
** Function name:     PINSEL_Init
** Descriptions:      初始化SDRAM
** input parameters:  none
** output parameters: none
**
** Created by:		  wangxiumei
** Created Date:	  2011.12.20
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**-------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void  PINSEL_Init( void )
{
	/* init all pinsel to GPIO */
	PINSEL0		= 0x00000000;
	PINSEL1		= 0x00000000;
	PINSEL2		= 0x00000000;
	PINSEL3		= 0x00000000;
	PINSEL4		= 0x00000000;
	PINSEL5		= 0x00000000;
	PINSEL6		= 0x00000000;
	PINSEL7		= 0x00000000;
	PINSEL8		= 0x00000000;
	PINSEL9		= 0x00000000;
	/* ADC enable P0.23~P0.26 AIN function  */
	PINSEL1 |= 0x00154000;
#if (BOARD_TYPE == BOARD_TYPE_MPCB_V2) || (BOARD_TYPE == BOARD_TYPE_MPCB_V3)
   	/* ADC enable P0.12 AIN function */
   	PINSEL0 |= 0x03000000;
   	/* ADC enable P1.30~P1.31 AIN function*/
   	PINSEL3 |= 0xf0000000;
#elif (BOARD_TYPE == BOARD_TYPE_EIPB_V2) || (BOARD_TYPE == BOARD_TYPE_EIPB_V3)
	/* ADC enable P1.30~P1.31 AIN function*/
   	PINSEL3 |= 0xf0000000;
#elif (BOARD_TYPE == BOARD_TYPE_XSCB_V2)
	/* ADC enable P1.30 AIN function*/
   	PINSEL3 |= 0x30000000;
#endif
	/* SDA1/SCL1,TXD0/RXD0 */
	PINSEL0	    |= 0x0000005f;
	/* SDA0/SCL0 */
	PINSEL1     |= 0x01400000;
	/* Enable CS2, EINT1, EINT2*/
 	PINSEL4     |= 0x11400000;
 	/* SDA2/SCL2 */
    PINSEL5     |= 0xf0000000;
    /* setup PINSEL6  D0-D15*/
    PINSEL6     |= 0x55555555;
    /* setup PINSEL8 A0-A15*/
    PINSEL8     |= 0x55555555;
    /* setup PINSEL9 A16-A23 CS0,CS1,BLS0,BLS1*/
    PINSEL9     |= 0x50550055;
    /* enable emc */
    EMCControl = 0x00000001;

}

/*********************************************************************************************************
** Function name:           TargetResetInit
** Descriptions:            Initialize the target
** input parameters:        None
** output parameters:       None
** Returned value:          None
** Created by:              Chenmingji
** Created Date:            2004/02/02
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if 0 
extern void Reset(void);
void TargetResetInit (void)
{
#ifdef __IN_CHIP
    PINSEL_Init();                                                        /* 配置外部SDRAM                */
    MEMMAP = 0x01;                   									/* remap 从片内Flash			*/
#endif                                                                  /* __IN_CHIP                    */

    /*
     * Edit for LPC2460/70
     * 将中断向量表复制到片内
     * 的SRAM的前64个字节
     */
    uint8 i;
    uint32 *cp1,*cp2;
    cp1=(uint32*)Reset;
    cp2=(uint32*)0x40000000;
    for(i=0;i<16;i++)
    {
       *cp2++ = *cp1++;
    }
    MEMMAP           = 0x02;                   							/* remap 到内部RAM	  	        */
	/* IPMC所连外部管角定义及初始化 */
	PINSEL_Init();

    /* enable PLL, main cclk is 60MHz, pclk = cclk*/
	if ( PLLSTAT & (1 << 25) )
    {
		PLLCON = 1;														/* Enable PLL, disconnected     */
		PLLFEED = 0xAA;
		PLLFEED = 0x55;
    }

    PLLCON = 0;															/* Disable PLL, disconnected    */
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
    while(PLLSTAT & (3 << 24));

	SCS |= 0x30;                                                        /* Enable the mainOSC,1MHz~20MHz*/

	while((SCS & 0x40) == 0 );			 								/* Wait until main OSC is usable*/

	CLKSRCSEL = 0x01;					 								/* select main OSC as the PLL 	*/
																		/* clock source 				*/

    PLLCFG  = (((PLL_NValue) << 16)|(PLL_MValue));

	PLLCON = 1;
    PLLFEED = 0xAA;														/* Enable but disconnect the PLL*/
    PLLFEED = 0x55;
   while (((PLLSTAT & (1 << 24)) == 0));								/* Wait until the PLL is usable */

	CCLKCFG = CCLKDivValue;

	#if USE_USB
 		USBCLKCFG = USBCLKDivValue;										/* usbclk = 480 MHz/10 = 48 MHz */
 		PCONP |= 0x80000000;											/* Turn On USB PCLK 			*/
	#else
		USBCLKCFG = USBCLKDivValue;
		PCONP &= 0x7FFFFFFF;
	#endif                                                              /* USE_USB                      */
	while ( ((PLLSTAT & (1 << 26)) == 0) );								/* Check lock bit status 		*/
	while (((PLLSTAT & 0x00007FFF) != PLL_MValue) && (((PLLSTAT & 0x00FF0000) >> 16) != PLL_NValue));

 	PLLCON  = 3;														/* connect the PLL 				*/
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
	while (((PLLSTAT & (1 << 25))!= (1 << 25)));						/* Wait until the PLL is 		*/
																		/* connected and locked 		*/

	/*
	 *  Set system timers for each component
	 */
#if (Fpclk / (Fcclk / 4)) == 1

    PCLKSEL0 = 0x00000000;												/* PCLK is 1/4 CCLK 	        */
    PCLKSEL1 = 0x00000000;

#else

    #if (Fpclk / (Fcclk / 4)) == 2

    PCLKSEL0 = 0xAAAAAAAA;												/* PCLK is 1/2 CCLK 			*/
    PCLKSEL1 = 0xAAAAAAAA;

    #else

    PCLKSEL0 = 0x55555555;												/* PCLK is the same as CCLK 	*/
    PCLKSEL1 = 0x55555555;

    #endif
#endif

	/*
	 *  Set memory accelerater module
	 */
   MAMCR = 0;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
    #if Fcclk < 40000000
    	MAMTIM = 2;
    #else
   		MAMTIM = 3;
    #endif
#endif
    MAMCR = 2;

    return;
}
#endif

/*********************************************************************************************************
  以下为一些与系统相关的库函数的实现
  具体作用请ads的参考编译器与库函数手册
  用户可以根据自己的要求修改
*********************************************************************************************************/
/*********************************************************************************************************
  The implementations for some library functions
  For more details, please refer to the ADS compiler handbook and The library
  function manual
  User could change it as needed
*********************************************************************************************************/
#pragma import(__use_no_semihosting_swi)
#pragma import(__use_two_region_memory)

void _ttywrch (int ch)
{
    ch = ch;
}
void _sys_exit(int status)  
{  
    while(1);  
}  

/*********************************************************************************************************
  End File
*********************************************************************************************************/

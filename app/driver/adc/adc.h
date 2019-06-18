/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.sycomm.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    ADC.h
** Last modified Date:      2012-1-10
** Last Version:		    1.0
** Descriptions:		    lpc2468 ADC head file
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2012-1-10
** Version:				    1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified Date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "config.h"
#include "boardinfo.h"

/*********************************************************************************************************
   ADC information
*********************************************************************************************************/
typedef struct __adc_info {
	uint32	ADC_Data;			/* ADC convertd date */
	uint8	ADC_Channel;		/* ADC channel */
}__ADC_INFO,*__ADCP_INFO;

/*********************************************************************************************************
  Voltage reference value
*********************************************************************************************************/
#if (BOARD_TYPE == BOARD_TYPE_MPCB_V2) 

#define ADC0_VREF	950			/* ADC0 reference voltage 0.95V */
#define ADC1_VREF	1000		/* ADC1 reference voltage 1v */
#define ADC2_VREF	1200		/* ADC2 reference voltage 1.2v */
#define ADC3_VREF	1800		/* ADC3 reference voltage 1.8v */
#define ADC4_VREF	2500		/* ADC4 reference voltage 2.5v */
#define ADC5_VREF	3300		/* ADC5 reference voltage 3.3v */
#define ADC6_VREF	12000		/* ADC6 reference voltage 12v */

#define ADC_CHANNEL_NUM		7

#elif (BOARD_TYPE == BOARD_TYPE_MPCB_V3)

#define ADC0_VREF	3300		/* ADC0 reference voltage 3.3V */
#define ADC1_VREF	2500		/* ADC1 reference voltage 2.5v */
#define ADC2_VREF	1200		/* ADC2 reference voltage 1.2v */
#define ADC3_VREF	12000		/* ADC3 reference voltage 12v */
#define ADC4_VREF	1800		/* ADC4 reference voltage 1.8v */
#define ADC5_VREF	1000		/* ADC5 reference voltage 1.0v */
#define ADC6_VREF	950			/* ADC6 reference voltage 0.95V */

#define ADC_CHANNEL_NUM		7

#elif (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3)

#define ADC0_VREF	3300		/* ADC0 reference voltage 3.3V */
#define ADC1_VREF	2500		/* ADC1 reference voltage 2.5v */
#define ADC2_VREF	1200		/* ADC2 reference voltage 1.2v */
#define ADC3_VREF	12000		/* ADC3 reference voltage 12v */

#define ADC_CHANNEL_NUM		PWR_SENSOR_NUM

#elif (BOARD_TYPE == BOARD_TYPE_EIPB_V2) || (BOARD_TYPE == BOARD_TYPE_EIPB_V3)
#define ADC0_VREF	3300		/* ADC0 reference voltage 3.3V */
#define ADC1_VREF	2500		/* ADC1 reference voltage 2.5v */
#define ADC2_VREF	12000		/* ADC2 reference voltage 12v */
#define ADC3_VREF	1200		/* ADC3 reference voltage 1.2v */
#define ADC4_VREF	1800		/* ADC4 reference voltage 1.8v */
#define ADC5_VREF	1000		/* ADC5 reference voltage 1.0v */

#define ADC_CHANNEL_NUM		6

#elif (BOARD_TYPE == BOARD_TYPE_XSCB_V2)
#define ADC0_VREF	3300		/* ADC0 reference voltage 3.3V */
#define ADC1_VREF	2500		/* ADC1 reference voltage 2.5v */
#define ADC2_VREF	1200		/* ADC2 reference voltage 1.2v */
#define ADC3_VREF	12000		/* ADC3 reference voltage 12v */
#define ADC4_VREF	1800		/* ADC4 reference voltage 1.8v */

#define ADC_CHANNEL_NUM		5

#endif

#define ADC_VREF	12000

/********************************************************************************************************
** Function name: ADC_Init
** Descriptions:
** Input:         NONE
** Output:        NONE
*********************************************************************************************************/
void ADC_Init(void);
uint8 Read_ADC_Value(uint16 *ADC_Val, uint8 *channel);

#ifdef __cplusplus
    }
#endif

#endif                                                                  /* __ADC_H                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

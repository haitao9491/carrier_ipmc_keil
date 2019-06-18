/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_device.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI NetFn and CMDs
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-01
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __IPMI_LED_H
#define __IPMI_LED_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Blue Led state macro definition
 */

#define LONG_BLINK      ((uint8)1)
#define SHORT_BLINK     ((uint8)2)
#define LED_ON          ((uint8)3)
#define LED_OFF         ((uint8)4)

/*
 * Other Led state macro definition
 */
#define LED_OSS_OFF     ((uint8)0)
#define LED_OSS_RED     ((uint8)1)
#define LED_OSS_GREEN   ((uint8)2)
#define LED_OSS_ON      ((uint8)3)
#define LED_OK_OFF      ((uint8)4)
#define LED_OK_RED      ((uint8)5)
#define LED_OK_GREEN    ((uint8)6)
#define LED_OK_ON       ((uint8)7)

/*
 * Function statement
 */
void Set_FRT_Other_Led(INT8U oss_state,INT8U ok_state);
void Set_RTM_Other_Led(INT8U oss_state,INT8U ok_state);
void Set_AMC_Blue_Led(INT8U fru_id,INT8U state);
void Set_FRT_Blue_Led(INT8U state);
void Set_RTM_Blue_Led(INT8U state);
void IPMI_Blue_LED_TASK (void *pdata);

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_LED_H */



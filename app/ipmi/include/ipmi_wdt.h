/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_wdt.h
** Last modified Date:  2015-07-02
** Last Version:        1.0
** Descriptions:        ATCA IPMI NetFn and CMDs
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-02
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
#ifndef __IPMI_WDT_H
#define __IPMI_WDT_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function statement
 */
void Watchdog_Enable (void);
void Watchdog_Feed (void);
void IPMI_Watchdog_Task (void *pdata);

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_WDT_H */



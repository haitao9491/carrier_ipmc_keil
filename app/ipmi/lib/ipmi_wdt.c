/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-led.c
** Last modified Date:  2015-07-02
** Last Version:        1.0
** Descriptions:        ATCA FRU Function
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
#include "ipmi_defs.h"
#include "ipmi_cpld.h"
#include "ipmi_wdt.h"

extern void UART0_SendStr(char *s);

/*********************************************************************************************************
** Function name:           Watchdog_Enable
**
** Descriptions:            Enable ipmc watchdog
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
void Watchdog_Enable (void)
{
	IPMI_CPLD_WATCHDOG_FEED_REG &= ~IPMI_CPLD_WATCHDOG_FEED;
	IPMI_CPLD_WATCHDOG_FEED_REG |= IPMI_CPLD_WATCHDOG_FEED;
	IPMI_CPLD_WATCHDOG_EN_REG |= IPMI_CPLD_WATCHDOG_EN;
}

/*********************************************************************************************************
** Function name:           Watchdog_Feed
**
** Descriptions:            feed ipmc watchdog
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
void Watchdog_Feed (void)
{
	IPMI_CPLD_WATCHDOG_FEED_REG &= ~IPMI_CPLD_WATCHDOG_FEED;
	IPMI_CPLD_WATCHDOG_FEED_REG |= IPMI_CPLD_WATCHDOG_FEED;
}


/*********************************************************************************************************
** Function name:       Watchdog_Task
** Descriptions:        None
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void IPMI_Watchdog_Task (void *pdata)
{
    pdata = pdata;
    Watchdog_Enable ();
    UART0_SendStr("IPMI_WDT:    Task Create!\n");
    while(1) {
    	Watchdog_Feed ();
        OSTimeDlyHMSM(0, 0, 0, 200);
    }
}



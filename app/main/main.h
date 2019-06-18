/****************************************Copyright (c) ***************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                               http://www.embedtools.com
**
**--File Info---------------------------------------------------------------------------------------------
**  File name:              main.h
**  Last modified Date:
**  Last Version:           V1.0
**  Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:
** Created date:
** Version:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*
  head file reference
 */
#include "config.h"
#include "uart.h"
#include "ipmi_led.h"
#include "ipmi_comm.h"
#include "ipmi_wdt.h"
#include "ipmi_cpld.h"

/*
  Task ID Prio Stack function statement
 */
/* IPMI_Start_TASK */
#define IPMI_Start_TASK_ID                  17
#define IPMI_Start_TASK_PRIO                IPMI_Start_TASK_ID
#define IPMI_Start_TASK_STACK_SIZE          384
OS_STK  IPMI_Start_TASK_STACK[IPMI_Start_TASK_STACK_SIZE];
void    IPMI_Start_TASK(void *pdata);
/* IPMI_Watchdog_Task */
#define IPMI_Watchdog_Task_ID               18
#define IPMI_Watchdog_Task_PRIO             IPMI_Watchdog_Task_ID
#define IPMI_Watchdog_Task_STACK_SIZE       64
OS_STK  IPMI_Watchdog_Task_STACK[IPMI_Watchdog_Task_STACK_SIZE];
/* IPMI_IPMB_TASK */
#define IPMI_IPMB_TASK_ID                   19
#define IPMI_IPMB_TASK_PRIO                 IPMI_IPMB_TASK_ID
#define IPMI_IPMB_TASK_STACK_SIZE           512
OS_STK  IPMI_IPMB_TASK_STACK[IPMI_IPMB_TASK_STACK_SIZE];
extern void IPMI_IPMB_TASK(void *pdata);
/* IPMI_Blue_LED_TASK */
#define IPMI_Blue_LED_TASK_ID               20
#define IPMI_Blue_LED_TASK_PRIO             IPMI_Blue_LED_TASK_ID
#define IPMI_Blue_LED_TASK_STACK_SIZE       64
OS_STK  IPMI_Blue_LED_TASK_STACK[IPMI_Blue_LED_TASK_STACK_SIZE];
extern void IPMI_Blue_LED_TASK(void *pdata);/* IPMI_Carrier_HW_Task */
#define IPMI_Carrier_HW_Task_ID             20
#define IPMI_Carrier_HW_Task_PRIO           IPMI_Carrier_HW_Task_ID
#define IPMI_Carrier_HW_Task_STACK_SIZE     256
OS_STK  IPMI_Carrier_HW_Task_STACK[IPMI_Carrier_HW_Task_STACK_SIZE];
extern void  IPMI_Carrier_HW_Task(void *pdata);

#define AMC_HW_Task_ID             			21
#define AMC_HW_Task_PRIO           			AMC_HW_Task_ID
#define AMC_HW_Task_STACK_SIZE     			256
OS_STK  AMC_HW_Task_STACK[AMC_HW_Task_STACK_SIZE];

#define RTM_HW_Task_ID             			22
#define RTM_HW_Task_PRIO           			RTM_HW_Task_ID
#define RTM_HW_Task_STACK_SIZE     			128
OS_STK  RTM_HW_Task_STACK[RTM_HW_Task_STACK_SIZE];

/* IPMI_Sensor_TASK */
#define IPMI_Sensor_TASK_ID                 23
#define IPMI_Sensor_TASK_PRIO               IPMI_Sensor_TASK_ID
#define IPMI_Sensor_TASK_STACK_SIZE         384
OS_STK  IPMI_Sensor_TASK_STACK[IPMI_Sensor_TASK_STACK_SIZE];
extern void IPMI_Sensor_TASK(void *pdata);
/* IPMI_Console_TASK */
#define IPMI_Console_TASK_ID                24
#define IPMI_Console_TASK_PRIO              IPMI_Console_TASK_ID
#define IPMI_Console_TASK_STACK_SIZE        256
OS_STK  IPMI_Console_TASK_STACK[IPMI_Console_TASK_STACK_SIZE];
extern void IPMI_Console_TASK(void *pdata);
/* Ucos_Check_STK_TASK */
#define Ucos_Check_STK_TASK_ID              27
#define Ucos_Check_STK_TASK_PRIO             Ucos_Check_STK_TASK_ID
#define Ucos_Check_STK_TASK_STACK_SIZE      256
OS_STK  Ucos_Check_STK_TASK_STACK[Ucos_Check_STK_TASK_STACK_SIZE];
/*********************************************************************************************************
** Function name:       FIQ_Exception
** Descriptions:        FIQ中断服务程序
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void FIQ_Exception (void);

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __MAIN_H                    */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


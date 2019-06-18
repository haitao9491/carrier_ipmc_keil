/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			main.c
** Last modified Date:  2004-09-16
** Last Version:		1.0
** Descriptions:		The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-09-16
** Version:				1.0
** Descriptions:		The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			wangxiumei
** Modified date:		2012-1-11
** Version:				v1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			zhangzongkai
** Modified date:		2015-06-29
** Version:				v2.0
** Descriptions:
**
*********************************************************************************************************/
#include "main.h"
#include "bsp_uart.h"
#include "bsp_int.h"
#include "bsp_os.h"
#include "boardinfo.h"
#include "ipmi_sensor.h"

extern BoardInfo g_boardinfo ;
/*********************************************************************************************************
** Function name:       main
** Descriptions:        main function
** Input parameters:    None
** output parameters:   None
** Created Date:
*********************************************************************************************************/

int main (void)
{
	OSInit();
	
    OSTaskCreateExt(IPMI_Start_TASK,
                    (void *)0,
                    &IPMI_Start_TASK_STACK[IPMI_Start_TASK_STACK_SIZE-1],
                    IPMI_Start_TASK_PRIO,
                    IPMI_Start_TASK_ID,
                    &IPMI_Start_TASK_STACK[0],
                    IPMI_Start_TASK_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSStart();
    return 0;
}

/*********************************************************************************************************
** Function name:       Ucos_Check_STK_TASK
** Descriptions:        None
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void Ucos_Check_STK_TASK (void *pdata)
{
    OS_STK_DATA StackBytes;
    INT8U i;

    pdata = pdata;

    UART0_SendStr("UCOS_Check_STK:  Task Create!\n");
    while(1) {
        for (i = 17; i <= 23; i++) {
    	    OSTaskStkChk(i, &StackBytes);
            UART0_Printf("ID:%d,Free:%ld,Used:%ld\n",i,StackBytes.OSFree,StackBytes.OSUsed);
            OSTimeDlyHMSM(0, 0, 2, 0);
        }
    }
}
/*********************************************************************************************************
** Function name:       Start_TASK
** Descriptions:        None
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/

void IPMI_Start_TASK (void *pdata)
{
	pdata = pdata;

	TargetInit();
	boardInfoInit();
	set_cpld_start_state();
	ipmi_sensor_init();
	UART0_Printf("ipmc mode :%d\n",g_boardinfo.ipmc_mode);
	UART0_Printf("Reset init count:%d\n",IPMI_CPLD_HOTSWAP_STATUS_ADDR);
    IPMI_CPLD_HOTSWAP_STATUS_ADDR += 1;
	
    OSTaskCreateExt(IPMI_Watchdog_Task,
                    (void *)0,
                    &IPMI_Watchdog_Task_STACK[IPMI_Watchdog_Task_STACK_SIZE-1],
                    IPMI_Watchdog_Task_PRIO,
                    IPMI_Watchdog_Task_ID,
                    &IPMI_Watchdog_Task_STACK[0],
                    IPMI_Watchdog_Task_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
					
	OSTaskCreateExt(IPMI_Console_TASK,
                    (void *)0,
                    &IPMI_Console_TASK_STACK[IPMI_Console_TASK_STACK_SIZE-1],
                    IPMI_Console_TASK_PRIO,
                    IPMI_Console_TASK_ID,
                    &IPMI_Console_TASK_STACK[0],
                    IPMI_Console_TASK_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
					
    OSTaskCreateExt(IPMI_Sensor_TASK,
                    (void *)0,
                    &IPMI_Sensor_TASK_STACK[IPMI_Sensor_TASK_STACK_SIZE-1],
                    IPMI_Sensor_TASK_PRIO,
                    IPMI_Sensor_TASK_ID,
                    &IPMI_Sensor_TASK_STACK[0],
                    IPMI_Sensor_TASK_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
										
	OSTaskCreateExt(IPMI_Carrier_HW_Task,
					(void *)0,
					&IPMI_Carrier_HW_Task_STACK[IPMI_Carrier_HW_Task_STACK_SIZE-1],
					IPMI_Carrier_HW_Task_PRIO,
					IPMI_Carrier_HW_Task_ID,
					&IPMI_Carrier_HW_Task_STACK[0],
					IPMI_Carrier_HW_Task_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
					
	OSTaskCreateExt(AMC_HW_Task,
					(void *)0,
					&AMC_HW_Task_STACK[AMC_HW_Task_STACK_SIZE-1],
					AMC_HW_Task_PRIO,
					AMC_HW_Task_ID,
					&AMC_HW_Task_STACK[0],
					AMC_HW_Task_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
					
	OSTaskCreateExt(RTM_HW_Task,
					(void *)0,
					&RTM_HW_Task_STACK[RTM_HW_Task_STACK_SIZE-1],
					RTM_HW_Task_PRIO,
					RTM_HW_Task_ID,
					&RTM_HW_Task_STACK[0],
					RTM_HW_Task_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSTaskCreateExt(IPMI_IPMB_TASK,
					(void *)0,
					&IPMI_IPMB_TASK_STACK[IPMI_IPMB_TASK_STACK_SIZE-1],
					IPMI_IPMB_TASK_PRIO,
					IPMI_IPMB_TASK_ID,
					&IPMI_IPMB_TASK_STACK[0],
					IPMI_IPMB_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);						

#if 1
    OSTaskCreateExt(Ucos_Check_STK_TASK,
                    (void *)0,
                    &Ucos_Check_STK_TASK_STACK[Ucos_Check_STK_TASK_STACK_SIZE-1],
                    Ucos_Check_STK_TASK_PRIO,
                    Ucos_Check_STK_TASK_ID,
                    &Ucos_Check_STK_TASK_STACK[0],
                    Ucos_Check_STK_TASK_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#endif

	printBoardInfo();
	
    while (1)
    {
    	OSTimeDlyHMSM(0, 0, 10, 0);
    }
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


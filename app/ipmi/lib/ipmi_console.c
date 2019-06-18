/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-console.c
** Last modified Date:  2015-07-02
** Last Version:        1.0
** Descriptions:        serial port control
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-06
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
#include "app_cfg.h"
#include "bsp_int.h"
#include "uart.h"
#include "ringbuf.h"
#include "ipmi_console.h"
#include "ipmi_cpld.h"
#include "ipmi_fru.h"
#include "boardinfo.h"

extern BoardInfo g_boardinfo ;
extern UART_INFO	UART0Data;
extern const UART_INFOP	uart[MAX_UART_NUM];
extern INT8U Debug_Flag;

/*****************************************************************************
** Function name:		IPMI_Console_Send_Usage
**
** Descriptions:		send console usage
** parameters:
** Returned value:
*****************************************************************************/
void IPMI_Console_Send_Usage(void)
{
    UART0_SendStr("\nIPMI-Carrier-Console-Cmd-Usage:\n");
    UART0_SendStr("r [f/s] [add_start] [num]\n");
}
/*****************************************************************************
** Function name:		UARTGetLine
**
** Descriptions:		get a line from UART receive ringbuf,  this function main to
**                  process the input command from console, it will be called
**                  by UARTGetCmd.
** parameters:			cprng: uart rx ringbuf
**                  buf: the user buf
**                  bufsize: the user buf size
** Returned value:
**
*****************************************************************************/
int IPMI_Console_Get_Line (cring_buf *cprng, char *buf, int bufsize)
{
	unsigned short r, w;
	int result = 0;

	if (RNG_EMPTY(cprng))
		return 0;

	r = cprng->r;
	w = cprng->w;

	while (r != w) {
		if (('\n' == cprng->buf[r]) || ('\r' == cprng->buf[r])) {
			break;
		}
		r = CADD_MOD(r);
	}

	if (r == w) {
		if (RNG_FULL(cprng)) {
			RESET_RNG(cprng);
			result = -1;
		} else {
			result = 0;
		}
	} else {
		if (bufsize < ((r + MAXCHARBUFLEN) - cprng->r) % MAXCHARBUFLEN) {
			return -2;
		}
		r = CADD_MOD(r);
		result = (((r + MAXCHARBUFLEN) - cprng->r) % MAXCHARBUFLEN);
		while (cprng->r != r) {
			*buf++ = cprng->buf[cprng->r];
			cprng->r = CADD_MOD(cprng->r);
			//UART0_SendStr(buf);
		}
	}

	return result;
}


/*****************************************************************************
** Function name:		IPMI_Console_Cmd_Parse
**
** Descriptions:		parse console command---This function not complete
** parameters:
** Returned value:
*****************************************************************************/
int IPMI_Console_Cmd_Parse(char *buf, int buflen)
{
	if (!strncmp(buf, "help", 4)) {
	    IPMI_Console_Send_Usage();
	}
	else if (!strncmp(buf, "reset", 5)) {
	    UART0_Printf("Reset count:%d\n",IPMI_CPLD_HOTSWAP_STATUS_ADDR);
	}
	else if (!strncmp(buf, "debug", 5)) {
	    if(Debug_Flag)  Debug_Flag = 0x00;
	    else Debug_Flag = 0x01;
		UART0_Printf("debug flag:%d\n",Debug_Flag);
	}
	else if (!strncmp(buf, "hss", 3)) {
	    UART0_Printf("current hot swap status:%d\n",g_boardinfo.hss.CurState);
	}
	else if (!strncmp(buf, "lockbit", 7)) {
	    UART0_Printf("lockbit:%d\n",g_boardinfo.lock.Locked_bit);
	}

	return 0;
}

/*********************************************************************************************************
** Function name:       IPMI_Console_TASK
** Descriptions:        Use UART0 as Console
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
int IPMI_Console_Get_Cmd(uint8 id)
{
	char cmd[MAXCHARBUFLEN];
	int len;
	len = IPMI_Console_Get_Line(&uart[id]->rx, cmd, sizeof(cmd));

	if (len > 0)
		return IPMI_Console_Cmd_Parse(cmd, len);
	else if (len < 0)
		return -1;
	else
		return 0;

}

/*********************************************************************************************************
** Function name:       IPMI_Console_TASK
** Descriptions:        Use UART0 as Console
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void IPMI_Console_TASK (void *pdata)
{
    pdata = pdata;
    UART0_SendStr("IPMI_Console:    Task Create!\n");
	BSP_IntVectSet((INT8U)BSP_INT_SRC_NBR_UART0, 
					(INT8U)UART0_ISR_PRIORITY,
					(INT8U)BSP_INT_SRC_TYPE_IRQ, 
					(OS_FNCT_VOID)UART0IRQ);
	U0IER |= (IER_RBR|IER_THRE|IER_RLS);    /* Enable interrupt */
	BSP_IntEn(BSP_INT_SRC_NBR_UART0);
    while(1) {
    	IPMI_Console_Get_Cmd(0);
        OSTimeDlyHMSM(0, 0, 0, 20);
    }
}




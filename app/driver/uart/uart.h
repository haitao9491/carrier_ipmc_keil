/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart0.h
** Last modified Date:  2015-07-06
** Last Version:        1.0
** Descriptions:        arm lpc2468 uart0 head
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
#ifndef __IPMI_UART0_H
#define __IPMI_UART0_H

#include "config.h"
#include "ringbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_UART_NUM    1
#define DELAY_TIMES		30000

typedef struct _uart_info {
	cring_buf 	tx;
	cring_buf	rx;
} UART_INFO;

typedef UART_INFO	*UART_INFOP;

/*
  Register Funtion Offset
 */
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

/*
 * Function statement
 */
/*********************************************************************************************************
** Function name:			UART0Init
**
** Descriptions:			Initialize the UART0
**
** input parameters:		bps
** Returned value:			None
**
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void UART0Init (uint32 bps);

/*********************************************************************************************************
** Function name:           UART0_SendStr
**
** Descriptions:            Send the data
**
** input parameters:        data
** Returned value:          None
**
** Used global variables:   None
** Calling modules:         None
**
** Created by:              Chenmingji
** Created Date:            2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void UART0_SendStr (char *str);

/*********************************************************************************************************
** Function name:			UART0_gets
**
** Descriptions:			Receive the data from uart0 use inquiry mode
**
** input parameters:		data
** Returned value:			None
**
** Used global variables:	None
** Calling modules:			None
**
** Created by:				zhangzongkai
** Created Date:			2015/07/06
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void UART0_gets(uint8 *BufferPtr);

/*********************************************************************************************************
** Function name:			UART0_Printf
**
** Descriptions:			Send the data
**
** input parameters:		data
** Returned value:			None
**
** Used global variables:	None
** Calling modules:			None
**
** Created by:				wangxiumei
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void UART0_Printf(char *fmt,...);
void  UART0IRQ (void);
//void UART0IRQ (void);

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_UART0_H */




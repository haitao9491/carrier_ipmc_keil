/************************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    uart0.c
** Last modified Date:      2011-12-31
** Last Version:		    1.0
** Descriptions:		    make uart0 as a console
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    zhangzongkai
** Created date:		    2015-07-06
** Version:				    1.0
** Descriptions:		    NONE
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             zhangzongkai
** Modified Date:           2015-07-03
** Version:                 1.0
** Descriptions:
**
*********************************************************************************************************/
#include "uart.h"

uint32 UART0Status;
UART_INFO UART0Data;
const UART_INFOP	uart[MAX_UART_NUM] = {&UART0Data};

void UART0Init (uint32 bps)
{
    uint16 Fdiv;
    switch (bps) {
		case   1200:	Fdiv = 3072;	break;
		case   9600:	Fdiv =  384;	break;
		case  19200:	Fdiv =  192;	break;
		case  38400:	Fdiv =   96;	break;
		case  57600:	Fdiv =   64;	break;
		case 115200:	Fdiv =   32;	break;
		default:		break;
	}

    PCONP |= 1<<3;                                     /* Enable UART0 power */
    PINSEL0 = (PINSEL0 & 0xffffff0f)|(1<<4)|(1<<6);    /* Enable UART0 pins P0.2 and P0.3 */

    U0LCR = 0x80;                               /* Enable access to Divisor Latche */
	U0DLL = (INT8U)(Fdiv & 0x00FF);
	U0DLM = (INT8U)(Fdiv >> 8);
    U0LCR = 0x03;                               /* Disable access to Divisor Latche */
                                                /* 8 bit character length,1 stop bit,
                                                   Disable parity generation and checking*/
	U0IER = 0x00;                               /* Disable interrupt */
    U0FCR = 0x07;                               /* Enable FIFO*/
}

/*********************************************************************************************************
** Function name:			UART0_SendByte
**
** Descriptions:			Send the data
**
** input parameters:		data
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
void UART0_SendByte (uint8 data)
{
   if (data == '\n')
	{
		while((U0LSR & (1<<5)) == 0); /* Wait for empty U0THR */
		U0THR = '\r';
	}

	while((U0LSR & (1<<5)) == 0); /* Wait for empty U0THR */
	U0THR = data;
}

/*********************************************************************************************************
** Function name:			UART0_RevByte
**
** Descriptions:			Receive the data
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
void UART0_RecvByte(uint8 *BufferPtr)
{
    while ((U0LSR & 0x01) == 0);         /* waiting receive data ti RBR */
    *BufferPtr = U0RBR;

    return;
}

void UART0_gets(uint8 *BufferPtr)
{
    while (1)
    {
      UART0_RecvByte(BufferPtr);
      if (*BufferPtr == '\0') break;    // if received data is the end seamphore,break
        BufferPtr ++;                   // not check the confine,may be dangerous
    }
    return;
}

void UART0_RevByte (uint8 data)
{
   if (data == '\n')
	{
		while((U0LSR & (1<<5)) == 0); /* Wait for empty U0THR */
		U0THR = '\r';
	}

	while((U0LSR & (1<<5)) == 0); /* Wait for empty U0THR */
	U0THR = data;
}


void UART0_SendStr (char *str)
{
    while (*str) {
        UART0_SendByte(*str++);
    }
}


/*****************************************************************************
** Function name:		UARTCheckSend
**
** Descriptions:		check the UART whether is sending or not, if UART send complete,
**						that's UART in idle state, then set the send interrupt, through
**						send interrupt start UART send.
** parameters:			None
** Returned value:		None
**
***************************************************************************/
uint8 UARTCheckSend(uint8 id)
{
    unsigned char len;
    char txData;

    if (id >= MAX_UART_NUM) {
        return 1;
    }

    while (!(U0LSR & 0x20));
    GETC(&uart[id]->tx, txData, len);
    if (len > 0) {
        U0THR = txData;
    }

    return 0;
}

/*****************************************************************************
** Function name:		UARTPutc2TxRng
**
** Descriptions:		put a character to UART transmit ringbuf, if the buf is empty,
**									maybe need trigger the UART transmit interrupt by yourself.
**									so you should call the checksend function.
** parameters:			id: uart num
**									c:	charactor
** Returned value:
**
*****************************************************************************/
int UARTPutc2TxRng(uint8 id, char c)
{
    int empty = 0;

    if (RNG_FULL(&uart[id]->tx)) {
        return 1;
    }
    else {

        if (RNG_EMPTY(&uart[id]->tx)) {
            empty = 1;
        }
        PUTC(&uart[id]->tx, c);
        if (empty) {
            UARTCheckSend(id);
        }

        return 0;
    }
}

/*****************************************************************************
** Function name:		UARTPuts2TxRng
**
** Descriptions:		put a string to UART transmit ringbuf, if the buf is empty,
**						maybe need trigger the UART transmit interrupt by yourself.
**						so you should call the checksend function.
** parameters:			id: uart num
**						str:
**						wait:
** Returned value:
**
*****************************************************************************/
int UARTPuts2TxRng(INT8S id, char *buf, char wait)
{
    int i, delay = 1;

    if (id >= MAX_UART_NUM) {
    	return 1;
    }

    while (*buf != '\0') {
    	if (wait) {
    		delay = DELAY_TIMES;
    	}
    	for (i = 0; i < delay; i++) {
    		if (UARTPutc2TxRng(id, *buf) == 0) {
    			buf++;
    			break;
    		}
    	}
    	if (i >= delay)
    		break;
    }

    return 0;
}


void UART0_Printf(char *fmt,...)
{
    va_list ap;
    char string[128];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
#if 0
    UARTPuts2TxRng(0, string, 0);
#else
    UART0_SendStr(string);
#endif
    va_end(ap);
}

/*****************************************************************************
** Function name:		UARTISR
**
** Descriptions:		UART interrupt service routine
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
static void UART0ISR (void)
{
//	unsigned char len = 0;
//	char txData;
	char rxData;
	uint8 IIRValue, LSRValue;

	IIRValue = U0IIR;

	IIRValue >>= 1;				/* skip pending bit in IIR */
	IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
	if ( IIRValue == IIR_RLS )		/* Receive Line Status */
	{
		LSRValue = U0LSR;
		/* Receive Line Status */
		if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UART0Status = LSRValue;
			rxData = U0RBR;		/* Dummy read on RX to clear interrupt, then bail out */
			return;
		}
		if ( LSRValue & LSR_RDR )	/* Receive Data Ready */
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			rxData = U0RBR;
			PUTC(&uart[0]->rx, rxData);
			if ('\r' == rxData) {
				UARTPuts2TxRng(0, "\r\n<LPC2468#>", 0);
			} else {
				UARTPutc2TxRng(0, rxData);
			}
		}
	}
	else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
	{
		/* Receive Data Available */
		rxData = U0RBR;
		PUTC(&uart[0]->rx, rxData);
		if ('\r' == rxData) {
			UARTPuts2TxRng(0, "\r\n<LPC2468#>", 0);
		} else {
			UARTPutc2TxRng(0, rxData);
		}
	}
	else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
	{
		/* Character Time-out indicator */
		UART0Status |= 0x100;		/* Bit 9 as the CTI error */
	}
	else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
	{
		/* THRE interrupt */
		LSRValue = U0LSR;		/* Check status in the LSR to see if valid data in U0THR or not */

		if ((LSRValue & LSR_THRE)) {
/*
			GETC(&uart[0]->rx, txData, len);
			if (len > 0) {
				U0THR = txData;
			}*/
		}

	}
}

void  UART0IRQ (void)
{
	UART0ISR ();
}



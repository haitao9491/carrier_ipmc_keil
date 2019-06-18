#ifndef  _BSP_UART_H_
#define  _BSP_UART_H_

#include "ucos_ii.h"

#define UART_TXD_BUFSIZE 512
#define UART_RXD_BUFSIZE 512

#define  BSP_UART_00                     0
#define  BSP_UART_01                     1
#define  BSP_UART_02                     2
#define  BSP_UART_03                     3

void BSP_Uart_Init( INT32U uartx,INT32U baud_rate );
INT32U BSP_Uartx_Write ( INT32U uartx,INT32U len,INT8U *txbuf );
INT32U BSP_Uartx_Read ( INT32U uartx,INT32U len,INT8U *rxbuf );

#endif

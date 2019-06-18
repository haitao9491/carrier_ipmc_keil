
#include "ucos_ii.h"
#include "bsp.h"

#define BSP_UART0_PORT BSP_GPIO_PORT0
#define BSP_UART1_PORT BSP_GPIO_PORT0
#define BSP_UART2_PORT BSP_GPIO_PORT0
#define BSP_UART3_PORT BSP_GPIO_PORT0 

#define BSP_UART0_PINS ((1uL<< 2)|(1uL<< 3))
#define BSP_UART1_PINS ((1uL<<15)|(1uL<<16))
#define BSP_UART2_PINS ((1uL<<10)|(1uL<<11))
#define BSP_UART3_PINS ((1uL<< 0)|(1uL<< 1))

#define BSP_UART0_FNCT BSP_GPIO_OPT_FNCT_2
#define BSP_UART1_FNCT BSP_GPIO_OPT_FNCT_2
#define BSP_UART2_FNCT BSP_GPIO_OPT_FNCT_2
#define BSP_UART3_FNCT BSP_GPIO_OPT_FNCT_3

#define BSP_UART0_REG_BASE_ADDR 0xE000C000
#define BSP_UART1_REG_BASE_ADDR 0xE0010000
#define BSP_UART2_REG_BASE_ADDR 0xE0078000
#define BSP_UART3_REG_BASE_ADDR 0xE007C000

#define BSP_UART_REG_OFFSET_UxRBR 0x00
#define BSP_UART_REG_OFFSET_UxTHR 0x00
#define BSP_UART_REG_OFFSET_UxDLL 0x00
#define BSP_UART_REG_OFFSET_UxDLM 0x04
#define BSP_UART_REG_OFFSET_UxIER 0x04
#define BSP_UART_REG_OFFSET_UxIIR 0x08
#define BSP_UART_REG_OFFSET_UxFCR 0x08
#define BSP_UART_REG_OFFSET_UxLCR 0x0C
#define BSP_UART_REG_OFFSET_UxMCR 0x10
#define BSP_UART_REG_OFFSET_UxLSR 0x14
#define BSP_UART_REG_OFFSET_UxMSR 0x18
#define BSP_UART_REG_OFFSET_UxSCR 0x1C
#define BSP_UART_REG_OFFSET_UxACR 0x20
#define BSP_UART_REG_OFFSET_UxICR 0x24
#define BSP_UART_REG_OFFSET_UxFDR 0x28
#define BSP_UART_REG_OFFSET_UxTER 0x30

INT8U uart_rxd_buf[4][UART_RXD_BUFSIZE];
INT8U uart_txd_buf[4][UART_RXD_BUFSIZE];

QUEUE uart_rxd_queue[4];
QUEUE uart_txd_queue[4];

static void BSP_Uartx_ISR_Handler ( INT32U uartx );

static void BSP_Uart0_ISR_Handler( void );
static void BSP_Uart1_ISR_Handler( void );
static void BSP_Uart2_ISR_Handler( void );
static void BSP_Uart3_ISR_Handler( void );

void BSP_Uart_Init(INT32U uartx,INT32U baud_rate)
{
	INT32U base;
    INT32U pclk_freq;
	INT16U div;

	switch (uartx) {
	case BSP_UART_00 :
		pclk_freq  = BSP_SysCtrl_PerClkFreqGet(BSP_SYS_CTRL_PER_NBR_UART0);
		BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_UART0);
		BSP_GPIO_Cfg(BSP_UART0_PORT,BSP_UART0_PINS,BSP_UART0_FNCT);
		base = BSP_UART0_REG_BASE_ADDR;
		break;
	case BSP_UART_01 :
		pclk_freq  = BSP_SysCtrl_PerClkFreqGet(BSP_SYS_CTRL_PER_NBR_UART1);
		BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_UART1);
		BSP_GPIO_Cfg(BSP_UART1_PORT,BSP_UART1_PINS,BSP_UART1_FNCT);
		base = BSP_UART1_REG_BASE_ADDR;
		break;
	case BSP_UART_02 :
		pclk_freq  = BSP_SysCtrl_PerClkFreqGet(BSP_SYS_CTRL_PER_NBR_UART2);
		BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_UART2);
		BSP_GPIO_Cfg(BSP_UART2_PORT,BSP_UART2_PINS,BSP_UART2_FNCT);
		base = BSP_UART2_REG_BASE_ADDR;
		break;
	case BSP_UART_03 :
		pclk_freq  = BSP_SysCtrl_PerClkFreqGet(BSP_SYS_CTRL_PER_NBR_UART3);
		BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_UART3);
		BSP_GPIO_Cfg(BSP_UART3_PORT,BSP_UART3_PINS,BSP_UART3_FNCT);
		base = BSP_UART3_REG_BASE_ADDR;
		break;
	default :
		return ;
	}

	div = (INT16U)(((2 * pclk_freq / 16 / baud_rate) + 1) / 2);

	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxLCR,(1uL<<7));		//DLAB=1,允许设置波特率

	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxDLL,(div&0x00FF));
	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxDLM,((div>>8)&0x00FF));
	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxFDR,0x10);

//	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxDLM,0);
//	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxDLL,48);
//	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxFDR,0x9D);

	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxLCR,(3uL<<0));

	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxFCR,(1uL<<0)|(2uL<<6));	//使能FIFO,触发深度8,清空FIFO
	BSP_WRITE_REG32(base+BSP_UART_REG_OFFSET_UxIER,(1uL<<0)|(1uL<<1));	//使能接收中断，发送中断
	
	switch (uartx) {
	case BSP_UART_00 :
		BSP_IntVectSet(	(INT8U)BSP_INT_SRC_NBR_UART0,
						(INT8U)BSP_INT_PRIO_LOWEST,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)BSP_Uart0_ISR_Handler );
																				
		BSP_Queue_Create( uart_txd_queue,&uart_txd_buf[0][0],UART_TXD_BUFSIZE );
		BSP_Queue_Create( uart_rxd_queue,&uart_rxd_buf[0][0],UART_RXD_BUFSIZE );

    	BSP_IntEn(BSP_INT_SRC_NBR_UART0);
		break ; 
	case BSP_UART_01 :
		BSP_IntVectSet(	(INT8U)BSP_INT_SRC_NBR_UART0,
						(INT8U)BSP_INT_PRIO_LOWEST,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)BSP_Uart1_ISR_Handler );
																				
		BSP_Queue_Create( uart_txd_queue,&uart_txd_buf[1][0],UART_TXD_BUFSIZE );
		BSP_Queue_Create( uart_rxd_queue,&uart_rxd_buf[1][0],UART_RXD_BUFSIZE );

    	BSP_IntEn(BSP_INT_SRC_NBR_UART1);
		break ;
	case BSP_UART_02 :
		BSP_IntVectSet(	(INT8U)BSP_INT_SRC_NBR_UART0,
						(INT8U)BSP_INT_PRIO_LOWEST,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)BSP_Uart2_ISR_Handler );
																				
		BSP_Queue_Create( uart_txd_queue,&uart_txd_buf[2][0],UART_TXD_BUFSIZE );
		BSP_Queue_Create( uart_rxd_queue,&uart_rxd_buf[2][0],UART_RXD_BUFSIZE );

    	BSP_IntEn(BSP_INT_SRC_NBR_UART2);
		break ;
	case BSP_UART_03 :
		BSP_IntVectSet(	(INT8U)BSP_INT_SRC_NBR_UART0,
						(INT8U)BSP_INT_PRIO_LOWEST,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)BSP_Uart3_ISR_Handler );
																				
		BSP_Queue_Create( uart_txd_queue,&uart_txd_buf[3][0],UART_TXD_BUFSIZE );
		BSP_Queue_Create( uart_rxd_queue,&uart_rxd_buf[3][0],UART_RXD_BUFSIZE );

    	BSP_IntEn(BSP_INT_SRC_NBR_UART3);
		break ;	
	 default :
	 	return ;
	}
}

INT32U BSP_Uartx_Write ( INT32U uartx,INT32U len,INT8U *txbuf )
{
	pQUEUE ptxd_queue;
	INT32U base;
	INT32U cnt;
	INT32U i;

	if ((0==len)||(NULL==txbuf)) {
		return 0;
	}
	switch (uartx) {
	case BSP_UART_00 :
		ptxd_queue = &uart_txd_queue[0];
		base = BSP_UART0_REG_BASE_ADDR;
		break ;
	case BSP_UART_01 :
		ptxd_queue = &uart_txd_queue[1];
		base = BSP_UART1_REG_BASE_ADDR;
		break ;
	case BSP_UART_02 :
		ptxd_queue = &uart_txd_queue[2];
		base = BSP_UART2_REG_BASE_ADDR;
		break ;
	case BSP_UART_03 :
		ptxd_queue = &uart_txd_queue[3];
		base = BSP_UART3_REG_BASE_ADDR;
		break ;
	default :
		return 0;
	}
//	if (0!=BSP_Queue_Get_Data_Count(ptxd_queue)) {
//		return 0;
//	}
	while (0!=BSP_Queue_Get_Data_Count(ptxd_queue)) {
		OSTimeDly(2);
	}

	cnt = BSP_Queue_Get_Empty_Count(ptxd_queue);
	if (cnt<len) {
		return 0;
	}
	if (len>16) {
		for (i=16;i<len;i++) {
			BSP_Queue_Input( ptxd_queue,txbuf[i] );
		}
		for (i=0;i<16;i++) {
			BSP_WRITE_REG8(base+BSP_UART_REG_OFFSET_UxTHR,txbuf[i]);
		}
	} else {
		for (i=0;i<len;i++) {
			BSP_WRITE_REG8(base+BSP_UART_REG_OFFSET_UxTHR,txbuf[i]);
		}
	}
	return len;
}

INT32U BSP_Uartx_Read ( INT32U uartx,INT32U len,INT8U *rxbuf )
{
	pQUEUE prxd_queue;
	INT32U cnt;
	INT32U i;

	if ((0==len)||(NULL==rxbuf)) {
		return 0;
	}
	switch (uartx) {
	case BSP_UART_00 :
		prxd_queue = &uart_rxd_queue[0];
		break ;
	case BSP_UART_01 :
		prxd_queue = &uart_rxd_queue[1];
		break ;
	case BSP_UART_02 :
		prxd_queue = &uart_rxd_queue[2];
		break ;
	case BSP_UART_03 :
		prxd_queue = &uart_rxd_queue[3];
		break ;
	default :
		return 0 ;
	}
	cnt = BSP_Queue_Get_Data_Count(prxd_queue);
	cnt = (cnt>len) ? len : cnt;
	for (i=0;i<cnt;i++) {
		rxbuf[i] = BSP_Queue_Output(prxd_queue);
	}
	return cnt;
}

static void BSP_Uart0_ISR_Handler( void )
{
	BSP_Uartx_ISR_Handler ( BSP_UART_00 );
}

static void BSP_Uart1_ISR_Handler( void )
{
	BSP_Uartx_ISR_Handler ( BSP_UART_01 );
}

static void BSP_Uart2_ISR_Handler( void )
{
	BSP_Uartx_ISR_Handler ( BSP_UART_02 );
}

static void BSP_Uart3_ISR_Handler( void )
{
	BSP_Uartx_ISR_Handler ( BSP_UART_03 );
}

static void BSP_Uartx_ISR_Handler ( INT32U uartx )
{
	INT8U lsr;
	INT8U iir; 
	INT8U dat;
	INT32U base;
	INT32U len;
	pQUEUE ptxd_queue,prxd_queue;

	switch (uartx) {
	case BSP_UART_00 :
		base = BSP_UART0_REG_BASE_ADDR;
		ptxd_queue = &uart_txd_queue[0];
		prxd_queue = &uart_rxd_queue[0];
		break ;
	case BSP_UART_01 :
		base = BSP_UART1_REG_BASE_ADDR;
		ptxd_queue = &uart_txd_queue[1];
		prxd_queue = &uart_rxd_queue[1];
		break ;
	case BSP_UART_02 :
		base = BSP_UART2_REG_BASE_ADDR;
		ptxd_queue = &uart_txd_queue[2];
		prxd_queue = &uart_rxd_queue[2];
		break ;
	case BSP_UART_03 :
		base = BSP_UART3_REG_BASE_ADDR;
		ptxd_queue = &uart_txd_queue[3];
		prxd_queue = &uart_rxd_queue[3];
		break ;
	default :
		return ; 
	}
	BSP_READ_REG8(iir,base+BSP_UART_REG_OFFSET_UxIIR);
	iir &= 0x0F;
	while (1 != iir) {
		switch ((0x0E&iir)) {
		case 0x02:
			len = BSP_Queue_Get_Data_Count(ptxd_queue);
			len = (len>16) ? 16 : len;
			while (len>0) {
				dat = BSP_Queue_Output(ptxd_queue);
				BSP_WRITE_REG8(base+BSP_UART_REG_OFFSET_UxTHR,dat);
				len--;
			}
			break ;
		case 0x0C:
		case 0x04:
			BSP_READ_REG8( lsr,base+BSP_UART_REG_OFFSET_UxLSR );
			while(0x01==(lsr&0x01)) {
				BSP_READ_REG8( dat,base+BSP_UART_REG_OFFSET_UxRBR );
				BSP_Queue_Input( prxd_queue,dat );
				BSP_READ_REG8( lsr,base+BSP_UART_REG_OFFSET_UxLSR );
			}
			break ;
		default :
			break ;
        }
        BSP_READ_REG8(iir,base+BSP_UART_REG_OFFSET_UxIIR);
		iir &= 0x0F;
    }
}



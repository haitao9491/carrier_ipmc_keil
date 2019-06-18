#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "ucos_ii.h"


typedef struct {
	INT32U in;
	INT32U out;
	INT32U size;
	volatile INT32U cnt;
	INT32U err;
	INT8U *pbuf;	
} QUEUE,*pQUEUE;

void	BSP_Queue_Input				( pQUEUE q,INT8U dat );
INT8U	BSP_Queue_Output			( pQUEUE q );
INT32U	BSP_Queue_Get_Size			( pQUEUE q );
INT32U	BSP_Queue_Get_Data_Count	( pQUEUE q );
INT32U	BSP_Queue_Get_Empty_Count	( pQUEUE q );
void	BSP_Queue_Clear				( pQUEUE q );
void	BSP_Queue_Create			( pQUEUE q,INT8U *buf,INT32U size );

#endif



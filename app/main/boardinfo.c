/********************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:			boardinfo.c
** Last modified Date:  2019-04-08
** Last Version:		1.0
** Descriptions:		The board informations function 
**
**--------------------------------------------------------------------------------------------------------
** Created by:			Xingjingfeng
** Created date:		2019-04-08
** Version:				1.0
** Descriptions:		The original version
**
**
*********************************************************************************************************/
#include "boardinfo.h"
#include "ipmi_cpld.h"

BoardInfo g_boardinfo ;
extern INT8U Read_Hardware_Address(INT8U *ha);

void boardInfoInit(void)
{
	g_boardinfo.ipmc_mode 	= (IPMC_MODE)get_carrier_ipmc_stat();
	if(g_boardinfo.ipmc_mode != IPMC_SHMC){	
		g_boardinfo.payLoadPL	= 1;
		g_boardinfo.activation	= ACT_PowerOn;
	}
	else{
		g_boardinfo.payLoadPL	= 0;
		g_boardinfo.activation	= ACT_NONE;
	}
	g_boardinfo.desiredPL = 5;		//POWER level 200w
	Read_Hardware_Address((INT8U *)(&g_boardinfo.hwAddr));
	g_boardinfo.hwAddr 		&= 0x7f;
	g_boardinfo.ipmbAddr 	= g_boardinfo.hwAddr << 1;
	g_boardinfo.comm_ss		= COMM_LOSS;
	g_boardinfo.initTime	= 1553918291;			//initial time
	g_boardinfo.hss.PreState		= M0;
	g_boardinfo.hss.CurState		= M0;
	g_boardinfo.rtm_s.cur_state		=	RTM_S_IN_SLOT;
	g_boardinfo.rtm_s.pre_state		=	RTM_S_IN_SLOT;
	g_boardinfo.lock.Deactivation_Locked_bit 	= 1;
	g_boardinfo.lock.Locked_bit					= 0;	
}

uint8 board_name_string(char *name)
{
	uint8 ret = 0;
	switch(BOARD_TYPE){
		case BOARD_TYPE_MACB_V2:
			strcpy(name,"BOARD_TYPE_MACB_V2");
			break;
		case BOARD_TYPE_MACB_V3:
			strcpy(name,"BOARD_TYPE_MACB_V3");
			break;
		case BOARD_TYPE_MPCB_V2:
			strcpy(name,"BOARD_TYPE_MPCB_V2");
			break;
		case BOARD_TYPE_MPCB_V3:
			strcpy(name,"BOARD_TYPE_MPCB_V3");
			break;
		case BOARD_TYPE_EIPB_V2:
			strcpy(name,"BOARD_TYPE_EIPB_V2");
			break;
		case BOARD_TYPE_EIPB_V3:
			strcpy(name,"BOARD_TYPE_EIPB_V3");
			break;
		case BOARD_TYPE_XSCB_V2:
			strcpy(name,"BOARD_TYPE_XSCB_V2");
			break;	
		default:
			ret = 1;
			break;			
	}
	return ret;
}

void printBoardInfo(void)
{
	char name[32] = {0};
	board_name_string(name);
	UART0_Printf("board type :%s \n",name);
}



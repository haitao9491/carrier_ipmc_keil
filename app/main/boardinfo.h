#ifndef __BOARD_INFO_H
#define __BOARD_INFO_H

#include "config.h"
#include "ipmi_fru.h"

/* BOARD TYPE define, when you compiled one board image, you must set BOARD_TYPE */
#define BOARD_TYPE_NULL             0
#define BOARD_TYPE_MACB_V2          1
#define BOARD_TYPE_MACB_V3          2
#define BOARD_TYPE_MPCB_V2          3
#define BOARD_TYPE_MPCB_V3          4
#define BOARD_TYPE_EIPB_V2          5
#define BOARD_TYPE_EIPB_V3          6
#define BOARD_TYPE_XSCB_V2          7

#define BOARD_TYPE                  BOARD_TYPE_MACB_V3
//#define BOARD_TYPE                  BOARD_TYPE_XSCB_V2


/*board XSCB */
#if (BOARD_TYPE == BOARD_TYPE_XSCB_V2)

	#define PWR_SENSOR_NUM              				0x4
	#define TEMP_SENSOR_NUM              				0x0a

/***Board MACB V3  **/
#elif ((BOARD_TYPE == BOARD_TYPE_MACB_V3) || (BOARD_TYPE == BOARD_TYPE_MACB_V2) )

	#define PWR_SENSOR_NUM              				0x4
	#define TEMP_SENSOR_NUM              				0x02
	#define MAX_AMC_NUM									0x04

#endif

/*sdr number :include sensors record, hot swap sensor,device locator record  */
#define TH_SENSOR_NUM              				(PWR_SENSOR_NUM + TEMP_SENSOR_NUM) 
#define SDR_NUM              					(TH_SENSOR_NUM + 2) 


typedef struct{
	
}AMCInfo;

typedef enum{
	COMM_LOSS = 0,
	COMM_ON,
}IPMC_COMM_SS;


typedef struct{
	IPMC_MODE ipmc_mode;		//Ipmc mode : fru power mode,from local ipmc or from shmc,or forced
	uint8 payLoadPL;			//payload power level,default 1
	uint8 desiredPL;
	ShMC_Activation activation;	// ShMC_Activation status
	uint8 hwAddr;				//Ipmc hardware address,read from cpld
	uint8 ipmbAddr;				//ipmb address ; hwAddr << 1
	IPMC_COMM_SS comm_ss;				//i2c communication status with ipmc
	uint32 initTime;			//start running time ;in unix timestamp,1553918291,2019-03-30 11:58:11	
	Ipmc_Hot_Swap hss;			// hot swap status,M0,M1,M2
	RTM_StateCtrl rtm_s;
	Fru_Activation_Policy lock;	//hot swap locked bit info,set by ShMC or the switch handle
}BoardInfo;


void boardInfoInit(void);
void printBoardInfo(void);
#endif

/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-fru.c
** Last modified Date:  2015-06-29
** Last Version:        1.0
** Descriptions:        ATCA FRU Function
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-06-29
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
#include <stdbool.h>
#include "i2c.h"
#include "ipmi_led.h"
#include "ipmi_comm.h"
#include "ipmi_cpld.h"
#include "ipmi_defs.h"
#include "ipmi_fru.h"
#include "ipmi_sensor.h"
#include "ipmi_sdr.h"
#include "ipmi_device.h"

/* define absolute address:__no_init char array[100]@0x2000*/
//extern function

//extern variable
extern BoardInfo g_boardinfo ;
extern OS_EVENT *MBox_Blue_Led;
//AMC HW Variable
struct FRU fru[4];
/*
  FRU store
 */
#if  (BOARD_TYPE == BOARD_TYPE_MACB_V3)

//#define MULTI_RECORD_DATA_LEN	104u
#define LED_RECORD_DATA_LEN		0x34		// led record date length
#define EKEY_RECORD_DATA_LEN	0x1a		//point to point connectivity record data length

uint8 fru_info[FRU_INVENTORY_AREA_SIZE] = {
/* FRU header, length 8bytes */
	0x01, 0x00, 0x00, 0x01, 0x09, 0x13, 0x00, 0xe2,
/* Board info area, length 64bytes */
	0x01, 0x08, 0x19, 										//3 ,head 
	0xbe, 0xf4, 0xa6, 										//3, mfg.Date/Time
	0xc4, 0x52, 0x59, 0x58, 0x20,							//5,manufacture
	0xc8, 0x4d, 0x41, 0x43, 0x42, 0x33, 0x30, 0x30, 0x20, 	//9, PRODUCT name 
	0xcd, 0x30, 0x32, 0x31, 0x36, 0x31, 0x30, 0x32, 0x30,	//14,seiral number: 0216102000038
		  0x30, 0x30, 0x30, 0x33, 0x38, 
	0xcf, 0x30, 0x32, 0x31, 0x30, 0x2d, 0x30, 0x30,	0x30, 	//16, part number
		  0x30,	0x33, 0x2d, 0x30, 0x30,	0x30, 0x31,			
	0xc0, 													//1,fru file id 
	0xc8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,	//9 ,custom info		
	0xc1, 0x00, 0x00, 0x00, 								//4,fillings
/* Product info area, length 80bytes */
	0x01, 0x0a, 0x19, 										//3,
	0xc4, 0x52, 0x59, 0x58, 0x20,							//5,manufacture
	0xcf, 0x4d, 0x41, 0x43, 0x42, 0x33, 0x30, 0x30, 0x2d,	//16,product name
		  0x30 ,0x34, 0x30, 0x2d, 0x30, 0x30, 0x20, 
	0xcf, 0x30, 0x32, 0x30, 0x36, 0x2d, 0x30, 0x30, 0x30,	//16, part number
		  0x30, 0x33, 0x2d, 0x30, 0x30, 0x30, 0x35,
	0xc7, 0x52, 0x65, 0x76, 0x20, 0x31, 0x20, 0x20,			//8,Rev 1 
	0xcd, 0x30, 0x32, 0x31, 0x36, 0x31, 0x30, 0x32, 0x30,	//14,seiral number: 0216102000038
		  0x30, 0x30, 0x30, 0x33, 0x38, 
	0xc0, 													//1, asset tag
	0xc0, 													//1, fru file id 
	0xc8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,	//9 ,custom info		
	0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 				//7,fillings
/* MultiRecord info area, length 104bytes */
/*  Led Descriptions */
	0xc0, 0x02, LED_RECORD_DATA_LEN, 0x00,0x00,
	MANUFACTURER_ID1,MANUFACTURER_ID2, MANUFACTURER_ID3,0x2f, 0x00,
	0x02,													//1,blue led 
	0x00,
	0xc0,
	0xc0,
	0xcc, 0x54, 0x68, 0x65, 0x20, 0x42, 0x4c, 0x55, 0x45, 	//13,led des
	      0x20, 0x4c, 0x45, 0x44,
	0x01,													//1,led 1
	0xc8, 0x46, 0x52, 0x55, 0x5f, 0x4c, 0x45, 0x44, 0x31,  	//9,led legend 
	0xc0, 													//1,led symbol
	0xd2, 0x4f, 0x75, 0x74, 0x2d, 0x6f, 0x66, 0x2d, 0x73, 	//19,led des
		  0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x4c,
		  0x45, 0x44,		  
	/* Board Point-to-Point Connectivity Record */
	0xc0, 0x82, EKEY_RECORD_DATA_LEN, 0x00, 0x00, 
	MANUFACTURER_ID1,MANUFACTURER_ID2, MANUFACTURER_ID3,0x14, 0x00, 0x00, 
	0x41, 0x2f, 0x00, 0x00,		//fabric channel 1
	0x42, 0x2f, 0x00, 0x00,		//fabric channel 2
	0x01, 0x11, 0x00, 0x00, 	//base channel 1
	0x02, 0x11, 0x00, 0x00, 	//base channel 2
	//0x81, 0x2f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

#elif (BOARD_TYPE == BOARD_TYPE_XSCB_V2)
#define MULTI_RECORD_DATA_LEN	104u
#define LED_RECORD_DATA_LEN		0x34		// led record date length
#define EKEY_RECORD_DATA_LEN	0x1a		//point to point connectivity record data length

uint8 fru_info[FRU_INVENTORY_AREA_SIZE] = {
/* FRU header, length 8bytes */
	0x01, 0x00, 0x00, 0x01, 0x09, 0x13, 0x00, 0xe2,
/* Board info area, length 64bytes */
	0x01, 0x08, 0x19, 										//3 ,head 
	0xbe, 0xf4, 0xa6, 										//3, mfg.Date/Time
	0xc4, 0x52, 0x59, 0x58, 0x20,							//5,manufacture
	0xc8, 0x58, 0x53, 0x43, 0x42, 0x33, 0x30, 0x30, 0x20, 	//9, PRODUCT name 
	0xcd, 0x30, 0x32, 0x31, 0x36, 0x31, 0x30, 0x32, 0x30,	//14,seiral number: 0216102000038
		  0x30, 0x30, 0x30, 0x33, 0x38, 
	0xcf, 0x30, 0x32, 0x31, 0x30, 0x2d, 0x30, 0x30,	0x30, 	//16, part number
		  0x30,	0x33, 0x2d, 0x30, 0x30,	0x30, 0x31,			
	0xc0, 													//1,fru file id 
	0xd8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,	//9 ,custom info		
	0xc1, 0x00, 0x00, 0x00, 								//4,fillings
/* Product info area, length 80bytes */
	0x01, 0x0a, 0x19, 										//3,
	0xc4, 0x52, 0x59, 0x58, 0x20,							//5,manufacture
	0xcf, 0x58, 0x53, 0x43, 0x42, 0x33, 0x30, 0x30, 0x2d,	//16,product name
		  0x30 ,0x34, 0x30, 0x2d, 0x30, 0x30, 0x20, 
	0xcf, 0x30, 0x32, 0x30, 0x36, 0x2d, 0x30, 0x30, 0x30,	//16, part number
		  0x30, 0x33, 0x2d, 0x30, 0x30, 0x30, 0x35,
	0xc7, 0x52, 0x65, 0x76, 0x20, 0x31, 0x20, 0x20,			//8,Rev 1 
	0xcd, 0x30, 0x32, 0x31, 0x36, 0x31, 0x30, 0x32, 0x30,	//14,seiral number: 0216102000038
		  0x30, 0x30, 0x30, 0x33, 0x38, 
	0xc0, 													//1, asset tag
	0xc0, 													//1, fru file id 
	0xd8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,	//9 ,custom info		
	0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 				//7,fillings
/* MultiRecord info area, length 104bytes */
/*  Led Descriptions */
	0xc0, 0x02, LED_RECORD_DATA_LEN, 0x00,0x00,
	MANUFACTURER_ID1,MANUFACTURER_ID2, MANUFACTURER_ID3,0x2f, 0x00,
	0x02,													//1,blue led 
	0x00,
	0xc0,
	0xc0,
	0xcc, 0x54, 0x68, 0x65, 0x20, 0x42, 0x4c, 0x55, 0x45, 	//13,led des
	      0x20, 0x4c, 0x45, 0x44,
	0x01,													//1,led 1
	0xc8, 0x46, 0x52, 0x55, 0x5f, 0x4c, 0x45, 0x44, 0x31,  	//9,led legend 
	0xc0, 													//1,led symbol
	0xd2, 0x4f, 0x75, 0x74, 0x2d, 0x6f, 0x66, 0x2d, 0x73, 	//19,led des
		  0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x4c,
		  0x45, 0x44,		  
	/* Board Point-to-Point Connectivity Record */
	0xc0, 0x82, EKEY_RECORD_DATA_LEN, 0x00, 0x00, 
	MANUFACTURER_ID1,MANUFACTURER_ID2, MANUFACTURER_ID3,0x14, 0x00, 0x00, 
	0x41, 0x2f, 0x00, 0x00,		//fabric channel 1
	0x42, 0x2f, 0x00, 0x00,		//fabric channel 2
	0x01, 0x11, 0x00, 0x00, 	//base channel 1
	0x02, 0x11, 0x00, 0x00, 	//base channel 2
	0x81, 0x2f, 0x00, 0x00,
};

#endif

//Carrier HW Variable --at last will be a struct
//Ipmc_Hot_Swap ipmc_hs_ptr;
//Fru_Activation_Policy fru_act_pol;
struct FRU Carrier_Fru;
uint8   HS_Current;
//uint8   Comm_flag;
//uint8   Activate_flag;/*0--init status;1--activate;2--activate complete;
//                       3--Deactivate;4--Deactivate complete*/
//uint8   Power_level;

uint8 get_amc_power_prestat(uint8 fru_id)
{
    uint8 ucRet = AMC_POWER_STAT_DOWN;

    if (fru[fru_id].AMC_Power_stat)
    {
        ucRet = AMC_POWER_STAT_UP;
    }

    return ucRet;
}


void Set_AMC_Event_Receiver(INT8U fru_id,INT8U state)
{
	I2c_MemCopy_Entry I2c_ptr;
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[2];
	uint8 payloadlen;
	uint8 i2cId;

    rsAddr = fru[fru_id].ipmb_addr;
    NetFn = IPMI_NETFN_SENSOR_EVENT_RQ;
    reqAddr = 0x20;
    Cmd = IPMI_SENSOR_EVENT_CMD_SET_EVENT_RECEIVER;
    switch(state){
        case EVENT_RCE_ON:
            payload[0] = 0x20;
            payload[1] = 0x00;
        break;
        case EVENT_RCE_OFF:
            payload[0] = 0xff;
            payload[1] = 0x00;
        break;
        default:break;
    }
    payloadlen = 2;
    i2cId = 2;
    IPMI_Comm_Construct_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                            Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(&I2c_ptr);
}

void Set_ShMC_Event_Receiver(INT8U state)
{
	I2c_MemCopy_Entry I2c_ptr;
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[2];
	uint8 payloadlen;
	uint8 i2cId;

    rsAddr = 0x20;
    NetFn = IPMI_NETFN_SENSOR_EVENT_RQ;
    reqAddr = g_boardinfo.ipmbAddr;
    Cmd = IPMI_SENSOR_EVENT_CMD_SET_EVENT_RECEIVER;
    switch(state){
        case EVENT_RCE_ON:
            payload[0] = 0x20;
            payload[1] = 0x00;
        break;
        case EVENT_RCE_OFF:
            payload[0] = 0xff;
            payload[1] = 0x00;
        break;
        default:break;
    }
    payloadlen = 2;
    i2cId = 2;
    IPMI_Comm_Construct_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                            Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(&I2c_ptr);
}
void Fru_Hot_Swap_Event(uint8 fru_id,uint8 prestat,uint8 curstat)
{
	I2c_MemCopy_Entry I2c_ptr;
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[7];
	uint8 payloadlen;
	uint8 i2cId;

    rsAddr = 0x20;
    NetFn = IPMI_NETFN_SENSOR_EVENT_RQ;
    reqAddr = g_boardinfo.ipmbAddr;
    reqSeq = 0x00;
    Cmd = IPMI_SENSOR_EVENT_CMD_PLATFORM_EVENT;
    payload[0] = 0x04;
    payload[1] = 0xf0;
    payload[2] = SENSOR_NUMBER_HANDLE_SWITCH;
    payload[3] = 0x6f;
    payload[4] = 0xa0 | curstat;
    payload[5] = 0x00 | prestat;
    payload[6] = fru_id;

    payloadlen = 7;
    i2cId = 1;
    IPMI_Comm_Construct_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                                Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(&I2c_ptr);
    UART0_Printf("IPMI_Carrier_HW:FRU%d: M%d->M%d \n",fru_id,prestat,curstat);
    OSTimeDlyHMSM(0, 0, 0, 100);
    UART0_Printf("%d-%d-%d-%d-%d-%d-%d-%d\n",M0,M1,M2,M3,M4,M5,M6,M7);
}



/*********************************************************************************************************
** Function name:           checksum
**
** Descriptions:            FRU Store zero checksum
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
INT8U Zero_checksum(INT8U *buf, INT8U len)
{
	INT8U sum = 0;

	for(; len > 0; len--)
	{
		sum += *buf++;
	}
	sum = ~sum + 1;

	return sum;
}
/*********************************************************************************************************
** Function name:           Ipmi_inin_fru_store
**
** Descriptions:            initial fru store data
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_inin_fru_store(void)
{
    uint8 record_checksum,head_checksum;
/* Board area checksum */
    record_checksum = Zero_checksum(&fru_info[FRU_BOARD_AREA_OFFSET],FRU_BOARD_AREA_SIZE);
    fru_info[FRU_PRODUCT_AREA_OFFSET-1] = record_checksum;
/* Product area checksum */
    record_checksum = Zero_checksum(&fru_info[FRU_PRODUCT_AREA_OFFSET],FRU_PRODUCT_AREA_SIZE);
    fru_info[FRU_MULTI_AREA_OFFSET-1] = record_checksum;
	/* multi area:led record area checksum */
    record_checksum = Zero_checksum(&fru_info[FRU_MULTI_AREA_OFFSET+5],LED_RECORD_DATA_LEN);
    fru_info[FRU_MULTI_AREA_OFFSET+3] = record_checksum;
    head_checksum = Zero_checksum(&fru_info[FRU_MULTI_AREA_OFFSET],4);
    fru_info[FRU_MULTI_AREA_OFFSET+4] = head_checksum;
	
	/* multi area:e key record area checksum */
	record_checksum = Zero_checksum(&fru_info[FRU_EKEY_AREA_OFFSET+5],EKEY_RECORD_DATA_LEN);
    fru_info[FRU_EKEY_AREA_OFFSET+3] = record_checksum;
    head_checksum = Zero_checksum(&fru_info[FRU_EKEY_AREA_OFFSET],4);
    fru_info[FRU_EKEY_AREA_OFFSET+4] = head_checksum;
}

/*********************************************************************************************************
** Function name:           IPMI_Monitor_AMC_State
**
** Descriptions:            
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
#if 0
    uint32  amc_led_counter = 0;
for(i=0;i<AMC_NUM;i++){
						if(( AMC_SLOT_IN == get_amc_slot_stat(i))
						    &&(!(amc_led_counter % 500))){
                            if(get_amc_power_prestat(i) == AMC_POWER_STAT_UP)
                                Set_AMC_Blue_Led(i, LONG_BLINK);
                            else 
                                Set_AMC_Blue_Led(i, LED_ON);
						}
						amc_led_counter++;
						if (amc_led_counter == 0xfffffffc)
						    amc_led_counter = 0;
				    }
#endif 
void IPMI_Monitor_AMC_State(void)
{
	static uint8 hs_pre = 0;
	uint8 i = 0;
	uint8 hs_current = IPMI_CPLD_AMC_ONLINE & 0xf0;
	uint8 hs_check = 0;
	
	/* AMC num changes */
	hs_check = hs_pre ^ hs_current;
	for(i = 0;i < MAX_AMC_NUM;i ++){
		if(!(hs_check & (IPMI_CPLD_AMC0_ONLINE << i)))		//no change
			continue;
		if(hs_current & (IPMI_CPLD_AMC0_ONLINE << i)){		//insert 
			UART0_Printf("New AMC IN:0x%02x\n",i);
			if (AMC_POWER_STAT_UP == get_AMC_power_stat(i)){
				fru[i].HS_Status = 0x01;
				fru[i].AMC_Power_stat = 1;
				UART0_SendStr("New AMC Power Up\n");
			}
			else{
				fru[i].HS_Status = 0xCC;
				fru[i].AMC_Power_stat = 0;
				UART0_SendStr("New AMC Power Down\n");
			}
		}
	}
	hs_pre = hs_current;

/* AMC power changes */
	for(i = 0;i < MAX_AMC_NUM;i ++){
		if(!(hs_current & (IPMI_CPLD_AMC0_ONLINE << i)))		//not in slot
			continue;
		if (get_amc_power_prestat(i) != get_AMC_power_stat(i)){
            if (AMC_POWER_STAT_UP == get_amc_power_prestat(i)){
                UART0_Printf("AMC[%d] POWER Down!\n",i);
                fru[i].HS_Status = 0xFF;
            }
            else{
                fru[i].HS_Status = 0x01;
                UART0_Printf("AMC[%d] POWER Up!\n",i);
            }
            fru[i].AMC_Power_stat = get_AMC_power_stat(i);
        }
	}
	/***** need more operations****************/
	/**           led operations            **/
}


void IPMI_Deal_AMC_Step(void)
{
    uint8 fru_id;

    for(fru_id=0;fru_id<AMC_NUM;fru_id++){
        switch(fru[fru_id].HS_Status){
/* New AMC inserted,set AMC event receiver enable */
            case 1:
                Set_AMC_Event_Receiver(fru_id,EVENT_RCE_ON);
                fru[fru_id].HS_Status++;
                Fru_Hot_Swap_Event(fru_id+1,M0,M1);
                OSTimeDlyHMSM(0, 0, 1, 0);
                break;
/* Set blue led long blink,present prepare to active the new AMC */
            case 2:
                Set_AMC_Blue_Led(fru_id,LONG_BLINK);
                fru[fru_id].HS_Status = 10;
                break;
            default: break;
        }
    }
}
#endif
/*********************************************************************************************************
** Function name:           AMC_HW_Task
**
** Descriptions:			Monitor AMC cards status and control them
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
void AMC_HW_Task(void *pdata)
{
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
	uint8 i = 0;
	IPMI_CPLD_AMC_PAYLOAD_POWER_STATE = IPMI_CPLD_ALL_AMC_PAYLOAD_POWER_OFF;
/* Initial AMC variables */
    for(i=0;i<4;i++){
        fru[i].HS_Status = 0x00;
        fru[i].ipmb_addr = 0x00;
        fru[i].AMC_Power_stat = 0;
    }
	while(1){
		IPMI_Monitor_AMC_State();
		IPMI_Deal_AMC_Step();
		OSTimeDlyHMSM(0, 0, 0, 200);
	}
#endif
	exit(0);
}

/*********************************************************************************************************
** Function name:           RTM_HW_Task
**
** Descriptions:			rtm card state control
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
void RTM_HW_Task(void *pdata)
{
	uint8 state = 0;
	while(1){
		OSTimeDlyHMSM(0, 0, 0, 200);
		if(!RTM_in_slot()){	//rtm card not in slot
			state = 0;
			continue;
		}
		if(CARRIER_HS_STAT_OPEN == get_carrier_rtm_hs_stat()){	//handle open
			if(state == 1)
				continue;
			set_RTM_power_off();
			Set_RTM_Blue_Led(LED_ON);
			Set_RTM_Other_Led(LED_OSS_RED,LED_OK_RED);
			state = 1;
			continue;
		}
		if(!get_Payload_power_state()){		//payload not powered up
			if(state == 2)
				continue;
			set_RTM_power_off();
			Set_RTM_Blue_Led(LONG_BLINK);
			Set_RTM_Other_Led(LED_OSS_RED,LED_OK_RED);
			state = 2;
			continue;
		}
		if(state == 3)
			continue;
		else{
			set_RTM_power_on();
			Set_RTM_Blue_Led(LED_OFF);
			Set_RTM_Other_Led(LED_OSS_OFF,LED_OK_GREEN);
			state = 3;
		}		
	}	
}

//		if(!RTM_in_slot())	//rtm card not in slot
//			g_boardinfo.rtm_s.cur_state = RTM_S_IN_SLOT;
//		switch(g_boardinfo.rtm_s.cur_state)
//		{
//			case RTM_S_IN_SLOT:
//				if(!RTM_in_slot())	//rtm card not in slot
//					break;
//				Set_RTM_Blue_Led(LED_ON);
//				if(CARRIER_HS_STAT_OPEN == get_carrier_rtm_hs_stat())	//handle open
//					g_boardinfo.rtm_s.cur_state = RTM_S_HANDLE_OPEN;
//				else
//					g_boardinfo.rtm_s.cur_state = RTM_S_HANDLE_CLOSE;
//				g_boardinfo.rtm_s.pre_state = RTM_S_IN_SLOT;
//				break;
//			case RTM_S_HANDLE_OPEN:				
//				if(CARRIER_HS_STAT_OPEN == get_carrier_rtm_hs_stat())	//handle open
//				{
//					if(g_boardinfo.rtm_s.pre_state == RTM_S_IN_SLOT)
//					{
//						set_RTM_power_off();
//						Set_RTM_Blue_Led(LONG_BLINK);
//					}
//					continue;
//				}
//				break;
//			case RTM_S_HANDLE_CLOSE:
//				break;
//			case RTM_S_POWER_ON:
//				break;
//			default:
//				break;
//		}			
/*********************************************************************************************************
** Function name:           IPMI_Carrier_HW_Local_Run
**
** Descriptions:			Carrier Power State Machine controlled  by local ipmc
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
void IPMI_Carrier_HW_Local_Run(void )
{
    UART0_SendStr("IPMI_Carrier_HW: Task create! local\n");
    while(1) {
        switch(g_boardinfo.hss.CurState) {
            case M0:
                g_boardinfo.hss.CurState = M1;
                break;
            case M1:
                Set_FRT_Blue_Led(LED_ON);
                Set_FRT_Other_Led(LED_OSS_OFF,LED_OK_GREEN);
                if(CARRIER_HS_STAT_CLOSE == get_carrier_frt_hs_stat()){
					g_boardinfo.hss.PreState = M1;
					g_boardinfo.hss.CurState = M2;
                }
                break;
            case M2:
                if(CARRIER_HS_STAT_CLOSE ==get_carrier_frt_hs_stat()){
                    Set_FRT_Blue_Led(LONG_BLINK);
                    if(g_boardinfo.hss.PreState == M1){
                        g_boardinfo.hss.PreState = M2;
                    }
                    g_boardinfo.hss.CurState = M3;
                }
                else{
                    g_boardinfo.hss.PreState = M2;
                    g_boardinfo.hss.CurState = M1;
                }
                break;
            case M3:
                if(CARRIER_HS_STAT_CLOSE == get_carrier_frt_hs_stat()){
                    Set_FRT_Blue_Led(LED_OFF);
                    g_boardinfo.hss.PreState = M3;
					g_boardinfo.hss.CurState = M4;
                }
				//switch handle open,extraction Criteria met ,jump to M6
                else{			
					g_boardinfo.hss.PreState = M3;
                    g_boardinfo.hss.CurState = M6;
                }
                break;
            case M4:
				if(g_boardinfo.hss.PreState != M4){
					Set_FRT_Blue_Led(LED_OFF);
					set_Payload_power_on();
					e_key_open();
				}
				if((g_boardinfo.hss.PreState == M3) || (g_boardinfo.hss.PreState == M5)){
					g_boardinfo.hss.PreState = M4;
				}
				/* M4->M5 Criteria: Deactivation-Locked bit is cleared.such as:1/Handle Switch opend;
                    2/ShMC "Set FRU Activation Policy (Deactivation-Locked = 0) */
                if(CARRIER_HS_STAT_OPEN == get_carrier_frt_hs_stat()){
					g_boardinfo.hss.PreState = M4;
					g_boardinfo.hss.CurState = M5;
					break;
				}

                break;
            case M5:
                Set_FRT_Blue_Led(SHORT_BLINK);
				if(g_boardinfo.hss.PreState == M4){
					g_boardinfo.hss.PreState = M5;
				}
                if(CARRIER_HS_STAT_CLOSE ==get_carrier_frt_hs_stat()){
                    g_boardinfo.hss.PreState = M5;
                    g_boardinfo.hss.CurState = M4;
                }
				else
				{
					g_boardinfo.hss.PreState = M5;
                    g_boardinfo.hss.CurState = M6;
				}
                break;
            case M6:
/* M6->M1 Criteria: completion of the deactivation process */
                Set_FRT_Blue_Led(SHORT_BLINK);
                if(g_boardinfo.hss.PreState != M6){
                    g_boardinfo.hss.PreState = M6;
                    g_boardinfo.hss.CurState = M1;
                }
/* deactivation process */
/* power down the Payload power */
				set_Payload_power_off();
				set_RTM_power_off();
/* disable all Ports */
				e_key_off();
                break;
            default:
                UART0_Printf("Hot Swap State:No %d state\n",g_boardinfo.hss.CurState);
                break;
        }
        OSTimeDlyHMSM(0, 0, 0, 200);
    }
}

/*********************************************************************************************************
** Function name:           IPMI_Carrier_HW_Run
**
** Descriptions:			Carrier Power State Machine controlled  by ShMC
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
void IPMI_Carrier_HW_Run(void)
{
    uint8 hs_opend = 0,hs_closed = 0;

/* Initial Store Data */
    IPMI_inin_fru_store();
    UART0_SendStr("IPMI_Carrier_HW: Task create!\n");
    while(1) {
        switch(g_boardinfo.hss.CurState) {
            case M0:
                g_boardinfo.hss.CurState = M1;
                break;
            case M1:
                Set_FRT_Blue_Led(LED_ON);
                Set_FRT_Other_Led(LED_OSS_OFF,LED_OK_GREEN);
                if((g_boardinfo.hss.PreState == M6)||(g_boardinfo.hss.PreState == M2)){
					Fru_Hot_Swap_Event(0,g_boardinfo.hss.PreState,M1);
                    g_boardinfo.hss.PreState = M1;
                }
                if(CARRIER_HS_STAT_CLOSE == get_carrier_frt_hs_stat()){
/* M1->M2 Criteria: the Locked bit shall be 0b.
                    Handle switch shall be closed. */
					if(hs_opend){
						hs_opend = 0;
						g_boardinfo.lock.Locked_bit = 0;
					}
                    if(g_boardinfo.hss.PreState == M0){
						Fru_Hot_Swap_Event(0,M0,M1);
                        g_boardinfo.hss.PreState = M1;
                    }
                    if(!g_boardinfo.lock.Locked_bit){
                        g_boardinfo.hss.PreState = M1;
                        g_boardinfo.hss.CurState = M2;
                    }
                }
                else{
/* M1 state and handle switch opend */
					hs_opend = 1;					
                }
                break;
            case M2:
                if(CARRIER_HS_STAT_CLOSE ==get_carrier_frt_hs_stat()){
                    Set_FRT_Blue_Led(LONG_BLINK);
                    if(g_boardinfo.hss.PreState == M1){
						Fru_Hot_Swap_Event(0,M1,M2);
                        g_boardinfo.hss.PreState = M2;
                    }
/* M1->M2 Criteria: receipt of a "Set FRU Activation (Activate FRU)" command */
                    if(ACT_Activate == g_boardinfo.activation){
                        g_boardinfo.hss.PreState = M2;
                        g_boardinfo.hss.CurState = M3;
                    }
                    else if(ACT_Deactivate == g_boardinfo.activation){
/* M2->M1 Criteria: receipt of a "Set FRU Activation(Deactivate FRU)" command
                   or if an extraction is requested by an operator. */
                        g_boardinfo.hss.PreState = M2;
                        g_boardinfo.hss.CurState = M1;
                    }
                }
                else{
                    g_boardinfo.hss.PreState = M2;
                    g_boardinfo.hss.CurState = M1;
                }
                break;
            case M3:
                if(CARRIER_HS_STAT_CLOSE == get_carrier_frt_hs_stat()){
                    Set_FRT_Blue_Led(LED_OFF);
                    if(g_boardinfo.hss.PreState == M2){
						Fru_Hot_Swap_Event(0,M2,M3);
                        g_boardinfo.hss.PreState = M3;
                    }
/* M3->M6 Criteria: receipt of a "Set FRU Activation(Deactivate FRU)" command. */
                    if(3 == g_boardinfo.activation){
                        g_boardinfo.hss.PreState = M3;
                        g_boardinfo.hss.CurState = M6;
                    }
/* M3->M4 Criteria: after being granted its power budget
                    completing its activation process. */
                    if(2 == g_boardinfo.activation){
                        g_boardinfo.hss.PreState = M3;
                        g_boardinfo.hss.CurState = M4;
                    }
                }
				//switch handle open,extraction Criteria met ,jump to M6
                else{			
					g_boardinfo.hss.PreState = M3;
                    g_boardinfo.hss.CurState = M6;
                }
                break;
            case M4:
				Set_FRT_Blue_Led(LED_OFF);
				if((g_boardinfo.hss.PreState == M3) || (g_boardinfo.hss.PreState == M5)){
					Fru_Hot_Swap_Event(0,g_boardinfo.hss.PreState,M4);
					g_boardinfo.hss.PreState = M4;
				}
				/* M4->M5 Criteria: Deactivation-Locked bit is cleared.such as:1/Handle Switch opend;
                    2/ShMC "Set FRU Activation Policy (Deactivation-Locked = 0) */
				if(!g_boardinfo.lock.Deactivation_Locked_bit){
					g_boardinfo.hss.PreState = M4;
					g_boardinfo.hss.CurState = M5;
					break;
                }
                if(CARRIER_HS_STAT_CLOSE == get_carrier_frt_hs_stat()){
					hs_closed = 1;
				}
                if(CARRIER_HS_STAT_OPEN == get_carrier_frt_hs_stat()){
					if(hs_closed){
						hs_closed = 0;
						g_boardinfo.lock.Deactivation_Locked_bit = 0;
						break;
					}
				}

/* M4->M6 Criteria: 1--receipt of a "Set FRU Activation(Deactivate FRU)" command.
                    2--receipt of a "Set Power Level (Power Level = 0)" command */
				if((ACT_Deactivate == g_boardinfo.activation)||(0 == g_boardinfo.payLoadPL)){
					g_boardinfo.hss.PreState = M4;
					g_boardinfo.hss.CurState = M6;
				}
                break;
            case M5:
                Set_FRT_Blue_Led(SHORT_BLINK);
                    if(g_boardinfo.hss.PreState == M4){
						Fru_Hot_Swap_Event(0,M4,M5);
                        g_boardinfo.hss.PreState = M5;
                    }
/* M5->M4 Criteria: 1--receipt of a "Set FRU Activation(activate FRU)" command.
                    2--transition from M5 to M4 and set the Deactivation-Locked bit
                    when Insertion Criteria Met occurs.*/
                if(ACT_Activate == g_boardinfo.activation){
                    g_boardinfo.hss.PreState = M5;
                    g_boardinfo.hss.CurState = M4;
                }
//                if((!g_boardinfo.lock.Locked_bit)&&(CARRIER_HS_STAT_CLOSE ==get_carrier_frt_hs_stat())){
//                    g_boardinfo.lock.Deactivation_Locked_bit = 1;
//                    g_boardinfo.hss.PreState = M5;
//                    g_boardinfo.hss.CurState = M4;
//                }
/* M5->M6 Criteria: 1--receipt of a "Set FRU Activation(Deactivate FRU)" command.
                    2--receipt of a "Set Power Level (Power Level = 0)" command */
                if((ACT_Deactivate == g_boardinfo.activation)||(0 == g_boardinfo.payLoadPL)){
                    g_boardinfo.hss.PreState = M5;
                    g_boardinfo.hss.CurState = M6;
                }
                break;
            case M6:
/* M6->M1 Criteria: completion of the deactivation process */
                Set_FRT_Blue_Led(SHORT_BLINK);
                if(g_boardinfo.hss.PreState != M6){
					Fru_Hot_Swap_Event(0,g_boardinfo.hss.PreState,M6);
                    g_boardinfo.hss.PreState = M6;
                    g_boardinfo.hss.CurState = M1;
					g_boardinfo.activation = ACT_NONE;
					hs_opend = 0;
					hs_closed = 0;
                }
/* deactivation process */
/* power down the Payload power */
                set_Payload_power_off();
				set_RTM_power_off();
/* disable all Ports */
				e_key_off();
                break;
            default:
                UART0_Printf("Hot Swap State:No %d state\n",g_boardinfo.hss.CurState);
                break;
        }
        OSTimeDlyHMSM(0, 0, 0, 200);
    }
}


void IPMI_Carrier_HW_Task(void *pdata)
{
	if(g_boardinfo.ipmc_mode == IPMC_SHMC)
		IPMI_Carrier_HW_Run();
	else if(g_boardinfo.ipmc_mode == IPMC_LOCAL)
		IPMI_Carrier_HW_Local_Run();
	//other modes ,task exit
	else
		exit(0);
}


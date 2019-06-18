/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-led.c
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
#include "i2c.h"
#include "ipmi_comm.h"
#include "ipmi_fru.h"
#include "ipmi_defs.h"
#include "ipmi_cpld.h"
#include "ipmi_led.h"

extern void UART0_SendStr(char *s);
extern struct FRU fru[4];
OS_EVENT *MBox_Blue_Led;

/*********************************************************************************************************
** Function name:       Set_FRT_Other_Led
** Descriptions:        according to FRU hot swap status set front board other led
** input parameters:    oss_state ok_state
** output parameters:   none
** Returned value:      none
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Set_FRT_Other_Led(INT8U oss_state,INT8U ok_state)
{
    switch(oss_state){
        case LED_OSS_ON:
			frt_oos_led_on();
            break;
        case LED_OSS_RED:
			frt_oos_led_red();
            break;
        case LED_OSS_GREEN:
			frt_oos_led_green();
            break;
        case LED_OSS_OFF:
			frt_oos_led_off();
            break;
        default:break;
    }
    switch(ok_state){
        case LED_OK_ON:
			frt_ok_led_on();
            break;
        case LED_OK_RED:
			frt_ok_led_red();
            break;
        case LED_OK_GREEN:
			frt_ok_led_green();
            break;
        case LED_OK_OFF:
			frt_ok_led_off();
            break;
        default:break;
    }
}
/*********************************************************************************************************
** Function name:       Set_RTM_Other_Led
** Descriptions:        according to FRU hot swap status set rtm board other led
** input parameters:    oss_state ok_state
** output parameters:   none
** Returned value:      none
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void Set_RTM_Other_Led(INT8U oss_state,INT8U ok_state)
{
    switch(oss_state){
        case LED_OSS_ON:
			rtm_oos_led_on();
            break;
        case LED_OSS_RED:
			rtm_oos_led_red();
            break;
        case LED_OSS_GREEN:
			rtm_oos_led_green();
            break;
        case LED_OSS_OFF:
			rtm_oos_led_off();
            break;
        default:break;
    }
    switch(ok_state){
        case LED_OK_ON:
			rtm_ok_led_on();
            break;
        case LED_OK_RED:
			rtm_ok_led_red();
            break;
        case LED_OK_GREEN:
			rtm_ok_led_green();
            break;
        case LED_OK_OFF:
			rtm_ok_led_off();
            break;
        default:break;
    }
}

/*********************************************************************************************************
** Function name:       Set_AMC_Blue_Led
** Descriptions:        Set AMC Blue Led On/Off/Blink
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void Set_AMC_Blue_Led(INT8U fru_id,INT8U state)
{
	I2c_MemCopy_Entry I2c_ptr;
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[6];
	uint8 payloadlen;
	uint8 i2cId;

    rsAddr = fru[fru_id].ipmb_addr;
    NetFn = IPMI_NETFN_PICMG_RQ;
    reqAddr = 0x20;
    Cmd = IPMI_PICMG_CMD_SET_FRU_LED_STATE;
    payload[0] = 0;
    payload[1] = 0;
    payload[2] = 0;

    switch(state){
        case LONG_BLINK:
            payload[3] = 0x0a;
            payload[4] = 0x5a;
            payload[5] = 0x01;
            break;
        case SHORT_BLINK:
            payload[3] = 0x3a;
            payload[4] = 0x0a;
            payload[5] = 0x01;
            break;
        case LED_ON:
            payload[3] = 0xFF;
            payload[4] = 0x00;
            payload[5] = 0x01;
            break;
        case LED_OFF:
            payload[3] = 0;
            payload[4] = 0;
            payload[5] = 0x01;
            break;
        default:break;
    }
    payloadlen = 6;

    i2cId = 2;
    IPMI_Comm_Construct_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                            Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(&I2c_ptr);
}

/*********************************************************************************************************
** Function name:       Set_FRT_Blue_Led
** Descriptions:        Set Carrier Blue Led On/Off/Blink
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void Set_FRT_Blue_Led(INT8U state)
{
    switch(state){
        case LED_ON:
			frt_blue_led_on();
            break;
        case SHORT_BLINK:
			frt_blue_led_sblink();
            break;
        case LONG_BLINK:
			frt_blue_led_lblink();
            break;
        case LED_OFF:
			frt_blue_led_off();
            break;
        default:break;
    }
}

/*********************************************************************************************************
** Function name:       Set_FRT_Blue_Led
** Descriptions:        Set Carrier Blue Led On/Off/Blink
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void Set_RTM_Blue_Led(INT8U state)
{
    switch(state){
        case LED_ON:
			rtm_blue_led_on();
            break;
        case SHORT_BLINK:
			rtm_blue_led_sblink();
            break;
        case LONG_BLINK:
			rtm_blue_led_lblink();
            break;
        case LED_OFF:
			rtm_blue_led_off();
            break;
        default:break;
    }
}



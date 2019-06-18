/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_cpld.c
** Last modified Date:  2019-03-18
** Last Version:        1.0
** Descriptions:        cpld related operations
**--------------------------------------------------------------------------------------------------------
** Created by:          xingjingfeng
** Created date:        2019-03-18
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

#include "config.h" 
#include <stdbool.h>
#include "ipmi_cpld.h"
#include "ipmi_fru.h"

uint8 get_carrier_ipmc_stat(void)
{
    uint8 ucRet = CARRIER_POWER_STAT_OFF;
#if(BOARD_TYPE == BOARD_TYPE_XSCB_V2)	
#if 0
	uint8 tmp1;
    tmp1 = IPMI_CPLD_PAYLOAD_POWER_CTL & 0xc0;
    UART0_Printf("CARRIER_PAYLOAD_POWER_STATE:0x%02x\n", IPMI_CPLD_PAYLOAD_POWER_CTL);
    if(tmp1 == IPMI_CPLD_PAYLOAD_POWER_FORCE_ON)
        ucRet = IPMC_FORCED;
    else if(tmp1 == IPMI_CPLD_PAYLOAD_POWER_ShMC)
        ucRet = IPMC_SHMC;
	else if(tmp1 == IPMI_CPLD_PAYLOAD_POWER_IPMC_LOCAL)
        ucRet = IPMC_LOCAL;
    else
        ucRet = IPMC_NULL;
#endif
	ucRet = IPMC_SHMC;
#else			//for test,always IPMC_SHMC.this part needs to be completed***********************
	ucRet = IPMC_SHMC;
#endif

    return ucRet;
}


uint8 get_carrier_frt_hs_stat(void)
{
    uint8 tmp1=0;
    uint8 ucRet = CARRIER_HS_STAT_OPEN;

    tmp1 = IPMI_CPLD_FRT_PNL_CTL&IPMI_CPLD_HS_DOWN;
    if(!tmp1)
        ucRet = CARRIER_HS_STAT_CLOSE;
    else
        ucRet = CARRIER_HS_STAT_OPEN;

    return ucRet;
}

uint8 get_carrier_rtm_hs_stat(void)
{
    uint8 tmp1=0;
    uint8 ucRet = CARRIER_HS_STAT_OPEN;

    tmp1 = IPMI_CPLD_RTM_PNL_CTL&IPMI_CPLD_HS_DOWN;
    if(!tmp1)
        ucRet = CARRIER_HS_STAT_CLOSE;
    else
        ucRet = CARRIER_HS_STAT_OPEN;

    return ucRet;
}

/*enable front handle interrupt*/
inline void frt_HS_int_enbale(void)
{
	IPMI_CPLD_INT_CTL_REG |= IMPI_CPLD_FRT_HANDLE_INT_ENABLE;
}	

/*enable rear handle interrupt*/
inline void rtm_HS_int_enbale(void)
{
	IPMI_CPLD_INT_CTL_REG |= IMPI_CPLD_RTM_HANDLE_INT_ENABLE;
}	

/*enable sensor handle interrupt*/
inline void temp_sensor_int_enbale(void)
{
	IPMI_CPLD_INT_CTL_REG |= IMPI_CPLD_TEMP_SENSOR_INT_ENABLE;
}

/* 
get front handle switch interrupt status;
return value : 1,interrupt happened;0,no interrupt;
*/
bool get_frt_handle_int_stat(void)
{
	uint8 status = IPMI_CPLD_INT_STAT_REG & IMPI_CPLD_FRT_HANDLE_INT_STAT;
	if(status)
		return true;
	else
		return false;
}

/* 
get rear handle switch interrupt status;
return value : 1,interrupt happened;0,no interrupt;
*/
bool get_rtm_handle_int_stat(void)
{
	uint8 status = IPMI_CPLD_INT_STAT_REG & IMPI_CPLD_RTM_HANDLE_INT_STAT;
	if(status)
		return true;
	else
		return false;
}

/* 
get temperature sensor interrupt status;
return value : 1,interrupt happened;0,no interrupt;
*/
bool get_temp_sensor_int_stat(void)
{
	uint8 status = IPMI_CPLD_INT_STAT_REG & IMPI_CPLD_TEMP_SENSOR_INT_STAT;
	if(status)
		return true;
	else
		return false;
}

bool RTM_in_slot(void)
{
	if(IPMI_CPLD_CARD_ONLINE & IPMI_CPLD_RTM_ONLINE)	//in
		return true;
	else		//not in slot
		return false;
}

/* get the RTM power state*/
bool get_RTM_power_state(void)
{
#if(BOARD_TYPE == BOARD_TYPE_XSCB_V2)
	if(IPMI_CPLD_PAYLOAD_POWER_CTL & IPMI_CPLD_RTM_POWER_ON)	//power on
		return true;
	else		//power off
		return false;
#endif
	return false;
}


/*power on the RTM */
inline void set_RTM_power_on(void)
{
#if(BOARD_TYPE == BOARD_TYPE_XSCB_V2)
	IPMI_CPLD_PAYLOAD_POWER_CTL |= IPMI_CPLD_RTM_POWER_ON;
#endif
}

/*power off the RTM */
inline void set_RTM_power_off(void)
{
#if(BOARD_TYPE == BOARD_TYPE_XSCB_V2)
	IPMI_CPLD_PAYLOAD_POWER_CTL &= ~IPMI_CPLD_RTM_POWER_ON;
#endif
}

/* get the payload power state*/
uint8 get_Payload_power_state(void)
{
	if(IPMI_CPLD_PAYLOAD_POWER_CTL & IPMI_CPLD_PAYLOAD_POWER_ON)	//power on
		return 1;
	else		//power off
		return 0;
}
/*power on the payload */
inline void set_Payload_power_on(void)
{
	IPMI_CPLD_PAYLOAD_POWER_CTL |= IPMI_CPLD_PAYLOAD_POWER_ON;
}

/*power on the payload */
inline void set_Payload_power_off(void)
{
	IPMI_CPLD_PAYLOAD_POWER_CTL &= ~IPMI_CPLD_PAYLOAD_POWER_ON;
}

#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
/*power off all the AMC payload */
inline void set_all_AMC_power_off(void)
{
	IPMI_CPLD_AMC_PAYLOAD_POWER_CTL = IPMI_CPLD_ALL_AMC_PAYLOAD_POWER_OFF;
}

/*fru_id :amc id ,eg,fru_id = 0,AMC0 ;fru_id = 1,AMC1 .....*/
uint8 get_AMC_power_stat(uint8 amc_id)
{
    uint8 tmp1;
    uint8 ucRet = AMC_POWER_STAT_DOWN;

    tmp1 = IPMI_CPLD_AMC_PAYLOAD_POWER_STATE & 0xf0;
    if(tmp1 & (IPMI_CPLD_AMC0_PAYLOAD_POWER_STATE << amc_id)){
        ucRet = AMC_POWER_STAT_UP;
    }
    return ucRet;
}

uint8 get_AMC_slot_stat(uint8 amc_id)
{
    uint8 tmp;
    uint8 ucRet = AMC_SLOT_OUT;

    tmp = IPMI_CPLD_AMC_ONLINE & 0xf0;
    if(tmp & (IPMI_CPLD_AMC0_ONLINE << amc_id)){
        ucRet = AMC_SLOT_IN;
    }
    return ucRet;
}

void AMC_power_ctrl(uint8 power_ctrl,uint8 amc_id)
{
    switch(power_ctrl){
        case AMC_POWER_CONTROL_ON:
            IPMI_CPLD_AMC_PAYLOAD_POWER_CTL |= (IPMI_CPLD_AMC0_PAYLOAD_POWER_ON << amc_id);
            break;
        case AMC_POWER_CONTROL_OFF:
            IPMI_CPLD_AMC_PAYLOAD_POWER_CTL &= (IPMI_CPLD_AMC0_PAYLOAD_POWER_ON << amc_id);
            break;
        default:break;
    }
}

#endif

inline void IPMB_Enable_All(void)
{
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
	 IPMI_CPLD_IPMB_CONTROL |= IPMI_CPLD_IPMB_ENABLE_ALL;
#endif
}

/* ekey open */
inline void e_key_open(void)
{
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
	IPMI_CPLD_EKEY_CTL = IPMI_CPLD_EKEY_OPEN;
#endif
}
/* ekey close ***************************/
inline void e_key_off(void)
{
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
	IPMI_CPLD_EKEY_CTL = IPMI_CPLD_EKEY_OFF;
#endif
}

/*********************************************************************************************************
** Function name:           frt_blue_led_on
**
** Descriptions:            Set frt blue led on
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void frt_blue_led_on (void)
{
	if((IPMI_CPLD_FRT_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_ON){
		IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_BLUE_ON;		
	}
}

/*********************************************************************************************************
** Function name:           frt_blue_led_off
**
** Descriptions:            Set blue led off
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void frt_blue_led_off (void)
{
	if((IPMI_CPLD_FRT_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_OFF){
		IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_BLUE_OFF;		
	}
}

/*********************************************************************************************************
** Function name:           frt_blue_led_lblink
**
** Descriptions:            Set blue led on 900ms,off 100ms
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void frt_blue_led_lblink (void)
{
	if((IPMI_CPLD_FRT_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_LBLINK){
		IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_BLUE_LBLINK;		
	}
}
/*********************************************************************************************************
** Function name:           frt_blue_led_sblink
**
** Descriptions:            Set blue led on 100ms,off 900ms
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void frt_blue_led_sblink (void)
{
	if((IPMI_CPLD_FRT_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_SBLINK){
		IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_BLUE_SBLINK;		
	}
}

/*********************************************************************************************************
** Function name:           rtm_blue_led_on
**
** Descriptions:            Set frt blue led on
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void rtm_blue_led_on (void)
{
	if((IPMI_CPLD_RTM_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_ON){
		IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_BLUE_ON;		
	}
}

/*********************************************************************************************************
** Function name:           rtm_blue_led_off
**
** Descriptions:            Set blue led off
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void rtm_blue_led_off (void)
{
	if((IPMI_CPLD_RTM_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_OFF){
		IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_BLUE_OFF;		
	}
}

/*********************************************************************************************************
** Function name:           rtm_blue_led_lblink
**
** Descriptions:            Set blue led on 900ms,off 100ms
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void rtm_blue_led_lblink (void)
{
	if((IPMI_CPLD_RTM_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_LBLINK){
		IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_BLUE_LBLINK;		
	}
}
/*********************************************************************************************************
** Function name:           rtm_blue_led_sblink
**
** Descriptions:            Set blue led on 100ms,off 900ms
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
**
*********************************************************************************************************/
inline void rtm_blue_led_sblink (void)
{
	if((IPMI_CPLD_RTM_PNL_CTL & IPMI_CPLD_BLUE_MASK) != IPMI_CPLD_BLUE_SBLINK){
		IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_BLUE_MASK;
		IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_BLUE_SBLINK;		
	}
}

/*frt oos led on */
inline void frt_oos_led_on(void)
{
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OOS_LED; //oos led on, 0:on 
}
/*frt oos led off */
inline void frt_oos_led_off(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OOS_LED; //oos led off, 1:off
}
/*frt oos led green on */
inline void frt_oos_led_green(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OOS_LED;	//oos led off
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OOS_LED_GREEN; //led green, 0:on 
}

/*frt oos led red on */
inline void frt_oos_led_red(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OOS_LED;	//oos led off
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OOS_LED_RED; //led red, 0:on 
}
/*frt ok led on */
inline void frt_ok_led_on(void)
{
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OK_LED; //ok led on, 0:on 
}
/*frt ok led off */
inline void frt_ok_led_off(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OK_LED; //ok led off, 1:on 
}

/*frt ok led green on */
inline void frt_ok_led_green(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OK_LED;	//oos led off
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OK_LED_GREEN; //led green, 0:on 
}

/*frt ok led red on */
inline void frt_ok_led_red(void)
{
	IPMI_CPLD_FRT_PNL_CTL |= IPMI_CPLD_OK_LED;	//oos led off
	IPMI_CPLD_FRT_PNL_CTL &= ~IPMI_CPLD_OK_LED_RED; //led red, 0:on 
}

/*rtm oos led on */
inline void rtm_oos_led_on(void)
{
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OOS_LED; //oos led on, 0:on 
}
/*rtm oos led off */
inline void rtm_oos_led_off(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OOS_LED; //oos led off, 1:on 
}

/*rtm oos led green on */
inline void rtm_oos_led_green(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OOS_LED;	//oos led off
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OOS_LED_GREEN; //led green, 0:on 
}

/*rtm oos led red on */
inline void rtm_oos_led_red(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OOS_LED;	//oos led off
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OOS_LED_RED; //led red, 0:on 
}

/*rtm ok led on */
inline void rtm_ok_led_on(void)
{
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OK_LED; //ok led on, 0:on 
}

/*rtm ok led off */
inline void rtm_ok_led_off(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OK_LED; //ok led off, 1:off
}
/* rtm ok led green on */
inline void rtm_ok_led_green(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OK_LED;	//oos led off
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OK_LED_GREEN; //led green, 0:on 
}

/* rtm ok led red on */
inline void rtm_ok_led_red(void)
{
	IPMI_CPLD_RTM_PNL_CTL |= IPMI_CPLD_OK_LED;	//oos led off
	IPMI_CPLD_RTM_PNL_CTL &= ~IPMI_CPLD_OK_LED_RED; //led red, 0:on 
}

void set_cpld_start_state(void)
{
	set_Payload_power_off();
	set_RTM_power_off();
	//enable IPMB_L, IPMB_A and IPMB_B
	IPMB_Enable_All();
}







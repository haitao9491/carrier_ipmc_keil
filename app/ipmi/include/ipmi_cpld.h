/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           IPMI_CPLD.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI CPLD Register
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-06-30
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
#ifndef __IPMI_CPLD_H
#define __IPMI_CPLD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h" 
#include "boardinfo.h"
#include <stdbool.h>


#define IPMI_CPLD_RACK_SHELF_REG            	(*(volatile unsigned char *)0x81000008)

/* IPMC Interrupt Register */
#define IPMI_CPLD_INT_STAT_REG   	    		(*(volatile unsigned char *)0x81000011)
#define IMPI_CPLD_RTM_HANDLE_INT_STAT			0x80
#define IMPI_CPLD_FRT_HANDLE_INT_STAT			0x40
#define IMPI_CPLD_TEMP_SENSOR_INT_STAT			0x01

/*Interrupt Control reg */
#define IPMI_CPLD_INT_CTL_REG   	    		(*(volatile unsigned char *)0x81000012)
#define IMPI_CPLD_RTM_HANDLE_INT_ENABLE			0x80
#define IMPI_CPLD_FRT_HANDLE_INT_ENABLE			0x40
#define IMPI_CPLD_TEMP_SENSOR_INT_ENABLE		0x01

/* Carrier Hardware */
#define IPMI_CPLD_HARDADDRESS_REG           	(*(volatile unsigned char *)0x81000013)

/* Watchdog */
#define	IPMI_CPLD_WATCHDOG_FEED_REG         	(*(volatile unsigned char *)0x81000014)
#define IPMI_CPLD_WATCHDOG_FEED             	0x01
#define	IPMI_CPLD_WATCHDOG_EN_REG           	(*(volatile unsigned char *)0x81000015)
#define IPMI_CPLD_WATCHDOG_EN               	0x01

/* Carrier Payload Power Control---0:on 1:off */
#define IPMI_CPLD_PAYLOAD_POWER_CTL         	(*(volatile unsigned char *)0x81000016)
	
#if(BOARD_TYPE == BOARD_TYPE_XSCB_V2)
#define IPMI_CPLD_PAYLOAD_POWER_ShMC        	0xC0
#define IPMI_CPLD_PAYLOAD_POWER_FORCE_ON    	0x80
#define IPMI_CPLD_PAYLOAD_POWER_IPMC_LOCAL  	0x40
#define IPMI_CPLD_RTM_POWER_ON    				0x2
#endif

#define IPMI_CPLD_PAYLOAD_POWER_ON    			0x1
#define IPMI_CPLD_PAYLOAD_POWER_OFF         	0x00

#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
/* AMC Payload Power Control */
#define IPMI_CPLD_AMC_PAYLOAD_POWER_CTL	    	(*(volatile unsigned char *)0x81000017)
#define IPMI_CPLD_ALL_AMC_PAYLOAD_POWER_ON  	0xff
#define IPMI_CPLD_ALL_AMC_PAYLOAD_POWER_OFF 	0x0f
#define IPMI_CPLD_AMC0_PAYLOAD_POWER_ON     	0x10
#define IPMI_CPLD_AMC1_PAYLOAD_POWER_ON     	0x20
#define IPMI_CPLD_AMC2_PAYLOAD_POWER_ON     	0x40
#define IPMI_CPLD_AMC3_PAYLOAD_POWER_ON     	0x80
/* AMC Payload Power State */
#define IPMI_CPLD_AMC_PAYLOAD_POWER_STATE   	(*(volatile unsigned char *)0x81000018)
#define IPMI_CPLD_AMC0_PAYLOAD_POWER_STATE   	0x10
#define IPMI_CPLD_AMC1_PAYLOAD_POWER_STATE   	0x20
#define IPMI_CPLD_AMC2_PAYLOAD_POWER_STATE   	0x40
#define IPMI_CPLD_AMC3_PAYLOAD_POWER_STATE   	0x80

#endif

#define IPMI_CPLD_CARD_ONLINE                	(*(volatile unsigned char *)0x81000019)
#define IPMI_CPLD_RTM_ONLINE					0x01

#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
/* AMC Online State */
#define IPMI_CPLD_AMC_ONLINE                	(*(volatile unsigned char *)0x81000019)
#define IPMI_CPLD_AMC0_ONLINE					0x10
#define IPMI_CPLD_AMC1_ONLINE					0x20
#define IPMI_CPLD_AMC2_ONLINE					0x40
#define IPMI_CPLD_AMC3_ONLINE					0x80

/* IPMB-0 IPMB_L Control */
#define IPMI_CPLD_IPMB_CONTROL              	(*(volatile unsigned char *)0x8100001A)
#define IPMI_CPLD_IPMB_ENABLE_ALL				0xF7
#endif

/* Front Pnl Control */
#define IPMI_CPLD_FRT_PNL_CTL               	(*(volatile unsigned char *)0x8100001C)

#define IPMI_CPLD_RTM_PNL_CTL               	(*(volatile unsigned char *)0x8100001D)
#define IPMI_CPLD_HS_UP                     	(0x80)
#define IPMI_CPLD_HS_DOWN                   	(0x40)
#define IPMI_CPLD_BLUE_MASK                     (0x30)
#define IPMI_CPLD_BLUE_ON                      	(0x00)
#define IPMI_CPLD_BLUE_SBLINK                   (0x10)
#define IPMI_CPLD_BLUE_LBLINK                   (0x20)
#define IPMI_CPLD_BLUE_OFF                      (0x30)
#define IPMI_CPLD_OOS_LED						0x0C
#define IPMI_CPLD_OOS_LED_GREEN					0x08
#define IPMI_CPLD_OOS_LED_RED					0x04
#define IPMI_CPLD_OK_LED						0x03
#define IPMI_CPLD_OK_LED_GREEN					0x02
#define IPMI_CPLD_OK_LED_RED					0x01

/* ekey control register*/
#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
#define IPMI_CPLD_EKEY_CTL                  	(*(volatile unsigned char *)0x8100001E)
#define IPMI_CPLD_EKEY_OPEN                 	0x03
#define IPMI_CPLD_EKEY_OFF                  	0x00
#endif

#define IPMI_CPLD_HOTSWAP_STATUS_ADDR       	(*(volatile unsigned char *)0x8100001F)
	
/***   functions  ***/

uint8 get_carrier_ipmc_stat(void);

/*handle switch related functions*/
uint8 get_carrier_frt_hs_stat(void);
uint8 get_carrier_rtm_hs_stat(void);

/**rtm in slot check***/
bool RTM_in_slot(void);

/*int related functions */
void frt_HS_int_enbale(void);
void rtm_HS_int_enbale(void);
void temp_sensor_int_enbale(void);
bool get_frt_handle_int_stat(void);
bool get_rtm_handle_int_stat(void);
bool get_temp_sensor_int_stat(void);

/*power related functions*/
bool get_RTM_power_state(void);
void set_RTM_power_on(void);
void set_RTM_power_off(void);
uint8 get_Payload_power_state(void);
void set_Payload_power_on(void);
void set_Payload_power_off(void);

#if( (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) )
void set_all_AMC_power_off(void);
uint8 get_AMC_power_stat(uint8 amc_id);
uint8 get_AMC_slot_stat(uint8 amc_id);
void AMC_power_ctrl(uint8 power_ctrl,uint8 amc_id);
#endif

/*IPMB functions */
void IPMB_Enable_All(void);
/*e-key functions */
void e_key_open(void);
void e_key_off(void);
/**blue led functions */
void frt_blue_led_on (void);
void frt_blue_led_off (void);
void frt_blue_led_lblink (void);
void frt_blue_led_sblink (void);

void rtm_blue_led_on (void);
void rtm_blue_led_off (void);
void rtm_blue_led_lblink (void);
void rtm_blue_led_sblink (void);

/*other led functions*/
void frt_oos_led_on(void);
void frt_oos_led_off(void);
void frt_oos_led_green(void);
void frt_oos_led_red(void);
void frt_ok_led_on(void);
void frt_ok_led_off(void);
void frt_ok_led_green(void);
void frt_ok_led_red(void);

void rtm_oos_led_on(void);
void rtm_oos_led_off(void);
void rtm_oos_led_green(void);
void rtm_oos_led_red(void);
void rtm_ok_led_on(void);
void rtm_ok_led_off(void);
void rtm_ok_led_green(void);
void rtm_ok_led_red(void);

void set_cpld_start_state(void);
#ifdef __cplusplus
}
#endif

#endif/* __IPMI_CPLD_H */


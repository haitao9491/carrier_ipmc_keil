/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_sdr.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI NetFn and CMDs
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-06-26
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
#ifndef __IPMI_SDR_H
#define __IPMI_SDR_H

#include "config.h"
#include "app_cfg.h"
#include "boardinfo.h"

#ifdef __cplusplus
extern "C" {
#endif
#define DEVICE_LOCATOR_RECORD_ID               	0x0000
#define FRU_HOTSWAP_RECORD_ID               	0x0001
#define FRU_TEMP0_RECORD_ID               		0x0002
#define FRU_PWR0_RECORD_ID               		(FRU_TEMP0_RECORD_ID + TEMP_SENSOR_NUM)

#define SDR_VERSION								0x51		//1.5

#define ENTITY_ID_IPMC							0xA0		
#define ENTITY_INSTANCE							0x60
/*
  SDR data
 */
#define SDR_INVENTORY_AREA_SIZE 64
#define SDR_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD_OFFSET   0
#define SDR_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD_SIZE     27
#define SDR_COMPACT_SENSOR_RECORD_OFFSET     (SDR_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD_OFFSET \
                                              + SDR_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD_SIZE)
#define SDR_COMPACT_SENSOR_RECORD_SIZE  43
#define SDR_FULL_SENSOR_RECORD_OFFSET   (SDR_COMPACT_SENSOR_RECORD_OFFSET + SDR_COMPACT_SENSOR_RECORD_SIZE)
#define SDR_FULL_SENSOR_RECORD_SIZE     58

/* IPMI SDR Type */
#define IPMI_SDR_FORMAT_FULL_SENSOR_RECORD                          0x01
#define IPMI_SDR_FORMAT_COMPACT_SENSOR_RECORD                       0x02
#define IPMI_SDR_FORMAT_EVENT_ONLY_RECORD                           0x03
#define IPMI_SDR_FORMAT_ENTITY_ASSOCIATION_RECORD                   0x08
#define IPMI_SDR_FORMAT_DEVICE_RELATIVE_ENTITY_ASSOCIATION_RECORD   0x09
#define IPMI_SDR_FORMAT_GENERIC_DEVICE_LOCATOR_RECORD               0x10
#define IPMI_SDR_FORMAT_FRU_DEVICE_LOCATOR_RECORD                   0x11
#define IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD 0x12
#define IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_CONFIRMATION_RECORD   0x13
#define IPMI_SDR_FORMAT_BMC_MESSAGE_CHANNEL_INFO_RECORD             0x14
#define IPMI_SDR_FORMAT_OEM_RECORD                                  0xC0

/****SDR type1 offset definitions **************/
#define SDR_HEAD_LEN							5
//head
#define SDR1_OFFSET_ID							0
#define SDR1_OFFSET_VERSION						2
#define SDR1_OFFSET_TYPE						3
#define SDR1_OFFSET_LENGTH						4
//key bytes
#define SDR1_OFFSET_OWNER_ID					5				//IPMB address
#define SDR1_OFFSET_OWNER_LUN					6				//1 for Device Locator Record,others 0
#define SDR1_OFFSET_SENSOR_NUMBER				7
//record body bytes
#define SDR1_OFFSET_ENTITY_ID					8
#define SDR1_OFFSET_ENTITY_INSTANCE				9
#define SDR1_OFFSET_SENSOR_INIT					10
#define SDR1_OFFSET_SENSOR_CAP					11
#define SDR1_OFFSET_SENSOR_TYPE					12
#define SDR1_OFFSET_EVENT_TYPE					13
#define SDR1_OFFSET_ASSERT_EVENT_MASK			14
#define SDR1_OFFSET_LOWER_THRESHOLD_READ_MASK	14
#define SDR1_OFFSET_DEASSERT_EVENT_MASK			16
#define SDR1_OFFSET_UPPER_THRESHOLD_READ_MASK	16
#define SDR1_OFFSET_DISCRETE_READ_MASK			18
#define SDR1_OFFSET_SENSOR_UNITS				20		//byte value 0
#define SDR1_OFFSET_BASE_UNITS					21
#define SDR1_OFFSET_MODIFIER_UNITS				22
#define SDR1_OFFSET_LINEARIZATION				23
#define SDR1_OFFSET_M							24
#define SDR1_OFFSET_B							26
#define SDR1_OFFSET_ACCURACY					28		//27 byte ls 6 bits
#define SDR1_OFFSET_EXP							29		//ls 4 bits for Bexp, ms 4 bits for Rexp
#define SDR1_OFFSET_ANALOG_FLAG					30		//bit0,normal reading specified,byte value 0x00 
#define SDR1_OFFSET_NORMAL_READING				31		// 0 
#define SDR1_OFFSET_NORMAL_MAX					32		// 0 
#define SDR1_OFFSET_NORMAL_MIN					33		// 0 
#define SDR1_OFFSET_SENSOR_MAX					34		// sensor maximum reading
#define SDR1_OFFSET_SENSOR_MIN					35		// sensor minimum reading
#define SDR1_OFFSET_UPPER_NON_RECOVER			36		// 
#define SDR1_OFFSET_UPPER_CRITICAL				37		// 
#define SDR1_OFFSET_UPPER_NON_CRITICAL			38		// 
#define SDR1_OFFSET_LOWER_NON_RECOVER			39		// 
#define SDR1_OFFSET_LOWER_CRITICAL				40		// 
#define SDR1_OFFSET_LOWER_NON_CRITICAL			41		//
#define SDR1_OFFSET_HYS_P						42		// 
#define SDR1_OFFSET_HYS_N						43		// 
#define SDR1_OFFSET_ID_TYPE_LEN					47		// sensor ID type/length
#define SDR1_OFFSET_ID_STRING					48		// sensor string

#define SENSOR_UNIT_TEMP 						0x01
#define SENSOR_UNIT_VOLTAGE 					0x04

#define SENSOR_CAP_IGNORE									 (1<<7)
#define SENSOR_CAP_AUTO_REARM								 (1<<6)
#define SENSOR_CAP_HYS_RD									 (1<<4)
#define SENSOR_CAP_HYS_RD_WR								 (2<<4)
#define SENSOR_CAP_THRESHOLD_ACCESS							 (3<<2)	//11b unreadable, threshold value fields 
																	//report the hardcoded threshold
#define SENSOR_CAP_THRESHOLD_AC_RD							 (1<<2)
#define SENSOR_CAP_THRESHOLD_AC_RD_WR						 (2<<2)	
#define SENSOR_CAP_EVENT_CTRL								 (3)	//11b no events from the sensor

typedef struct{
	uint16 id;		//record id 
	uint8 type;		// record type
	uint8 length;	//record length
	uint8 *record_ptr;	//pointor to the record
}SDR_t;

/*
  function
 */
void sdr_generate(void);
#ifdef __cplusplus
}
#endif

#endif/* __IPMI_SDR_H */


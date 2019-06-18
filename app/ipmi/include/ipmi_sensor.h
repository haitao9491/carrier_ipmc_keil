/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-sensor.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI sensor
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-03
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
#ifndef __IPMI_SENSOR_H
#define __IPMI_SENSOR_H

#include "config.h"
#include "ipmi_sdr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IPMI Sensor Type */
#define IPMI_SENSOR_TYPE_RESERVED                            0x00
#define IPMI_SENSOR_TYPE_TEMPERATURE                         0x01
#define IPMI_SENSOR_TYPE_VOLTAGE                             0x02
#define IPMI_SENSOR_TYPE_CURRENT                             0x03
#define IPMI_SENSOR_TYPE_FAN                                 0x04
#define IPMI_SENSOR_TYPE_PHYSICAL_SECURITY                   0x05
#define IPMI_SENSOR_TYPE_PLATFORM_SECURITY_VIOLATION_ATTEMPT 0x06
#define IPMI_SENSOR_TYPE_PROCESSOR                           0x07
#define IPMI_SENSOR_TYPE_POWER_SUPPLY                        0x08
#define IPMI_SENSOR_TYPE_POWER_UNIT                          0x09
#define IPMI_SENSOR_TYPE_COOLING_DEVICE                      0x0A
#define IPMI_SENSOR_TYPE_OTHER_UNITS_BASED_SENSOR            0x0B
#define IPMI_SENSOR_TYPE_MEMORY                              0x0C
#define IPMI_SENSOR_TYPE_DRIVE_SLOT                          0x0D
#define IPMI_SENSOR_TYPE_POST_MEMORY_RESIZE                  0x0E
#define IPMI_SENSOR_TYPE_SYSTEM_FIRMWARE_PROGRESS            0x0F
#define IPMI_SENSOR_TYPE_EVENT_LOGGING_DISABLED              0x10
#define IPMI_SENSOR_TYPE_WATCHDOG1                           0x11
#define IPMI_SENSOR_TYPE_SYSTEM_EVENT                        0x12
#define IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT                  0x13
#define IPMI_SENSOR_TYPE_BUTTON_SWITCH                       0x14
#define IPMI_SENSOR_TYPE_MODULE_BOARD                        0x15
#define IPMI_SENSOR_TYPE_MICROCONTROLLER_COPROCESSOR         0x16
#define IPMI_SENSOR_TYPE_ADD_IN_CARD                         0x17
#define IPMI_SENSOR_TYPE_CHASSIS                             0x18
#define IPMI_SENSOR_TYPE_CHIP_SET                            0x19
#define IPMI_SENSOR_TYPE_OTHER_FRU                           0x1A
#define IPMI_SENSOR_TYPE_CABLE_INTERCONNECT                  0x1B
#define IPMI_SENSOR_TYPE_TERMINATOR                          0x1C
#define IPMI_SENSOR_TYPE_SYSTEM_BOOT_INITIATED               0x1D
#define IPMI_SENSOR_TYPE_BOOT_ERROR                          0x1E
/* OS BOOT renamed Base OS Boot/Installation Status, but gonna keep legacy name for ease */
#define IPMI_SENSOR_TYPE_OS_BOOT                             0x1F
#define IPMI_SENSOR_TYPE_OS_CRITICAL_STOP                    0x20
#define IPMI_SENSOR_TYPE_SLOT_CONNECTOR                      0x21
#define IPMI_SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE             0x22
#define IPMI_SENSOR_TYPE_WATCHDOG2                           0x23
#define IPMI_SENSOR_TYPE_PLATFORM_ALERT                      0x24
#define IPMI_SENSOR_TYPE_ENTITY_PRESENCE                     0x25
#define IPMI_SENSOR_TYPE_MONITOR_ASIC_IC                     0x26
#define IPMI_SENSOR_TYPE_LAN                                 0x27
#define IPMI_SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH         0x28
#define IPMI_SENSOR_TYPE_BATTERY                             0x29
#define IPMI_SENSOR_TYPE_SESSION_AUDIT                       0x2A
#define IPMI_SENSOR_TYPE_VERSION_CHANGE                      0x2B
#define IPMI_SENSOR_TYPE_FRU_STATE                           0x2C
#define IPMI_SENSOR_TYPE_OEM_MIN                             0xC0
#define IPMI_SENSOR_TYPE_HS                             	 0xF0
#define IPMI_SENSOR_TYPE_OEM_MAX                             0xFF

#define EVENT_TYPE_THRESHOLD									0x01
#define EVENT_TYPE_SENSOR_SPECIFIC								0x6F

#define THRESHOLD_EVENT_ASSERT_MASK							(0x200)
#define THRESHOLD_EVENT_DEASSERT_MASK						(0x200)

#define HS_EVENT_ASSERT_MASK								(0xff)

#define THRESHOLD_UPPER_NONE_RECOVERABLE					 (1<<5)
#define THRESHOLD_UPPER_CRITICAL							 (1<<4)
#define THRESHOLD_UPPER_NONE_CRITICAL					 	 (1<<3)
#define THRESHOLD_LOWER_NONE_RECOVERABLE					 (1<<2)
#define THRESHOLD_LOWER_CRITICAL							 (1<<1)
#define THRESHOLD_LOWER_NONE_CRITICAL					 	 1


#define TERMOERATURE_U_NONE_RECOVERABLE					 	(85)	//in celsius
#define TERMOERATURE_U_CRITICAL							 	(75)
#define TERMOERATURE_U_NONE_CRITICAL					 	(65)
#define TERMOERATURE_L_NONE_RECOVERABLE					 	(-10)
#define TERMOERATURE_L_CRITICAL							 	(0)
#define TERMOERATURE_L_NONE_CRITICAL					 	(10)

#define TERMOERATURE_HYS_P								 	(5)	//in celsius
#define TERMOERATURE_HYS_N								 	(5)

#define VOLTAGE_U_NONE_RECOVERABLE					 		(85)	//in celsius
#define VOLTAGE_U_CRITICAL							 		(75)
#define VOLTAGE_U_NONE_CRITICAL					 			(65)
#define VOLTAGE_L_NONE_RECOVERABLE					 		(-10)
#define VOLTAGE_L_CRITICAL							 		(0)
#define VOLTAGE_L_NONE_CRITICAL					 			(10)

#define VOLTAGE_HYS_P								 		(5)	//in celsius
#define VOLTAGE_HYS_N								 		(5)

//#define SENSOR_NUM              0x03
/* Sensor number */
#define SENSOR_NUMBER_HANDLE_SWITCH     0x80

#define SENSOR_NUMBER_TEMPERATURE0      0x10
#define SENSOR_NUMBER_TEMPERATURE1      0x11
#define SENSOR_NUMBER_TEMPERATURE2      0x12
#define SENSOR_NUMBER_TEMPERATURE3     	0x13
#define SENSOR_NUMBER_TEMPERATURE4      0x14

#define SENSOR_NUMBER_VOLTAGE0      	0x40
#define SENSOR_NUMBER_VOLTAGE1      	0x41
#define SENSOR_NUMBER_VOLTAGE2      	0x42
#define SENSOR_NUMBER_VOLTAGE3      	0x43
#define SENSOR_NUMBER_VOLTAGE4	     	0x44

/* Temperature Sensor Thresholds and Type */
#define TERMOERATURE_UPPER_MINOR        0x57
#define TERMOERATURE_UPPER_MAJOR        0x59
#define TERMOERATURE_UPPER_CRITICAL     0x5b
#define TERMOERATURE_UPPER_MINOR_THRESHOLD      0x41
#define TERMOERATURE_UPPER_MAJOR_THRESHOLD      0x50
#define TERMOERATURE_UPPER_CRITICAL_THRESHOLD   0x51

/*
  Return Operation to Read Sensor
 */
typedef enum{
	VOL_1,
	VOL_1_2,
	VOL_1_5,
	VOL_2_5,
	VOL_3_3,
	VOL_5,
	VOL_12,
	VOL_48,	
}Vol_Type;

typedef struct{
	uint8 type;
	uint8 number;
	uint8 event_type;
	uint16 eventmask;
}SensorBasic;

typedef struct{
	SensorBasic baseinfo;
	uint8 entity_id;
	uint8 entity_instance;
	float u_non_recoverable_threshold;		// temp in celsius,voltage in v
	float l_non_recoverable_threshold;
	float u_critical_threshold;
	float l_critical_threshold;
	float u_non_critical_threshold;
	float l_non_critical_threshold;
	float hys_positive;				// temp in celsius,voltage in v
	float hys_negative;
	Vol_Type vol_type;
	float data_real;
	uint8 data_encode;
	
	int16 M:10;
	int16 B:10;
	int8  Rexp:4;
	int8  Bexp:4;
	uint8 unitcode;			//1,degree C;4,volts
	char name[20];	
	SDR_t sdr;		
}ThresholdSensor;

typedef struct{
	SensorBasic baseinfo; 
	uint8 entity_id;
	uint8 entity_instance;
	char name[20];	
	SDR_t sdr;		
}DiscreteSensor;		//for discrete sensor ,esp hotswap handle
/*
  Temperature information struct
 */
typedef struct _tempdata {
    uint8 temp_integer;
    uint8 temp_fraction;
}TempData;

typedef enum {
	S_Type_HS,
    S_Type_TEMP,
    S_Type_PWR,	
	S_Type_None
}S_Type;

#define TMP421_4C	0
#define TMP421_4D	1
#define TMP421_4E	2
#define TMP421_4F	3
#define	TMP_POWER 	4
#define TMP_5464	5
/*
 * Function statement
 */

//ThresholdSensor* get_sensor(uint8 sensor_num);
uint8 get_sdr_id(uint8 sensor_num);
void IPMI_Sensor_TASK (void *pdata);

uint8 TH_sensor_datacode_gen(ThresholdSensor *sensor,float data);
int8 ipmi_get_sensor_hys(uint8 sensor_num,uint8 *payload,uint8 *payload_len);
int8 ipmi_get_threshold(uint8 sensor_num,uint8 *payload,uint8 *payload_len);
int8 ipmi_get_event_en(uint8 sensor_num,uint8 *payload,uint8 *payload_len);
int8 ipmi_get_sensor_reading(uint8 sensor_num,uint8 *payload,uint8 *payload_len);
//void temp_sensor_init(void);
//void vol_sensor_init(void);
void ipmi_sensor_init(void);


#ifdef __cplusplus
}
#endif

#endif/* __IPMI_SENSOR_H */




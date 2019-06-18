/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-sdr.c
** Last modified Date:  2015-06-29
** Last Version:        1.0
** Descriptions:        ATCA IPMI SDR
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
#include "ipmi_sdr.h"
#include "ipmi_sensor.h"


extern BoardInfo g_boardinfo ;
extern ThresholdSensor g_sensor_temp[TEMP_SENSOR_NUM];
extern ThresholdSensor g_sensor_vol[PWR_SENSOR_NUM] ;

extern INT8U Debug_Flag;


uint8 sdr_info[SDR_NUM][SDR_INVENTORY_AREA_SIZE] = {
/* Management Controller Device Locator Record , length 27bytes */
    {
    	0x00, 0x00, 0x51, 0x12, 0x16, 0x00, 0x01, 0x0c,
    	//0x7b, 0x00, 0x00, 0x00,ENTITY_ID_IPMC, ENTITY_INSTANCE, 0x00, 0xcb,
		0x29, 0x00, 0x00, 0x00,ENTITY_ID_IPMC, ENTITY_INSTANCE, 0x00, 0xcb,
    	0x52, 0x59, 0x58, 0x20, 0x41, 0x54, 0x43, 0x41,
    	0x20, 0x46, 0x50
    },
/* Compact Sensor Record, length 43bytes */
/* [Handle switch] senser number 0x90--144*/
    {
    	0x01, 0x00, 0x51, 0x02, 0x26, 0x00, 0x00, 0x80,
    	0xa0, 0x60, 0x27, 0x42, 0xf0, 0x6f, 0x07, 0x00,
    	0x00, 0x00, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x01,
    	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcb,
        0x52, 0x59, 0x58, 0x20, 0x41, 0x54, 0x43, 0x41,
        0x20, 0x48, 0x53
    },
};

void sdr_output(uint8 record_id)
{
	uint8 *record_ptr = sdr_info[record_id];
	uint8 i = 0;
	for(i = 0;i < 64;i++)
	{
		UART0_Printf("%02x,",record_ptr[i]);
		if(((i+1) % 8) == 0)
			UART0_SendStr("\n");
	}
	UART0_SendStr("\n");
}



void threshold_field_fill(ThresholdSensor *sensor)
{
	uint8 id = sensor->sdr.id;
	uint8 *record_ptr = sdr_info[id];
	record_ptr[SDR1_OFFSET_UPPER_NON_RECOVER] = TH_sensor_datacode_gen(sensor,sensor->u_non_recoverable_threshold);
	record_ptr[SDR1_OFFSET_UPPER_CRITICAL] = TH_sensor_datacode_gen(sensor,sensor->u_critical_threshold);
	record_ptr[SDR1_OFFSET_UPPER_NON_CRITICAL] = TH_sensor_datacode_gen(sensor,sensor->u_non_critical_threshold);
	record_ptr[SDR1_OFFSET_LOWER_NON_RECOVER] = TH_sensor_datacode_gen(sensor,sensor->l_non_recoverable_threshold);
	record_ptr[SDR1_OFFSET_LOWER_CRITICAL] = TH_sensor_datacode_gen(sensor,sensor->l_critical_threshold);
	record_ptr[SDR1_OFFSET_LOWER_NON_CRITICAL] = TH_sensor_datacode_gen(sensor,sensor->l_non_critical_threshold);
	//if(sensor->baseinfo.type == IPMI_SENSOR_TYPE_TEMPERATURE) {
		record_ptr[SDR1_OFFSET_HYS_P] = TH_sensor_datacode_gen(sensor,sensor->hys_positive);
		record_ptr[SDR1_OFFSET_HYS_N] = TH_sensor_datacode_gen(sensor,sensor->hys_negative);
	//}

#if 1	
	UART0_Printf("u_non_recoverable_threshold: %f,",
			sensor->u_non_recoverable_threshold);
	UART0_Printf("raw value:%d\n",
			record_ptr[SDR1_OFFSET_UPPER_NON_RECOVER]);
	
	UART0_Printf("u_critical_threshold: %f,",
			sensor->u_critical_threshold);
	UART0_Printf(" raw value:%d\n",
			record_ptr[SDR1_OFFSET_UPPER_CRITICAL]);
	
	UART0_Printf("u_non_critical_threshold: %f,",
			sensor->u_non_critical_threshold);
	UART0_Printf("raw value:%d\n",
			record_ptr[SDR1_OFFSET_UPPER_NON_CRITICAL]);
	
	UART0_Printf("l_non_recoverable_threshold: %f,",
			sensor->l_non_recoverable_threshold);	
	UART0_Printf(" raw value:%d\n",
			record_ptr[SDR1_OFFSET_LOWER_NON_RECOVER]);
	
	UART0_Printf("l_critical_threshold: %f,",
			sensor->l_critical_threshold);		
	UART0_Printf("raw value:%d\n",
			record_ptr[SDR1_OFFSET_LOWER_CRITICAL]);
			
	UART0_Printf("l_non_critical_threshold: %f,",
			sensor->l_non_critical_threshold);				
	UART0_Printf("raw value:%d\n",
			record_ptr[SDR1_OFFSET_LOWER_NON_CRITICAL]);
#endif
}


void temp_sdr_gen(ThresholdSensor *sensor)
{
	uint8 id = sensor->sdr.id;		//record id
	uint8 *record_ptr = sdr_info[id];
	int16 accuracy = 0;
	
	memset(record_ptr,0,SDR_INVENTORY_AREA_SIZE);		//reset mem area
	threshold_field_fill(sensor);
	//head
	record_ptr[SDR1_OFFSET_ID] = sensor->sdr.id;
	record_ptr[SDR1_OFFSET_ID+1] = sensor->sdr.id >> 8;
	record_ptr[SDR1_OFFSET_VERSION] = SDR_VERSION;
	record_ptr[SDR1_OFFSET_TYPE] = sensor->sdr.type;
	record_ptr[SDR1_OFFSET_LENGTH] = SDR1_OFFSET_ID_STRING - SDR_HEAD_LEN + strlen(sensor->name);
	//key values
	record_ptr[SDR1_OFFSET_OWNER_ID] = g_boardinfo.ipmbAddr;
	record_ptr[SDR1_OFFSET_OWNER_LUN] = 0;
	record_ptr[SDR1_OFFSET_SENSOR_NUMBER] = sensor->baseinfo.number;
	//body
	record_ptr[SDR1_OFFSET_ENTITY_ID] = sensor->entity_id;
	record_ptr[SDR1_OFFSET_ENTITY_INSTANCE] = sensor->entity_instance;
	record_ptr[SDR1_OFFSET_SENSOR_INIT] = 0x7f;
	record_ptr[SDR1_OFFSET_SENSOR_CAP] = SENSOR_CAP_AUTO_REARM |SENSOR_CAP_HYS_RD|
								SENSOR_CAP_THRESHOLD_AC_RD ;	
	record_ptr[SDR1_OFFSET_SENSOR_TYPE] = sensor->baseinfo.type;
	record_ptr[SDR1_OFFSET_EVENT_TYPE] = sensor->baseinfo.event_type;
	record_ptr[SDR1_OFFSET_ASSERT_EVENT_MASK] = (THRESHOLD_EVENT_ASSERT_MASK & 0xff);
	// lower thrshold comparisons are returned through sensor reading
	record_ptr[SDR1_OFFSET_ASSERT_EVENT_MASK + 1] = 0x70 | ((THRESHOLD_EVENT_ASSERT_MASK & 0xf00) >> 8);		
	record_ptr[SDR1_OFFSET_DEASSERT_EVENT_MASK] = (THRESHOLD_EVENT_DEASSERT_MASK & 0xff);
	// upper thrshold comparisons are returned through sensor reading
	record_ptr[SDR1_OFFSET_DEASSERT_EVENT_MASK + 1] = 0x70 | ((THRESHOLD_EVENT_ASSERT_MASK & 0xf00) >> 8);
	record_ptr[SDR1_OFFSET_DISCRETE_READ_MASK] = 0x3F;	//thresholds are readable
	record_ptr[SDR1_OFFSET_DISCRETE_READ_MASK + 1] = 0x0; //threshold is not setable
	//record_ptr[SDR1_OFFSET_SENSOR_UNITS] = 0;
	record_ptr[SDR1_OFFSET_BASE_UNITS] = sensor->unitcode;
	//record_ptr[SDR1_OFFSET_MODIFIER_UNITS] =	0;
	//record_ptr[SDR1_OFFSET_LINEARIZATION] = 0; //linear
	record_ptr[SDR1_OFFSET_M] = (sensor->M & 0xff);
	record_ptr[SDR1_OFFSET_M + 1] = (sensor->M & 0x300 ) >> 2;
	record_ptr[SDR1_OFFSET_B] = sensor->B;
	record_ptr[SDR1_OFFSET_B + 1] = ((sensor->B & 0x300) >> 2) | ( accuracy & 0x3F);
	record_ptr[SDR1_OFFSET_ACCURACY] = ((accuracy & 0x3C0) >> 2)  ; //bit7:4,ms 4 bits of 10 bits accuracy,bit2:3,Aexp = 2,
	record_ptr[SDR1_OFFSET_EXP] = (sensor->Rexp << 4 ) | sensor->Bexp;  //Rexp = -1,Bexp = 0
	record_ptr[SDR1_OFFSET_ANALOG_FLAG] = 0;
	record_ptr[SDR1_OFFSET_NORMAL_READING] = 100;	 // 40 celsius
	record_ptr[SDR1_OFFSET_NORMAL_MAX] = 166;		//80 celsius
	record_ptr[SDR1_OFFSET_NORMAL_MIN] = 34;		//0 celsius
	record_ptr[SDR1_OFFSET_SENSOR_MAX] = 233;		//120 celsius,according to M ,B and Rexp,Bexp
	record_ptr[SDR1_OFFSET_SENSOR_MIN] = 0;			//-20 celsius,according to M ,B and Rexp,Bexp
    record_ptr[SDR1_OFFSET_ID_TYPE_LEN] = 0xC0;	
	record_ptr[SDR1_OFFSET_ID_TYPE_LEN] |= strlen(sensor->name);
    strcpy((char *)&(sdr_info[id][SDR1_OFFSET_ID_STRING]),sensor->name);	
}

void pwr_sdr_gen(ThresholdSensor *sensor)
{
	uint8 id = sensor->sdr.id;		//record id
	uint8 *record_ptr = sdr_info[id];
	int16 accuracy = 0;
	
	memset(record_ptr,0,SDR_INVENTORY_AREA_SIZE);		//reset mem area
	threshold_field_fill(sensor);
	//head
	record_ptr[SDR1_OFFSET_ID] = sensor->sdr.id;
	record_ptr[SDR1_OFFSET_ID+1] = sensor->sdr.id >> 8;
	record_ptr[SDR1_OFFSET_VERSION] = SDR_VERSION;
	record_ptr[SDR1_OFFSET_TYPE] = sensor->sdr.type;
	record_ptr[SDR1_OFFSET_LENGTH] = SDR1_OFFSET_ID_STRING - SDR_HEAD_LEN + strlen(sensor->name);
	//key values
	record_ptr[SDR1_OFFSET_OWNER_ID] = g_boardinfo.ipmbAddr;
	record_ptr[SDR1_OFFSET_OWNER_LUN] = 0;
	record_ptr[SDR1_OFFSET_SENSOR_NUMBER] = sensor->baseinfo.number;
	//body
	record_ptr[SDR1_OFFSET_ENTITY_ID] = sensor->entity_id;
	record_ptr[SDR1_OFFSET_ENTITY_INSTANCE] = sensor->entity_instance;
	record_ptr[SDR1_OFFSET_SENSOR_INIT] = 0x7f;
	record_ptr[SDR1_OFFSET_SENSOR_CAP] = SENSOR_CAP_AUTO_REARM |SENSOR_CAP_HYS_RD|
								SENSOR_CAP_THRESHOLD_AC_RD ;	
	record_ptr[SDR1_OFFSET_SENSOR_TYPE] = sensor->baseinfo.type;
	record_ptr[SDR1_OFFSET_EVENT_TYPE] = sensor->baseinfo.event_type;
	record_ptr[SDR1_OFFSET_ASSERT_EVENT_MASK] = (THRESHOLD_EVENT_ASSERT_MASK & 0xff);
	// lower thrshold comparisons are returned through sensor reading
	record_ptr[SDR1_OFFSET_ASSERT_EVENT_MASK + 1] = 0x70 | ((THRESHOLD_EVENT_ASSERT_MASK & 0xf00) >> 8);		
	record_ptr[SDR1_OFFSET_DEASSERT_EVENT_MASK] = (THRESHOLD_EVENT_DEASSERT_MASK & 0xff);
	// upper thrshold comparisons are returned through sensor reading
	record_ptr[SDR1_OFFSET_DEASSERT_EVENT_MASK + 1] = 0x70 | ((THRESHOLD_EVENT_ASSERT_MASK & 0xf00) >> 8);
	record_ptr[SDR1_OFFSET_DISCRETE_READ_MASK] = 0x3F;	//thresholds are readable
	record_ptr[SDR1_OFFSET_DISCRETE_READ_MASK + 1] = 0x0; //threshold is not setable
	//record_ptr[SDR1_OFFSET_SENSOR_UNITS] = 0;
	record_ptr[SDR1_OFFSET_BASE_UNITS] = sensor->unitcode;
	//record_ptr[SDR1_OFFSET_MODIFIER_UNITS] =	0;
	//record_ptr[SDR1_OFFSET_LINEARIZATION] = 0; //linear
	record_ptr[SDR1_OFFSET_M] = (sensor->M & 0xff);
	record_ptr[SDR1_OFFSET_M + 1] = (sensor->M & 0x300 ) >> 2;
	record_ptr[SDR1_OFFSET_B] = sensor->B;
	record_ptr[SDR1_OFFSET_B + 1] = ((sensor->B & 0x300) >> 2) | ( accuracy & 0x3F);
	record_ptr[SDR1_OFFSET_ACCURACY] = ((accuracy & 0x3C0) >> 2)  ; //bit7:4,ms 4 bits of 10 bits accuracy,bit2:3,Aexp = 2,
	record_ptr[SDR1_OFFSET_EXP] = (sensor->Rexp << 4 ) | sensor->Bexp;  //Rexp = -1,Bexp = 0
	record_ptr[SDR1_OFFSET_ANALOG_FLAG] = 0;
//	record_ptr[SDR1_OFFSET_NORMAL_READING] = 100;	 // 40 celsius
//	record_ptr[SDR1_OFFSET_NORMAL_MAX] = 166;		//80 celsius
//	record_ptr[SDR1_OFFSET_NORMAL_MIN] = 34;		//0 celsius
//	record_ptr[SDR1_OFFSET_SENSOR_MAX] = 233;		//120 celsius,according to M ,B and Rexp,Bexp
//	record_ptr[SDR1_OFFSET_SENSOR_MIN] = 0;			//-20 celsius,according to M ,B and Rexp,Bexp
    record_ptr[SDR1_OFFSET_ID_TYPE_LEN] = 0xC0;	
	record_ptr[SDR1_OFFSET_ID_TYPE_LEN] |= strlen(sensor->name);
    strcpy((char *)&(sdr_info[id][SDR1_OFFSET_ID_STRING]),sensor->name);	
}

void sdr_init(void)	//fill address field
{
	sdr_info[0][5] = g_boardinfo.ipmbAddr;
	sdr_info[1][5] = g_boardinfo.ipmbAddr;
}

void sdr_generate(void)
{
	int i = 0;
	sdr_init();
	for( i = 0; i < TEMP_SENSOR_NUM;i++) {
		temp_sdr_gen(&g_sensor_temp[i]);
		if(Debug_Flag){
			sdr_output(g_sensor_temp[i].sdr.id);
		}
	}
	for( i = 0; i < PWR_SENSOR_NUM;i++) {
		pwr_sdr_gen(&g_sensor_vol[i]);
		if(Debug_Flag){
			sdr_output(g_sensor_vol[i].sdr.id);
		}
	}
}


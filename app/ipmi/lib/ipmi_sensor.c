/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-led.c
** Last modified Date:  2015-07-02
** Last Version:        1.0
** Descriptions:        ATCA FRU Function
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-02
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
//#include "app_cfg.h"
#include "exi2c.h"
#include "adc.h"
//#include "uart.h"
//#include "eeprom.h"
//#include "ipmi_defs.h"
#include "ipmi_sensor.h"
#include "boardinfo.h"
#include "sensor_temp.h"
#include "ipmi_defs.h"
#include <math.h>

extern BoardInfo g_boardinfo ;
extern uint8 sdr_info[SDR_NUM][SDR_INVENTORY_AREA_SIZE];


INT8U Temperature_Power,Temperature_5464;
INT8U Voltage;

ThresholdSensor g_sensor_temp[TEMP_SENSOR_NUM] = {0} ;
ThresholdSensor g_sensor_vol[PWR_SENSOR_NUM] = {0} ;
#if ((BOARD_TYPE == BOARD_TYPE_MACB_V3) || (BOARD_TYPE == BOARD_TYPE_MACB_V2) )
Vol_Type g_vol_sensor_type[PWR_SENSOR_NUM] = {		
	VOL_3_3,
	VOL_2_5,
	VOL_1_2,
	VOL_12
};
#endif

DiscreteSensor g_sensor_hs = {
	.baseinfo.event_type = EVENT_TYPE_SENSOR_SPECIFIC,
	.baseinfo.type	= IPMI_SENSOR_TYPE_HS,
	.baseinfo.number = SENSOR_NUMBER_HANDLE_SWITCH,
	.baseinfo.eventmask = HS_EVENT_ASSERT_MASK,
	.entity_id = ENTITY_ID_IPMC,
	.entity_instance = ENTITY_INSTANCE,
	.name = "FRU 0 Hot Swap",
};


void get_vol_lieaner_factor(ThresholdSensor *sensor)
{
	switch(sensor->vol_type){
		case VOL_1:
		case VOL_1_2:
		case VOL_1_5:
			sensor->M = 8;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		case VOL_2_5:
			sensor->M = 12;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		case VOL_3_3:
			sensor->M = 15;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		case VOL_5:
			sensor->M = 24;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		case VOL_12:
			sensor->M = 55;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		case VOL_48:
			sensor->M = 315;
			sensor->B = 0;
			sensor->Bexp = 0;
			sensor->Rexp = -3;
			break;
		default:
			sensor->M = 200;
			sensor->B = 300;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
#if 0
		case VOL_3_3:
			sensor->M = 8;
			sensor->B = 23;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
		case VOL_5:
			sensor->M = 8;
			sensor->B = 40;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
		case VOL_12:
			sensor->M = 16;
			sensor->B = 100;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
		case VOL_48:
			sensor->M = 200;
			sensor->B = 300;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
		default:
			sensor->M = 200;
			sensor->B = 300;
			sensor->Bexp = 2;
			sensor->Rexp = -3;
			break;
#endif
	}
}


void get_vol_threshold(ThresholdSensor *sensor)
{
	switch(sensor->vol_type){
		case VOL_1:
			sensor->u_non_recoverable_threshold = 1.08;
			sensor->u_critical_threshold = 1.05;
			sensor->u_non_critical_threshold = 1.040;
			sensor->l_non_critical_threshold = 0.960;
			sensor->l_non_recoverable_threshold = 0.950 ;
			sensor->l_critical_threshold = 0.930;
			sensor->hys_positive = 0.01;
			sensor->hys_negative = 0.01;
			break;
		case VOL_1_2:
			sensor->u_non_recoverable_threshold = 1.30;
			sensor->u_critical_threshold = 1.24;
			sensor->u_non_critical_threshold = 1.23;
			sensor->l_non_critical_threshold = 1.17;
			sensor->l_non_recoverable_threshold = 1.16;
			sensor->l_critical_threshold = 1.10;
			sensor->hys_positive = 0.01;
			sensor->hys_negative = 0.01;
			break;
		case VOL_1_5:
			sensor->u_non_recoverable_threshold = 1.62;
			sensor->u_critical_threshold = 1.57;
			sensor->u_non_critical_threshold = 1.56;
			sensor->l_non_critical_threshold = 1.44;
			sensor->l_non_recoverable_threshold = 1.43;
			sensor->l_critical_threshold = 1.38;
			sensor->hys_positive = 0.01;
			sensor->hys_negative = 0.01;
			break;
		case VOL_2_5:
			sensor->u_non_recoverable_threshold = 2.7;
			sensor->u_critical_threshold = 2.63;
			sensor->u_non_critical_threshold = 2.6;
			sensor->l_non_critical_threshold = 2.39;
			sensor->l_non_recoverable_threshold = 2.37;
			sensor->l_critical_threshold = 2.35;
			sensor->hys_positive = 0.01;
			sensor->hys_negative = 0.01;
			break;
		case VOL_3_3:
			sensor->u_non_recoverable_threshold = 3.5;
			sensor->u_critical_threshold = 3.46;
			sensor->u_non_critical_threshold = 3.43;
			sensor->l_non_critical_threshold = 3.15;
			sensor->l_non_recoverable_threshold = 3.11;
			sensor->l_critical_threshold = 3.08;
			sensor->hys_positive = 0.02;
			sensor->hys_negative = 0.02;
			break;
		case VOL_5:
			sensor->u_non_recoverable_threshold = 5.35;
			sensor->u_critical_threshold = 5.25;
			sensor->u_non_critical_threshold = 5.2;
			sensor->l_non_critical_threshold = 4.8;
			sensor->l_non_recoverable_threshold = 4.75;
			sensor->l_critical_threshold = 4.65;
			sensor->hys_positive = 0.02;
			sensor->hys_negative = 0.02;
			break;
		case VOL_12:
			sensor->u_non_recoverable_threshold = 13.0;
			sensor->u_critical_threshold = 12.60;
			sensor->u_non_critical_threshold = 12.50;
			sensor->l_non_critical_threshold = 11.5;
			sensor->l_non_recoverable_threshold = 11.4;
			sensor->l_critical_threshold = 11.0;
			sensor->hys_positive = 0.05;
			sensor->hys_negative = 0.05;
			break;
		case VOL_48:
			sensor->u_non_recoverable_threshold = 76;
			sensor->u_critical_threshold = 75;
			sensor->u_non_critical_threshold = 72;
			sensor->l_non_critical_threshold = 39;
			sensor->l_non_recoverable_threshold = 32;
			sensor->l_critical_threshold = 31;
			sensor->hys_positive = 0;
			sensor->hys_negative = 0;
			break;
		default:
			UART0_SendStr("Voltage type not found!\n");
			break;
	}
}


void temp_sensor_init(void)
{
	uint8 i = 0;
	char number[4] = {0};
	for(i = 0;i < TEMP_SENSOR_NUM;i++){
		g_sensor_temp[i].baseinfo.event_type = EVENT_TYPE_THRESHOLD;		
		g_sensor_temp[i].baseinfo.type = IPMI_SENSOR_TYPE_TEMPERATURE;	
		g_sensor_temp[i].baseinfo.number = SENSOR_NUMBER_TEMPERATURE0+i;		//temp sensor id should be successive
		g_sensor_temp[i].baseinfo.eventmask = 0;		//not defined here
		
		g_sensor_temp[i].entity_id = ENTITY_ID_IPMC;
		g_sensor_temp[i].entity_instance = ENTITY_INSTANCE;
		g_sensor_temp[i].u_non_recoverable_threshold = TERMOERATURE_U_NONE_RECOVERABLE;
		g_sensor_temp[i].l_non_recoverable_threshold = TERMOERATURE_L_NONE_RECOVERABLE;
		g_sensor_temp[i].u_critical_threshold = TERMOERATURE_U_CRITICAL;
		g_sensor_temp[i].l_critical_threshold = TERMOERATURE_L_CRITICAL;
		g_sensor_temp[i].u_non_critical_threshold = TERMOERATURE_U_NONE_CRITICAL;
		g_sensor_temp[i].l_non_critical_threshold = TERMOERATURE_L_NONE_CRITICAL;
		g_sensor_temp[i].hys_positive = TERMOERATURE_HYS_P;		//threshold upper and lower region that do not trig event
		g_sensor_temp[i].hys_positive = TERMOERATURE_HYS_N;		
		g_sensor_temp[i].data_real = 0;
		g_sensor_temp[i].data_encode = 0;
		g_sensor_temp[i].B = -200;
		g_sensor_temp[i].M = 6;
		g_sensor_temp[i].Rexp = -1;
		g_sensor_temp[i].Bexp = 0;		//Temperature = (M*x+B*10^Bexp)*10^Rexp
		g_sensor_temp[i].unitcode = SENSOR_UNIT_TEMP;	//1,degree C;
		strcpy(g_sensor_temp[i].name ,"Temp ");
		if(i < 100) {		
			number[0] = 0x30 + (i /10);
			number[1] =  0x30 + (i % 10);
			number[2] = '\0';
		}
		strcat(g_sensor_temp[i].name,number);
		
		g_sensor_temp[i].sdr.type = IPMI_SDR_FORMAT_FULL_SENSOR_RECORD;		//full sensor record
		g_sensor_temp[i].sdr.id = get_sdr_id(g_sensor_temp[i].baseinfo.number);
	}
}

void vol_sensor_init(void)
{
	uint8 i = 0;
	char number[4] = {0};
	for(i = 0;i < PWR_SENSOR_NUM;i++){
		g_sensor_vol[i].baseinfo.event_type = EVENT_TYPE_THRESHOLD;		
		g_sensor_vol[i].baseinfo.type = IPMI_SENSOR_TYPE_VOLTAGE;	
		g_sensor_vol[i].baseinfo.number = SENSOR_NUMBER_VOLTAGE0+i;		//temp sensor id should be successive
		g_sensor_vol[i].baseinfo.eventmask = 0;		//not defined here
		
		g_sensor_vol[i].entity_id = ENTITY_ID_IPMC;
		g_sensor_vol[i].entity_instance = ENTITY_INSTANCE;
		g_sensor_vol[i].vol_type = g_vol_sensor_type[i];
		g_sensor_vol[i].data_real = 0;
		g_sensor_vol[i].data_encode = 0;
		get_vol_lieaner_factor(&g_sensor_vol[i]);
		get_vol_threshold(&g_sensor_vol[i]);
		g_sensor_vol[i].unitcode = SENSOR_UNIT_VOLTAGE;	//1,degree C;
		strcpy(g_sensor_vol[i].name ,"Volt ");
		if(i < 100)
		{
			number[0] = 0x30 + (i /10);
			number[1] =  0x30 + (i % 10);
			number[2] = '\0';
		}
		strcat(g_sensor_vol[i].name,number);
		
		g_sensor_vol[i].sdr.type = IPMI_SDR_FORMAT_FULL_SENSOR_RECORD;		//full sensor record
		g_sensor_vol[i].sdr.id = get_sdr_id(g_sensor_vol[i].baseinfo.number);
	}
}

/*
function: check whether the  sensor_num is legal 
return value: the sensor group which the sensor belongs
*/

S_Type sensor_check(uint8 sensor_num)
{
	if( (sensor_num >= SENSOR_NUMBER_TEMPERATURE0) && 
					(sensor_num <= SENSOR_NUMBER_TEMPERATURE0 + TEMP_SENSOR_NUM) ){
		return S_Type_TEMP;
	}
	else if((sensor_num >= SENSOR_NUMBER_VOLTAGE0) && 
			(sensor_num <= SENSOR_NUMBER_VOLTAGE0 + PWR_SENSOR_NUM) ){
		return S_Type_PWR;
	}
	else if(sensor_num == SENSOR_NUMBER_HANDLE_SWITCH)
		return S_Type_HS;
	
	return S_Type_None;
}


/*
function: get sensor index for g_sensor_temp[] from sensor_num  
return value: sensor pointor,or NULL if sensor not found
*/
ThresholdSensor* get_sensor_th(uint8 sensor_num,S_Type s_type)
{
	ThresholdSensor *sensor_ptr = NULL;
	uint8 sensor_index = 0;
		
	if(S_Type_TEMP ==  s_type){
		sensor_index = sensor_num - SENSOR_NUMBER_TEMPERATURE0;
		sensor_ptr = &g_sensor_temp[sensor_index];
	}
	else if(S_Type_PWR == s_type ){
		sensor_index = sensor_num - SENSOR_NUMBER_VOLTAGE0;
		sensor_ptr = &g_sensor_vol[sensor_index];
	}
	return sensor_ptr;
}


DiscreteSensor* get_sensor_dic(uint8 sensor_num,S_Type s_type)
{
	if(SENSOR_NUMBER_HANDLE_SWITCH == sensor_num )
		return &g_sensor_hs;
	else
		return NULL;
}


/*
function: get SDR id for g_sensor_temp[] from sensor_num  
return value: SDR id ,or 0xff if sensor not found
*/
uint8 get_sdr_id(uint8 sensor_num)
{
	uint8 sensor_index = 0;
	uint8 id = 0xff;
	S_Type s_type = sensor_check(sensor_num);
	switch(s_type){
		case S_Type_HS:
			id = FRU_HOTSWAP_RECORD_ID;
			break;
		case S_Type_TEMP:
			sensor_index = sensor_num - SENSOR_NUMBER_TEMPERATURE0;
			id = FRU_TEMP0_RECORD_ID + sensor_index;
			break;
		case S_Type_PWR:
			sensor_index = sensor_num - SENSOR_NUMBER_VOLTAGE0;
			id = FRU_PWR0_RECORD_ID + sensor_index;
			break;
		case S_Type_None:			
			break;
	}	
	return id;
}


/*
function: calculate the 8bit code from sensor data in unit; y = (M*x + B) * 10^Rexp;
		  Bexp given as 0;
return value: the 8bit code to be transferred
*/
uint8 TH_sensor_datacode_gen(ThresholdSensor *sensor,float data)
{
	uint8 ret = 0;
	float data_raw = 0;
	data_raw = ( data / (pow(10,sensor->Rexp)) - sensor->B * (pow(10, sensor->Bexp)) ) / sensor->M;
	ret = floor(data_raw);
	UART0_Printf("***temp data:%f\n",data);
	UART0_Printf("***coded data:%d \n", ret);
	return ret;
}


int8 ipmi_get_sensor_hys(uint8 sensor_num,uint8 *payload,uint8 *payload_len)
{
	S_Type s_type = sensor_check(sensor_num);
	uint8 sdr_id = 0;
	int ret = 0;
	switch(s_type){
		case S_Type_None:
			UART0_SendStr("Sensor not found!\n");
			payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
			*payload_len = 1;
			ret = -1;
		break;
		case S_Type_HS:
			UART0_SendStr("hs do not support hys!\n");
			payload[0] = IPMI_COMPLETE_CODE_COMMAND_INVALID;
			*payload_len = 1;
			ret = -1;
		break;
		case S_Type_TEMP:
		case S_Type_PWR:
			sdr_id = get_sdr_id(sensor_num);
			if(sdr_id == 0xff){
				UART0_SendStr("Sensor not found!\n");
				payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
				*payload_len = 1;
				ret = -1;
			}
			else{
				payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
				payload[1] = sdr_info[sdr_id][SDR1_OFFSET_HYS_P];
				payload[2] = sdr_info[sdr_id][SDR1_OFFSET_HYS_N];
//				payload[2] = TH_sensor_datacode_gen(sensor_ptr,sensor_ptr->hys_positive);
//				payload[3] = TH_sensor_datacode_gen(sensor_ptr,sensor_ptr->hys_negative);
				*payload_len = 3;
			}
		break;
	}	
	return ret;
}

int8 ipmi_get_threshold(uint8 sensor_num,uint8 *payload,uint8 *payload_len)
{
	S_Type s_type = sensor_check(sensor_num);
	uint8 sdr_id = 0;
	int ret = 0;
	switch(s_type){
		case S_Type_None:
			UART0_SendStr("Sensor not found!\n");
			payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
			*payload_len = 1;
			ret = -1;
		break;
		case S_Type_HS:
			UART0_SendStr("hs do not support hys!\n");
			payload[0] = IPMI_COMPLETE_CODE_COMMAND_INVALID;
			*payload_len = 1;
			ret = -1;
		break;
		case S_Type_TEMP:
		case S_Type_PWR:
			sdr_id = get_sdr_id(sensor_num);
			if(sdr_id == 0xff){
				UART0_SendStr("Sensor not found!\n");
				payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
				*payload_len = 1;
				ret = -1;
			}
			else{
				payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
				payload[1] = 0x3f;
				payload[2] = sdr_info[sdr_id][SDR1_OFFSET_LOWER_NON_CRITICAL];
				payload[3] = sdr_info[sdr_id][SDR1_OFFSET_LOWER_CRITICAL];
				payload[4] = sdr_info[sdr_id][SDR1_OFFSET_LOWER_NON_RECOVER];
				payload[5] = sdr_info[sdr_id][SDR1_OFFSET_UPPER_NON_CRITICAL];
				payload[6] = sdr_info[sdr_id][SDR1_OFFSET_UPPER_CRITICAL];
				payload[7] = sdr_info[sdr_id][SDR1_OFFSET_UPPER_NON_RECOVER];
				*payload_len = 8;	
			}
		break;
	}	
	return ret;
}

int8 ipmi_get_event_en(uint8 sensor_num,uint8 *payload,uint8 *payload_len)
{
	S_Type s_type = sensor_check(sensor_num) ;
	if(S_Type_None == s_type ){
		UART0_SendStr("Sensor not found!\n");
		payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
		*payload_len = 1;
		return -1;
	}
	else if((S_Type_TEMP == s_type ) ||(S_Type_PWR == s_type ) ) {
		payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
		payload[1] = 0xc0;
		payload[2] = THRESHOLD_EVENT_ASSERT_MASK & 0xff;
		payload[3] = (THRESHOLD_EVENT_ASSERT_MASK & 0xf00) >> 8;
		*payload_len = 4;
	}
	else if((S_Type_HS == s_type ) ) {
		payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
		payload[1] = 0xc0;
		payload[2] = HS_EVENT_ASSERT_MASK;
		*payload_len = 3;
	}
	return 0;
}


int8 ipmi_get_sensor_reading(uint8 sensor_num,uint8 *payload,uint8 *payload_len)
{
	ThresholdSensor* sensor_ptr = NULL;
	S_Type s_type = sensor_check(sensor_num);
	int ret = 0;
	switch(s_type){
		case S_Type_None:
			UART0_SendStr("Sensor not found!\n");
			payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
			*payload_len = 1;
			ret = -1;
			break;
		case S_Type_HS:
			payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
			payload[1] = 0x0;
			payload[2] = 0xC0;
			payload[3] = (1 << g_boardinfo.hss.CurState);
			payload[4] = 0x80;	//discrete sensors must have this byte
			*payload_len = 5;
			break;
		case S_Type_TEMP:
		case S_Type_PWR:
			sensor_ptr = get_sensor_th(sensor_num,s_type);
			if(sensor_ptr == NULL){
				UART0_SendStr("Sensor not found!\n");
				payload[0] = IPMI_COMPLETE_CODE_SENSOR_NOPRES;
				*payload_len = 1;
				ret = -1;
				break;
			}				
			payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
			payload[1] = sensor_ptr->data_encode;
			payload[2] = 0xc0;
			payload[3] = 0;
			*payload_len = 4;
			break;
	}	
	return ret;
}

/*********************************************************************************************************
** Function name:       ipmi_sensor_init
** Descriptions:        init temperature ,power... sensors and related sdr
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void ipmi_sensor_init(void)
{
	temp_sensor_init();
	vol_sensor_init();
	sdr_generate();
}

/*********************************************************************************************************
** Function name:       IPMI_Monitor_TASK
** Descriptions:        Monitor board voltage and temperature
** input parameters:    None
** output parameters:   None
*********************************************************************************************************/
void IPMI_Sensor_TASK (void *pdata)
{
	
    uint8  err,i;
    uint16 ADC_Value[ADC_CHANNEL_NUM];
    uint8 channel;
//    uint8	tpcount;
//    uint8 wrbuf[300];//write
//    uint8 rebuf[300];//read
 
	/* Expand i2c init and Temprature Sensor init */
    exi2cInit();
    /* ADC init */
    ADC_Init();
    memset(ADC_Value, 0, sizeof(ADC_Value));
	Temp_Sensor_Init();

/* EEPROM for test */
#if 0
    if(eeprom_m24xx_write(EEPROM_24XX08,10,0,wrbuf,20)==I2C_NO_ERR)//write 300 numbers to address 0x0a
    {
        if(eeprom_m24xx_read(EEPROM_24XX08,10,0,rebuf,20)==I2C_NO_ERR) //read 300 numbers from address 0x0a to rebuf
        {
            for(i=0; i < 20; i++){
                UART0_Printf("%x ",i,rebuf[i]);
            }
        }
    }
    else
    {
        UART0_SendStr("Read EEPROM ERROR!\n");
    }
#endif
	pdata = pdata;
	UART0_SendStr("IPMI_Monitor: Task create!\n");
    while(1) {
		/* Read temperature */
        PCA9665_Read_Sensor_Temp(g_sensor_temp);
        for (i = 0; i < TEMP_SENSOR_NUM; i++) {
        	UART0_Printf("Temp[%d]: %f¡æ\n", i, g_sensor_temp[i].data_real);
        }
		/* Read Voltage */
        err = Read_ADC_Value(ADC_Value, &channel);
		if(err)
			UART0_Printf("read ADC_Value[%d] error!\n",i);
        for(i=0; i < ADC_CHANNEL_NUM; i++){
			g_sensor_vol[i].data_real = ADC_Value[i] / 1000.0;
			g_sensor_vol[i].data_encode = TH_sensor_datacode_gen(&g_sensor_vol[i],g_sensor_vol[i].data_real);
            UART0_Printf("ADC_Value[%d]:%d\n",i,ADC_Value[i]);
        }
        OSTimeDlyHMSM(0, 0, 10, 0);
    }
}




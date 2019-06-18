/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           sensor_temp.c
** Last modified Date:  2019-04-16
** Last Version:        1.0
** Descriptions:        FRU sensor drivers 
**--------------------------------------------------------------------------------------------------------
** Created by:          Xingjingfeng
** Created date:        2019-04-16
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
#include "app_cfg.h"
#include "exi2c.h"
#include "adc.h"
#include "uart.h"
#include "eeprom.h"
#include "ipmi_defs.h"
#include "sensor_temp.h"
#include "boardinfo.h"

extern void ADC_Init(void);
extern uint8 Read_ADC_Value(uint16 * ADC_Val, uint8 * channel);
extern void ADC_Exception(void);

/*********************************************************************************************************
** Function name:           temp_convert
** Descriptions:			convert fraction in bits to persent 
** Input parameters:        lsbdata         :temperature date which ti convert
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void temp_convert(uint8 *lsbdata)
{
	uint8 tmpdata = 0;
	uint8 tmpdata1 = 0;
	uint8 i;

	*lsbdata &= 0xC0;

	for (i = 1; i <= 2; i++) {
		tmpdata1 = *lsbdata;
		if((tmpdata1 & 0x80) == 0x80) {
			tmpdata += 50/i;
		}else {
			tmpdata += 0;
		}
		*lsbdata = (*lsbdata << 1);
	}
	*lsbdata = tmpdata;
}

/*********************************************************************************************************
** Function name:           temp_read
** Descriptions:
** Input parameters:        tempaddr  :temperature sensor 7bit address, don't need offset
**                          tempreg   :temperature sensor register address
**                          dbuf      :read data buffer
**                          dlen      :read data length
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int temp_read(uint8 tempaddr, uint8 tempreg, uint8 *dbuf, uint8 dlen)
{
	uint8 headbuf[4];
	uint8 headlen;
	
	if (dbuf == NULL || dlen == 0) {
		return -1;
	}
	UART0_Printf("Rtemp:0x%02x\n", tempaddr);
	
	headbuf[0] = (tempaddr << 1) | 1;
	headbuf[1] = tempreg;
	headlen = 2;
	exi2cRead(&headbuf[0], headlen, dbuf, dlen);
	
	return 0;
}

/*********************************************************************************************************
** Function name:           temp_write
** Descriptions:
** Input parameters:        tempaddr  :temperature sensor 7bit address, don't need offset
**                          tempreg   :temperature sensor register address
**                          dbuf      :write data buffer
**                          dlen      :write data length
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int temp_write(uint8 tempaddr, uint8 tempreg, uint8 *dbuf, uint8 dlen)
{
	uint8 headbuf[4];
	uint8 headlen;
	
	if (dbuf == NULL || dlen == 0) {
		return -1;
	}
	
	headbuf[0] = (tempaddr << 1) & 0xfe;
	headbuf[1] = tempreg;
	headlen = 2;
	exi2cWrite(&headbuf[0], headlen, dbuf, dlen);
	
	return 0;
}

/*********************************************************************************************************
** Function name:           Temp_Sensor_LM95231_Init
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int Temp_Sensor_LM95231_Init(void)
{
	uint8 databuf[8] = {0};
	
	// LM95231_SENSOR MPCB Temperature Sensor
	/* LM95231 Addr is 0101011b=0x2b, sla+r=0x57,sla+w=0x56*/

	/*	LM95231 Manufacturer ID reg 0xfe */
	temp_read(0x2b, 0xfe, databuf, 1);
	DEBUG("LM95231 Manufac is %02x\n", databuf[0]);

	/*	LM95231 Revision ID reg 0xff */
	temp_read(0x2b, 0xff, databuf, 1);
	DEBUG("LM95231 Revision is %02x\n", databuf[0]);

	/*	LM95231 Configuration reg 0x03 */
	databuf[0] = 0x40;
	temp_write(0x2b, 0x03, &databuf[0], 1);

	/*	LM95231 Remote Diode Filter Control reg 0x06 */
	databuf[0] = 0x05;
	temp_write(0x2b, 0x06, &databuf[0], 1);

	/*	LM95231 Remote Diode TruTherm Mode Control reg 0x07*/
	databuf[0] = 0x77;
	temp_write(0x2b, 0x07, &databuf[0], 1);

	/*	LM95231 Remote Diode Model Type Select reg 0x30*/
	databuf[0] = 0x05;
	temp_write(0x2b, 0x30, &databuf[0], 1);
	
	return 0;
}

/*********************************************************************************************************
** Function name:           Temp_Sensor_TCN75_Init
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int Temp_Sensor_TCN75_Init(uint8 addr, uint8 hyster, uint8 limit)
{
	uint8 databuf[8] = {0};
	
	// TCN75AVOA_SENSOR temperature
	/* pointer sensor config reg addr is 0x01 */
	databuf[0] = 0xA1;	/* configuration data is 0xA1 */
	temp_write(addr, 0x01, &databuf[0], 1);

	/* pointer hysteresis reg addr is 0x02 */
	databuf[0] = hyster;	/* 0x4b: hysteresis data 75¡æ */
	databuf[1] = 0x00;
	temp_write(addr, 0x02, &databuf[0], 2);

	/* pointer limit-set reg addr is 0x03 */
	databuf[0] = limit;	/* limit-set 80¡æ */
	databuf[1] = 0x00;
	temp_write(addr, 0x03, &databuf[0], 2);
	
	return 0;
}

/*********************************************************************************************************
** Function name:           Temp_Sensor_Init
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void Temp_Sensor_Init (void)
{
	
#if (BOARD_TYPE == BOARD_TYPE_MPCB_V2) || (BOARD_TYPE == BOARD_TYPE_MPCB_V3)
	Temp_Sensor_LM95231_Init();
#elif (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) || \
	  (BOARD_TYPE == BOARD_TYPE_EIPB_V2) || (BOARD_TYPE == BOARD_TYPE_EIPB_V3) || \
	  (BOARD_TYPE == BOARD_TYPE_XSCB_V2)
	// TCN75AVOA_SENSOR temperature
	/* MACB have two sensors,
	 * power sensor addr is 1001000b=0x48,SLA+R=0x91,SLA+W=0x90
	 * 5464 sensor addr is 1001001b=0x49,SLA+R=0x93,SLA+W=0x92
	 */
	Temp_Sensor_TCN75_Init(0x48, 75, 80);
	Temp_Sensor_TCN75_Init(0x49, 75, 80);
	
#endif
}

void temp_sensor_data_fill(TempData *tp,ThresholdSensor *sensor)
{
	uint32 tmp = 100 * tp->temp_integer + tp->temp_fraction;
	float data = tmp / 100.0;
	
	sensor->data_real = data;
    sensor->data_encode =  TH_sensor_datacode_gen(sensor,data);	
}

/*********************************************************************************************************
** Function name:           Read_MPCB_Temp_Data
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint8 Read_MPCB_Temp_Data(TempData *tp, uint8 *tpcount)
{
	uint8 databuf[4];
	
	if (!tp || !tpcount) 
		return 1;
	
    /* LM95231 one-shot reg 0x0f */
    databuf[0] = 0x01;
    temp_write(0x2b, 0x0f, databuf, 1);
    
    OSTimeDlyHMSM(0, 0, 0, 100);  /* delay 100ms wait to conversion */
    
    /* LM95231 local MSB temp reg 0x10 */
    temp_read(0x2b, 0x10, databuf, 1);
    tp[0].temp_integer =  databuf[0];
    /* LM95231 local LSB temp reg 0x20 */
    temp_read(0x2b, 0x20, databuf, 1);
    temp_convert(&databuf[0]);
    tp[0].temp_fraction = databuf[0];
    
    /* LM95231 remote1 MSB temp reg 0x11 */
    temp_read(0x2b, 0x11, databuf, 1);
    tp[1].temp_integer =  databuf[0] - 35;
    /* LM95231 remote1 LSB temp reg 0x21 */
    temp_read(0x2b, 0x21, databuf, 1);
    temp_convert(&databuf[0]);
    tp[1].temp_fraction = databuf[0];
    
    /* LM95231 remote2 MSB temp reg 0x12 */
    temp_read(0x2b, 0x12, databuf, 1);
    tp[2].temp_integer =  databuf[0] - 35;
    /* LM95231 remote1 LSB temp reg 0x22 */
    temp_read(0x2b, 0x22, databuf, 1);
    temp_convert(&databuf[0]);
    tp[2].temp_fraction = databuf[0];
    
    *tpcount = 3;
    return 0;
}

/*********************************************************************************************************
** Function name:           Read_MACB_Temp_Data
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint8 Read_MACB_Temp_Data(ThresholdSensor *tp)
{
    uint8 databuf[4];
	TempData temp_val;
	/*
  	 * MACB have two sensors,
	 * power sensor addr is 1001000b=0x48,SLA+R=0x91,SLA+W=0x90
 	 * 5464 sensor addr is 1001001b=0x49,SLA+R=0x93,SLA+W=0x92
 	*/
    /* pointer sensor config reg addr is 0x00 */
    if(temp_read(0x48, 0x00, databuf, 2))
		return 0xff;
    temp_convert(&databuf[1]);
	temp_val.temp_integer = databuf[0];
	temp_val.temp_fraction = databuf[1];
	temp_sensor_data_fill(&temp_val,&tp[0]);
    
    /* pointer sensor config reg addr is 0x00 */
    if(temp_read(0x49, 0x00, databuf, 2))
		return 0xff;
    temp_convert(&databuf[1]);
	temp_val.temp_integer = databuf[0];
	temp_val.temp_fraction = databuf[1];
	temp_sensor_data_fill(&temp_val,&tp[1]);
	
    return SENSOR_OK;
}

/*********************************************************************************************************
** Function name:           Read_XSCB_Temp_Data
** Descriptions:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint8 Read_XSCB_Temp_Data(ThresholdSensor *tp)
{
    uint8 databuf[4];
    uint8 i = 0;
	TempData temp_val;
	/*
  	 * XSCB have two TCN75 sensors and 4 tmp421 sensors,
	 * power sensor addr is 1001000b=0x48,SLA+R=0x91,SLA+W=0x90
 	 * 5464 sensor addr is 1001001b=0x49,SLA+R=0x93,SLA+W=0x92
 	 */
    /* pointer sensor config reg addr is 0x00 */
    temp_read(0x48, 0x00, databuf, 2);
    temp_convert(&databuf[1]);
	temp_val.temp_integer = databuf[0];
	temp_val.temp_fraction = databuf[1];
	temp_sensor_data_fill(&temp_val,&tp[0]);

    /* pointer sensor config reg addr is 0x00 */
    temp_read(0x49, 0x00, databuf, 2);
    temp_convert(&databuf[1]);
	temp_val.temp_integer = databuf[0];
	temp_val.temp_fraction = databuf[1];
	temp_sensor_data_fill(&temp_val,&tp[1]);

	/* tmp421 addr 0x4c,0x4d,0x4e,0x4f */
	for(i = 0; i < 4; i++)
	{
		/* local temp reg addr is 0x00 */
    	temp_read(0x4c + i, 0x00, databuf, 2);
    	temp_convert(&databuf[1]);
		temp_val.temp_integer = databuf[0];
		temp_val.temp_fraction = databuf[1];
		temp_sensor_data_fill(&temp_val,&tp[2*i+2]);
    	
    	/* remote temp reg addr is 0x01 */
    	temp_read(0x4c + i, 0x01, databuf, 2);
    	temp_convert(&databuf[1]);
		temp_val.temp_integer = databuf[0];
		temp_val.temp_fraction = databuf[1];
		temp_sensor_data_fill(&temp_val,&tp[2*i+3]);
	}
	
    return SENSOR_OK;
}


/*********************************************************************************************************
** Function name:           PCA9665_Read_Sensor_Temp
** Descriptions:            ¶Á´«¸ÐÆ÷ÎÂ¶È
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void PCA9665_Read_Sensor_Temp (ThresholdSensor *tp)
{
#if (BOARD_TYPE == BOARD_TYPE_MPCB_V2) || (BOARD_TYPE == BOARD_TYPE_MPCB_V3)
	Read_MPCB_Temp_Data(tp, tpcount);	
#elif (BOARD_TYPE == BOARD_TYPE_MACB_V2) || (BOARD_TYPE == BOARD_TYPE_MACB_V3) || \
	  (BOARD_TYPE == BOARD_TYPE_EIPB_V2) || (BOARD_TYPE == BOARD_TYPE_EIPB_V3)
	   
	Read_MACB_Temp_Data(tp);
#elif (BOARD_TYPE == BOARD_TYPE_XSCB_V2)	
	Read_XSCB_Temp_Data(tp);
#endif
}

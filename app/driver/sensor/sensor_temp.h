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
#ifndef __SENSOR_TEMP_H
#define __SENSOR_TEMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "ipmi_sensor.h"

#define SENSOR_OK       0x01
#define SENSOR_ERROR    0x00

void Temp_Sensor_Init (void);
void PCA9665_Read_Sensor_Temp (ThresholdSensor *tp);

#endif


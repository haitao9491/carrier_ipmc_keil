/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-device.c
** Last modified Date:  2019-03-14
** Last Version:        1.0
** Descriptions:        device infomation
**--------------------------------------------------------------------------------------------------------
** Created by:          xingjingfeng
** Created date:        2019-03-14
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

#include "ipmi_device.h"


//uint8 deviceid_info[DEVICEID_LEN] = {
//	DEVICE_ID, DEVICE_PROVIDES_SDRS|DEVICE_REVISION, DEVICE_NORMAL_OPERATION|MAJOR_FIRMWARE_REVISION,
//	MINOR_FIRMWARE_REVISION, IPMI_VERSION,
//	BRIDGE|IPMB_EVENT_GENERATOR|IPMB_EVENT_RECEIVER|FRU_INVENTORY_DEVICE|SDR_REPOSITORY_DEVICE|SENSOR_DEVICE,
//	MANUFACTURER_ID1, MANUFACTURER_ID2, MANUFACTURER_ID3,
//	PRODUCT_ID1, PRODUCT_ID2
//};
uint8 deviceid_info[DEVICEID_LEN] = {
	DEVICE_ID, DEVICE_PROVIDES_SDRS|DEVICE_REVISION, DEVICE_NORMAL_OPERATION|MAJOR_FIRMWARE_REVISION,
	MINOR_FIRMWARE_REVISION, IPMI_VERSION,
	IPMB_EVENT_GENERATOR|FRU_INVENTORY_DEVICE|SENSOR_DEVICE,
	MANUFACTURER_ID1, MANUFACTURER_ID2, MANUFACTURER_ID3,
	PRODUCT_ID1, PRODUCT_ID2,4,0,0,0
};



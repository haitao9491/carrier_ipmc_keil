/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_device.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI NetFn and CMDs
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-07-01
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
#ifndef __IPMI_DEVICE_H
#define __IPMI_DEVICE_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
  Device information macri define
 */
#define DEVICE_ID               0x86
/* Device Revision */
// bit 7 valid
#define DEVICE_PROVIDES_SDRS    0x80
#define DEVICE_PROVIDES_NO_SDRS 0x00
// bit 0-3 valid
#define DEVICE_REVISION         0x02
/* Firmware Revision 1 */
// Device available:bit 7 valid
#define DEVICE_NORMAL_OPERATION 0x00
#define DEVICE_FIRMWARE         0x80
// Major Firmware Revision,binary encoded:bit 0-6 valid
#define MAJOR_FIRMWARE_REVISION 0x02
/* Firmware Revision 2 */
//Minor Firmware Revision. BCD encoded
#define MINOR_FIRMWARE_REVISION 0x10
/* IPMI Version. BCD encoded. 02h for implementations that provide IPMI v2.0 */
#define IPMI_VERSION            0x51
/* Additional Device Support */
#define CHASSIS_DEVICE          0x80
#define BRIDGE                  0x40
#define IPMB_EVENT_GENERATOR    0x20
#define IPMB_EVENT_RECEIVER     0x10
#define FRU_INVENTORY_DEVICE    0x08
#define SEL_DEVICE              0x04
#define SDR_REPOSITORY_DEVICE   0x02
#define SENSOR_DEVICE           0x01
/* Manufacturer ID,LS Byte first.The manufacturer ID is a 20-bit value.Most significant four bits = reserved (0000b).
    000000h = unspecified. 0FFFFFh = reserved. This value is binary encoded */
#define MANUFACTURER_ID         5555 //hex 15b3h
//#define MANUFACTURER_ID1        0x32
//#define MANUFACTURER_ID2        0x5d
#define MANUFACTURER_ID1        0x5a
#define MANUFACTURER_ID2        0x31
#define MANUFACTURER_ID3        0x00
/*Product ID, LS Byte first. 0000h = unspecified. FFFFh = reserved. */
#define PRODUCT_ID              2222 //hex 08aeh
#define PRODUCT_ID1             0x05
#define PRODUCT_ID2             0x42

#define DEVICEID_LEN            15



extern uint8 deviceid_info[DEVICEID_LEN];

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_DEVICE_H */



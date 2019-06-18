/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi_defs.h
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
#ifndef __IPMI_DEFS_H
#define __IPMI_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * NetFn definition
 */
#define IPMI_NETFN_CHASSIS_RQ       0x00
#define IPMI_NETFN_CHASSIS_RS       0x01
#define IPMI_NETFN_BRIDGE_RQ        0x02
#define IPMI_NETFN_BRIDGE_RS        0x03
#define IPMI_NETFN_SENSOR_EVENT_RQ  0x04
#define IPMI_NETFN_SENSOR_EVENT_RS  0x05
#define IPMI_NETFN_APP_RQ           0x06
#define IPMI_NETFN_APP_RS           0x07
#define IPMI_NETFN_FIRMWARE_RQ      0x08
#define IPMI_NETFN_FIRMWARE_RS      0x09
#define IPMI_NETFN_STORAGE_RQ       0x0A
#define IPMI_NETFN_STORAGE_RS       0x0B
#define IPMI_NETFN_TRANSPORT_RQ     0x0C
#define IPMI_NETFN_TRANSPORT_RS     0x0D
#define IPMI_NETFN_PICMG_RQ         0x2C
#define IPMI_NETFN_PICMG_RS         0x2C
#define IPMI_NETFN_OEM              0x2E
#define IPMI_NETFN_ISOL             0x34
#define IPMI_NETFN_TSOL             0x30

/*
 * CMD definition
 */

/* SENSOR/EVENT Command */
#define IPMI_SENSOR_EVENT_CMD_SET_EVENT_RECEIVER		0x00
#define IPMI_SENSOR_EVENT_CMD_GET_EVENT_RECEIVER		0x01
#define IPMI_SENSOR_EVENT_CMD_PLATFORM_EVENT			0x02
#define IPMI_SENSOR_EVENT_CMD_GET_DEVICE_SDR_INFO       0x20
#define IPMI_SENSOR_EVENT_CMD_GET_DEVICE_SDR            0x21
#define IPMI_SENSOR_EVENT_CMD_RESERVE_DEVICE_REPOSITORY 0x22
#define IPMI_SENSOR_EVENT_CMD_GET_SENSOR_HYS		    0x25
#define IPMI_SENSOR_EVENT_CMD_GET_SENSOR_THRESHOLD      0x27
#define IPMI_SENSOR_EVENT_CMD_GET_SENSOR_EVENT_EN      	0x29
#define IPMI_SENSOR_EVENT_CMD_GET_SENSOR_READING        0x2d
#define IPMI_SENSOR_EVENT_CMD_REARM_SENSOR_EVENTS       0x2a


/* App Commands */
#define IPMI_APP_CMD_GET_DEVICE_ID                      0x01
#define IPMI_APP_CMD_BROAD_GET_DEVICE_ID                0x01
#define IPMI_APP_CMD_GET_SELF_TEST_RESULTS              0x04
#define IPMI_APP_CMD_GET_MESSAGE                        0x33
#define IPMI_APP_CMD_SEND_MESSAGE                       0x34
#define IPMI_APP_CMD_READ_EVENT_MESSAGE_BUFFER          0x35
#define IPMI_APP_CMD_GET_BT_INTERFACE_CAPABILITIES		0x36

/* Storage Commands */
#define IPMI_STORAGE_CMD_GET_FRU_INVENTORY_AREA_INFO    0x10
#define IPMI_STORAGE_CMD_READ_FRU_DATA                  0x11
#define IPMI_STORAGE_CMD_GET_SDR_REPOSITORY_INFO        0x20
#define IPMI_STORAGE_CMD_RESERVE_SDR_REPOSITORY         0x22
#define IPMI_STORAGE_CMD_GET_SDR                        0x23
#define IPMI_STORAGE_CMD_GET_SEL_TIME					0x48
#define IPMI_STORAGE_CMD_SET_SEL_TIME					0x49

/* PICMG Commands */
#define IPMI_PICMG_CMD_GET_PROPERTIES                       0x00
#define IPMI_PICMG_CMD_GET_ADDRESS_INFO                     0x01
#define IPMI_PICMG_CMD_GET_SHELF_ADDRESS_INFO               0x02
#define IPMI_PICMG_CMD_SET_SHELF_ADDRESS_INFO               0x03
#define IPMI_PICMG_CMD_FRU_CONTROL                          0x04
#define IPMI_PICMG_CMD_GET_FRU_LED_PROPERTIES               0x05
#define IPMI_PICMG_CMD_GET_LED_COLOR_CAPABILITIES           0x06
#define IPMI_PICMG_CMD_SET_FRU_LED_STATE                    0x07
#define IPMI_PICMG_CMD_GET_FRU_LED_STATE                    0x08
#define IPMI_PICMG_CMD_SET_IPMB_STATE                       0x09
#define IPMI_PICMG_CMD_SET_FRU_ACTIVATION_POLICY            0x0a
#define IPMI_PICMG_CMD_GET_FRU_ACTIVATION_POLICY            0x0b
#define IPMI_PICMG_CMD_SET_FRU_ACTIVATION                   0x0c
#define IPMI_PICMG_CMD_GET_DEVICE_LOCATOR_RECORD            0x0d
#define IPMI_PICMG_CMD_SET_PORT_STATE                       0x0e
#define IPMI_PICMG_CMD_GET_PORT_STATE                       0x0f
#define IPMI_PICMG_CMD_COMPUTE_POWER_PROPERTIES             0x10
#define IPMI_PICMG_CMD_SET_POWER_LEVEL                      0x11
#define IPMI_PICMG_CMD_GET_POWER_LEVEL                      0x12
#define IPMI_PICMG_CMD_RENEGOTIATE_POWER                    0x13
#define IPMI_PICMG_CMD_GET_FAN_SPEED_PROPERTIES             0x14
#define IPMI_PICMG_CMD_SET_FAN_LEVEL                        0x15
#define IPMI_PICMG_CMD_GET_FAN_LEVEL                        0x16
#define IPMI_PICMG_CMD_BUSED_RESOURCE                       0x17
#define IPMI_PICMG_CMD_IPMB_LINK_INFO                       0x18
#define IPMI_PICMG_CMD_SET_AMC_PORT_STATE                   0x19
#define IPMI_PICMG_CMD_GET_AMC_PORT_STATE                   0x1a
#define IPMI_PICMG_CMD_SHELF_MANAGER_IPMB_ADDRESS           0x1b
#define IPMI_PICMG_CMD_SET_FAN_POLICY                       0x1c
#define IPMI_PICMG_CMD_GET_FAN_POLICY                       0x1d
#define IPMI_PICMG_CMD_FRU_CONTROL_CAPABILITIES             0x1e
#define IPMI_PICMG_CMD_FRU_INVENTORY_DEVICE_LOCK_CONTROL    0x1f
#define IPMI_PICMG_CMD_FRU_INVENTORY_DEVICE_WRITE           0x20
#define IPMI_PICMG_CMD_GET_SHELF_MANAGER_IP_ADDRESSES       0x21
#define IPMI_PICMG_CMD_SHELF_POWER_ALLOCATION               0x22

/*
 * Completion definition
 */
#define IPMI_COMPLETE_CODE_COMMAND_SUCCESS      0x00
#define IPMI_COMPLETE_CODE_COMMAND_INVALID      0xC1
#define IPMI_COMPLETE_CODE_COMMAND_TIMEOUT      0xC3
#define IPMI_COMPLETE_CODE_COMMAND_UNKNOWN      0xC4
#define IPMI_COMPLETE_CODE_SENSOR_NOPRES	    0xCB
#define IPMI_COMPLETE_CODE_COMMAND_NOEXECUTE    0xD6



#ifdef __cplusplus
}
#endif

#endif/* __IPMI_DEFS_H */


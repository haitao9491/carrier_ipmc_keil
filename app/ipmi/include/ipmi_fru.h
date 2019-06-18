/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-fru.h
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
#ifndef __IPMI_FRU_H
#define __IPMI_FRU_H

#include "config.h"
#include "app_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MPCB_USE
#define AMC_NUM     0x02
#else
#define AMC_NUM     0x04
#endif

/*
  fru power level
 */
#define POWER_TYPE_STEADY_STATE_POWER_DRAW_LEVELS       0x00
#define POWER_TYPE_DESIRED_STEADY_STATE_DRAW_LEVELS     0x01
#define POWER_TYPE_EARLY_POWER_DRAW_LEVELS              0x02
#define POWER_TYPE_DESIRED_EARLY_LEVELS                 0x03

/*
  fru store area type
*/
#define IPMI_FRU_AREA_TYPE_CHASSIS_INFO_AREA                          0
#define IPMI_FRU_AREA_TYPE_BOARD_INFO_AREA                            1
#define IPMI_FRU_AREA_TYPE_PRODUCT_INFO_AREA                          2
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_POWER_SUPPLY_INFORMATION       3
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_DC_OUTPUT                      4
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_DC_LOAD                        5
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_MANAGEMENT_ACCESS_RECORD       6
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_BASE_COMPATABILITY_RECORD      7
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_COMPATABILITY_RECORD  8
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_FIXED_SMBUS_DEVICE_RECORD  9
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_LEGACY_DEVICE_ALERTS      10
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_REMOTE_CONTROL            11
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_DC_OUTPUT            12
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_DC_LOAD              13
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_OEM                           14
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_UNKNOWN                       15
#define IPMI_FRU_AREA_TYPE_RAW_DATA                                  16

#define IPMI_FRU_COMMON_HEADER_FORMAT_VERSION         0x01
#define IPMI_FRU_CHASSIS_INFO_AREA_FORMAT_VERSION     0x01
#define IPMI_FRU_BOARD_INFO_AREA_FORMAT_VERSION       0x01
#define IPMI_FRU_PRODUCT_INFO_AREA_FORMAT_VERSION     0x01
#define IPMI_FRU_MULTIRECORD_AREA_FORMAT_VERSION      0x02

#define IPMI_FRU_MULTIRECORD_AREA_TYPE_POWER_SUPPLY_INFORMATION       0x00
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_DC_OUTPUT                      0x01
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_DC_LOAD                        0x02
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_MANAGEMENT_ACCESS_RECORD       0x03
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_BASE_COMPATIBILITY_RECORD      0x04
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_COMPATIBILITY_RECORD  0x05
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_FIXED_SMBUS_DEVICE_RECORD  0x06
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_LEGACY_DEVICE_ALERTS       0x07
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_REMOTE_CONTROL             0x08
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_DC_OUTPUT             0x09
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_DC_LOAD               0x0A
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MIN                        0xC0
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MAX                        0xFF

#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_BINARY          0x00
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_BCD             0x01
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_SIXBIT_ASCII    0x02
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_LANGUAGE_CODE   0x03
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_MASK            0xC0
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_SHIFT           0x06
#define IPMI_FRU_TYPE_LENGTH_NUMBER_OF_DATA_BYTES_MASK 0x3F
/*
  fru store data
 */
#define FRU_INVENTORY_AREA_SIZE 256
#define FRU_COMMON_HEADER_SIZE  8
#define FRU_BOARD_AREA_OFFSET   FRU_COMMON_HEADER_SIZE
#define FRU_BOARD_AREA_SIZE     64
#define FRU_PRODUCT_AREA_OFFSET (FRU_BOARD_AREA_OFFSET + FRU_BOARD_AREA_SIZE)
#define FRU_PRODUCT_AREA_SIZE   80
#define FRU_MULTI_AREA_OFFSET   (FRU_PRODUCT_AREA_OFFSET + FRU_PRODUCT_AREA_SIZE)
#define FRU_MULTI_AREA_SIZE     104
#define FRU_EKEY_AREA_OFFSET 	(FRU_MULTI_AREA_OFFSET + 5 + LED_RECORD_DATA_LEN)

#define DEVICE_ACCESSED_BYTES 1
#ifdef DEVICE_ACCESSED_BYTES
    #define DEVICE_ACCESSED_TYPE 0x00 //by bytes
#else
    #define DEVICE_ACCESSED_TYPE 0x01 //by words
#endif

/*
  fru language codes definition
 */
#define IPMI_FRU_LANGUAGE_CODE_ENGLISH_LEGACY       0
#define IPMI_FRU_LANGUAGE_CODE_CHINESE              135

/*
  frus state macro
 */
#define AMC_POWER_STAT_UP       ((uint8)1)
#define AMC_POWER_STAT_DOWN     ((uint8)0)
#define AMC_POWER_CONTROL_ON    ((uint8)1)
#define AMC_POWER_CONTROL_OFF   ((uint8)0)
#define AMC_STAT_IN             ((uint8)1)
#define AMC_STAT_OUT            ((uint8)0)
#define AMC_SLOT_IN             ((uint8)1)
#define AMC_SLOT_OUT            ((uint8)0)
#define EVENT_RCE_ON            ((uint8)1)
#define EVENT_RCE_OFF           ((uint8)0)
#define CARRIER_POWER_STAT_OFF      	((uint8)0)
#define CARRIER_POWER_STAT_IPMC_LOCAL   ((uint8)1)
#define CARRIER_POWER_STAT_FORCEON  	((uint8)2)
#define CARRIER_POWER_STAT_ShMC		((uint8)3)

#define CARRIER_HS_STAT_CLOSE       	((uint8)1)
#define CARRIER_HS_STAT_OPEN        	((uint8)0)


/*
  Board/FRU participation
 */

/*
  frus hotswap state macro
*/
#if 0
enum Hot_Swap_State {
	M0,     //FRU Not Installed
	M1,     //FRU Inactive
	M2,     //FRU Activation Request
	M3,     //FRU Activation In Progress
	M4,     //FRU Active
	M5,     //FRU Deactivation Request
	M6,     //FRU Deactivation In Progress
	M7      //FRU Communication Lost
};
#endif
typedef enum{
	M0,
	M1,
	M2,
	M3,
	M4,
	M5,
	M6,
	M7
}FRT_State;

typedef enum{
	RTM_S_IN_SLOT,
	RTM_S_HANDLE_OPEN,
	RTM_S_HANDLE_CLOSE,
	RTM_S_POWER_ON,
}RTM_State;


typedef struct{
	RTM_State pre_state;
	RTM_State cur_state;
}RTM_StateCtrl;


typedef enum{
	IPMC_NULL,
	IPMC_LOCAL,
	IPMC_FORCED,
	IPMC_SHMC
}IPMC_MODE;

typedef enum{
	ACT_NONE,
	ACT_Activate,
	ACT_PowerOn,
	ACT_Deactivate,
}ShMC_Activation;

typedef struct _Ipmc_Hot_Swap {
	FRT_State PreState;
	FRT_State CurState;
}Ipmc_Hot_Swap;

typedef struct _Fru_Activation_Policy{
    uint8 Deactivation_Locked_bit;
    uint8 Locked_bit;
}Fru_Activation_Policy;

/*
 * FRU Data Defines
 */

struct fru_record_mul_module_current{
    uint8 current_draw;
};

struct fru_record_mul_amc{
    uint8   chan_num;
    uint8   chan_data[5][4];
    uint8   amc_ld_num;
    struct{
        uint8   link_group_id;
        uint8   link_extension;
        uint8   link_type;
        uint8   lane_flag;
        uint8   channel_id;
    }amc_ld[10];
};

struct fru_record_mul{
    struct fru_record_mul_module_current module_current;
    struct fru_record_mul_amc amc;
};

struct fru_record{

    struct fru_record_mul mul;
};
struct AMC_Power{
    uint8 AMC_Power_pre;
    uint8 AMC_Power_cur;
};

struct FRU{
    uint8 HS_Status;
    uint8 ipmb_addr;
    uint8 AMC_Power_stat;
    struct fru_record record;
};

/*
 * Function statement
 */

void IPMI_Carrier_HW_Task(void *pdata);
void AMC_HW_Task(void *pdata);
void RTM_HW_Task(void *pdata);

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_FRU_H */



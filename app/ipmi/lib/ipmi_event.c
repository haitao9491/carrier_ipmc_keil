/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-event.c
** Last modified Date:  2015-06-30
** Last Version:        1.0
** Descriptions:        ATCA IPMI NetFn and CMDs
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-06-30
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
#include "ipmi_event.h"
#include "config.h"
#include "i2c.h"
#include "ipmi_comm.h"
#include "ipmi_fru.h"
//extern struct FRU fru[4];

//void Set_AMC_Event_Receiver(INT8U fru_id,INT8U state)
//{
//    I2c_MemCopy_Entry I2c_ptr;
//    uint8 rsAddr;
//    uint8 reqAddr;
//    uint8 NetFn;
//    uint8 Cmd;
//    uint8 reqSeq;
//    uint8 payload[2];
//    uint8 payloadlen;
//    uint8 i2cId;

//    rsAddr = fru[fru_id].ipmb_addr;
//    NetFn = IPMI_NETFN_SE;
//    reqAddr = 0x20;
//    Cmd = CMD_SET_EVENT_RECEIVER;
//    switch(state){
//        case EVENT_RCE_ON:
//            payload[0] = 0x20;
//            payload[1] = 0x00;
//        break;
//        case EVENT_RCE_OFF:
//            payload[0] = 0xff;
//            payload[1] = 0x00;
//        break;
//        default:break;
//    }
//    payloadlen = 2;
//    i2cId = 2;
//    Construct_IPMI_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
//                            Cmd, payload, payloadlen, i2cId);
//    Tansfer_I2c_Data(&I2c_ptr);
//}





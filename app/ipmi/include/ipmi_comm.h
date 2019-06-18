/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           IPMI-COMM.h
** Last modified Date:  2015-06-26
** Last Version:        1.0
** Descriptions:        ATCA IPMI Communication
**--------------------------------------------------------------------------------------------------------
** Created by:          ZhangZongkai
** Created date:        2015-06-29
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
#ifndef __IPMI_COMM_H
#define __IPMI_COMM_H

#include "config.h"
#include "../driver/i2c/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

//Return of communication
#define IPMI_COMM_OK                    0x01
#define IPMI_COMM_ERROR_CHKSUM          0x10
#define IPMI_COMM_ERROR_NETFN           0x11
#define IPMI_COMM_ERROR_CMD             0x12

//Return of operation to IPMB table
#define OK	0x00
#define NOK	0x01
#define IPMI_IPMB_TBL_OPT_OK	OK
#define IPMI_IPMB_TBL_OPT_ERR	NOK
#define IPMI_IPMB_TBL_OPT_NO_RECORD		0x02
#define IPMI_IPMB_TBL_OPT_RECORD_NULL 	0x03
#define IPMI_IPMB_TBL_OPT_RECORD_FULL 	0x04
#define IPMI_IPMB_TBL_OPT_NO_SUBRECORD	0x05

#define N_I2C_MSG	16


typedef struct __ipmi_req {
	INT8U	RsAddr;				//requset address
	INT8U	NetFn_rsLUN;		//netfn:6bit----response lun:2bit
	INT8U	HeadChksum;
	INT8U	ReqAddr;			//response address
	INT8U	reqSeq_reqLUN;		//request sequest:6bit----request lun:2bit
	INT8U	rsCMD;				//command
	INT8U	data1;
	INT8U	data2;
	INT8U	data3;
}IPMI_Req;

typedef struct __ipmi_rs {
	INT8U	ReqAddr;			//requset address
	INT8U	NetFn_reqLUN;		//netfn:6bit----response lun:2bit
	INT8U	HeadChksum;
	INT8U	RsAddr;				//response address
	INT8U	reqSeq_rsLUN;		//request sequest:6bit----request lun:2bit
	INT8U	rsCMD;				//command
	INT8U	CompCode;			//complete code
	INT8U	data1;
}IPMI_Res;



extern struct info_collect i2cInfo[3];

typedef struct request_flag {
	uint8 NetFn;
	uint8 Cmd;
	uint8 SeqFlag;	    //bit7:res timeout:bit6
	                    //bit5~4:00:I2C0, 01:I2C1, 10:I2C2, 11:BTI
	                    //bit3~0:count Reserve
	uint8 BoardFlag;	//Flag of Carrier or AMC address
	uint8 ATCAIPMB;		//Carrier IPMB address
	uint8 AMCIPMB;		//AMC IPMB address
	uint32 RecCurTime;	//Record of present time
	uint8 Timeout;		//Timeout /s
	uint8 TimeoutFlag;  //0x01: Timeout 0x10:Receive ringht 0x20:Receive false
}Request_Flag_Buf;


typedef struct {
	uint32 initialTime;
	uint32 timediff;
}TimeInfo;
/*
 * Function statement
 */
INT8U Tansfer_I2c_Data(I2c_MemCopy_Entry *I2c_ptr);
void IPMI_Comm_Construct_Req_Pkt(I2c_MemCopy_Entry *I2c_ptr,uint8 rsAddr, uint8 NetFn, uint8 reqAddr,
                            uint8 reqSeq,uint8 Cmd, uint8 *payload, uint8 payloadlen, uint8 i2cId);
void IPMI_IPMB_TASK(void *pdata);

#ifdef __cplusplus
}
#endif

#endif/* __IPMI_COMM_H */



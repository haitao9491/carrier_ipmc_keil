/****************************************Copyright (c)****************************************************
**                          BeiJing Raycore Technology Co.,LTD.
**
**                               http://
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ipmi-comm.c
** Last modified Date:  2015-07-02
** Last Version:        1.0
** Descriptions:        ATCA IPMB Communication base on i2c
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
#include <time.h>
#include "bsp_int.h"
#include "app_cfg.h"
#include "ipmi_fru.h"
#include "ipmi_sdr.h"
#include "ipmi_sensor.h"
#include "ipmi_device.h"
#include "ipmi_defs.h"
#include "ipmi_cpld.h"
#include "ipmi_comm.h"
#include "boardinfo.h"

#include "bsp_os.h"

/****************************************external variables*****************************************/
extern BoardInfo g_boardinfo ;
extern ThresholdSensor g_sensor_temp[TEMP_SENSOR_NUM];
extern uint8 DataBuffer0[DATA_BUFFER_SIZE];
extern uint8 DataBuffer1[DATA_BUFFER_SIZE];
extern uint8 DataBuffer2[DATA_BUFFER_SIZE];
extern uint8 fru_info[FRU_INVENTORY_AREA_SIZE];
extern uint8 sdr_info[SDR_NUM][SDR_INVENTORY_AREA_SIZE];
extern INT8U Temperature_Power,Temperature_5464;
extern INT8U Voltage;

/****************************************external functions*****************************************/
extern void UART0_SendStr(char *s);

/****************************************local variables*****************************************/
OS_EVENT *I2c_Q = NULL;	//declare I2C receive queue here

//i2c2 msg mem and queue definition
void *MsgGrp[N_I2C_MSG];	//specify I2c message pointer array

INT8U Debug_Flag = 1;

uint32_t g_SEL_TimeDiff = 0;	//for calculating present time in unix timestamp

/*********************************************************************************************************
** Function name:           checksum
**
** Descriptions:            IPMB Message checksum
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
INT8U checksum(INT8U *buf, INT8U len)
{
	INT8U sum = 0;

	for(; len > 0; len--)
	{
		sum += *buf++;
	}
	sum ^= 0xff;
	sum += 1;

	return sum;
}
/*********************************************************************************************************
** Function name:           get_timestamp
**
** Descriptions:            get now timestamp
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
#if 0
INT32U get_timestamp(void)
{
	INT32U local_s;
	INT32U sel_time;

    local_s = OSTimeGet() / OS_TICKS_PER_SEC;
	sel_time = local_s + g_SEL_TimeDiff;
	return sel_time;
}

void get_timestamp(void)
{
	struct tm time_input;
	int year = 2019;
	int month = 3;
	int day = 21;
	int hour = 6;
	int minute = 6;
	int second = 6;

    time_input.tm_year = year - 1970;
    time_input.tm_mon = month -1;
    time_input.tm_mday = day;
    time_input.tm_hour = hour;
    time_input.tm_min = minute;
    time_input.tm_sec = second;

    g_boardinfo.initTime = mktime(&time_input);
}

#endif

/*********************************************************************************************************
** Function name:           Addr_Odd_Parity
** Descriptions:            Odd Parity geted hardware address
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
INT8U Addr_Odd_Parity (INT8U data)
{
	INT8U tmp, tmp1;
	INT8S count = 0;
	INT8U i;

	tmp = data;
	tmp1 = data & 0x80;
	for(i = 0; i < 7; i++) {
		if((data & 0x01) == 1)
			count++;
		tmp = tmp >> 1;
		data = tmp;
	}
	if(((count % 2) == 1 && tmp1 == 0) || ((count % 2) == 0 && tmp1 == 0x80))
		return 0;
	else
		return 1;
}

/*********************************************************************************************************
** Function name:           Read_Hardware_Address
** Descriptions:            read hardware address
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
INT8U Read_Hardware_Address(INT8U *ha)
{
	unsigned char count = 0;

	/*read ha and odd parity the ha*/
	while(1) {
		*ha = IPMI_CPLD_HARDADDRESS_REG;

		if(Addr_Odd_Parity(*ha)) {
			count++;
			if(count < 1)
				continue;
			else {
				*ha = 0x77;
				break;
			}
		}
		else
		    break;
	}
		return 0;
}
/*********************************************************************************************************
** Function name:           Tansfer_I2c_Data
** Descriptions:            Send IPMB message
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
INT8U Tansfer_I2c_Data(I2c_MemCopy_Entry *I2c_ptr)
{

	int32	ret;
	uint8 j = 0;	//Resend times
	uint8 i;

	while (1) {
		j++;
		ret = i2cWrite(I2c_ptr->i2cID, I2c_ptr->databuf[0], &I2c_ptr->databuf[1], I2c_ptr->len-1);
		if (ret == I2C_RET_SUCCESS)
			break;
		else if (ret == I2C_RET_BUS_BUSY || ret == I2C_RET_LOSS_BUS){
			OSTimeDlyHMSM(0, 0, 0, 20);
			if (j > 2){
				UART0_Printf("i2c send fail ,ret: %d\n",ret);
				return OPERATE_FAIL;
			}
			continue;
		}
		else{
			UART0_Printf("i2c send fail ,ret: %d\n",ret);
			return OPERATE_FAIL;
		}
	}
    if(Debug_Flag){
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif
		OS_ENTER_CRITICAL();
        UART0_Printf("i2c ID is %d,len is %d,Mwrite data is:\n", I2c_ptr->i2cID,I2c_ptr->len);
        for(i = 0; i < I2c_ptr->len; i++) {
        	UART0_Printf("\t0x%02x", I2c_ptr->databuf[i]);
        	if(((i+1) % 9) == 0)
        	    UART0_SendStr("\n");
        }
        UART0_SendStr("\n");
		OS_EXIT_CRITICAL();
    }
	return OPERATE_SUCCESS;
}
/*********************************************************************************************************
** Function name:           IPMI_Comm_Construct_Req_Pkt
** Descriptions:            Construct IPMB Request Packet
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Comm_Construct_Req_Pkt(I2c_MemCopy_Entry *I2c_ptr,
				uint8 rsAddr, uint8 NetFn, uint8 reqAddr, uint8 reqSeq,
					uint8 Cmd, uint8 *payload, uint8 payloadlen, uint8 i2cId)
{
	uint8 chksum;
	uint8 *p = NULL;
	IPMI_Req	*ipmi_req = NULL;

	ipmi_req = (IPMI_Req *)&I2c_ptr->databuf[0];
	p = (uint8 *)&I2c_ptr->databuf[0];

	ipmi_req->RsAddr = rsAddr;
	ipmi_req->NetFn_rsLUN = NetFn << 2;
	chksum = checksum(p, 2);
	ipmi_req->HeadChksum = chksum;
	ipmi_req->ReqAddr = reqAddr;
	ipmi_req->reqSeq_reqLUN = reqSeq <<2;
	ipmi_req->rsCMD = Cmd;
	if(payload != NULL) {
		memcpy(&I2c_ptr->databuf[6], payload, payloadlen);
	}

	I2c_ptr->len = 6 + payloadlen;
	chksum = checksum((p+3), (payloadlen+3));
	I2c_ptr->databuf[I2c_ptr->len] = chksum;

	I2c_ptr->len += 1;

	I2c_ptr->i2cID = i2cId;
}

/*********************************************************************************************************
** Function name:           IPMI_Comm_Construct_Res_Pkt
**
** Descriptions:            Construct IPMB Respond Packet
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Comm_Construct_Res_Pkt(I2c_MemCopy_Entry *I2c_ptr,
				uint8 *payload, uint8 payloadlen)
{
	uint8 tmp;
	IPMI_Req *ipmi_req = NULL;
	uint8 *p=NULL;
	uint8 reqLUN = I2c_ptr->databuf[4] & 0x3;

	ipmi_req = (IPMI_Req *)I2c_ptr->databuf;
	p = (uint8 *)I2c_ptr->databuf;

	tmp = ipmi_req->RsAddr;
	ipmi_req->RsAddr = ipmi_req->ReqAddr;
	ipmi_req->ReqAddr = tmp;
	ipmi_req->NetFn_rsLUN += (1 << 2);
	ipmi_req->NetFn_rsLUN &= 0xfc;
	ipmi_req->NetFn_rsLUN |= reqLUN;
	ipmi_req->reqSeq_reqLUN &= 0xfc;

	tmp = checksum(p, 2);
	ipmi_req->HeadChksum = tmp;

	memcpy(&I2c_ptr->databuf[6], payload, payloadlen);

	I2c_ptr->len = 6 + payloadlen;

	tmp = checksum((p+3), (I2c_ptr->len - 3));
	I2c_ptr->databuf[I2c_ptr->len] = tmp;

	I2c_ptr->len += 1;
}

/*********************************************************************************************************
** Function name:           IPMI_Comm_Construct_Forward_Req_Pkt
** Descriptions:            Construct IPMB Request Packet
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Comm_Construct_Forward_Res_Pkt(I2c_MemCopy_Entry *I2c_ptr,uint8 reqLUN, uint8 reqSeq)
{
	uint8 chksum,i;
	uint8 *p = NULL;
	uint8 *payload;
	uint8 payloadlen;
	IPMI_Res	*ipmi_res = NULL;

	ipmi_res->RsAddr = 0x20;
	ipmi_res->NetFn_reqLUN = IPMI_NETFN_APP_RS << 2|reqLUN;
	chksum = checksum((INT8U *)ipmi_res, 2);
	ipmi_res->HeadChksum = chksum;
	ipmi_res->ReqAddr = g_boardinfo.ipmbAddr;
	ipmi_res->reqSeq_rsLUN = reqSeq <<2;
	ipmi_res->rsCMD = IPMI_APP_CMD_SEND_MESSAGE;
	payloadlen = 1 + I2c_ptr->len;
	payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
    for(i=0;i<I2c_ptr->len;i++)
	    payload[1+i] = I2c_ptr->databuf[i];

    I2c_ptr->databuf[0] = ipmi_res->RsAddr;
    I2c_ptr->databuf[1] = ipmi_res->NetFn_reqLUN;
    I2c_ptr->databuf[2] = ipmi_res->HeadChksum;
    I2c_ptr->databuf[3] = ipmi_res->ReqAddr;
    I2c_ptr->databuf[4] = ipmi_res->reqSeq_rsLUN;
    I2c_ptr->databuf[5] = ipmi_res->rsCMD;
    memcpy(&I2c_ptr->databuf[6], payload, payloadlen);

    I2c_ptr->len = 6 + payloadlen;

    p = (uint8 *)&I2c_ptr->databuf[0];
	chksum = checksum((p+3), (I2c_ptr->len+4));

	I2c_ptr->databuf[I2c_ptr->len] = chksum;

	I2c_ptr->len += 1;
	I2c_ptr->i2cID = 0;
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_OK
** Descriptions:            General respond OK to Received IPMB Request Message
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Parse_Receive_Req_Cmd_OK(I2c_MemCopy_Entry *I2c_ptr)
{
    INT8U payload[1];

    payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
    IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, 1);
    Tansfer_I2c_Data(I2c_ptr);
}

/*********************************************************************************************************
** Function name:           IPMI_Deal_Req_Cmd_SDR_Read
**
** Descriptions:            deal with requst cmd of sdr reading
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Deal_Req_Cmd_SDR_Read(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U payload[28];
	INT8U payloadlen;
	INT8U i,count,send_flag=1;
	INT16U offset,record_id,reservation_id,id_next;

    if (I2c_ptr->i2cID != 2){
        reservation_id = I2c_ptr->databuf[6]|(I2c_ptr->databuf[7]<<8);
        record_id = I2c_ptr->databuf[8]|(I2c_ptr->databuf[9]<<8);
        offset = I2c_ptr->databuf[10];
        count = I2c_ptr->databuf[11];
		if(record_id < (SDR_NUM - 1) )
		{
			id_next = record_id + 1;
			payload[1] = id_next ;
            payload[2] = id_next >> 8;
		}
		else if(record_id == (SDR_NUM - 1) )
		{
			payload[1] = 0xff;
            payload[2] = 0xff;
		}
		else
			send_flag = 0;
			
        if(send_flag){
            UART0_Printf("Read [%d]SDR[%d] Data %d bytes from %d\n",reservation_id,record_id,count,offset);
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;

            for(i=0;i<count;i++)
				payload[3+i] = sdr_info[record_id][offset+i];
            payloadlen = count+3;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
        }
    }
    return ret;
}

/*********************************************************************************************************
** Function name:           IPMI_Deal_Req_Cmd_Get_Sel_Time
**
** Descriptions:            deal with requst cmd of get sel time
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Deal_Req_Cmd_Get_Sel_Time(I2c_MemCopy_Entry *I2c_ptr)
{
    INT8U ret = IPMI_COMM_OK;
	INT8U payload[5];
	INT8U payloadlen;
    INT32U local_s;
	uint32_t sel_time;

    payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
    local_s = OSTimeGet() / OS_TICKS_PER_SEC;
	sel_time = local_s + g_SEL_TimeDiff;

	payload[1] = (sel_time ) & 0xff;
	payload[2] = (sel_time >> 8) & 0xff;
	payload[3] = (sel_time >> 16) & 0xff;
	payload[4] = (sel_time >> 24) & 0xff;
	UART0_Printf("get sel time:%d", sel_time);

    payloadlen = 5;
    IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
    Tansfer_I2c_Data(I2c_ptr);
    return ret;
}



/*********************************************************************************************************
** Function name:           IPMI_Deal_Req_Cmd_Set_Sel_Time
**
** Descriptions:            deal with requst cmd of set sel time
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Deal_Req_Cmd_Set_Sel_Time(I2c_MemCopy_Entry *I2c_ptr)
{
    INT8U ret = IPMI_COMM_OK;
    INT32U local_s;
	INT8U payload = 0;
	INT8U payloadlen;
	INT8U data[4];
	uint32_t *p_time = (uint32_t *)data;
	
	memcpy(&data[0], &(I2c_ptr->databuf[6]), 4);
//	g_boardinfo.initTime = *p_time;					//the initial time get from ShMC			
	
    local_s = OSTimeGet() / OS_TICKS_PER_SEC;
	g_SEL_TimeDiff = *p_time - local_s;
	
	UART0_Printf("local tick in s %d:", local_s);
	UART0_Printf("sel time reciecved s :%d\n",*p_time);
	
    payload = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
	payloadlen = 1;
	IPMI_Comm_Construct_Res_Pkt(I2c_ptr, &payload, payloadlen);
    Tansfer_I2c_Data(I2c_ptr);
    return ret;
}

/*********************************************************************************************************
** Function name:           IPMI_Deal_Req_Cmd_SDR_Read
**
** Descriptions:            deal with requst cmd of sdr reading
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Deal_Req_Cmd_SDR_Event(uint8 sensor_num,uint8 threshold)
{
	I2c_MemCopy_Entry I2c_ptr = {0};
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[10];
	uint8 payloadlen;
	uint8 i2cId;

    rsAddr = 0x20;
    NetFn = IPMI_NETFN_SENSOR_EVENT_RQ;
    reqAddr = g_boardinfo.ipmbAddr;
    reqSeq = 0x00;
    Cmd = IPMI_SENSOR_EVENT_CMD_PLATFORM_EVENT;
    payload[0] = 0x04;
    switch(sensor_num){
        case SENSOR_NUMBER_HANDLE_SWITCH:
            payload[1] = 0xf0;
            payload[2] = SENSOR_NUMBER_HANDLE_SWITCH;
            payload[3] = 0x6f;
            payload[4] = 0xa0 | g_boardinfo.hss.CurState;
            payload[5] = 0x00 | M3;
            payload[6] = 0;
            payloadlen = 7;
            UART0_Printf("SDR_Event:Handle switch!\n");
            break;
        case SENSOR_NUMBER_TEMPERATURE1:
            payload[1] = 0x01;
            payload[2] = SENSOR_NUMBER_TEMPERATURE1;
            payload[3] = 0x81;
            payload[4] = threshold;
            payload[5] = Temperature_Power;

            switch(threshold){
                case TERMOERATURE_UPPER_MINOR:
                    payload[6] = TERMOERATURE_UPPER_MINOR_THRESHOLD;
                    break;
                case TERMOERATURE_UPPER_MAJOR:
                    payload[6] = TERMOERATURE_UPPER_MINOR_THRESHOLD;
                    break;
                case TERMOERATURE_UPPER_CRITICAL:
                    payload[6] = TERMOERATURE_UPPER_MINOR_THRESHOLD;
                    break;
                default:break;
            }
            payloadlen = 7;
            UART0_Printf("SDR_Event:Temperature1!\n");
            break;
        default:break;
    }

    i2cId = 1;
    IPMI_Comm_Construct_Req_Pkt(&I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                                Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(&I2c_ptr);
    OSTimeDlyHMSM(0,0,0,200);
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_SE
**
** Descriptions:            Deal Received IPMB Request SE Message
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Parse_Receive_Req_Cmd_SE(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U payload[12];
	INT8U payloadlen;
	INT8U cmd;
	INT8U sensor_num;
	
    cmd = I2c_ptr->databuf[5];
    switch(cmd){
        case IPMI_SENSOR_EVENT_CMD_SET_EVENT_RECEIVER:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Set Event Receiver!\n");
                IPMI_Parse_Receive_Req_Cmd_OK(I2c_ptr);
            }
            break;
        case IPMI_SENSOR_EVENT_CMD_GET_EVENT_RECEIVER:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Get Event Receiver!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = 0x20;
                payload[2] = 0x00;
                payloadlen = 3;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_SENSOR_EVENT_CMD_PLATFORM_EVENT:
            if (I2c_ptr->i2cID == 2){
                UART0_SendStr("Receive Req CMD: Platform Event!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payloadlen = 1;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_SENSOR_EVENT_CMD_GET_DEVICE_SDR_INFO:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Get Device SDR Info!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = SDR_NUM;
                payload[2] = 0x01; /* LUN 0 have sensor */
                payloadlen = 3;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_SENSOR_EVENT_CMD_GET_DEVICE_SDR:
            UART0_SendStr("Receive Req CMD: Get Device SDR!\n");
            IPMI_Deal_Req_Cmd_SDR_Read(I2c_ptr);
            break;
        case IPMI_SENSOR_EVENT_CMD_RESERVE_DEVICE_REPOSITORY:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Reserve Device SDR Repository!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = 0x00;
                payload[2] = 0x00;
                payloadlen = 3;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
		case IPMI_SENSOR_EVENT_CMD_GET_SENSOR_HYS:
			UART0_SendStr("Receive Req CMD: Get Sensor Hys!\n");
			sensor_num = I2c_ptr->databuf[6];
			ipmi_get_sensor_hys(sensor_num,payload,&payloadlen);			
			IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);	
			break;
		case IPMI_SENSOR_EVENT_CMD_GET_SENSOR_THRESHOLD:
			if (I2c_ptr->i2cID != 2){
				UART0_SendStr("Receive Req CMD: Get Sensor Threshold!\n");
				sensor_num = I2c_ptr->databuf[6];
				ipmi_get_threshold(sensor_num,payload,&payloadlen);
				IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
				Tansfer_I2c_Data(I2c_ptr);
			}
			break;
		case IPMI_SENSOR_EVENT_CMD_GET_SENSOR_EVENT_EN:
			if (I2c_ptr->i2cID != 2){
				UART0_SendStr("Receive Req CMD: Get Sensor Event Enable!\n");
				sensor_num = I2c_ptr->databuf[6];
				ipmi_get_event_en(sensor_num,payload, &payloadlen);
				IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
				Tansfer_I2c_Data(I2c_ptr);
			}
			break;
        case IPMI_SENSOR_EVENT_CMD_GET_SENSOR_READING:
            UART0_SendStr("Receive Req CMD: Get Sensor Reading!\n");
            if (I2c_ptr->i2cID != 2){
                sensor_num = I2c_ptr->databuf[6];
				ipmi_get_sensor_reading(sensor_num,payload,&payloadlen);
				IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
				Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_SENSOR_EVENT_CMD_REARM_SENSOR_EVENTS:
            UART0_SendStr("Receive Req CMD: Re-arm Sensor Events!\n");
			sensor_num = I2c_ptr->databuf[6];
		
            IPMI_Parse_Receive_Req_Cmd_OK(I2c_ptr);			
            OSTimeDlyHMSM(0,0,0,200);
		
            if(M4 != g_boardinfo.hss.CurState)
				break;
			switch(sensor_num){
                    case SENSOR_NUMBER_HANDLE_SWITCH:/* Handle switch */
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_HANDLE_SWITCH,0x00);
                        break;
                    case SENSOR_NUMBER_TEMPERATURE0:/* Temperature0 */
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE0,TERMOERATURE_UPPER_MINOR);
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE0,TERMOERATURE_UPPER_MAJOR);
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE0,TERMOERATURE_UPPER_CRITICAL);
                        break;
					case SENSOR_NUMBER_TEMPERATURE1:/* Temperature1 */
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE1,TERMOERATURE_UPPER_MINOR);
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE1,TERMOERATURE_UPPER_MAJOR);
						IPMI_Deal_Req_Cmd_SDR_Event(SENSOR_NUMBER_TEMPERATURE1,TERMOERATURE_UPPER_CRITICAL);
                        break;
                    default:
                        UART0_SendStr("No this sensor!\n");
                }               
            break;
        default:
            ret = IPMI_COMM_ERROR_CMD;
            break;
    }
	return ret;
}

/*********************************************************************************************************
** Function name:           IPMI_Deal_Req_Cmd_SDR_Read
**
** Descriptions:            deal with requst cmd of sdr reading
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Deal_Req_Cmd_Send_Message(I2c_MemCopy_Entry *I2c_ptr)
{
	uint8 rsAddr;
	uint8 reqAddr;
	uint8 NetFn;
	uint8 Cmd;
	uint8 reqSeq;
	uint8 payload[16];
	uint8 payloadlen;
	uint8 i2cId;
	uint8 i;

	IPMI_Req *ipmi_req = NULL;

	ipmi_req = (IPMI_Req *)I2c_ptr->databuf[7];

	rsAddr = ipmi_req->RsAddr;
	NetFn = ipmi_req->NetFn_rsLUN >> 2;
	reqAddr = 0x20;
	reqSeq = ipmi_req->reqSeq_reqLUN >> 2;
	Cmd = ipmi_req->rsCMD;
	payloadlen = I2c_ptr->len - 15;
	for(i=0;i<payloadlen;i++)
        payload[i] = I2c_ptr->databuf[13+i];

    i2cId = 2;
    I2c_ptr->databuf[0] = I2c_ptr->databuf[7];
    IPMI_Comm_Construct_Req_Pkt(I2c_ptr, rsAddr, NetFn, reqAddr, reqSeq,
                                Cmd, payload, payloadlen, i2cId);
    Tansfer_I2c_Data(I2c_ptr);
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_App
**
** Descriptions:            Deal Received IPMB Request App Message
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Parse_Receive_Req_Cmd_App(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U payload[20];
	INT8U payloadlen;
	INT8U i;
	INT8U cmd;

    cmd = I2c_ptr->databuf[5];
    switch(cmd){
        case IPMI_APP_CMD_GET_DEVICE_ID:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Get Device id!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                for (i=0;i<DEVICEID_LEN;i++){
                    payload[1+i] = deviceid_info[i];
                }
                payloadlen = DEVICEID_LEN+1;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_APP_CMD_GET_SELF_TEST_RESULTS:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Get Self Test Results!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = 0x55;
                payload[2] = 0x00;
                payloadlen = 3;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_APP_CMD_SEND_MESSAGE:
            UART0_SendStr("Receive Req CMD: Send Message!\n");
            if (I2c_ptr->i2cID !=2){
/* The format of a ¡°Send Message¡± command encapsulating a message
that needs to be bridged from IPMB-0 to IPMB-L */
                IPMI_Deal_Req_Cmd_Send_Message(I2c_ptr);
            }
            break;
        default:
            ret = IPMI_COMM_ERROR_CMD;
            break;
    }
	return ret;
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_Storage
**
** Descriptions:            Deal Received IPMB Request Storage Message
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Parse_Receive_Req_Cmd_Storage(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U payload[28];
	INT8U payloadlen;
	INT8U i;
	INT8U cmd;
	INT8U count;
	INT16U offset;
	//INT32U Timestamp;

    cmd = I2c_ptr->databuf[5];
    switch(cmd){
        case IPMI_STORAGE_CMD_GET_FRU_INVENTORY_AREA_INFO:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Get FRU Inventory Area Info!\n");
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = (INT8U)(FRU_INVENTORY_AREA_SIZE);
                payload[2] = (INT8U)(FRU_INVENTORY_AREA_SIZE>>8);
                payload[3] = DEVICE_ACCESSED_TYPE;
                payloadlen = 4;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_STORAGE_CMD_READ_FRU_DATA:
            if (I2c_ptr->i2cID != 2){
                UART0_SendStr("Receive Req CMD: Read FRU Data!\n");
                offset = I2c_ptr->databuf[7]|(I2c_ptr->databuf[8]<<8);
                count = I2c_ptr->databuf[9];
                UART0_Printf("Read FRU Data %d bytes from %d\n",count,offset);
                payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
                payload[1] = count;
                for(i=0;i<count;i++)
                payload[2+i] = fru_info[offset+i];
                payloadlen = count+2;
                IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
                Tansfer_I2c_Data(I2c_ptr);
            }
            break;
        case IPMI_STORAGE_CMD_GET_SDR_REPOSITORY_INFO:
            UART0_SendStr("Receive Req CMD: Get SDR Repository Info!\n");
			//Timestamp = get_timestamp();
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x02;
            payload[2] = (SDR_INVENTORY_AREA_SIZE & 0xff);
            payload[3] = SDR_INVENTORY_AREA_SIZE >> 8;
            payload[4] = 0xff;
            payload[5] = 0xff;
            payload[6] = g_boardinfo.initTime;
            payload[7] = g_boardinfo.initTime>>8;
            payload[8] = g_boardinfo.initTime>>16;
            payload[9] = g_boardinfo.initTime>>24;
            payload[10] = g_boardinfo.initTime;
            payload[11] = g_boardinfo.initTime>>8;
            payload[12] = g_boardinfo.initTime>>16;
            payload[13] = g_boardinfo.initTime>>24;
            payload[14] = 0x42;
            payloadlen = 15;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);

            break;
        case IPMI_STORAGE_CMD_RESERVE_SDR_REPOSITORY:
            UART0_SendStr("Receive Req CMD: Reserve SDR Repository!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x00;
            payloadlen = 3;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_STORAGE_CMD_GET_SDR:
            UART0_SendStr("Receive Req CMD: Get SDR!\n");
            IPMI_Deal_Req_Cmd_SDR_Read(I2c_ptr);
            break;
        case IPMI_STORAGE_CMD_GET_SEL_TIME:
            UART0_SendStr("Receive Req CMD: Get SEL TIME!\n");
            IPMI_Deal_Req_Cmd_Get_Sel_Time(I2c_ptr);
            break;
        case IPMI_STORAGE_CMD_SET_SEL_TIME:
            UART0_SendStr("Receive Req CMD: SET SEL TIME!\n");
			IPMI_Deal_Req_Cmd_Set_Sel_Time(I2c_ptr);
            break;

        default:
            ret = IPMI_COMM_ERROR_CMD;
            break;
    }
	return ret;
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_Picmg_OK
** Descriptions:            General respond OK to Received IPMB Request Picmg Message
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_MemCopy_Entry *I2c_ptr)
{
    INT8U payload[2];

    payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
    payload[1] = 0x00;
    IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, 2);
    Tansfer_I2c_Data(I2c_ptr);
}
/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_Picmg_OK
** Descriptions:            General respond OK to Received IPMB Request Picmg Message
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
void IPMI_Deal_Req_Cmd_GET_POWER_LEVEL(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U payload[12];
	INT8U payloadlen;

    INT8U power_type;

    power_type = I2c_ptr->databuf[8];
    payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
    payload[1] = 0x00;
	/* Power level of the FRU:1 */
    payload[2] = g_boardinfo.desiredPL;
/* delay to stable power level,steady state should be 0 */
    payload[3] = 0x00;
/* Power Multiplier. c8 means 20W per level */
    payload[4] = 0xc8;
	//all the power levels need a list
	/* Power Draw[1]. 80W--Carrier self */		
    payload[5] = 0x04;
	/* Power Draw[2]. 120W--Carrier+1*AMC */
    payload[6] = 0x06;
	/* Power Draw[3]. 160W--Carrier+2*AMC */
    payload[7] = 0x08;
	/* Power Draw[4]. 180W--Carrier+3*AMC */
	payload[8] = 0x09;
	/* Power Draw[5]. 200W--Carrier+3*AMC */
    payload[9] = 0x0a;
	
	payloadlen = 10;
    switch(power_type)
    {
        case POWER_TYPE_STEADY_STATE_POWER_DRAW_LEVELS:
			payload[2] = g_boardinfo.desiredPL;
            UART0_SendStr("Power Type:Steady state power draw levels!\n");
            
            break;
        case POWER_TYPE_DESIRED_STEADY_STATE_DRAW_LEVELS:
			payload[2] = g_boardinfo.desiredPL;
            UART0_SendStr("Power Type:Desired steady state draw levels!\n");
            break;
        case POWER_TYPE_EARLY_POWER_DRAW_LEVELS:
			payload[2] = g_boardinfo.desiredPL;
            UART0_SendStr("Power Type:Early power draw levels!\n");
            break;
        case POWER_TYPE_DESIRED_EARLY_LEVELS:
			payload[2] = g_boardinfo.desiredPL;
            UART0_SendStr("Power Type:Desired early levels!\n");
            break;
        default:
            UART0_SendStr("Power Type:UNKNOWN!\n");
            break;
    }
    IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
    Tansfer_I2c_Data(I2c_ptr);
}

/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive_Req_Cmd_Picmg
** Descriptions:            Deal Received IPMB Request Picmg Message
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
uint8 IPMI_Parse_Receive_Req_Cmd_Picmg(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U payload[12];
	INT8U payloadlen;
	INT8U cmd;
    INT8U policy_mask_bits,policy_set_bits;
    INT8U level_change;
    INT8U fru_activation;

    cmd = I2c_ptr->databuf[5];
    switch(cmd){
        case IPMI_PICMG_CMD_GET_PROPERTIES:
            UART0_SendStr("Receive Req CMD: Get PICMG Properties!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x12;  //version
            payload[3] = 0x00;
            payload[4] = 0x00;
            payloadlen = 5;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_ADDRESS_INFO:
            UART0_SendStr("Receive Req CMD: Get Address Info!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = g_boardinfo.hwAddr;
            payload[3] = g_boardinfo.ipmbAddr;
            payload[4] = 0xff;
            payload[5] = 0x00;		//fru device id 
            payload[6] = g_boardinfo.hwAddr & 0x1f;		//site id 
            payload[7] = 0x00;
            payloadlen = 8;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_FRU_CONTROL:
            UART0_SendStr("Receive Req CMD: FRU Control!\n");
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_FRU_LED_PROPERTIES:
            UART0_SendStr("Receive Req CMD: Get FRU LED Properties!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x07;
            payload[3] = 0x00;
            payloadlen = 4;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_LED_COLOR_CAPABILITIES:
            UART0_SendStr("Receive Req CMD: Get LED Color Capabilities!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x02;
            payload[3] = 0x01;
            payload[4] = 0x01;
            payloadlen = 5;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_FRU_LED_STATE:
            UART0_SendStr("Receive Req CMD: Set FRU LED State!\n");
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_FRU_LED_STATE:
            UART0_SendStr("Receive Req CMD: Get FRU LED State!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x02;
            payload[3] = 0x00;
            payload[4] = 0x00;
            payload[5] = 0x00;
            payload[6] = 0x01;
            payloadlen = 7;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_IPMB_STATE:
            UART0_SendStr("Receive Req CMD: Set IPMB State!\n");
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_FRU_ACTIVATION_POLICY:
            UART0_SendStr("Receive Req CMD: Set FRU Activation Policy!\n");

            //fru_device_id = I2c_ptr->databuf[7];
            policy_mask_bits = I2c_ptr->databuf[8];
            policy_set_bits = I2c_ptr->databuf[9];
            if(policy_mask_bits&0x01){
                if(policy_set_bits&0x01)
                    g_boardinfo.lock.Locked_bit = 1;
                else g_boardinfo.lock.Locked_bit = 0;
				g_boardinfo.activation = ACT_NONE;
            }
            if(policy_mask_bits&0x02){
                if(policy_set_bits&0x02)
                    g_boardinfo.lock.Deactivation_Locked_bit = 1;
                else g_boardinfo.lock.Deactivation_Locked_bit = 0;
				g_boardinfo.activation = ACT_NONE;
            }
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_FRU_ACTIVATION_POLICY:
            UART0_SendStr("Receive Req CMD: Get FRU Activation Policy!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            payload[2] = 0x03&(g_boardinfo.lock.Locked_bit|(g_boardinfo.lock.Deactivation_Locked_bit << 1));
            payloadlen = 3;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_FRU_ACTIVATION:
            UART0_SendStr("Receive Req CMD: Set FRU Activation!\n");
            fru_activation = I2c_ptr->databuf[8];
            if(fru_activation) 
			{
				g_boardinfo.activation = ACT_Activate;
				g_boardinfo.lock.Deactivation_Locked_bit = 1;
			}
            else 
			{
				g_boardinfo.activation = ACT_Deactivate;
				g_boardinfo.lock.Locked_bit = 1;
			}
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_DEVICE_LOCATOR_RECORD:
            UART0_SendStr("Receive Req CMD: Get Device Locator Record ID!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            /* Infact:Result of below two bytes is each Record ID LS
                and Record ID MS */
            payload[2] = DEVICE_LOCATOR_RECORD_ID;
            payload[3] = DEVICE_LOCATOR_RECORD_ID>>8;
            payloadlen = 4;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_PORT_STATE:
            UART0_SendStr("Receive Req CMD: Set Port State!\n");
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_PORT_STATE:
            UART0_SendStr("Receive Req CMD: Get Port State!\n");
            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_COMPUTE_POWER_PROPERTIES:
            UART0_SendStr("Receive Req CMD: Compute Power Properties!\n");
            payload[0] = IPMI_COMPLETE_CODE_COMMAND_SUCCESS;
            payload[1] = 0x00;
            /* Number of Spanned Slots.*/
            payload[2] = 0x01;
            /* IPM Controller Location.*/
            payload[3] = 0x00;
            payloadlen = 4;
            IPMI_Comm_Construct_Res_Pkt(I2c_ptr, payload, payloadlen);
            Tansfer_I2c_Data(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_SET_POWER_LEVEL:
            UART0_SendStr("Receive Req CMD: Set Power Level!\n");
            g_boardinfo.payLoadPL = I2c_ptr->databuf[8];
            level_change = I2c_ptr->databuf[9];
            switch(g_boardinfo.payLoadPL){
                case 0x00:
					set_Payload_power_off();
					e_key_off();
                    UART0_SendStr("Power Level:Power off!\n");
                    break;
                case 0x01:
                    UART0_SendStr("Power Level:Power level1!\n");
                    break;
                case 0xff:
                    UART0_SendStr("Power Level:Power Do not change current!\n");
                    break;
                default:
                    UART0_Printf("Power Level:%d!\n",g_boardinfo.payLoadPL);
            }
            if(level_change){
                UART0_SendStr("Copy desired level to present levels!\n");
/* power on the Payload power */
				set_Payload_power_on();
				e_key_open();
                g_boardinfo.activation = ACT_PowerOn;
            }
            else
                UART0_SendStr("Power Do not change current!\n");

            IPMI_Parse_Receive_Req_Cmd_Picmg_OK(I2c_ptr);
            break;
        case IPMI_PICMG_CMD_GET_POWER_LEVEL:
            UART0_SendStr("Receive Req CMD: Get Power Level!\n");
            IPMI_Deal_Req_Cmd_GET_POWER_LEVEL(I2c_ptr);
            break;
        default:
            ret = IPMI_COMM_ERROR_CMD;
            break;
    }
	return ret;
}

/*********************************************************************************************************
** Function name:           deal_IPMB_Req_Cmd
**
** Descriptions:            Deal Received IPMB Request Message
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
INT8U	IPMI_Parse_Receive_Req_Cmd(I2c_MemCopy_Entry *I2c_ptr)
{
	IPMI_Req	*ipmi_req = NULL;
    INT8U net_fn;
    INT8U ret;

    ipmi_req = (IPMI_Req *)&I2c_ptr->databuf[0];
	net_fn = ipmi_req->NetFn_rsLUN >> 2;
	//OSTimeDlyHMSM(0, 0, 0, 10);
	switch(net_fn)
	{
        case IPMI_NETFN_SENSOR_EVENT_RQ:
            ret = IPMI_Parse_Receive_Req_Cmd_SE(I2c_ptr);
            break;
        case IPMI_NETFN_APP_RQ:
            ret = IPMI_Parse_Receive_Req_Cmd_App(I2c_ptr);
            break;
        case IPMI_NETFN_STORAGE_RQ:
            ret = IPMI_Parse_Receive_Req_Cmd_Storage(I2c_ptr);
            break;
        case IPMI_NETFN_PICMG_RQ:
            ret = IPMI_Parse_Receive_Req_Cmd_Picmg(I2c_ptr);
            break;
        default:
            UART0_Printf("Receive Req CMD: Unkonwn NetFn%#x!\n",net_fn);
            ret = IPMI_COMM_ERROR_NETFN;
            break;
	}
	//OSTimeDlyHMSM(0, 0, 0, 50);
	return ret;
}

INT8U IPMI_Parse_Receive_Res_Cmd_SE(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U ret = IPMI_COMM_OK;
	INT8U cmd;

    cmd = I2c_ptr->databuf[5];

    switch(cmd){
        case IPMI_SENSOR_EVENT_CMD_SET_EVENT_RECEIVER:
            UART0_SendStr("Receive Res CMD:set event receiver!\n");
            break;
        case IPMI_SENSOR_EVENT_CMD_GET_EVENT_RECEIVER:
            UART0_SendStr("Receive Res CMD:get event receiver!\n");
            break;
        case IPMI_SENSOR_EVENT_CMD_PLATFORM_EVENT:
            UART0_SendStr("Receive Res CMD:Platform Event!\n");
            break;
        case IPMI_SENSOR_EVENT_CMD_GET_SENSOR_READING:
            UART0_SendStr("Receive Res CMD:Get Sensor Reading!\n");
            break;
        default:
            ret = IPMI_COMM_ERROR_CMD;
            break;
    }

	return ret;
}

/*********************************************************************************************************
** Function name:           deal_IPMB_Res_Cmd
**
** Descriptions:            Deal Received IPMB Response Message
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/
INT8U	IPMI_Parse_Receive_Res_Cmd(I2c_MemCopy_Entry *I2c_ptr)
{
    IPMI_Res	*ipmi_res = NULL;
    INT8U net_fn;
    INT8U ret;

	ipmi_res = (IPMI_Res *)&I2c_ptr->databuf[0];
	net_fn = ipmi_res->NetFn_reqLUN >> 2;
	switch(net_fn){
        case IPMI_NETFN_SENSOR_EVENT_RS:
            ret = IPMI_Parse_Receive_Res_Cmd_SE(I2c_ptr);
            break;
        case IPMI_NETFN_APP_RS:
//            ret = deal_IPMI_NetFn_App_Res_Cmd(I2c_ptr);
            break;
        case IPMI_NETFN_STORAGE_RS:
//            ret = deal_IPMI_NetFn_Storage_Res_Cmd(I2c_ptr);
            break;
        case IPMI_NETFN_PICMG_RS:
//            ret = deal_IPMI_NetFn_SE_Res_Cmd(I2c_ptr);
            break;
        default:
            ret = IPMI_COMM_ERROR_NETFN;
            break;

	}
	return ret;
}
/*********************************************************************************************************
** Function name:           IPMI_Parse_Receive
**
** Descriptions:            parse received data from ipmb
**
**
** input parameters:        None
** output parameters:       none
** Returned value:          None
*********************************************************************************************************/

INT8U IPMI_Parse_Receive(I2c_MemCopy_Entry *I2c_ptr)
{
	INT8U cshead,csdata;
	INT8U ret;

	cshead = I2c_ptr->databuf[2];
	csdata = I2c_ptr->databuf[I2c_ptr->len-1];
	if((cshead == checksum(I2c_ptr->databuf, 2)) &&
    csdata == checksum(&I2c_ptr->databuf[3], (I2c_ptr->len-4))) {
        if(I2c_ptr->i2cID != 2) g_boardinfo.comm_ss = COMM_ON;
/* distinguish request or response */
/* request is even num */
        if (((I2c_ptr->databuf[1] >> 2) % 2) == 0) {
            ret = IPMI_Parse_Receive_Req_Cmd(I2c_ptr);
        	return ret;
        }
/* response is odd num */
        else {
            ret = IPMI_Parse_Receive_Res_Cmd(I2c_ptr);
        	return ret;
        }
	}
	else {
		return IPMI_COMM_ERROR_CHKSUM;
	}
}


/*********************************************************************************************************
** Function name:           Mem_Q_Create_Func
**
** Descriptions:
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
INT8U	I2C_Mem_Q_Create_Func(void)
{
	I2c_Q = OSQCreate(&MsgGrp[0], N_I2C_MSG);
	if(I2c_Q)
		return 1;
	else
		return 0;
}

//Request_Flag_Buf ReqFlgBuf[REQUEST_MAX_FLAG];
//OS_EVENT *ReqFlagSem;
//void initReqFlgBuf(void)
//{
//	memset(&ReqFlgBuf, 0, sizeof(ReqFlgBuf));
//	ReqFlagSem = OSSemCreate(1);
//	if(ReqFlagSem == NULL) {
//		UART0_SendStr("IPMI_IPMB:ReqFlagSem create err\n");
//		return;
//	}
//}

/*********************************************************************************************************
** Function name:           Do_Rx_Req_HA_TASK
**
** Descriptions:
**
**
** input parameters:        None
** output parameters:       an character
** Returned value:          None
*********************************************************************************************************/
void IPMI_IPMB_TASK(void *pdata)
{
	INT8U err = 0;
	uint8 I2C0_SLAVE_ADDR;
	uint8 I2C1_SLAVE_ADDR;
	uint8 i;
	I2c_MemCopy_Entry *I2cMem_PtrPut = NULL;
	// need no communication with the IPMC
	if(g_boardinfo.ipmc_mode != IPMC_SHMC)
		exit(0);
	
	//disable debug
    Debug_Flag = 0x1;

	if((g_boardinfo.hwAddr & 0x7f) == 0x41) {
		I2C0_SLAVE_ADDR = 0x20;
		I2C1_SLAVE_ADDR = 0x20;
	}
	else {
		I2C0_SLAVE_ADDR = g_boardinfo.ipmbAddr;
		I2C1_SLAVE_ADDR = g_boardinfo.ipmbAddr;
	}
	BSP_IntVectSet(	(INT8U)I2C0_IRQ,
						(INT8U)I2C0_ISR_PRIORITY,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)i2c0IRQ );
	BSP_IntEn(I2C0_IRQ);
	BSP_IntVectSet(	(INT8U)I2C1_IRQ,
						(INT8U)I2C1_ISR_PRIORITY,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)i2c1IRQ );
	BSP_IntEn(I2C1_IRQ);
	BSP_IntVectSet(	(INT8U)I2C2_IRQ,
						(INT8U)I2C2_ISR_PRIORITY,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)i2c2IRQ );
	BSP_IntEn(I2C2_IRQ);

	i2cInit(0, I2C0_SLAVE_ADDR, &DataBuffer0[0]);
	i2cInit(1, I2C1_SLAVE_ADDR, &DataBuffer1[0]);
	i2cInit(2, I2C2_SLAVE_ADDR, &DataBuffer2[0]);

	I2C_Mem_Q_Create_Func();    //initial i2c memory and queue
//	init_ipmb_table();          //initial address table
//	initReqFlgBuf();            //initial flags

	UART0_SendStr("IPMI_Ipmb:   Task create!\n");
	while(1) {

		//I2cMem_PtrPut = (I2c_MemCopy_Entry *)OSQAccept(I2c_Q);	//not wait,direct return
		I2cMem_PtrPut = (I2c_MemCopy_Entry *)OSQPend(I2c_Q, 0, &err);	//wait queue,and trigger once scheduling

		//if(I2cMem_PtrPut != NULL) {
		if(err == OS_ERR_NONE){
            if(Debug_Flag){
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif
				OS_ENTER_CRITICAL();
    			UART0_Printf("i2c Id is %d, len is %d, Srx data is:\n", I2cMem_PtrPut->i2cID, I2cMem_PtrPut->len);
    			for(i = 0; i< I2cMem_PtrPut->len; i++)
    			{
    				UART0_Printf("\t0x%02x", I2cMem_PtrPut->databuf[i]);
    				if(((i+1) % 9) == 0) {
    					UART0_SendStr("\n");
    				}
    			}
    			UART0_SendStr("\n");
				OS_EXIT_CRITICAL();
            }
			if(IPMI_Parse_Receive(I2cMem_PtrPut) != IPMI_COMM_OK) {
				UART0_SendStr("IPMI_IPMB:RX Parse Data Err!\n");
#ifdef INFO_COLLECT
				i2cInfo[I2cMem_PtrPut->i2cID].rxErrCnt++;
#endif
			}
		}
	}
}



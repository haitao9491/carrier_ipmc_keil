/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    I2C.h
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    I2CÍ·ÎÄ¼þ
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    lixiaocheng
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    wangxiumei
** Modified Date:		    2011-12-22
** Version:				    1.0
** Descriptions:
**
*********************************************************************************************************/
#ifndef __IIC_H
#define __IIC_H

#include "config.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*********************************************************************************************************
   i2c bus work state
 *********************************************************************************************************/
#define I2C_OK                      1
#define I2C_NOK                     0

/*********************************************************************************************************
   Error macro
*********************************************************************************************************/
#ifndef OPERATE_FAIL
#define OPERATE_FAIL        I2C_NOK
#endif

#ifndef OPERATE_SUCCESS
#define OPERATE_SUCCESS     I2C_OK
#endif

/*********************************************************************************************************
   i2c device work state
 *********************************************************************************************************/
#define I2C_BUSY					0x10
#define I2C_IDLE					0x11
#define I2C_MASTER_WRITE_END		0x12
#define I2C_SLAVE_READ_END			0x13
#define I2C_MASTER_READ_END			0x14
#define I2C_ERR						0xff

/*********************************************************************************************************
   slave address type not support 3+X
 *********************************************************************************************************/
#define I2C_ONE_BYTE               0x01
#define I2C_TWO_BYTE               0x02
#define I2C_THREE_BYTE             0x03

#define I2C2_SLAVE_ADDR			0x20

//return i2cbus operation
#define I2C_RET_SUCCESS					1
#define I2C_RET_BUS_BUSY				2
#define I2C_RET_NO_PARTNER				3
#define I2C_RET_LOSS_BUS				4
#define I2C_RET_ERR						5
#define I2C_RET_TIMEOUT					6

//timeout operation
#define I2C_BUS_ERR					0x15
#define I2C_SEM_GET_TIMEOUT			(OS_TICKS_PER_SEC / 2)

void getI2cInfo(uint8 *data, uint8 *bytes);

struct test_collect {
	uint32 rxTimeout;
	uint32 rxRcnt;
	uint32 rxTotal;
	uint32 txTotal;
	uint32 txRcnt;
};

extern struct test_collect tcp;
struct info_collect {
	uint8 rxErrCnt;
	uint8 rxTLLCnt;
	uint8 txRCnt;
	uint8 txTLLCnt;
};

#define DATA_BUFFER_SIZE 64
#define I2C_MEMCPY_BUF_SIZE 32
#define I2C_MEM_COPY_ENTRY_NUM		4	

typedef struct i2c_mem_cpy {
	uint8 databuf[I2C_MEMCPY_BUF_SIZE];
	uint8 len;
	uint8 i2cID;
}I2c_MemCopy_Entry;

typedef struct i2c_mem_cpy_fifo {
	I2c_MemCopy_Entry entry[I2C_MEM_COPY_ENTRY_NUM];
	uint8 index;
}I2c_MemCopy_FiFo;

int	i2cInit ( uint32 ID,uint8 ucAddr,uint8 *Buf );
int32 i2cSetMode (uint32   ID,uint32	speed,uint8   ucSlave);
int32 i2cWrite(uint32  ID,uint8 Addr,uint8  *Buf,uint16  Nbyte);
int32 i2cMasterRead(uint32 ID, uint8 Addr, uint8 *Buf, uint16 Nbyte);
int32 i2cGetFlag(uint8 ID);
uint8 i2cGetHostFlag(uint8 ID);
uint8 i2cSetFlagIdle(uint8 ID);
uint8 i2cGetIsrState (uint8 ID);
uint32 i2cGetRemainBytes(uint8 ID);
void i2c0IRQ( void );
void i2c1IRQ( void );
void i2c2IRQ( void );

#ifdef __cplusplus
    }
#endif

#endif                                                                  /*  __IIC_H                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

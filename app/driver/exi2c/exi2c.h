/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    exi2c.h
** Last modified Date:      2011-12-31
** Last Version:		    1.0
** Descriptions:		    expand i2c header
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2011-12-31
** Version:				    1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified Date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __EXIIC_H
#define __EXIIC_H

#include "config.h"

#ifdef __cplusplus
    extern "C" {
#endif


/*********************************************************************************************************
   I2C Device information struct
*********************************************************************************************************/
struct __exi2cinfo {

    volatile    uint8      *pucAddrBase;        /* I2C register base address */
  			    uint8       ucIICflag;          /* I2C_IDLE */
							                    /* I2C_ERR */
							                    /* I2C_BUSY */
        						 	            /* I2C_WRITE_END */
         							            /* I2C_READ_END */
                uint8       ucSlave;            /* Slave Flag */
   	            uint8 	    *ucSLAddrHead;		/* Slave address to visit */
	            uint8 		ucSLAddrNum;	    /* Slave interior subaddrss bytenum */
	            uint8      	ucI2CSubAddrCtl;    /* Subaddress control */
									            /* 1--Opreation write to read */
									            /* 2--Write operation*/
	volatile    uint8	   *pucDataBuf;
	volatile    uint16		usDataNum;		    /* num of data which waiting operation */
};

typedef struct __exi2cinfo    __EXI2C_INFO;
typedef __EXI2C_INFO         *__EXPI2C_INFO;

/*********************************************************************************************************
  Register Address
*********************************************************************************************************/
#define E9665_I2C_BASE_ADDR					0x82000000

/* PCA9665 Direct register offset */
#define E9665_I2CSTA_REG					0				/* status, read only */
#define E9665_INDPTR_REG					0				/* indirect register pointer, write only*/
#define E9665_I2CDAT_REG					1				/* data, read/write */
#define E9665_I2CCON_REG					3				/* control, read/write */
#define E9665_INDIRECT_REG					2				/* indirect data field access, read/write */

/* PCA9665 interior Indirect register offset */
#define __9665_I2CCOUNT						0x00			/* byte count */
#define __9665_I2CADR						0x01			/* own address */
#define __9665_I2CSCLL						0x02			/* SCL LOW period */
#define __9665_I2CSCLH						0x03			/* SCL HIGH period */
#define __9665_I2CTO						0x04			/* time out */
#define __9665_I2CPRESET					0x05			/* parallel software reset */
#define __9665_I2CMODE						0x06			/* I2C-bus mode */

#define STANDARD_MODE                       0x00
#define FAST_MODE                           0x01
#define FAST_MODE_PLUS                      0x02
#define TURBO_MODE                          0x03

#define E9665_CHIP_RESET_CTRL_REG			(*(volatile unsigned char *)81000010)
#define RESET_E9665_CHIP					0x02
#define CLEAR_RESET_E9665_BIT				0x00

/*********************************************************************************************************
** Function name:           exi2cInit
** Descriptions:
** Input parameters:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int exi2cInit (void);

/*********************************************************************************************************
** Function name:           i2cSetMode
** Descriptions:            set i2c speed
** Input parameters:        eParm
**							i2cMode         set i2c bus mode(total 4 modes)
** Output parameters:       NONE
** Returned value:          OPERATE_FAIL
**                          OPERATE_SUCCESS
*********************************************************************************************************/
int32 exi2cSetMode (__EXPI2C_INFO eParm, uint8 i2cMode);

/*********************************************************************************************************
** Function name:           exi2cSetTimeout
** Descriptions:            set I2C timeout
** Input parameters:        eParm
**							timeoutval
** Output parameters:       NONE
** Returned value:          OPERATE_FAIL
**                          OPERATE_SUCCESS
*********************************************************************************************************/
int32 exi2cSetTimeout(__EXPI2C_INFO eParm, uint8 timeoutval);

/*********************************************************************************************************
** Function name:           i2cRead
** Descriptions:
** Input parameters:        headBuf		   :
**                          headBytes	   :
**                          retData		   : reading date buffer
**                          retBytes	   : reading date bytes
** Returned value:          OPERATE_SUCCESS
**                          OPERATE_FAIL
*********************************************************************************************************/
int32 exi2cRead (uint8 *headBuf,uint8 headBytes,uint8 *retData,uint16 retBytes);

/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:
** Input parameters:        headBuf
**                          headBytes
**                          dataBuf
**                          dataBytes
** Output parameters:       NONE
** Returned value:          OPERATE_SUCCESS
**                          OPERATE_FAIL
*********************************************************************************************************/
int32 exi2cWrite (uint8 *headBuf,uint8  headBytes,uint8 *dataBuf,uint16 dataBytes);

/*********************************************************************************************************
** Function name:           ExI2CIRQ
** Descriptions:
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void ExI2cIRQ ( void );

/*********************************************************************************************************
** Function name:           exi2cGetFlag
** Descriptions:            return i2c device current state
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int32 exi2cGetFlag (void);

#ifdef __cplusplus
    }
#endif

#endif/* __EXIIC_H */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

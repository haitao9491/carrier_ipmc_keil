/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    IICPrivate.h
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    IIC private header
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    lixiaocheng
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:		    just in this docment include
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    wangxiumei
** Modified Date:		    2011-12-22
** Version:				    1.0
** Descriptions:
**
*********************************************************************************************************/
#ifndef __I2CPRIVATE_H
#define __I2CPRIVATE_H

#include "config.h"
#include "includes.h"

/*********************************************************************************************************
   struct of i2c device information
*********************************************************************************************************/
struct __i2cinfo {
                uint32  uiID;                   /* which device */
                uint32  uiOffBase;              /* I2C register OffBase */
    volatile    uint8   *pucAddrBase;           /* I2C register base address */
                uint8   ucIICflag;              /* I2C_IDLE	*/
                                                /* I2C_ERR */
                                                /* I2C_BUSY	*/
                                                /* I2C_WRITE_END */
                                                /* I2C_READ_END */
                uint8   ucSlave;                /* slave flag */
   	            uint8   ucSLAddr;		        /* which slave to visit */
                uint8   *pucDataSlaveBuf;
			    uint8   *pucDataMasterBuf;

	volatile    uint16  usDataSlaveNum;         /* num of device which waiting for deal with */
	volatile	uint16  usDataMasterNum;		/* num of data which waiting for deal with */
	volatile	uint16  usMasterCounter;

				uint8   i2cSlaveErrFlag;

				uint8   i2cintendflag;
};

typedef struct __i2cinfo    __I2C_INFO;
typedef __I2C_INFO         *__PI2C_INFO;


/*********************************************************************************************************
   Num of i2c device
*********************************************************************************************************/
#define __IIC_MAX_NUM                 3

/*********************************************************************************************************
   i2c device is master or slave
*********************************************************************************************************/
#define __IIC_MASTER              0x16
#define __IIC_SLAVER              0x17

#define IIC_MASTER_WRITE			0x01
#define IIC_MASTER_READ				0x02
/*********************************************************************************************************
   Sub address mirco define
*********************************************************************************************************/
#define __IIC_SUB_W                   2
#define __IIC_SUB_R                   1
#define __IIC_SUB_NONE                0

/*********************************************************************************************************
  Offset of register
*********************************************************************************************************/
#define __B_IIC_SET                   0 /*  I20CONSET                   */
#define __B_IIC_STAT                  1 /*  I20STAT                     */
#define __B_IIC_DAT                   2 /*  I20DAT                      */
#define __B_IIC_ADR                   3 /*  I20ADR                      */
#define __B_IIC_SCLH                  4 /*  I20SCLH                     */
#define __B_IIC_SCLL                  5 /*  I20SCLL                     */
#define __B_IIC_CLR                   6 /*  I20CONCLR                   */

/*********************************************************************************************************
  State of interrupt
*********************************************************************************************************/
#define __SEND_START                  0x08
#define __SEND_RESTART                0x10
#define __SEND_SLA_W_ACK              0x18
#define __SEND_DATA_ACK               0x28
#define __SEND_SLA_W_NOACK            0x20
#define __SEND_DATA_NOACK             0x30
#define __LOSS_BUS                    0x38

#define __SEND_SLA_R_NOACK            0x48
#define __SEND_SLA_R_ACK              0x40
#define __RECV_DATA_ACK               0x50
#define __RECV_DATA_NOACK             0x58

#define __IICSTAT_SR_SLA_START		  0x60
#define __IICSTAT_SR_SLA_START2		  0x68
#define __IICSTAT_SR_ALL_START		  0x70
#define __IICSTAT_SR_ALL_START2		  0x78
#define __IICSTAT_SR_DATASLA_ACK	  0x80
#define __IICSTAT_SR_DATASLA_NOACK	  0x88
#define __IICSTAT_SR_DATAALL_ACK	  0x90
#define __IICSTAT_SR_DATAALL_NOACK	  0x98
#define __IICSTAT_SR_STOP			  0xA0

#define __IICSTAT_ST_SLA_START		  0xA8
#define __IICSTAT_ST_SLA_START2		  0xB0
#define __IICSTAT_ST_DATASLA_ACK	  0xB8
#define __IICSTAT_ST_DATASLA_NOACK	  0xC0
#define __IICSTAT_ST_DATALAST_ACK	  0xC8

#define __IDLE_STATE				  0xF8
/*********************************************************************************************************
  If this driver used in ucos system
*********************************************************************************************************/
#define __UCOSII_EN                   1  /* 1 enable UCOS,0 disable UCOS */

/*********************************************************************************************************
  Macro about ucos system
*********************************************************************************************************/

#if __UCOSII_EN > 0

#define __I2C_LOCK(nblock)  do {                                        \
                                uint8   ucErr;                          \
                                OSSemPend(nblock, 0, &ucErr);           \
                                if (ucErr != OS_ERR_NONE) {               \
                                    return  (OPERATE_FAIL);             \
                                }                                       \
                            } while (0)

#define __I2C_UNLOCK(nblock) do {                                       \
                                OSSemPost(nblock);                      \
                             } while(0)

#define __OS_ENTER_CIRCT()              OS_ENTER_CRITICAL()
#define __OS_EXIT_CIRCT()               OS_EXIT_CRITICAL()

#else

#define __I2C_LOCK(nblock)
#define __I2C_UNLOCK(nblock)

#define __OS_ENTER_CIRCT()
#define __OS_EXIT_CIRCT()

#endif                                                                  /*  __UCOSII_EN                 */
#endif



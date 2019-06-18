/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    exi2c.c
** Last modified Date:      2011-12-31
** Last Version:		    1.0
** Descriptions:		    expand i2c function:operate base on device descriptor
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2011-12-31
** Version:				    1.0
** Descriptions:		    NONE
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             zhangzongkai
** Modified Date:           2015-07-03
** Version:                 1.0
** Descriptions:
**
*********************************************************************************************************/
#include "app_cfg.h"
#include "bsp_int.h"
#include "i2c.h"
#include "uart.h"
#include "exi2c.h"
#include "i2cPrivate.h"

/*********************************************************************************************************
   Struct of operation of i2c device
*********************************************************************************************************/
static __EXI2C_INFO   __PCA9665_I2CData;

OS_EVENT    *PCA9665I2cSem;
OS_EVENT	*MboxExI2c;
/*********************************************************************************************************
   Pointer to Struct of operation of i2c device
*********************************************************************************************************/
const __EXPI2C_INFO   PCA9665DatePtr = &__PCA9665_I2CData;

/*********************************************************************************************************
** Function name:           __Write_Pca9665_Inderict_Addr
** Descriptions:            Set 9665 Indirect
** Input parameters:        eParm
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __Write_Pca9665_Inderict_Addr (__EXPI2C_INFO eParm, uint8 InAddr, uint8 value)
{
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= eParm->pucAddrBase;

	pucAddrBase[E9665_INDPTR_REG]	= InAddr;
	pucAddrBase[E9665_INDIRECT_REG]	= value;
}

/*********************************************************************************************************
** Function name:           PCA9665_Reset
** Descriptions:            Send two bytes 0xA5,0x5A to PCA9665 reset register 0x05
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void PCA9665_Reset (__EXPI2C_INFO eParm)
{
    volatile uint8 *pucAddrBase;

    pucAddrBase = eParm->pucAddrBase;

    pucAddrBase[E9665_INDPTR_REG]  = 0x05;
    pucAddrBase[E9665_INDIRECT_REG]  = 0xA5;
    pucAddrBase[E9665_INDIRECT_REG]  = 0x5A;
}
/*********************************************************************************************************
** Function name:           exi2cStart
** Descriptions:
** Input parameters:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void exi2cStart (__EXPI2C_INFO eParm)
{
	volatile uint8     *pucAddrBase;

	pucAddrBase = eParm->pucAddrBase;
	eParm->ucIICflag = I2C_BUSY;
	pucAddrBase[E9665_I2CCON_REG]  = 0x61;		/* ENSIO = 1, STA = 1, Mode = 1 */
}

/*********************************************************************************************************
** Function name:           exI2cEndBus
** Descriptions:
** Input parameters:        eParm--
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __exI2cEndBus (__EXPI2C_INFO eParm)
{
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= eParm->pucAddrBase;
    pucAddrBase[E9665_I2CCON_REG] = 0x51;   /* bus error,end bus.STO */
	eParm->ucIICflag   = I2C_ERR;
	OSMboxPost(MboxExI2c, &eParm->ucIICflag);
}

/*********************************************************************************************************
** Function name:           __exI2cDateWrite
** Descriptions:            expand i2c write data
** Input parameters:        eParm
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __exI2cDateWrite (__EXPI2C_INFO eParm)
{

	volatile 	uint8 	           *pucAddrBase;
	uint16 i;
	pucAddrBase	= eParm->pucAddrBase;

	if(eParm->usDataNum == 0) {
		pucAddrBase[E9665_I2CCON_REG] = 0x51; /* set stop bit,clear interrupt flag and start bit */
		eParm->ucIICflag   = I2C_MASTER_WRITE_END;
		OSMboxPost(MboxExI2c, &eParm->ucIICflag);
	}
	else {
		pucAddrBase[E9665_INDPTR_REG]  	 = 0x00;				/* set count register*/
		pucAddrBase[E9665_INDIRECT_REG]  = eParm->usDataNum;	/* count */
		i = 0;
		while( eParm->usDataNum > 0) {
			pucAddrBase[E9665_I2CDAT_REG] = eParm->pucDataBuf[i++];
			eParm->usDataNum--;
		}
		pucAddrBase[E9665_I2CCON_REG]= 0x41; /* clear interrupt flag and start flag */
	}
}

/*********************************************************************************************************
** Function name:           exI2cDateRead
** Descriptions:
** Input parameters:        Parm
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __exI2cDateRead (__EXPI2C_INFO eParm)
{

	volatile 	uint8 	           *pucAddrBase;
	uint16 i;
	pucAddrBase	= eParm->pucAddrBase;

	for (i = 0; i < eParm->usDataNum; i++) {
		eParm->pucDataBuf[i] = pucAddrBase[E9665_I2CDAT_REG];
	}

	pucAddrBase[E9665_I2CCON_REG] = 0x51;     /* set stop bit,clear interrupt flag and start bit */
	eParm->ucIICflag   = I2C_MASTER_READ_END;
	OSMboxPost(MboxExI2c, &eParm->ucIICflag);

}

//this is used in interrupt mode

static void __exI2cIRQ(__EXPI2C_INFO eParm)
{
	uint8				ucSta;
	volatile 	uint8 	*pucAddrBase;
	int32 i,j;
	pucAddrBase	= eParm->pucAddrBase;

	for (i = 0; i < 10; i++)
		for(j = 0; j < 5000; j++);

	ucSta = pucAddrBase[E9665_I2CSTA_REG];                  /* get i2c state */

	switch(ucSta) {

   			case __SEND_START:
			case __SEND_RESTART:
        		pucAddrBase[E9665_I2CCON_REG] = 0x41;       /* clear interrupt and statr flag*/
				break;
			case __SEND_SLA_W_ACK:                          /* sended SLA+W and receive ACK */
			case __SEND_DATA_ACK:                           /* sending data and receive ACK */
       			if (eParm->ucI2CSubAddrCtl == __IIC_SUB_R) {/* read operation send subaddress */
					pucAddrBase[E9665_INDPTR_REG] = 0x00;	/* set count register */
					pucAddrBase[E9665_INDIRECT_REG] = (eParm->usDataNum | 0x80);/* count of will receive */
					pucAddrBase[E9665_I2CDAT_REG] = eParm->ucSLAddrHead[0];
					exi2cStart(eParm);
				} else if (eParm->ucI2CSubAddrCtl == __IIC_SUB_W) { /* write operation send subaddress */
					__exI2cDateWrite(eParm);
				} else {
					__exI2cDateWrite(eParm);
				}
				break;
			case __SEND_SLA_W_NOACK:                        /* send SLA_W and receive NoACK */
			case __SEND_DATA_NOACK:                         /* send date and receive NoACK */
			case __LOSS_BUS:                                /* lost the arbitration */
			case __SEND_SLA_R_NOACK:                        /* send SLA+R and receive NoACK */
	    		__exI2cEndBus ( eParm );                    /* end bus */
				break;

			case __RECV_DATA_ACK:                           /* receive date and ACK */
			case __RECV_DATA_NOACK:                         /* receive all dates and receive NoACK */
				__exI2cDateRead ( eParm );
				break;

			case __IDLE_STATE:
				eParm->ucIICflag = I2C_IDLE;
				break;

			default:
        		__exI2cEndBus ( eParm );                    /* end bus */
				break;
		}

}

void ExI2cIRQ (void)
{
	__exI2cIRQ(PCA9665DatePtr);
	EXTINT = 0x04;
}

/*********************************************************************************************************
** Function name:           __i2cSetMode
** Descriptions:            set i2c speed
** Input parameters:        eParm
**							i2cMode
**                          i2cSclh
**                          i2cScll
** Output parameters:       NONE
** Returned value:          OPERATE_FAIL
**                          OPERATE_SUCCESS
*********************************************************************************************************/
static void __exi2cSetMode(__EXPI2C_INFO eParm,uint8 i2cMode,uint8 i2cSclh,uint8 i2cScll)
{
	volatile uint8     *pucAddrBase;

	pucAddrBase = eParm->pucAddrBase;
	pucAddrBase[E9665_INDPTR_REG]  = 0x06;		/* set i2c bus mode ,Indirect register 0x06 */
	pucAddrBase[E9665_INDIRECT_REG]  = i2cMode;

	pucAddrBase[E9665_INDPTR_REG]  = 0x03;		/* set i2c speed register 0x03 */
	pucAddrBase[E9665_INDIRECT_REG]  = i2cSclh;

	pucAddrBase[E9665_INDPTR_REG]  = 0x02;		/* set i2c speed register 0x02 */
	pucAddrBase[E9665_INDIRECT_REG]  = i2cScll;
}

int32 exi2cSetMode(__EXPI2C_INFO eParm, uint8 i2cMode)
{
	__I2C_LOCK(PCA9665I2cSem);
	switch(i2cMode) {
		case STANDARD_MODE:
			__exi2cSetMode(eParm, STANDARD_MODE, 0x86, 0x9d);
			break;
		case FAST_MODE:
			__exi2cSetMode(eParm, FAST_MODE, 0x14, 0x2c);
			break;
		case FAST_MODE_PLUS:
			__exi2cSetMode(eParm, FAST_MODE_PLUS, 0x09, 0x11);
			break;
		case TURBO_MODE:
			__exi2cSetMode(eParm, TURBO_MODE, 0x05, 0x0e);
			break;
	}
	__I2C_UNLOCK(PCA9665I2cSem);
	return OPERATE_SUCCESS;
}

int32 exi2cSetTimeout(__EXPI2C_INFO eParm, uint8 timeoutval)
{
	__I2C_LOCK(PCA9665I2cSem);
	__Write_Pca9665_Inderict_Addr (eParm, 0x04, timeoutval);/* set i2c timeout register 0x04 */
	__I2C_UNLOCK(PCA9665I2cSem);
	return OPERATE_SUCCESS;
}


int exi2cInit (void)
{
	volatile uint8 *pucAddrBase;

/* Creat semaphore */
    PCA9665I2cSem = OSSemCreate(1);
    if(PCA9665I2cSem == NULL) {
        UART0_SendStr("ExI2c Sem create failed\n");
        return OPERATE_FAIL;
    }

    MboxExI2c = OSMboxCreate((void *)0);
 	if(MboxExI2c == (void *)NULL) {
        UART0_SendStr("ExI2c MBox create failed\n");
        return OPERATE_FAIL;
 	}
/* initial parameter */
	PCA9665DatePtr->pucAddrBase   = (uint8*)E9665_I2C_BASE_ADDR;
	PCA9665DatePtr->ucIICflag     = I2C_IDLE;
	PCA9665DatePtr->ucSlave       = __IIC_MASTER;
	PCA9665DatePtr->usDataNum     = 0;

	pucAddrBase = PCA9665DatePtr->pucAddrBase;

	PCA9665_Reset(PCA9665DatePtr);
	exi2cSetMode(PCA9665DatePtr, STANDARD_MODE);
   	exi2cSetTimeout(PCA9665DatePtr, 0xe3);
    pucAddrBase[E9665_I2CCON_REG]  = 0x41;/* ENSIO = 1, Mode = 1 apply in master buffer mode*/

	BSP_IntVectSet(	(INT8U)I2C_EINT2_IRQ,
						(INT8U)EXI2C_ISR_PRIORITY,
						(INT8U)BSP_INT_SRC_TYPE_IRQ,
						(OS_FNCT_VOID)ExI2cIRQ );
	BSP_IntEn(I2C_EINT2_IRQ);
    //SetVICIRQ(I2C_EINT2_IRQ, EXI2C_ISR_PRIORITY, (uint32)ExI2cIRQ);
    return OPERATE_SUCCESS;
}

int32 exi2cRead (uint8  *headBuf,uint8 headBytes,uint8 *retData,uint16 retBytes)
{
	uint8 err;
	uint8 *getMboxFlag = NULL;
	volatile uint8     *pucAddrBase;
	uint8 i;
	pucAddrBase = PCA9665DatePtr->pucAddrBase;

	if(retBytes < 1 || headBytes > 68) {
	    UART0_SendStr("PCA9665 Read Byte Error!\n");
		return OPERATE_FAIL;
	}
     __I2C_LOCK(PCA9665I2cSem);                               /* apply for semaphore */
	if (PCA9665DatePtr->ucIICflag == I2C_BUSY) {
		__I2C_UNLOCK(PCA9665I2cSem);                          /* release semaphore */
		UART0_SendStr("PCA9665 Read Busy!\n");
		return OPERATE_FAIL;
	}
	PCA9665DatePtr->ucSLAddrHead      = headBuf;
	PCA9665DatePtr->ucSLAddrNum       = headBytes;
	PCA9665DatePtr->ucI2CSubAddrCtl   = __IIC_SUB_R;
	PCA9665DatePtr->pucDataBuf        = retData;
	PCA9665DatePtr->usDataNum         = retBytes;

	if(headBytes == 1) {
		pucAddrBase[E9665_INDPTR_REG]  	 = 0x00;					/* set count register */
		pucAddrBase[E9665_INDIRECT_REG]  = (retBytes | 0x80);		/* count */
		pucAddrBase[E9665_I2CDAT_REG] 	 = headBuf[0];
	}
	else {
		pucAddrBase[E9665_INDPTR_REG]  = 0x00;						/* set count register */
		pucAddrBase[E9665_INDIRECT_REG]  = headBytes;				/* count */

		for (i = 0; i < headBytes; i++) {
	 		if(i == 0) {
				pucAddrBase[E9665_I2CDAT_REG] = (headBuf[i] & 0xFE);
			}
			else {
				pucAddrBase[E9665_I2CDAT_REG] = headBuf[i];
			}
		}
	}
	exi2cStart(PCA9665DatePtr);
	getMboxFlag = OSMboxPend(MboxExI2c, OS_TICKS_PER_SEC, &err);
	if (err == OS_ERR_NONE) {
		if(*getMboxFlag == I2C_MASTER_READ_END) {
            __I2C_UNLOCK(PCA9665I2cSem);                          /* release semaphore */
			return OPERATE_SUCCESS;
		}
	}
	UART0_Printf("PCA9665 Read[%d]!\n",*getMboxFlag);
    __I2C_UNLOCK(PCA9665I2cSem);                          /* release semaphore */
	return OPERATE_FAIL;
}

int32 exi2cWrite ( uint8 *headBuf,uint8 headBytes,uint8 *dataBuf,uint16 dataBytes)
{
	uint8 err;
	uint8 *getMboxFlag = NULL;
    volatile uint8     *pucAddrBase;
	uint16	i;
	pucAddrBase = PCA9665DatePtr->pucAddrBase;

	if(headBytes > 68) {
        UART0_SendStr("PCA9665 Write Bytes Error!\n");
		return OPERATE_FAIL;
	}
    __I2C_LOCK(PCA9665I2cSem);
	if (PCA9665DatePtr->ucIICflag == I2C_BUSY) {
        UART0_SendStr("PCA9665 Write Busy!\n");
	     __I2C_UNLOCK(PCA9665I2cSem);
	    return OPERATE_FAIL;
	}
	PCA9665DatePtr->ucSLAddrHead    = headBuf;
	PCA9665DatePtr->ucSLAddrNum     = headBytes;
	PCA9665DatePtr->ucI2CSubAddrCtl = __IIC_SUB_W;
	PCA9665DatePtr->pucDataBuf      = dataBuf;
	PCA9665DatePtr->usDataNum       = dataBytes;

	pucAddrBase[E9665_INDPTR_REG]  = 0x00;			/* set count register*/
	pucAddrBase[E9665_INDIRECT_REG]  = headBytes;	/* count */

	for (i = 0; i < headBytes; i++) {
		 pucAddrBase[E9665_I2CDAT_REG] = headBuf[i];
	}
	exi2cStart(PCA9665DatePtr);
	getMboxFlag = OSMboxPend(MboxExI2c, OS_TICKS_PER_SEC, &err);
	if (err == OS_ERR_NONE) {
		if(*getMboxFlag == I2C_MASTER_WRITE_END) {
            __I2C_UNLOCK(PCA9665I2cSem);                          /* release semaphore */
			return OPERATE_SUCCESS;
		}
	}
	UART0_Printf("PCA9665 Write[%d]!\n",*getMboxFlag);
    __I2C_UNLOCK(PCA9665I2cSem);                          /* release semaphore */
	return OPERATE_FAIL;
}

int32 exi2cGetFlag (void)
{
	return PCA9665DatePtr->ucIICflag;
}

/*********************************************************************************************************
   END FILE
*********************************************************************************************************/


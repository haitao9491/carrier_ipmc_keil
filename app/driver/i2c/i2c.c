/***********************************************Copyright (c)*********************************************
**                                BeiJing Shiyuan Telecom Technology Co.,LTD.
**
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    IIC.c
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    I2C函数实现，采用设备描述符来操作
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    lixiaocheng
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:		    无
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    wangxiumei
** Modified Date:		    2011-12-22
** Version:				    1.1
** Descriptions:		    增加了I2C对UCOSII操作系统的兼容
**
*********************************************************************************************************/
#include "config.h"
#include "i2cPrivate.h"
#include "i2c.h"
#include "app_cfg.h"

//#define I2CMBOX


/*********************************************************************************************************
   定义操作I2C器件的结构体，有多个器件就需要声明多个结构体
*********************************************************************************************************/
static __I2C_INFO   __I2C0Data;
static __I2C_INFO   __I2C1Data;
static __I2C_INFO   __I2C2Data;

uint8 DataBuffer0[DATA_BUFFER_SIZE];
uint8 DataBuffer1[DATA_BUFFER_SIZE];
uint8 DataBuffer2[DATA_BUFFER_SIZE];

I2c_MemCopy_FiFo g_I2C_MemCpy_fifo; 	//used as mem copy mailbox data

/*********************************************************************************************************
   是操作系统就申明信号量
*********************************************************************************************************/
#if __UCOSII_EN > 0
    OS_EVENT       *GposeI2c0Sem;
    OS_EVENT       *GposeI2c1Sem;
    OS_EVENT       *GposeI2c2Sem;
    OS_EVENT      **GpposeI2cTable[__IIC_MAX_NUM] = {&GposeI2c0Sem, &GposeI2c1Sem, &GposeI2c2Sem};
#endif

#ifdef I2CMBOX
	OS_EVENT		*I2C0Mbox;
	OS_EVENT		*I2C1Mbox;
	OS_EVENT		*I2C2Mbox;
	OS_EVENT		**I2CMboxTable[__IIC_MAX_NUM] = {&I2C0Mbox, &I2C1Mbox, &I2C2Mbox};

#endif
/*********************************************************************************************************
   下面使用指针数组来保存结构体指针,方便对该驱动的扩展
*********************************************************************************************************/
const __PI2C_INFO   __GpiinfoDateTab[__IIC_MAX_NUM] = {&__I2C0Data, &__I2C1Data, &__I2C2Data};

/*********************************************************************************************************
   下面定义了I2C0基地址值，如果有多个I2C器件可以在该位置添加相应的基地址即可
*********************************************************************************************************/
const uint32        __GuiI2cBaseAddrTab[__IIC_MAX_NUM] = {I2C0_BASE_ADDR, I2C1_BASE_ADDR, I2C2_BASE_ADDR};

#ifdef INFO_COLLECT
struct info_collect i2cInfo[3];
#endif

extern OS_EVENT *I2c_Q;
extern void UART0_SendStr(char *);

#ifdef INFO_COLLECT
void initI2cInfo(uint8 id)
{
	memset(&i2cInfo[id], 0, sizeof(struct info_collect));
}

void getI2cInfo(uint8 *data, uint8 *bytes) {

	*bytes = 3*sizeof(struct info_collect);
	memcpy(data, i2cInfo, *bytes);
}

#endif

I2c_MemCopy_Entry * get_I2c_mailbox_buf(void)
{
	I2c_MemCopy_Entry *ptr = &(g_I2C_MemCpy_fifo.entry[g_I2C_MemCpy_fifo.index++]);
	if(g_I2C_MemCpy_fifo.index >= I2C_MEM_COPY_ENTRY_NUM)
		g_I2C_MemCpy_fifo.index = 0;
	return ptr;	
}

/*********************************************************************************************************
** Function name:           endBus
** Descriptions:            总线错误结束总线，改函数被__i2cISR调用
** Input parameters:        Parm--I2C设备描述符结构体指针
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __endBus (__PI2C_INFO Parm)
{
	            uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

    Parm->ucIICflag     = I2C_ERR;
	Parm->ucSlave   = __IIC_MASTER;


	pucAddrBase[__B_IIC_SET << uiOffBase] = 0x14;                     /*  总线出错，结束总线.STO      */
	pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;                       /*  总线出错，清零STA,SI     */

}
/* I2C作为主机时，正确发送完或读完数据时，结束总线前，发送此标志给读写函数 */
static void __retAck (__PI2C_INFO Parm)
{
	#ifdef I2CMBOX
		Parm->i2cintendflag = 1;
		OSMboxPost(*I2CMboxTable[Parm->uiID], (void *)&Parm->i2cintendflag);
	#endif
}
/* I2C作为主机时，发送完SLA+W/R后，收到NACK，结束总线前，发送此标志给读写函数 */
static void __retNack (__PI2C_INFO Parm)
{
	#ifdef I2CMBOX
		Parm->i2cintendflag = 2;
		OSMboxPost(*I2CMboxTable[Parm->uiID], (void *)&Parm->i2cintendflag);
	#endif
}

/* I2C作为主机时，发送一半数据后，丢失总线，结束总线前，发送此标志给读写函数 */
static void __retLossBus (__PI2C_INFO Parm)
{
	#ifdef I2CMBOX
		Parm->i2cintendflag = 3;
		OSMboxPost(*I2CMboxTable[Parm->uiID], (void *)&Parm->i2cintendflag);
	#endif
}

/* I2C收到其它状态标志时，结束总线前，发送此标记给读写函数 */
static void __retOtherStatus (__PI2C_INFO Parm)
{
	#ifdef I2CMBOX
		Parm->i2cintendflag = 4;
		OSMboxPost(*I2CMboxTable[Parm->uiID], (void *)&Parm->i2cintendflag);
	#endif
}
/*********************************************************************************************************
** Function name:           AddrWrite
** Descriptions:            写入从机地址，改函数被__i2cISR调用
** Input parameters:        Parm--I2C设备描述符结构体指针
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __AddrWrite (__PI2C_INFO Parm)
{
	            uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

	pucAddrBase[__B_IIC_DAT << uiOffBase] = (uint8)(Parm->ucSLAddr);

	pucAddrBase[__B_IIC_SET << uiOffBase]     = 0x04;
	pucAddrBase[__B_IIC_CLR << uiOffBase]     = 0x28;                   /*  清除中断标志                */
}

/*********************************************************************************************************
** Function name:           dateWrite
** Descriptions:            写入数据，改函数被__subAddrWrite调用
** Input parameters:        Parm--I2C设备描述符结构体指针
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __dataWrite (__PI2C_INFO Parm)
{
	            uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

	if (Parm->usDataMasterNum > 0) {
		pucAddrBase[__B_IIC_DAT << uiOffBase] = Parm->pucDataMasterBuf[Parm->usMasterCounter++];
		Parm->usDataMasterNum--;
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;                   /*  清零SI               */

	} else {
		Parm->ucIICflag = I2C_MASTER_WRITE_END;						        /*  设置总线结束标志            */

		__retAck(Parm);

		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x14;                   /*  无数据发送结束总线          */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;

	}
}

/*********************************************************************************************************
** Function name:           __dataMasterRead
** Descriptions:            I2C主读操作
** Input parameters:        Parm--I2C设备描述符结构体指针
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __dataMasterRead(__PI2C_INFO Parm)
{
	uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

	if (Parm->usMasterCounter < (Parm->usDataMasterNum - 1)) {
		Parm->pucDataMasterBuf[Parm->usMasterCounter] = pucAddrBase[__B_IIC_DAT << uiOffBase];

		if(Parm->usMasterCounter == (Parm->usDataMasterNum - 2)) {
			Parm->usMasterCounter++;
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x04;
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;                   /*  清零SI ,AA      */
		} else {
			Parm->usMasterCounter++;
			pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;                   /*  清零SI          */
		}

	} else {
		Parm->pucDataMasterBuf[Parm->usMasterCounter] = pucAddrBase[__B_IIC_DAT << uiOffBase];

        UART0_Printf("i2c MRead data is %02x\n", pucAddrBase[__B_IIC_DAT << uiOffBase]);

		Parm->ucIICflag = I2C_MASTER_READ_END;						        /*  设置总线结束标志            */

  		__retAck(Parm);

		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x14;                   /*  无数据接收结束总线          */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;

	}
}

/*********************************************************************************************************
** Function name:           __dateReadEnd
** Descriptions:            写入数据，改函数被__subAddrWrite调用
** Input parameters:        Parm--I2C设备描述符结构体指针
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static uint8 __dataReadEnd (__PI2C_INFO Parm)
{
	uint8 err;
	I2c_MemCopy_Entry *I2cMem_PtrGet;

	if (Parm->i2cSlaveErrFlag == 1) {
		return 1;
	}
	I2cMem_PtrGet = get_I2c_mailbox_buf();
	if(Parm->usDataSlaveNum > I2C_MEMCPY_BUF_SIZE)
		I2cMem_PtrGet->len = I2C_MEMCPY_BUF_SIZE;
	else 
		I2cMem_PtrGet->len = Parm->usDataSlaveNum;
	I2cMem_PtrGet->i2cID = Parm->uiID;

	memcpy(I2cMem_PtrGet->databuf, Parm->pucDataSlaveBuf, I2cMem_PtrGet->len);

	err = OSQPost(I2c_Q, I2cMem_PtrGet);

	#ifdef INFO_COLLECT
	i2cInfo[Parm->uiID].rxTLLCnt++;
	#endif
	return err;
}
/*********************************************************************************************************
** Function name:           ISR_I2C
** Descriptions:
** Input parameters:
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __i2cISR (__PI2C_INFO Parm)
{
	            uint8				ucSta;
	            uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

	ucSta = pucAddrBase[__B_IIC_STAT << uiOffBase];                     /*  获取I2C状态码               */
	//UART0_Printf("i2c status reg:%x\n",ucSta);
	switch(ucSta) {

    case __SEND_START:                                                  /*  已发送起始条件,共用写函数   */
	case __SEND_RESTART:                                                /*  重新启动总线后，发送从机地址*/

		__AddrWrite ( Parm );
		break;

	case __SEND_SLA_W_ACK:												/*  已发送SLA+W并已经接收应答    */
	case __SEND_DATA_ACK:                                               /*  发送数据，已接收应答         */
	                                                                    /*  这两种情况都使用下面函数     */
        __dataWrite( Parm );                                            /*  I2C写数据和地址在一起        */

		break;

	case __SEND_SLA_R_ACK:
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;	/* clear SI */
		break;

	case __RECV_DATA_ACK:
	case __RECV_DATA_NOACK:

		__dataMasterRead(Parm);
		break;

	case __SEND_SLA_W_NOACK:                                            /*  发送SLA_W,收到非应答         */
	case __SEND_SLA_R_NOACK:											/*  发送SLA_R,收到非应答		 */
		__retNack (Parm);
		__endBus(Parm);
		break;
	case __LOSS_BUS:                                                    /*  丢失仲裁                     */
	case __SEND_DATA_NOACK:                                             /*  发送数据，收到非应答         */
	    __retLossBus (Parm);                                            /*  以上四中情况都要结束总线     */
	    __endBus( Parm );                                               /*  结束总线                     */
		break;

	case __IICSTAT_SR_SLA_START:
	case __IICSTAT_SR_SLA_START2:
	case __IICSTAT_SR_ALL_START:
	case __IICSTAT_SR_ALL_START2:
			Parm->ucIICflag = I2C_BUSY;
			Parm->ucSlave   = __IIC_SLAVER;
			Parm->usDataSlaveNum = 0;
			Parm->i2cSlaveErrFlag = 0;
			Parm->pucDataSlaveBuf[Parm->usDataSlaveNum] = pucAddrBase[__B_IIC_ADR << uiOffBase];
			Parm->usDataSlaveNum++;
			pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;	/* clear SI */

		break;

	case __IICSTAT_SR_DATASLA_ACK:
	case __IICSTAT_SR_DATAALL_ACK:
		if(Parm->usDataSlaveNum < DATA_BUFFER_SIZE) {
			Parm->pucDataSlaveBuf[Parm->usDataSlaveNum] = pucAddrBase[__B_IIC_DAT << uiOffBase];
			Parm->usDataSlaveNum++;
		}
		else {
			Parm->i2cSlaveErrFlag = 1;
		}
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;	/* clear SI */

		break;

	case __IICSTAT_SR_DATASLA_NOACK:
	case __IICSTAT_SR_DATAALL_NOACK:
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;	/* clear SI */

		break;
	case __IICSTAT_SR_STOP:
		__dataReadEnd( Parm );
		Parm->ucIICflag = I2C_SLAVE_READ_END;
		Parm->ucSlave   = __IIC_MASTER; //切换回主机模式
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x08;	/* clear SI */

		break;
	default:
		__retOtherStatus(Parm);                                         /*  其他状态      */
        __endBus( Parm );                                               /*  结束总线      */
		break;
	}
}

/*********************************************************************************************************
** Function name:           I2CxIRQ
** Descriptions:            i2cx interrupt service
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void i2c0IRQ ( void )
{
	__i2cISR(__GpiinfoDateTab[0]);
}

void i2c1IRQ ( void )
{
	__i2cISR(__GpiinfoDateTab[1]);
}

void i2c2IRQ ( void )
{
	__i2cISR(__GpiinfoDateTab[2]);
}
/*********************************************************************************************************
** Function name:           I2CInit
** Descriptions:            initial of i2c
** Input parameters:        ID              device id
**							ucSlave			master or slave
**							ucAddr			I2C address
** Output parameters:       NONE
** Returned value:          PIN_ERR
**                          OPERATE_FAIL
**                          OPERATE_SUCCESS
*********************************************************************************************************/

int	i2cInit ( uint32 ID,
                     uint8 ucAddr,
                      uint8 *Buf )
{
	volatile uint8 *pucAddrBase;
	volatile uint32 uiOffBase;

	/*
	 *  参数过滤,判断
	 */
	if ( ID >= __IIC_MAX_NUM ) {
	    return OPERATE_FAIL;
	}

	/*
	 *  创建信号量，操作系统部分
	 */
#if __UCOSII_EN > 0
    *GpposeI2cTable[ID] = OSSemCreate(1);
    if(*GpposeI2cTable[ID] == (void *)NULL) {                       /*  如果创建信号量失败返回错误  */
        UART0_SendStr("Sem create failed\n");
        return OPERATE_FAIL;
    }
#endif

#ifdef I2CMBOX
 	*I2CMboxTable[ID] = OSMboxCreate((void *)0);
 	if(*I2CMboxTable[ID] == (void *)NULL) {
 		UART0_SendStr("i2c Mbox create failed\n");
 		return OPERATE_FAIL;
 	}
#endif

	/*
	 *  初始化一些参数
	 */
	__GpiinfoDateTab[ID]->uiID          = ID;
	__GpiinfoDateTab[ID]->pucAddrBase   = (uint8*)__GuiI2cBaseAddrTab[ID];
	__GpiinfoDateTab[ID]->uiOffBase     = 2;
	__GpiinfoDateTab[ID]->ucIICflag     = I2C_IDLE;                     /*  标识该器件现在空闲          */
	__GpiinfoDateTab[ID]->ucSlave       = __IIC_MASTER;                 /*  标识该器件为从机            */
	__GpiinfoDateTab[ID]->usDataMasterNum    = 0;
	__GpiinfoDateTab[ID]->usDataSlaveNum     = 0;
	__GpiinfoDateTab[ID]->usMasterCounter    = 0;

#ifdef I2CMBOX
	__GpiinfoDateTab[ID]->i2cintendflag     = 0;
#endif


	pucAddrBase = __GpiinfoDateTab[ID]->pucAddrBase;	                /*  获取指针参数                */
	uiOffBase   = __GpiinfoDateTab[ID]->uiOffBase;

	*(uint16*)(pucAddrBase+(__B_IIC_SCLH << uiOffBase) ) = 100;
	                                                                    /*  设置时钟高电平时间          */

	*(uint16*)(pucAddrBase+(__B_IIC_SCLL << uiOffBase) ) = 100;
	                                                                    /*  设置时钟低电平时间          */
    *(uint8*)(pucAddrBase+(__B_IIC_ADR << uiOffBase) ) = (ucAddr);        /*  设置I2C地址,未使能通用调用地址 */

    __GpiinfoDateTab[ID]->pucDataSlaveBuf  = Buf;					/*  保存数据的缓冲区            */
    __GpiinfoDateTab[ID]->pucDataMasterBuf = NULL;
    pucAddrBase[__B_IIC_CLR << uiOffBase]  = 0x28;
    pucAddrBase[__B_IIC_SET << uiOffBase]  = 0x44;                      /*  设置从模式 	*/

#ifdef INFO_COLLECT
    initI2cInfo(ID);
#endif

    return OPERATE_SUCCESS;
}


/*********************************************************************************************************
** Function name:           i2cSetMode
** Descriptions:            设置I2C速度，主要用在初始化后用户想改变I2C参数，暂时该函数只开放设置主从模式和速度。
**                          如果写入速度大于400K，则设置成系统默认的300K
** Input parameters:        ID   器件子设备号,例如ID=0,表示操作的设备是I2C0
**				            speed	设置I2C速度
**				 	        ucSlave  设置I2C工作模式
**				            Rsv	 保留参数
** Output parameters:       NONE
** Returned value:          OPERATE_FAIL    设置失败
**                          OPERATE_SUCCESS 设置成功
*********************************************************************************************************/
int32 i2cSetMode (uint32   ID,
				   uint32	speed,
                   uint8   ucSlave)
{
	volatile uint8     *pucAddrBase;
	volatile uint32     uiOffBase;

	pucAddrBase = __GpiinfoDateTab[ID]->pucAddrBase;
	uiOffBase   = __GpiinfoDateTab[ID]->uiOffBase;

	if (ID < __IIC_MAX_NUM) {

		/*
		 *  参数过滤
		 */
		if (speed > 400000) {
		    speed = 300000;
		}

    	__I2C_LOCK(*GpposeI2cTable[ID]);                                /*  申请I2C资源                 */

		                                                                /*  设置速度                    */
		*(uint16*)(pucAddrBase + (__B_IIC_SCLH << uiOffBase)) = (uint16)((Fpclk / speed) / 2);
		*(uint16*)(pucAddrBase + (__B_IIC_SCLL << uiOffBase)) = (uint16)((Fpclk / speed) / 2);
		__GpiinfoDateTab[ID]->ucSlave       = ucSlave;

        __I2C_UNLOCK(*GpposeI2cTable[ID]);                              /*  释放I2C资源                 */

		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

/*********************************************************************************************************
** Function name:           __i2cStart
** Descriptions:            启动I2C总线
** Input parameters:        ID   器件子设备号,例如ID=0,表示操作的设备是I2C0
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static uint8 __i2cStart (uint32 ID)
{
	volatile uint8     *pucAddrBase;
	volatile uint32     uiOffBase;

	pucAddrBase = __GpiinfoDateTab[ID]->pucAddrBase;
	uiOffBase   = __GpiinfoDateTab[ID]->uiOffBase;

	if (__GpiinfoDateTab[ID]->ucIICflag == I2C_BUSY) {
		    return OPERATE_FAIL;
	}
	__GpiinfoDateTab[ID]->ucIICflag = I2C_BUSY;

	pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;                       /*  启动总线,设置为主机         */
	pucAddrBase[__B_IIC_SET << uiOffBase] = 0x64;

	return OPERATE_SUCCESS;
}


/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:
** Input parameters:        ID			   : which i2c device
**                          Buf 		   : pointer to memory which to write
**                          Nbyte          : write lengh
** Output parameters:       NONE
** Returned value:          success        : OPERATE_SUCCESS
**                          fail           : OPERATE_FAIL
*********************************************************************************************************/

int32 i2cWrite (uint32  ID,
				uint8	Addr,
                uint8  *Buf,
                uint16  Nbyte)
{
#ifdef I2CMBOX
	uint8 err;
	uint8 i2cflag;
#endif

#ifdef I2CPOLLEND
	uint8 j;
#endif
	uint8 i2cbuf[64];

	if (Nbyte == 0) {
	    return I2C_RET_ERR;                 /* Can't no write (0 byte is wrong)*/
	}

    if(Nbyte > DATA_BUFFER_SIZE) {
		return I2C_RET_ERR;
	}

	if (ID < __IIC_MAX_NUM) {
         __I2C_LOCK(*GpposeI2cTable[ID]);   /* Apply semaphore */

		memset(i2cbuf, 0, sizeof(i2cbuf));
		memcpy(i2cbuf, Buf, Nbyte);
    	__GpiinfoDateTab[ID]->ucSLAddr        	= (uint8)(Addr & 0xfe); /* Slave address */
		__GpiinfoDateTab[ID]->pucDataMasterBuf  = i2cbuf;               /* Write buffer */
		__GpiinfoDateTab[ID]->usDataMasterNum   = Nbyte;                /* Num of write */
		__GpiinfoDateTab[ID]->usMasterCounter 	= 0;
#ifdef I2CMBOX
		__GpiinfoDateTab[ID]->i2cintendflag  	= 0;
		i2cflag = 0;
#endif

		if(__i2cStart(ID) == OPERATE_FAIL) {
			__I2C_UNLOCK(*GpposeI2cTable[ID]);
			return I2C_RET_BUS_BUSY;
		}

#ifdef I2CMBOX
		i2cflag = *(uint8 *)OSMboxPend(*I2CMboxTable[ID], I2C_SEM_GET_TIMEOUT, &err);
#ifdef INFO_COLLECT
		i2cInfo[ID].txTLLCnt++;
#endif
#ifdef TESTI2C
		tcp.txTotal++;
#endif
		if (err == OS_ERR_NONE) {
			if (i2cflag == 1) {
				#ifdef INFO_COLLECT
				i2cInfo[ID].txRCnt++;
				#endif
				#ifdef TESTI2C
				tcp.txRcnt++;
				#endif
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_SUCCESS;
			}
			else if (i2cflag == 2) {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_NO_PARTNER;
			}
			else if (i2cflag == 3) {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_LOSS_BUS;
			}
			else {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_ERR;
			}
		}
		else if (err == OS_ERR_TIMEOUT) {
			__endBus(__GpiinfoDateTab[ID]);
			__I2C_UNLOCK(*GpposeI2cTable[ID]);
			return I2C_RET_TIMEOUT;
		}
		else {
			__I2C_UNLOCK(*GpposeI2cTable[ID]);
			return I2C_RET_ERR;
		}
#endif

	}
	return I2C_RET_ERR;
}


int32 i2cMasterRead(uint32 ID, uint8 Addr, uint8 *Buf, uint16 Nbyte)
{
#ifdef I2CMBOX
	uint8 err;
	uint8 i2cflag;
#endif

	if(Nbyte == 0) {
		return I2C_RET_ERR;
	}
	if(Nbyte > DATA_BUFFER_SIZE) {
		return I2C_RET_ERR;
	}
	if (ID < __IIC_MAX_NUM) {
		__I2C_LOCK(*GpposeI2cTable[ID]);                                /* Apply semaphore */

		__GpiinfoDateTab[ID]->ucSLAddr = (uint8)((Addr & 0xfe) | 0x01); /* Slave address */
		__GpiinfoDateTab[ID]->pucDataMasterBuf = Buf;                   /* Read buffer */
		__GpiinfoDateTab[ID]->usDataMasterNum = Nbyte;                  /* Num of read */
		__GpiinfoDateTab[ID]->usMasterCounter = 0;
#ifdef I2CMBOX
		__GpiinfoDateTab[ID]->i2cintendflag = 0;
		i2cflag = 0;
#endif
		if(__i2cStart(ID) == OPERATE_FAIL) {
			__I2C_UNLOCK(*GpposeI2cTable[ID]);
			return I2C_RET_BUS_BUSY;
		}

#ifdef I2CMBOX
		i2cflag = *(uint8 *)OSMboxPend(*I2CMboxTable[ID], I2C_SEM_GET_TIMEOUT, &err);
		if (err == OS_ERR_NONE) {
			if (i2cflag == 1) {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_SUCCESS;
			}
			else if (i2cflag == 2) {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_NO_PARTNER;
			}
			else if (i2cflag == 3) {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_LOSS_BUS;
			}
			else {
				__I2C_UNLOCK(*GpposeI2cTable[ID]);
				return I2C_RET_ERR;
			}

		}

		__I2C_UNLOCK(*GpposeI2cTable[ID]);
		return I2C_RET_ERR;
#endif

	}
	return I2C_RET_ERR;
}
/*********************************************************************************************************
** Function name:           i2cGetFlag
** Descriptions:
** Input parameters:        ID             : which i2c device
** Output parameters:       NONE
** Returned value:          success        :
**                                           I2C_IDLE： idle
**                                           I2C_WRITE_END：write success
**                                           I2C_READ_END：read success
**                                           I2C_ERR：i2c bus error
**                                           I2C_BUSY：i2c bus busy
**                          fail           : OPERATE_FAIL
*********************************************************************************************************/

int32 i2cGetFlag (uint8 ID)
{

	if (ID < __IIC_MAX_NUM) {
		return __GpiinfoDateTab[ID]->ucIICflag;
	}
	return OPERATE_FAIL;
}
uint8	i2cGetHostFlag(uint8 ID)
{
	if (ID < __IIC_MAX_NUM) {
		return __GpiinfoDateTab[ID]->ucSlave;
	}
	return OPERATE_FAIL;
}
uint8 i2cSetFlagIdle (uint8 ID)
{
	if (ID < __IIC_MAX_NUM) {
	    __I2C_LOCK(*GpposeI2cTable[ID]);                /* Apply resource to affirm bus busy or idle*/

		__GpiinfoDateTab[ID]->ucIICflag = I2C_IDLE;
		__GpiinfoDateTab[ID]->ucSlave   = __IIC_MASTER;
		__I2C_UNLOCK(*GpposeI2cTable[ID]);              /* Release I2C resource*/
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

uint8 i2cGetIsrState (uint8 ID)
{
	            uint32				uiOffBase;
	volatile 	uint8 	           *pucAddrBase;

	pucAddrBase	= __GpiinfoDateTab[ID]->pucAddrBase;
	uiOffBase   = __GpiinfoDateTab[ID]->uiOffBase;

	return pucAddrBase[__B_IIC_STAT << uiOffBase];                     /* Get i2c state */
}
/*********************************************************************************************************
** Function name:           i2cGetRemainBytes
** Descriptions:            return i2c have how many bytes not sends
** Input parameters:        ID:which i2c device
** Output parameters:       NONE
** Returned value:          success: return bytes
**                          fail: OPERATE_FAIL
*********************************************************************************************************/
uint32 i2cGetRemainBytes(uint8 ID)
{
    if (ID < __IIC_MAX_NUM) {
        return __GpiinfoDateTab[ID]->usDataMasterNum;
    }
    return OPERATE_FAIL;
}

/*********************************************************************************************************
   END FILE
*********************************************************************************************************/





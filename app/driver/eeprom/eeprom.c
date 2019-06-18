/***********************************************Copyright (c)*********************************************
**                                BeiJing RuiYuanXin Telecom Technology Co.,LTD.
**
**                                       http://www.raycores.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    eeprom.c
** Last modified Date:      2018-11-29
** Last Version:		    1.0
** Descriptions:		    eeprom driver
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2018-11-29
** Version:				    1.0
** Descriptions:		    无
**
*********************************************************************************************************/
#include "uart.h"
#include "exi2c.h"
#include "eeprom.h"

//=======================================================================================================
//================ EEPROM 24XX series ===================================================================
//=======================================================================================================
/*********************************************************************************************************
** Function name:           eeprom_m24xx_page_size
** Descriptions:            set eeprom page base on eeprom type and addr
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          pg_sz:          page size (return)
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static int eeprom_m24xx_page_size(int eeprom_type, int eeprom_addr,int * pg_sz)
{
   int page_size,rc;

   page_size = 0;
   rc = I2C_NO_ERR;
   switch(eeprom_type)
   {
      case EEPROM_24XX04:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX04)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 16; // 24LC04B have page size = 16,24C04A = 8
         break;
      case EEPROM_24XX08:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX08)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 16;
         break;
      case EEPROM_24XX16:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX16)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 16;
         break;
      case EEPROM_24XX32:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX32)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 32;
         break;
      case EEPROM_24XX64:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX64)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 32;
         break;
      case EEPROM_24XX128:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX128)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 64;
         break;
      case EEPROM_24XX256:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX256)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 64;
         break;
      case EEPROM_24XX512:
         if(eeprom_addr > EEPROM_MAX_ADDR_24XX512)
            rc = I2C_ERR_24XX_BAD_ADDR;
         else
            page_size = 128;
         break;
   }
   if(rc != I2C_NO_ERR)
      return rc;
   if(page_size == 0)  //-- Bad eeprom_type
      return I2C_ERR_24XX_BAD_TYPE;

   if(pg_sz)
      *pg_sz = page_size;
   return I2C_NO_ERR;
}

/*********************************************************************************************************
** Function name:           m24xx_set_addr
** Descriptions:
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          eeprom_cs_val:  Hardware A2,A1,A0 (valid from 24XX32)
**                          * ctrl_val:     Value of ctrl(return)
**                          * addr_hi_val:  Value of addr_hi(return)
**                          * addr_lo_val:  Value of addr_lo(return)
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static int eeprom_m24xx_set_addr(int eeprom_type,int eeprom_addr,int eeprom_cs_val,
                          int * ctrl_val,int * addr_hi_val,int * addr_lo_val){
   int ctrl;
   int addr_hi;
   int addr_lo;
   int rc;

   rc = I2C_NO_ERR;
   ctrl = 0;
   addr_hi = 0;
   addr_lo = 0;

   switch(eeprom_type)
   {
      case EEPROM_24XX04:               // 24LC04B ignore AO,A1,A2 pins
         ctrl = (eeprom_addr>>7) & 0x02;//-- 00000010
         ctrl |= 0xA0;                  //-- 1010xxxx
         addr_hi = eeprom_addr & 0xFF;
         addr_lo = -1;
         break;
      case EEPROM_24XX08:               // 24LC08B ignore AO,A1,A2 pins
         ctrl = (eeprom_addr>>7) & 0x06;//-- 00000110
         ctrl |= 0xA8; //-- 1010xxxx
         addr_hi = eeprom_addr & 0xFF;
         addr_lo = -1;
         break;
      case EEPROM_24XX16:               // 24LC16B ignore AO,A1,A2 pins
         ctrl = (eeprom_addr>>7) & 0x0e;//BUG已经消除
		 ctrl |= 0xA0; //-- 1010xxxx
         addr_hi = eeprom_addr & 0xFF;
         addr_lo = -1;
         break;
      case EEPROM_24XX32:
         ctrl = (eeprom_cs_val<<1) & 0x07;  //-- 00001110
         ctrl |= 0xA0;                      //-- 1010xxxx
         addr_hi = (eeprom_addr>>8) & 0x0F;
         addr_lo = eeprom_addr & 0xFF;
         break;
      case EEPROM_24XX64:

         ctrl = (eeprom_cs_val<<1) & 0x07;  //-- 00001110
         ctrl |= 0xA0;                      //-- 1010xxxx
         addr_hi = (eeprom_addr>>8) & 0x1F;
         addr_lo = eeprom_addr & 0xFF;
         break;
      case EEPROM_24XX128:
         ctrl = (eeprom_cs_val<<1) & 0x07;  //-- 00001110
         ctrl |= 0xA0;                      //-- 1010xxxx
         addr_hi = (eeprom_addr>>8) & 0x3F;
         addr_lo = eeprom_addr & 0xFF;
         break;
      case EEPROM_24XX256:
         ctrl = (eeprom_cs_val<<1) & 0x07;  //-- 00001110
         ctrl |= 0xA0;                      //-- 1010xxxx
         addr_hi = (eeprom_addr>>8) & 0x7F;
         addr_lo = eeprom_addr & 0xFF;
         break;
      case EEPROM_24XX512:
         ctrl = (eeprom_cs_val<<1) & 0x07;  //-- 00001110
         ctrl |= 0xA0;                      //-- 1010xxxx
         addr_hi = (eeprom_addr>>8) & 0xFF;
         addr_lo = eeprom_addr & 0xFF;
         break;
   }
   if(rc != I2C_NO_ERR)
      return rc;
   if(ctrl == 0)
      return I2C_ERR_24XX_BAD_TYPE;

   if(ctrl_val)
      *ctrl_val = ctrl;
   if(addr_hi_val)
      *addr_hi_val = addr_hi;
   if(addr_lo_val)
      *addr_lo_val = addr_lo;

   return I2C_NO_ERR;
}
/*********************************************************************************************************
** Function name:           m24xx_write
** Descriptions:
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          eeprom_cs_val:  Hardware A2,A1,A0 (valid from 24XX32)
**                          * buf           Data src buf
**                          num             Bytes to write
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static int eeprom_i2c_lpc_m24xx_wr(int eeprom_type,int eeprom_addr,int eeprom_cs_val,uint8 * buf,int num )
{
    int rc;
    int ctrl;
    int addr_hi;
    int addr_lo;
    uint8 headbuf[3];
    uint8 headlen;
    uint8 *databuf;
    uint16 datalen;

    rc = eeprom_m24xx_set_addr(eeprom_type,eeprom_addr,eeprom_cs_val,
                                  &ctrl,&addr_hi,&addr_lo);
    if(rc != I2C_NO_ERR)
      return rc;

    //--- wr START + CONTROL
    headbuf[0] = ctrl;      //slave device address
   	headbuf[1] = addr_hi;   //date high address
   	if(addr_lo != -1)
   	{
       	headbuf[2] = addr_lo;   //date low address
    	headlen = 3;
	}
	else headlen = 2;
	databuf = buf;
	datalen = (uint16)num;
	rc = exi2cWrite(&headbuf[0], headlen, databuf, datalen);
	OSTimeDlyHMSM(0,0,0,20);
    if(rc)
        return I2C_NO_ERR;
    else
        return I2C_ERR_NO_RESPONSE;
}

/*********************************************************************************************************
** Function name:           m24xx_write
** Descriptions:
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          eeprom_cs_val:  Hardware A2,A1,A0 (valid from 24XX32)
**                          * buf           Data src buf
**                          num             Bytes to write
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int eeprom_m24xx_write(int eeprom_type,int eeprom_addr,int eeprom_cs_val,uint8 * buf,int num)
{
    int page_size = 0;
    int rc;
    int b_to_wr;

    rc = I2C_NO_ERR;
    for(;;){
      rc = eeprom_m24xx_page_size(eeprom_type,eeprom_addr,&page_size);
      if(rc != I2C_NO_ERR)
         break;
      if(page_size == 0)
      {
         rc = I2C_ERR_24XX_BAD_PAGESIZE;
         break;
      }

      rc = eeprom_addr%page_size;
      if(rc != 0) //-- not fit on page alignment
      {
         b_to_wr = page_size - rc;
         if(num < b_to_wr)
            b_to_wr = num;
         if(b_to_wr > 0)
         {
             rc = eeprom_i2c_lpc_m24xx_wr(eeprom_type,eeprom_addr,eeprom_cs_val, buf,b_to_wr);
             if(rc != I2C_NO_ERR)
                break;
             num -= b_to_wr;
             eeprom_addr += b_to_wr;
             buf += b_to_wr;
         }
      }
       //--- write remainder(by pages,if possible)
      while(num > 0)
      {
          if(num < page_size)
             b_to_wr = num;
          else
             b_to_wr = page_size;
          rc = eeprom_i2c_lpc_m24xx_wr(eeprom_type,eeprom_addr,eeprom_cs_val, buf,b_to_wr);
          if(rc != I2C_NO_ERR)
             break;
          num -= b_to_wr;
          eeprom_addr += b_to_wr;
          buf += b_to_wr;
      }
      break;
   }

   return rc;
}

/*********************************************************************************************************
** Function name:           eeprom_m24xx_read
** Descriptions:
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          eeprom_cs_val:  Hardware A2,A1,A0 (valid from 24XX32)
**                          * buf           Data read buf
**                          num             Bytes to read
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
int eeprom_m24xx_read(int eeprom_type,int eeprom_addr,int eeprom_cs_val,uint8 * buf,int num)
{
    int page_size;
    int rc;
    int ctrl;
    int addr_hi;
    int addr_lo;
    uint8 headbuf[3];
    uint8 headlen;
    uint8 *databuf;
    uint16 datalen;

    rc = I2C_NO_ERR;
    for(;;)
    {
        if(num <=0)
        {
            rc = I2C_ERR_24XX_WRONG_NUM;
            break;
        }
//--- Here - just for addr checking
        page_size = 0;
        rc = eeprom_m24xx_page_size(eeprom_type,eeprom_addr,&page_size);
        if(rc != I2C_NO_ERR)
            break;
        if(page_size == 0)
        {
            rc = I2C_ERR_24XX_BAD_PAGESIZE;
            break;
        }
        rc =eeprom_m24xx_set_addr(eeprom_type,eeprom_addr,eeprom_cs_val,
                                           &ctrl,&addr_hi,&addr_lo);
        if(rc != I2C_NO_ERR)
            break;
/* wr START + CONTROL + data address */
        headbuf[0] = ctrl & 0xfe;   //slave device address&No WR
        headbuf[1] = addr_hi;       //date high address
        if(addr_lo != -1)
        {
            headbuf[2] = addr_lo;   //date low address
            headlen = 3;
        }
        else headlen = 2;
        datalen = 0;
        rc = exi2cWrite(&headbuf[0], headlen, databuf, datalen);
        OSTimeDlyHMSM(0,0,0,20);
/* wr START + CONTROL again for read start */
        headbuf[0] = ctrl | 0x01;   //slave device address|read operation
        headlen = 1;
        datalen = num;
        rc = exi2cRead(&headbuf[0], headlen, buf, datalen);
        OSTimeDlyHMSM(0,0,0,20);
        if(rc)
            rc = I2C_NO_ERR;
    	break;
   }

   return rc;
}

/*********************************************************************************************************
** Function name:           eeprom_wp
** Descriptions:
** Input parameters:        eeprom_type:    EEPROM type
**                          eeprom_addr:    start eeprom addr (not included Hardware A2,A1,A0)
**                          eeprom_cs_val:  Hardware A2,A1,A0 (valid from 24XX32)
**                          * buf           Data read buf
**                          num             Bytes to read
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void eeprom_wp(uint8 state)
{
    IO0DIR |= EEPROM_WP_PIN;//out
    if(EEPROM_WP_OFF == state)
        IO1SET |= EEPROM_WP_PIN;
    else if(EEPROM_WP_ON == state)
        IO1SET &= (~EEPROM_WP_PIN);
}

/*********************************************************************************************************
   END FILE
*********************************************************************************************************/


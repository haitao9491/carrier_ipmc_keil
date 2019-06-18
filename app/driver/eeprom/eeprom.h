/***********************************************Copyright (c)*********************************************
**                                BeiJing RuiYuanXin Telecom Technology Co.,LTD.
**
**                                       http://www.raycores.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    eeprom.h
** Last modified Date:      2018-11-29
** Last Version:		    1.0
** Descriptions:		    eeprom driver head file
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wangxiumei
** Created date:		    2018-11-29
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
#ifndef __EEPROM_H
#define __EEPROM_H

#include "config.h"

/*
  EEPROM MACRO
 */
#define  EEPROM_WP_ON                  1
#define  EEPROM_WP_OFF                 0
#define  EEPROM_WP_PIN                 0x00001000

/* EEPROM Errors */
#define  I2C_NO_ERR                    0
#define  I2C_ERR_NO_RESPONSE           1
#define  I2C_ERR_WRONG_PARAM           2
#define  I2C_ERR_24XX_WR_TIMEOUT       3
#define  I2C_ERR_24XX_BAD_ADDR         4
#define  I2C_ERR_24XX_BAD_TYPE         5
#define  I2C_ERR_24XX_BAD_PAGESIZE     6
#define  I2C_ERR_24XX_WRONG_NUM        7

/* EEPROM 24xx types */
#define  EEPROM_24XX04                 1
#define  EEPROM_24XX08                 2
#define  EEPROM_24XX16                 3
#define  EEPROM_24XX32                 4
#define  EEPROM_24XX64                 5
#define  EEPROM_24XX128                6
#define  EEPROM_24XX256                7
#define  EEPROM_24XX512                8

/* EEPROM 24xx max addr values */
#define  EEPROM_MAX_ADDR_24XX04    0x01FF   //-- 512 Bytes
#define  EEPROM_MAX_ADDR_24XX08    0x03FF   //--  1 KBytes
#define  EEPROM_MAX_ADDR_24XX16    0x07FF   //--  2 KBytes
#define  EEPROM_MAX_ADDR_24XX32    0x0FFF   //--  4 KBytes
#define  EEPROM_MAX_ADDR_24XX64    0x1FFF   //--  8 KBytes
#define  EEPROM_MAX_ADDR_24XX128   0x3FFF   //-- 16 KBytes
#define  EEPROM_MAX_ADDR_24XX256   0x7FFF   //-- 32 KBytes
#define  EEPROM_MAX_ADDR_24XX512   0xFFFF   //-- 64 KBytes
/*
chip             bit7  bit6  bit5   bit4  bit3   bit2   bit1   bit0
24C01/02/21       1     0     1      0     E2     E1     E0     R/W
24C04             1     0     1      0     E2     E1     A8     R/W
24C08             1     0     1      0     E2     A9     A8     R/W
24C16             1     0     1      0     A10    A9     A8     R/W
24C32/64          1     0     1      0     E2     E1     E0     R/W
24C128/256/512    1     0     1      0     0      E1     E0     R/W
24C1024           1     0     1      0     0      E1     A16    R/W
*/
/*
chip        bit of address              range of address
24C01       bit7-bit0                   0x00-0x7F
24C02       bit7-bit0                   0x00-0xFF
24C04       A8,bit7-bit0                0x00-0x1FF
24C08       A9,A8,bit7-bit0             0x00-0x3FF
24C16       A10,A9,A8,bit7-bit0         0x00-0x7FF
24C32       bit15-bit8£¬bit7-bit0       0x00-0xFFF
24C64       bit15-bit8£¬bit7-bit0       0x00-0x1FFF
24C128      bit7-bit0                   0x00-0x3FFF
24C256      bit7-bit0                   0x00-0x7FFF
24C512      bit7-bit0                   0x00-0xFFFF
24C1024     A16,bit15-bit8,bit7-bit0    0x00-0x1FFFF
*/
#ifdef __cplusplus
    extern "C" {
#endif

int eeprom_m24xx_write(int eeprom_type,int eeprom_addr,int eeprom_cs_val,uint8 * buf,int num);
int eeprom_m24xx_read(int eeprom_type,int eeprom_addr,int eeprom_cs_val,uint8 * buf,int num);
void eeprom_wp(uint8 state);

#ifdef __cplusplus
    }
#endif

#endif                                                                  /* __EEPROM_H                     */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

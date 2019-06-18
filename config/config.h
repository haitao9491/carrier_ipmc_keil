/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           config.h
** Last modified Date:  2004-09-17
** Last Version:        1.0
** Descriptions:        User Configurable File,clock and type configuration
**	
**--------------------------------------------------------------------------------------------------------
** Created By:          Chenmingji
** Created date:        2004-09-17
** Version: 1.0
** Descriptions:        First version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			wangxiumei
** Modified date:		2011-12-20
** Version:				v1.0
** Descriptions:
**
*********************************************************************************************************/
#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE  1
#endif                                                                  /*  TRUE                        */

#ifndef FALSE
#define FALSE 0
#endif                                                                  /*  FALSE                       */

typedef unsigned char  uint8;                                           /*  无符号8位整型变量           */
typedef signed   char  int8;                                            /*  有符号8位整型变量           */
typedef unsigned short uint16;                                          /*  无符号16位整型变量          */
typedef signed   short int16;                                           /*  有符号16位整型变量          */
typedef unsigned int   uint32;                                          /*  无符号32位整型变量          */
typedef signed   int   int32;                                           /*  有符号32位整型变量          */
typedef float          fp32;                                            /*  单精度浮点数（32位长度）    */
typedef double         fp64;                                            /*  双精度浮点数（64位长度）    */

typedef unsigned char  INT8U;                                           /*  无符号8位整型变量           */
typedef signed   char  INT8S;                                           /*  有符号8位整型变量           */
typedef unsigned short INT16U;                                          /*  无符号16位整型变量          */
typedef signed   short INT16S;                                          /*  有符号16位整型变量          */
typedef unsigned int   INT32U;                                          /*  无符号32位整型变量          */
typedef signed   int   INT32S;                                          /*  有符号32位整型变量          */
typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */

/*********************************************************************************************************
  uC/OS-II specital code
  uC/OS-II的特殊代码
*********************************************************************************************************/
//#include "includes.h"
#include    "os_cpu.h"
#include    "os_cfg.h"
#include    "ucos_ii.h"

/*********************************************************************************************************
  ARM的特殊代码
  ARM specital code
*********************************************************************************************************/
#include    "LPC2400.h"
#include    "target.h"
#include    "vicControl.h"

/*********************************************************************************************************
  应用程序配置
  Application Program Configurations
*********************************************************************************************************/
#include    <stdio.h>
#include    <rt_sys.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h>
#include	<stdarg.h>
#include    <string.h>

/*********************************************************************************************************
  本例子的配置
  Configuration of the example
*********************************************************************************************************/
#define	USE_USB				0

//#define Fosc                12000000								    /*	OSC = 12MHz                 */
#define Fosc                20000000								    /*	OSC = 12MHz                 */

#if USE_USB

	#define Fusbclk	 48000000

	//#define Fcclk	(Fosc * 4) 										    /* 主频 Fcclk = 48MHz 		    */
	#define Fcclk	60000000 										    /* 主频 Fcclk = 60MHz 		    */

	/*
	 * 如果用了USB,则Fcco是Fcclk
	 * 与Fusbclk在275~550M之间的
	 * 最小公倍数
	 * Fcco是Fcclk在275~550M之间
	 * 的最小倍数
	 */
	#define Fcco	(Fusbclk * (USBCLKDivValue + 1))
	#define Fpclk	(Fcclk / 4)

	#define PLL_NValue			1
	#define PLL_MValue			(((Fcco / Fosc) * (PLL_NValue + 1) / 2) - 1)
	#define CCLKDivValue		(Fcco / Fcclk - 1)
	#define USBCLKDivValue		5
#else
//	#define Fcclk	(Fosc  * 4)											/* 主频 Fcclk = 48MHz		    */
//	#define Fcco    (Fcclk * 6)

	//#define Fpclk	(Fcclk / 4)
	#define Fcclk	60000000										/* 主频 Fcclk = 60MHz		    */
	#define Fcco    (Fcclk * 8)
	#define Fpclk	Fcclk
	//#define PLL_NValue			1
	//#define PLL_MValue			(((Fcco / Fosc) * (PLL_NValue + 1) / 2) - 1)
	#define PLL_NValue			0x00
	#define PLL_MValue			0x0B

	#define CCLKDivValue		(Fcco / Fcclk - 1)
	//#define USBCLKDivValue		254
	#define USBCLKDivValue		9
#endif	                                                                /*  USE_USB                     */

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */
#endif                                                                  /*  __CONFIG_H                  */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

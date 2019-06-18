/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           target.h
** Last modified Date:  2004-09-17
** Last Version:        1.0
** Descriptions:        header file of the specific codes for LPC2200 target boards
**                      Every project should include a copy of this file, user may modify it as needed
**--------------------------------------------------------------------------------------------------------
** Created by:          Chenmingji
** Created date:        2004-02-02
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         Chenmingji
** Modified date:       2004-09-17
** Version:             1.01
** Descriptions:        Renewed the template, added codes to surport more compilers
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			wangxiumei
** Modified date:		2011-12-20
** Version:				v1.0
** Descriptions:
**
*********************************************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H

#define	__PRJ_TEMPLET_VER	0x2008070914								/*  工程模板版本为 V1.4			*/

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

#ifndef IN_TARGET

extern void Reset (void);
/*********************************************************************************************************
** Function name:           Reset
** Descriptions:            resets the target board.
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/

extern void TargetInit (void);
/*********************************************************************************************************
** Function name:           TargetInit
**
** Descriptions:            Initialize the target board; it is called in a necessary place, change it as
**                          needed
**
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
#endif                                                                  /*  IN_TARGET                   */

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  _TARGET_H                   */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

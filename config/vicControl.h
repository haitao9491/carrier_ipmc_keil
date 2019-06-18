/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               vicControl.h
** Latest modified Date:    2008-04-21
** Latest Version:          1.0
** Descriptions:            VIC控制代码
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2008-04-21
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef _VIC_CONTROL_H_
#define _VIC_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
  兼容定义，以后不要使用
*********************************************************************************************************/
#define VIC_Config      VIC_IRQ_CFG
#define pVIC_Config     PVIC_IRQ_CFG

#define SetVICIRQ       vicIrqFuncSet
#define FreeVICIRQ      vicIrqFuncClr
#define ReEnableVICIRQ  vicIrqEnable
#define DisableVICIRQ   vicIrqDisable
#define GetVICIRQState  vicIrqStatusGet
#define SetVICFIQ       vicFiqSet
#define FreeVICFIQ      vicFiqClr

/*********************************************************************************************************
  VIC配置信息定义
*********************************************************************************************************/
struct vic_irq_cfg {
    INT32U      ulChannel;                                              /*  通道                        */
    INT32U      ulPri;                                                  /*  优先级                      */
    INT32U      ulFunctionAddr;                                         /*  ISR地址                     */
    INT32U      ulEnable;                                               /*  使能标识                    */
};

typedef struct vic_irq_cfg      VIC_IRQ_CFG;
typedef struct vic_irq_cfg     *PVIC_IRQ_CFG;


/*********************************************************************************************************
** Function name:           swiHandle
** Descriptions:            SWI函数声明
** input parameters:        iHandle: 用于区分功能
**                          其他:    根据功能决定
** output parameters:       根据功能决定
** Returned value:          根据功能决定
*********************************************************************************************************/
__swi(0x01) unsigned int swiHandle (int iHandle, unsigned int, unsigned int, unsigned int);

/*********************************************************************************************************
** Function name:           vicIrqFuncSet
** Descriptions:            设置所选外设的中断优先级、中断服务函数地址，并使能中断
** input parameters:        uiChannel:  外设对应的中断通道号
**                          uiPri:      中断优先级
**                          uiFuncAddr: 中断服务函数地址
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicIrqFuncSet (unsigned int uiChannel,
                                     unsigned int uiPri,
                                     unsigned int uiFuncAddr)
{
    return swiHandle(0x100, uiChannel, uiPri, uiFuncAddr);
}

/*********************************************************************************************************
** Function name:           vicIrqFuncClr
** Descriptions:            清除所选外设的IRQ资源
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicIrqFuncClr (unsigned int uiChannel)
{
    return swiHandle(0x101, uiChannel ,0 ,0);
}

/*********************************************************************************************************
** Function name:           vicIrqEnable
** Descriptions:            使能相应外设的中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicIrqEnable (unsigned int uiChannel)
{
    return swiHandle(0x102, uiChannel, 0, 0);
}

/*********************************************************************************************************
** Function name:           vicIrqDisable
** Descriptions:            禁止相应外设的中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicIrqDisable (unsigned int uiChannel)
{
    return swiHandle(0x103, uiChannel, 0, 0);
}

/*********************************************************************************************************
** Function name:           vicIrqStatusGet
** Descriptions:            获取所选外设的中断通道号、优先级、中断服务函数地址及中断使能状态
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       pvicInfo:   配置信息
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicIrqStatusGet (unsigned int uiChannel, PVIC_IRQ_CFG pvicInfo)
{
    return swiHandle(0x104, uiChannel, (unsigned int)pvicInfo, 0);
}

/*********************************************************************************************************
** Function name:           vicFiqSet
** Descriptions:            设置并使能所选中断通道号为FIQ中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicFiqSet (unsigned int uiChannel)
{
    return swiHandle(0x105, uiChannel, 0, 0);
}

/*********************************************************************************************************
** Function name:           vicFiqClr
** Descriptions:            清除所选中断通道号的FIQ中断
** input parameters:        uiChannel:  外设对应的中断通道号
** output parameters:       none
** Returned value:          1:          成功
**                          0:          失败
*********************************************************************************************************/
__inline unsigned int vicFiqClr (unsigned int uiChannel)
{
    return swiHandle(0x106, uiChannel, 0, 0);
}

/*********************************************************************************************************
  允许中断嵌套宏定义
*********************************************************************************************************/
#define		OS_ENABLE_NESTING		OS_EXIT_CRITICAL
#define		OS_DISABLE_NESTING		OS_ENTER_CRITICAL

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TARGET_H                  */
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


#ifndef  _BSP_H_
#define  _BSP_H_

#include <stdio.h>

#include "ucos_ii.h"
#include "bsp_queue.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_os.h"
#include "bsp_sys_ctrl.h"
#include "bsp_uart.h"

#define BSP_WRITE_REG32(reg,data) ((*(volatile INT32U *)(reg)) = (data))
#define BSP_READ_REG32(data,reg)   ((data) = (*(volatile INT32U *)(reg)))

#define BSP_WRITE_REG16(reg,data) ((*(volatile INT16U *)(reg)) = (data))
#define BSP_READ_REG16(data,reg)   ((data) = (*(volatile INT16U *)(reg)))

#define BSP_WRITE_REG8(reg,data) ((*(volatile INT8U *)(reg)) = (data))
#define BSP_READ_REG8(data,reg)   ((data) = (*(volatile INT8U *)(reg)))

void BSP_Init (void);
void BSP_SDRAM_Init (void);

#endif    

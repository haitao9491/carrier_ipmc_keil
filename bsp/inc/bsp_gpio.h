#ifndef  _BSP_GPIO_H_
#define  _BSP_GPIO_H_

#include "ucos_ii.h"

#define  BSP_GPIO_PORT0                                   0
#define  BSP_GPIO_PORT1                                   1
#define  BSP_GPIO_PORT0_FAST                              2
#define  BSP_GPIO_PORT1_FAST                              3
#define  BSP_GPIO_PORT2_FAST                              4
#define  BSP_GPIO_PORT3_FAST                              5
#define  BSP_GPIO_PORT4_FAST                              6


#define  BSP_GPIO_OPT_NONE                       0uL
#define  BSP_GPIO_OPT_OUT_EN                     (1uL<<1)
#define  BSP_GPIO_OPT_IN_EN                      (1uL<<2)
#define  BSP_GPIO_OPT_INT_RISING_EN              (1uL<<3)            
#define  BSP_GPIO_OPT_INT_FALLING_EN             (1uL<<4)
#define  BSP_GPIO_OPT_RD_WR_EN                   (1uL<<5)
#define  BSP_GPIO_OPT_RD_WR_DIS                  (1uL<<6)

#define  BSP_GPIO_OPT_FNCT_1                     (1uL<<7)
#define  BSP_GPIO_OPT_FNCT_2                     (1uL<<8)
#define  BSP_GPIO_OPT_FNCT_3                     (1uL<<9)
#define  BSP_GPIO_OPT_FNCT_4                     (1uL<<10)

#define  BSP_GPIO_OPT_MODE_PULLUP                (1uL<<11)
#define  BSP_GPIO_OPT_MODE_RESERVED              (1uL<<12)
#define  BSP_GPIO_OPT_MODE_NONE                  (1uL<<13)
#define  BSP_GPIO_OPT_MODE_PULLDOWN              (1uL<<14)



void	BSP_GPIO_Cfg ( INT8U gpio_port,INT32U gpio_pins,INT16U gpio_opt );
void	BSP_GPIO_Clr ( INT8U gpio_port,INT32U gpio_pins );
void	BSP_GPIO_IntClr ( INT8U gpio_port,INT32U gpio_pins );
void	BSP_GPIO_Set ( INT8U gpio_port,INT32U gpio_pins );
INT32U	BSP_GPIO_StatusGet ( INT8U gpio_port );
void	BSP_GPIO_Toggle ( INT8U gpio_port,INT32U gpio_pins );


#endif

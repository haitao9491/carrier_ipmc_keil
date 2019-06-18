/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2006-2009; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        MICRIUM BOARD SUPPORT PACKAGE
*                                           GENERAL PURPOSE I/O
*
* Filename      : bsp_gpio.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GPIO_MODULE
#include "bsp.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_GPIO_REG_PINSEL_BASE_ADDR                             (INT32U  )(0xE002C000)

#define  BSP_GPIO_REG_PINSEL0                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x00)
#define  BSP_GPIO_REG_PINSEL1                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x04)
#define  BSP_GPIO_REG_PINSEL2                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x08)
#define  BSP_GPIO_REG_PINSEL3                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x0C)
#define  BSP_GPIO_REG_PINSEL4                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x10)
#define  BSP_GPIO_REG_PINSEL5                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x14)
#define  BSP_GPIO_REG_PINSEL6                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x18)
#define  BSP_GPIO_REG_PINSEL7                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x1C)
#define  BSP_GPIO_REG_PINSEL8                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x20)
#define  BSP_GPIO_REG_PINSEL9                                      (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x24)
#define  BSP_GPIO_REG_PINSEL10                                     (*(INT32U *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x28)

#define  BSP_GPIO_REG_PINMODE_BASE_ADDR                            (INT32U  )(0xE002C040)

#define  BSP_GPIO_REG_PINMODE0                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x00)
#define  BSP_GPIO_REG_PINMODE1                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x04)
#define  BSP_GPIO_REG_PINMODE2                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x08)
#define  BSP_GPIO_REG_PINMODE3                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x0C)
#define  BSP_GPIO_REG_PINMODE4                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x10)
#define  BSP_GPIO_REG_PINMODE5                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x14)
#define  BSP_GPIO_REG_PINMODE6                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x18)
#define  BSP_GPIO_REG_PINMODE7                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x1C)
#define  BSP_GPIO_REG_PINMODE8                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x20)
#define  BSP_GPIO_REG_PINMODE9                                     (*(INT32U *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x24)

#define  BSP_GPIO_REG_INT_BASE_ADDR                                (INT32U   )(0xE0028080)
#define  BSP_GPIO_REG_INT_IOINTSTATUS                              (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x00))
#define  BSP_GPIO_REG_INT_IO0INTSTATR                              (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x04))
#define  BSP_GPIO_REG_INT_IO0INTSTATF                              (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x08))
#define  BSP_GPIO_REG_INT_IO0INTCLR                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x0C))
#define  BSP_GPIO_REG_INT_IO0INTENR                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x10))
#define  BSP_GPIO_REG_INT_IO0INTENF                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x14))

#define  BSP_GPIO_REG_INT_IO1INTSTATR                              (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x24))
#define  BSP_GPIO_REG_INT_IO1INTSTATF                              (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x28))
#define  BSP_GPIO_REG_INT_IO1INTCLR                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x2C))
#define  BSP_GPIO_REG_INT_IO1INTENR                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x30))
#define  BSP_GPIO_REG_INT_IO1INTENF                                (*(INT32U *)(BSP_GPIO_REG_INT_BASE_ADDR + 0x34))



#define  BSP_GPIO_REG_PORT0_BASE_ADDR                              ((INT32U)0xE0028000)
#define  BSP_GPIO_REG_PORT1_BASE_ADDR                              ((INT32U)0xE0028010)

#define  BSP_GPIO_REG_PORTx_FAST_BASE_ADDR                         ((INT32U)0x3FFFC000)
#define  BSP_GPIO_REG_PORT0_FAST_BASE_ADDR                         ((INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x00))
#define  BSP_GPIO_REG_PORT1_FAST_BASE_ADDR                         ((INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x20))
#define  BSP_GPIO_REG_PORT2_FAST_BASE_ADDR                         ((INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x40))
#define  BSP_GPIO_REG_PORT3_FAST_BASE_ADDR                         ((INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x60))
#define  BSP_GPIO_REG_PORT4_FAST_BASE_ADDR                         ((INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x80))

#define  BSP_GPIO_OPT_FNCT_ANY                                     (BSP_GPIO_OPT_FNCT_1 | \
                                                                    BSP_GPIO_OPT_FNCT_2 | \
                                                                    BSP_GPIO_OPT_FNCT_3 | \
                                                                    BSP_GPIO_OPT_FNCT_4)

#define  BSP_GPIO_OPT_MODE_ANY                                     (BSP_GPIO_OPT_MODE_PULLUP   | \
                                                                    BSP_GPIO_OPT_MODE_NONE     | \
                                                                    BSP_GPIO_OPT_MODE_PULLDOWN)

#define  BSP_GPIO_OPT_MODE_INVALID                                  0xFF
#define  BSP_GPIO_OPT_FNCT_INVALID                                  0xFF


/*
*********************************************************************************************************
*                                       EXTERN  GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

typedef struct bsp_gpio_reg {
    INT32U  IOPIN;
    INT32U  IOSET;
    INT32U  IODIR;
    INT32U  IOCLR;    
} BSP_GPIO_REG;

typedef struct bsp_gpio_fast_reg {
    INT32U  FIODIR;
    INT32U  RESERVED0[3];
    INT32U  FIOMASK;
    INT32U  FIOPIN;
    INT32U  FIOSET;
    INT32U  FIOCLR;    
} BSP_GPIO_FAST_REG;



/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*********************************************************************************************************
**                                        GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*
*********************************************************************************************************
*                                           BSP_GPIO_Cfg()
*
* Description : This function configures the I/O pins in the Parallel Input/Output controller.
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0
*                                       BSP_GPIO_PORT1      
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST 
*                                       BSP_GPIO_PORT4_FAST
*
*               gpio_pins           Port pin(s) to be configured.
*
*               gpio_cfg_opt        PIO configuration options
*                                       BSP_GPIO_OPT_OUT_EN           Controlled pin is output
*                                       BSP_GPIO_OPT_IN_EN            Controlled pin is input
*                                       BSP_GPIO_OPT_INT_RISING_EN    Interrupt enable for rising edge
*                                       BSP_GPIO_OPT_INT_FALLING_EN   Interrupt disable for falling edge
*                                       BSP_GPIO_OPT_RD_WR_EN         Controlled pin is affected by writes to
*                                                                     FIOSET, FIOCLR, FIOPIN registers.
*                                       BSP_GPIO_OPT_FNCT_1           Controlled pin is configured with function 1
*                                       BSP_GPIO_OPT_FNCT_2           Controlled pin is configured with function 2
*                                       BSP_GPIO_OPT_FNCT_3           Controlled pin is configured with function 3
*                                       BSP_GPIO_OPT_FNCT_4           Controlled pin is configured with function 4
*
*                                       BSP_GPIO_OPT_MODE_PULLUP      Controlled pin is configured has a pull-up resitor enabled.
*                                       BSP_GPIO_OPT_MODE_RESERVED    Reserved. This value should no be used.
*                                       BSP_GPIO_OPT_MODE_NONE        Controlled pin is configured has neither pull-up nor pull-down.
*                                       BSP_GPIO_OPT_MODE_PULLDOWN    Controlled pin is configured has a pull-down resistor enabled
*
*
*
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_GPIO_Cfg (INT8U   gpio_port,
                    INT32U   gpio_pins,     
                    INT16U   gpio_opt)
{
    BSP_GPIO_REG       *p_gpio_reg;
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    
    INT32U          *p_gpio_pinsel;
    INT32U          *p_gpio_pinmode;    
    INT32U          pinsel_opt;
    INT32U          pinmode_opt;
    INT32U          pin_nbr;
    
                                                                /* ------- INVALID CONFIGURATION CHECKING ----------- */
                                                                /* GPIO pin can be only configured as Input or Output */
    if (DEF_BIT_IS_SET(gpio_opt,BSP_GPIO_OPT_OUT_EN | BSP_GPIO_OPT_IN_EN)) {
        return;
    }
                                                                /* Only GPIO Inputs can have interrupt enable         */
    if (DEF_BIT_IS_SET(gpio_opt,BSP_GPIO_OPT_OUT_EN | BSP_GPIO_OPT_INT_RISING_EN)) {
        return;
    }
                                                                /* Only GPIO Inputs can have interrupt enable         */    
    if (DEF_BIT_IS_SET(gpio_opt,BSP_GPIO_OPT_OUT_EN | BSP_GPIO_OPT_INT_FALLING_EN)) {
        return;
    }
                                                                /* Only pins controlled by the GPIO controller can ...*/
                                                                /* ... be configured (Input/Output/Interrupt enable)  */
    if ((DEF_BIT_IS_CLR(gpio_opt, BSP_GPIO_OPT_FNCT_1)) &&        
        (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_OUT_EN         |
                                      BSP_GPIO_OPT_IN_EN          |
                                      BSP_GPIO_OPT_INT_RISING_EN  |
                                      BSP_GPIO_OPT_INT_FALLING_EN | 
                                      BSP_GPIO_OPT_RD_WR_EN))
	) {
        return;
    }

                                                               /* Only PORT0 and PORT 1 can enable interrupts         */
    if ((gpio_port != BSP_GPIO_PORT0) &&
        (gpio_port != BSP_GPIO_PORT1) &&
        (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_INT_RISING_EN |BSP_GPIO_OPT_INT_FALLING_EN))
	) {
        return;
    }    
                                                                /* ----------- BASE ADDRESS CONFIGURATION ----------- */
    switch (gpio_port) {
    case BSP_GPIO_PORT0:
		p_gpio_reg      = (BSP_GPIO_REG      *)(BSP_GPIO_REG_PORT0_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x00);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x00);
		break;

	case BSP_GPIO_PORT1:
		p_gpio_reg      = (BSP_GPIO_REG      *)(BSP_GPIO_REG_PORT1_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x08);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x08);
		break;

	case BSP_GPIO_PORT0_FAST:
		p_gpio_fast_reg = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x00);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x00);
		break;

	case BSP_GPIO_PORT1_FAST:
		p_gpio_fast_reg = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x08);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x08);
		break;

	case BSP_GPIO_PORT2_FAST:
		p_gpio_fast_reg = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x10);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x10);
		break;

	case BSP_GPIO_PORT3_FAST:
		p_gpio_fast_reg = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x18);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x18);
		break;

	case BSP_GPIO_PORT4_FAST:
		p_gpio_fast_reg = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
		p_gpio_pinsel   = (INT32U         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x20);
		p_gpio_pinmode  = (INT32U         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x20);
		break;
             
	default:
		return;
	}

                                                                /* ---------- I/O DIRECTION CONFIGURATION ----------- */
    if ((gpio_port == BSP_GPIO_PORT0)||(gpio_port == BSP_GPIO_PORT1)) {
    
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_OUT_EN)) {
            DEF_BIT_SET(p_gpio_reg->IODIR, gpio_pins);
        }
    
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_IN_EN)) {
            DEF_BIT_CLR(p_gpio_reg->IODIR, gpio_pins);
        }
        
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_INT_RISING_EN)) {
            if (gpio_port == BSP_GPIO_PORT0) {
                BSP_GPIO_REG_INT_IO0INTENR = gpio_pins;    
            }             
            if (gpio_port == BSP_GPIO_PORT1) {
                BSP_GPIO_REG_INT_IO1INTENR = gpio_pins;
            }
        }

        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_INT_FALLING_EN)) {
            if (gpio_port == BSP_GPIO_PORT0) {
                BSP_GPIO_REG_INT_IO0INTENF = gpio_pins;    
            }             
            if (gpio_port == BSP_GPIO_PORT1) {
                BSP_GPIO_REG_INT_IO1INTENF = gpio_pins;
            }
        }                        
    } else {
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_OUT_EN)) {
            DEF_BIT_SET(p_gpio_fast_reg->FIODIR, gpio_pins);
        }
    
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_IN_EN)) {
            DEF_BIT_CLR(p_gpio_fast_reg->FIODIR, gpio_pins);
        }            
        
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_RD_WR_EN)) {
            DEF_BIT_CLR(p_gpio_fast_reg->FIOMASK, gpio_pins);
        }            
    
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_RD_WR_DIS)) {
            DEF_BIT_SET(p_gpio_fast_reg->FIOMASK, gpio_pins);
        }            
    }
                
                                                                /* --- I/O MODE/PERIPHERAL FUNCTION CONFIGURATION --- */

    pinsel_opt  = BSP_GPIO_OPT_FNCT_INVALID;                   
    pinmode_opt = BSP_GPIO_OPT_MODE_INVALID;
                                                                /* Set PINSELxx based on BSP_GPIO_OPT_FNCT_xxx        */
    if (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_FNCT_ANY)) {
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_1)) {
            pinsel_opt = 0x00;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_2)) {
            pinsel_opt = 0x01;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_3)) {
            pinsel_opt = 0x02;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_4)) {
            pinsel_opt = 0x03;
        } else {
            return;
        }
    }

                                                                /* Set PMODExx based on BSP_GPIO_OPT_MDOE_xxx         */
    if (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_MODE_ANY)) {
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_PULLUP)) {
            pinmode_opt = 0x00;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_NONE)) {
            pinmode_opt = 0x02;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_PULLDOWN)) {
            pinmode_opt = 0x03;
        } else {
            return;
        }
    }
    if ((pinsel_opt != BSP_GPIO_OPT_FNCT_INVALID) ||
        (pinmode_opt  != BSP_GPIO_OPT_MODE_INVALID)) {
        for (pin_nbr = 0; pin_nbr < 32; pin_nbr++) {
            if (DEF_BIT_IS_SET(gpio_pins, (1uL<<pin_nbr))) {
                
                if (pinsel_opt != BSP_GPIO_OPT_FNCT_INVALID) {
                    if (pin_nbr < 16) {
                        DEF_BIT_CLR(*p_gpio_pinsel, DEF_BIT_FIELD(2, pin_nbr * 2));
                        DEF_BIT_SET(*p_gpio_pinsel, DEF_BIT_MASK(pinsel_opt, pin_nbr * 2));
                    } else {
                        DEF_BIT_CLR(*((INT32U *)((INT32U)p_gpio_pinsel + 0x04)), DEF_BIT_FIELD(2, (pin_nbr - 16) * 2));                
                        DEF_BIT_SET(*((INT32U *)((INT32U)p_gpio_pinsel + 0x04)), DEF_BIT_MASK(pinsel_opt, (pin_nbr - 16) * 2));
                    }
                }
        
                if (DEF_BIT_IS_SET(gpio_pins, (1uL<<pin_nbr))) {                
                    if (pinmode_opt != BSP_GPIO_OPT_MODE_INVALID) {                    
                        if (pin_nbr < 16) {                        
                            DEF_BIT_CLR(*p_gpio_pinmode, DEF_BIT_FIELD(2, pin_nbr * 2));
                            DEF_BIT_SET(*p_gpio_pinmode, DEF_BIT_MASK(pinmode_opt, pin_nbr * 2));                    
                        } else {
                            DEF_BIT_CLR(*((INT32U *)((INT32U)p_gpio_pinmode + 0x04)), DEF_BIT_FIELD(2, (pin_nbr - 16) * 2));                                        
                            DEF_BIT_SET(*((INT32U *)((INT32U)p_gpio_pinmode + 0x04)), DEF_BIT_MASK(pinmode_opt, (pin_nbr - 16) * 2));                    
                        }                
                    }                
                }                
            }
        }                    
    }
}

/*
*********************************************************************************************************
*                                           BSP_GPIO_Set()
*
* Description : This function sets the data to be driven on the I/O line
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_PIO_PORT0       
*                                       BSP_PIO_PORT1    
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pins           Port pin(s) to be set.
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void BSP_GPIO_Set (INT8U gpio_port,INT32U gpio_pins)
{
    BSP_GPIO_REG       *p_gpio_reg;
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    
	    
	switch (gpio_port) {
	case BSP_GPIO_PORT0:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT0_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT1_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT0_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT2_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT3_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT4_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
		break;                          
	default:
		return;    
    }

    if ((gpio_port == BSP_GPIO_PORT0)||(gpio_port == BSP_GPIO_PORT1)) {             
        p_gpio_reg->IOSET       = gpio_pins;
    } else {
        p_gpio_fast_reg->FIOSET = gpio_pins;
    }
    
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_Clr()
*
* Description : This function clears the data to be driven on the I/O line
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pins           Port pin(s) to be cleared.
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_GPIO_Clr (INT8U  gpio_port,INT32U  gpio_pins)
{
    BSP_GPIO_REG       *p_gpio_reg;
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    
        
	switch (gpio_port) {
	case BSP_GPIO_PORT0:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT0_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT1_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT0_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT2_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT3_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT4_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
		break;   
	default:
		return;
    }

    if ((gpio_port == BSP_GPIO_PORT0)||(gpio_port == BSP_GPIO_PORT1)) {             
        p_gpio_reg->IOCLR = gpio_pins;
    } else {
        p_gpio_fast_reg->FIOCLR = gpio_pins;
    }    
}

/*
*********************************************************************************************************
*                                           BSP_GPIO_IntClr()
*
* Description : This function clears the interrupt on the I/O line
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0
*                                       BSP_GPIO_PORT1
*
*               gpio_pin            Port pin(s) where the interrup will be cleared.
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/
         
void  BSP_GPIO_IntClr (INT8U gpio_port,INT32U gpio_pins)
{
	switch (gpio_port) {
	case BSP_GPIO_PORT0:
		BSP_GPIO_REG_INT_IO0INTCLR = gpio_pins;
		break;      
	case BSP_GPIO_PORT1:
		BSP_GPIO_REG_INT_IO1INTCLR = gpio_pins;
		break;     
	default:
		break;
	}
}

         

/*
*********************************************************************************************************
*                                           BSP_GPIO_StatusGet()
*
* Description : This function returns the status of the pin(s).
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be read.
*
* Return(s)   : The status of the pin(s)
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/
INT32U  BSP_GPIO_StatusGet  (INT8U   gpio_port)

{
    BSP_GPIO_REG       *p_gpio_reg;
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;     
    INT32U          port_status;
        
	switch (gpio_port) {
	case BSP_GPIO_PORT0:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT0_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT1_BASE_ADDR); 
		break;   
	case BSP_GPIO_PORT0_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT2_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT3_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT4_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
		break;      
	default:
		return 0uL;
    }
        
    if ((gpio_port == BSP_GPIO_PORT0)||(gpio_port == BSP_GPIO_PORT1)) {             
        port_status = p_gpio_reg->IOPIN;
    } else {
        port_status = p_gpio_fast_reg->FIOPIN;
    }  
    return (port_status);
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_Toggle()
*
* Description : This function toggle a I/O pin(s)
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be toggled
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_GPIO_Toggle (INT8U   gpio_port,INT32U   gpio_pins)
{
    BSP_GPIO_REG       *p_gpio_reg;
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;         
    INT32U          pin_set;
    INT32U          pin_clr;

	switch (gpio_port) {
	case BSP_GPIO_PORT0:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT0_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1:
		p_gpio_reg   = (BSP_GPIO_REG *)(BSP_GPIO_REG_PORT1_BASE_ADDR); 
		break;   
	case BSP_GPIO_PORT0_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
		break;
	case BSP_GPIO_PORT1_FAST:
		p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
		break;  
	default:
		return;
    }
    
    if ((gpio_port == BSP_GPIO_PORT0)||(gpio_port == BSP_GPIO_PORT1)) {  
        pin_clr                 =  (p_gpio_reg->IOPIN) & gpio_pins;    
        pin_set                 = ~(p_gpio_reg->IOPIN) & gpio_pins;
        p_gpio_reg->IOCLR       = pin_clr;
        p_gpio_reg->IOSET       = pin_set;        
    } else {
        pin_clr                 =  (p_gpio_fast_reg->FIOPIN) & gpio_pins;    
        pin_set                 = ~(p_gpio_fast_reg->FIOPIN) & gpio_pins;
        p_gpio_fast_reg->FIOCLR = pin_clr;
        p_gpio_fast_reg->FIOSET = pin_set;            
    }    
}

/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* 
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                             OS LAYER
*
* Filename      : bsp_os.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_OS_MODULE
#include "bsp.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* --------- TIMER COUNTER BASE ADDR DEFINES -------- */
#define  BSP_OS_TC0_BASE_REG              ((BSP_OS_TMR_REG_PTR)(0xE0004000))
#define  BSP_OS_TC1_BASE_REG              ((BSP_OS_TMR_REG_PTR)(0xE0008000))

                                                                /* ------- TIMER CONTROL REGISTER BIT DEFINES ------- */
#define  BSP_OS_REG_TCR_CNTR_EN                    (1uL<<0)
#define  BSP_OS_REG_TCR_CNTR_RST                   (1uL<<1)

                                                                /* ------- MATCH CONTROL REGISTER BIT DEFINES ------- */
#define  BSP_OS_REG_TC_MR0I                        (1uL<<0)
#define  BSP_OS_REG_TC_MR0R                        (1uL<<1)
#define  BSP_OS_REG_TC_MR0S                        (1uL<<2)

#define  BSP_OS_REG_TC_MR1I                        (1uL<<4)
#define  BSP_OS_REG_TC_MR1R                        (1uL<<5)
#define  BSP_OS_REG_TC_MR1S                        (1uL<<6)

#define  BSP_OS_REG_TC_MR2I                        (1uL<<7)
#define  BSP_OS_REG_TC_MR2R                        (1uL<<8)
#define  BSP_OS_REG_TC_MR2S                        (1uL<<9)

#define  BSP_OS_REG_TC_MR3I                        (1uL<<10)
#define  BSP_OS_REG_TC_MR3R                        (1uL<<11)
#define  BSP_OS_REG_TC_MR3S                        (1uL<<2)


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

typedef  struct bsp_os_tmr_reg {
    INT32U  IR;
    INT32U  TCR;
    INT32U  TC;
    INT32U  PR;
    INT32U  PC;
    INT32U  MCR;
    INT32U  MR[4];
    INT32U  CCR;
    INT32U  CR[4];
    INT32U  EMR;
} BSP_OS_TMR_REG, *BSP_OS_TMR_REG_PTR;




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

static  void  BSP_OS_TmrTickISR_Handler (void);

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                          OS_CPU_ExceptHndlr()
*
* Description : Handle any exceptions.
*
* Argument(s) : except_id     ARM exception type:
*
*                                  OS_CPU_ARM_EXCEPT_RESET             0x00
*                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
*                                  OS_CPU_ARM_EXCEPT_SWI               0x02
*                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
*                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
*                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
*                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
*                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_ARM_EXCEPT_HANDLER(), which is declared in os_cpu_a.s.
*
* Note(s)     : (1) Only OS_CPU_ARM_EXCEPT_FIQ and OS_CPU_ARM_EXCEPT_IRQ exceptions handler are implemented. 
*                   For the rest of the exception a infinite loop is implemented for debuging pruposes. This behavior
*                   should be replaced with another behavior (reboot, etc).
*********************************************************************************************************
*/

void  OS_CPU_ExceptHndlr (INT32U  except_id)
{
      
    switch (except_id) {
        case OS_CPU_ARM_EXCEPT_FIQ:   
             BSP_IntSched(BSP_INT_SRC_TYPE_FIQ);
             break;
             
       
       case OS_CPU_ARM_EXCEPT_IRQ:    
             BSP_IntSched(BSP_INT_SRC_TYPE_IRQ);
             break;
                        
 
        case OS_CPU_ARM_EXCEPT_RESET:
             /* $$$$ Insert code to handle a Reset exception               */
        
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
            /* $$$$ Insert code to handle a Undefine Instruction exception */ 

        case OS_CPU_ARM_EXCEPT_SWI:               
            /* $$$$ Insert code to handle a Software exception             */ 
        
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
            /* $$$$ Insert code to handle a Prefetch Abort exception       */ 
        
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:        
            /* $$$$ Insert code to handle a Data Abort exception           */ 
        
        case OS_CPU_ARM_EXCEPT_ADDR_ABORT:        
            /* $$$$ Insert code to handle a Address Abort exception        */ 
        default:        
 
            while (1) {                                  /* Infinite loop on other exceptions. (see note #1)          */
                ;                                               
            }
    }      
}

/*
*********************************************************************************************************
*                                            BSP_OS_TmrTickInit()
*
* Description : Initialize uC/OS-II's tick source
*
* Argument(s) : ticks_per_sec              Number of ticks per second.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_TmrTickInit (INT32U  tick_per_sec)
{
    INT32U  pclk_freq;
    INT32U  tmr_reload;
    

    BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_TMR0);

                                                                /* Determine the number of counts per tick.           */
    pclk_freq  = BSP_SysCtrl_PerClkFreqGet(BSP_SYS_CTRL_PER_NBR_TMR0);

    tmr_reload = (pclk_freq / tick_per_sec);


    BSP_IntVectSet((INT8U   )BSP_INT_SRC_NBR_TMR0,
                   (INT8U   )BSP_INT_PRIO_LOWEST,
                   (INT8U   )BSP_INT_SRC_TYPE_IRQ,
                   (OS_FNCT_VOID)BSP_OS_TmrTickISR_Handler);
    
    BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_TMR0);
    

    BSP_OS_TC0_BASE_REG->TCR   = 0uL;                  /* Disable Timer 0                                    */
    BSP_OS_TC0_BASE_REG->PR    = 0uL;                  /* Prescaler is set to no division                    */
    BSP_OS_TC0_BASE_REG->PC    = 0uL;                  
    BSP_OS_TC0_BASE_REG->IR    = 0xFFFFFFFF;
        
    BSP_OS_TC0_BASE_REG->MR[0] = tmr_reload;                   
    BSP_OS_TC0_BASE_REG->MCR   = BSP_OS_REG_TC_MR0I
                               | BSP_OS_REG_TC_MR0R;                   
    
    BSP_OS_TC0_BASE_REG->CCR   = 0uL;
    BSP_OS_TC0_BASE_REG->EMR   = 0uL;
    BSP_OS_TC0_BASE_REG->TCR   = BSP_OS_REG_TCR_CNTR_EN;        /* Enable timer                                       */
    
    BSP_IntEn(BSP_INT_SRC_NBR_TMR0);

}



/*
*********************************************************************************************************
*                                           BSP_TmrTickISR_Handler()
*
* Description : This function handles the PIT interrupt that is used to generate TICKs for uC/OS-II.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Sys_Int_Handler()
*
* Note(s)     : none.              
*********************************************************************************************************
*/

static  void  BSP_OS_TmrTickISR_Handler (void)
{
    BSP_OS_TC0_BASE_REG->IR = BSP_OS_REG_TC_MR0I;               /* Clear the match interrupt                          */                                                              

    OSTimeTick();                                               /* Tell uC/OS-II about clock tick                     */

}












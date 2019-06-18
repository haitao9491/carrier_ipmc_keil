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
*                                         BOARD SUPPORT PACKAGE
*                                         (INTERRUPT CONTROLLER)
*
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_INT_MODULE
#include "bsp.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_VIC_BASE_ADDR                          ((INT32U)0xFFFFF000)
#define  BSP_INT_VIC_REG                                ((BSP_INT_REG_PTR)(BSP_INT_VIC_BASE_ADDR))


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

typedef  struct bsp_int_reg {
    INT32U  VIC_IRQ_Status;                                  /* IRQ status register                                */
    INT32U  VIC_FIQ_Status;                                  /* FIQ status register                                */
    INT32U  VIC_RawInt;                                      /* Raw interrupt register                             */
    INT32U  VIC_IntSel;                                      /* Interrupt select register                          */
    INT32U  VIC_IntEn;                                       /* Interrupt enable register                          */
    INT32U  VIC_IntEnClr;                                    /* Interrupt enable clear register                    */
    INT32U  VIC_SoftInt;                                     /* Software interrupt register                        */
    INT32U  VIC_SoftIntClr;                                  /* Software interrupt clear register                  */
    INT32U  VIC_Protection;                                  /* Protection enable register                         */
    INT32U  VIC_SW_PrioMak;                                  /* Software Priotiry Mask                             */
    INT32U  RESERVED0[54];
    INT32U  VIC_VectAddrx[BSP_INT_SLOT_NBR_MAX];             /* Vector Address  xx register                        */
    INT32U  RESERVED2[32];
    INT32U  VIC_VectPriox[BSP_INT_SLOT_NBR_MAX];             /* Vector Priority xx register                        */
    INT32U  RESERVED3[800];
    INT32U  VIC_VectAddr;                                    /* Vector address register                            */
} BSP_INT_REG, *BSP_INT_REG_PTR;


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
*********************************************************************************************************
*                                          BSP_IntClr()
*
* Description : This function clears an interrupt
*
* Argument(s) : int_src_nbr           The interrupt source number
*                                         BSP_INT_SRC_NBR_WDT   
*                                         BSP_INT_SRC_NBR_SW   
*                                         BSP_INT_SRC_NBR_DBG_RX
*                                         BSP_INT_SRC_NBR_DBG_TX  
*                                                   .
*                                                   .
*                                                   .
*                                         BSP_INT_SRC_NBR_CAN2RX
*
* Returns     : DEF_OK    if the interrupt was clear
*               DEF_FAIL  if the interrupt could not be clear.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

BOOLEAN  BSP_IntClr (INT8U  int_src_nbr)
{
    if (int_src_nbr > (BSP_INT_SRC_NBR_MAX - 1)) {
        return 0;
    }         
    return 1;

}


/*
*********************************************************************************************************
*                                          BSP_IntDis()
*
* Description : This function disables an interrupt
*
* Argument(s) : int_src_nbr           The interrupt source number
*                                         BSP_INT_SRC_NBR_WDT   
*                                         BSP_INT_SRC_NBR_SW   
*                                         BSP_INT_SRC_NBR_DBG_RX
*                                         BSP_INT_SRC_NBR_DBG_TX  
*                                                   .
*                                                   .
*                                                   .
*                                         BSP_INT_SRC_NBR_I2S 
*
* Returns     : DEF_OK    if the interrupt was disabled
*               DEF_FAIL  if the interrupt could not be disabled
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

BOOLEAN  BSP_IntDis (INT8U  int_src_nbr)
{                                                                /* -------------- ARGUMENTS CHECKING ---------------- */       
    if (int_src_nbr > (BSP_INT_SRC_NBR_MAX - 1)) {
        return 0;
    }   
    BSP_INT_VIC_REG->VIC_IntEnClr = (1uL<<int_src_nbr);  
    return 1;
}


/*
*********************************************************************************************************
*                                             bsp_inttrupt_disable_all()
*
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Argument(s) : none.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{    
                                                                /* Disable all interrupts                             */
    BSP_INT_VIC_REG->VIC_IntEnClr = DEF_BIT_FIELD(BSP_INT_SRC_NBR_MAX, 0);             
}


/*
*********************************************************************************************************
*                                          BSP_IntClr()
*
* Description : This function enables an interrupt
*
* Argument(s) : int_src_nbr    the interrupt source number
*                                  BSP_INT_SRC_NBR_WDT   
*                                  BSP_INT_SRC_NBR_SW   
*                                  BSP_INT_SRC_NBR_DBG_RX
*                                  BSP_INT_SRC_NBR_DBG_TX  
*                                              .
*                                              .
*                                              .
*                                  BSP_INT_SRC_NBR_I2S 
*
* Returns     : DEF_OK         if the interrupt was enabled
*               DEF_FAIL       if the interrupt could not be enabled
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

BOOLEAN  BSP_IntEn (INT8U  int_src_nbr)
{
                                                                /* -------------- ARGUMENTS CHECKING ---------------- */                                                                       
    if (int_src_nbr > (BSP_INT_SRC_NBR_MAX - 1)) {
        return 0;
    }  
    BSP_INT_VIC_REG->VIC_IntEn = (1uL<<int_src_nbr);  
    return 1;
}

/*
*********************************************************************************************************
*                                          BSP_IntVectSet()
*
* Description : This function sets the specified interrupt source's ISR handler call back function.
*
* Argument(s) : int_src_nbr     The interrupt source number
*                                   BSP_INT_SRC_NBR_WDT   
*                                   BSP_INT_SRC_NBR_SW   
*                                   BSP_INT_SRC_NBR_DBG_RX
*                                   BSP_INT_SRC_NBR_DBG_TX  
*                                               .
*                                               .
*                                               .
*                                   BSP_INT_SRC_NBR_I2S 
*
*               int_src_prio    Interrupt priority 
*                                   0        Highest
*                                   15       Lowest
*
*               int_src_type    Interrupt source type.
*                                   BSP_INT_SRC_TYPE_IRQ
*                                   BSP_INT_SRC_TYPE_FIQ
*
*               int_isr         ISR handler function in the form of 'void ISR_Handler (void)'.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none
*********************************************************************************************************
*/

BOOLEAN  BSP_IntVectSet (INT8U     int_src_nbr,
                         INT8U     int_src_prio,
                         INT8U     int_src_type,
                         OS_FNCT_VOID  int_isr_fnct)
{
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif    
                                                                /* ---------------- ARGUMENTS CHECKING -------------- */
    if (int_src_prio > BSP_INT_PRIO_LOWEST) {                   /* Invalid interrupt source priority ?                */
        return 0;
    }
    if ((int_src_type != BSP_INT_SRC_TYPE_IRQ) &&               /* Invalid interrupt type                             */
        (int_src_type != BSP_INT_SRC_TYPE_FIQ)) {
        return 0;
    }                        
    if (int_isr_fnct == (OS_FNCT_VOID)0 ) {                    /* NULL function pointer                              */
        return 0;
    }
    OS_ENTER_CRITICAL();

    BSP_INT_VIC_REG->VIC_VectPriox[int_src_nbr] = int_src_prio & DEF_BIT_FIELD(4, 0);
    BSP_INT_VIC_REG->VIC_VectAddrx[int_src_nbr] = (INT32U)int_isr_fnct;

    if (int_src_type == BSP_INT_SRC_TYPE_IRQ) {
        DEF_BIT_CLR(BSP_INT_VIC_REG->VIC_IntSel, (1uL<<int_src_nbr));    
    } else {
        DEF_BIT_SET(BSP_INT_VIC_REG->VIC_IntSel, (1uL<<int_src_nbr));            
    }
    OS_EXIT_CRITICAL();
    
    return 1;
}


/*
*********************************************************************************************************
*                                        BSP_IntSched()
*
* Description : This function schedules a new interrup service routine (ISR)
*
* Argument(s) : int_type   Interrupt type selection, 
*                              BSP_INT_SRC_TYPE_IRQ   The interrupt is a standard interrupt request (IRQ)
*                              BSP_INT_SRC_TYPE_FIQ   The interrupt is a fast     interrupt request (FIQ)
*
* Return(s)   : none.
*
* Caller(s)   : OS Global Interrupt Handler
*
* Note(s)     : none               
*********************************************************************************************************
*/

void  BSP_IntSched(INT8U  int_type) 
{
    OS_FNCT_VOID   p_isr;
    INT32U      fiq_status;
    INT32U      fiq_en;
    INT32U      irq_status;
    INT32U      irq_en;

        
    if (int_type == BSP_INT_SRC_TYPE_FIQ) {                     /* Schedule IRQ interrupts                            */
        fiq_status  = BSP_INT_VIC_REG->VIC_FIQ_Status;          /* Read the FIQ status register                       */
        fiq_en      = BSP_INT_VIC_REG->VIC_IntEn;
        fiq_en     &= BSP_INT_VIC_REG->VIC_IntSel;
        fiq_status &= fiq_en;                                   /* Process only the enabled interrupts source         */
        
        while (fiq_status != 0uL) {
                                                                /* Read the interrupt vector address from the VIC     */        
            p_isr = (OS_FNCT_VOID)BSP_INT_VIC_REG->VIC_VectAddr;  

            if (p_isr != (OS_FNCT_VOID)0) {                     /* Make sure we don't have a NULL pointer             */
                (*p_isr)();
                BSP_INT_VIC_REG->VIC_VectAddr = 0uL;    /* Acknowlege the VIC interrupt                       */
            }
            
            fiq_status  = BSP_INT_VIC_REG->VIC_FIQ_Status;
            fiq_en      = BSP_INT_VIC_REG->VIC_IntEn;
            fiq_en     &= BSP_INT_VIC_REG->VIC_IntSel;
            fiq_status &= fiq_en;
        }
    }                
                                               
    if (int_type == BSP_INT_SRC_TYPE_IRQ) {                     /* Schedule IRQ interrupts                            */
        irq_status  = BSP_INT_VIC_REG->VIC_IRQ_Status;          /* Read the IRQ status register                       */
        irq_en      = BSP_INT_VIC_REG->VIC_IntEn;
        DEF_BIT_CLR(irq_en, BSP_INT_VIC_REG->VIC_IntSel);
        irq_status &= irq_en;                                   /* Process only the enabled interrupts source         */

        while (irq_status != 0uL) {
                                                                /* Read the interrupt vector address from the VIC     */        
            p_isr = (OS_FNCT_VOID)BSP_INT_VIC_REG->VIC_VectAddr;  

            if (p_isr != (OS_FNCT_VOID)0) {                     /* Make sure we don't have a NULL pointer             */
                (*p_isr)();
                BSP_INT_VIC_REG->VIC_VectAddr = 0uL;    /* Acknowlege the VIC interrupt                       */
            }
            irq_status  = BSP_INT_VIC_REG->VIC_IRQ_Status; 
            irq_en      = BSP_INT_VIC_REG->VIC_IntEn;
            DEF_BIT_CLR(irq_en, BSP_INT_VIC_REG->VIC_IntSel);
            irq_status &= irq_en;                         
        }
    }
}


/*
*********************************************************************************************************
*                                    BSP_IntCtrlInit()
*
* Description : This function initialize the interrupt controller.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : bsp_init().
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_IntInit (void)
{
    INT8U  int_src_nbr;   
    BSP_IntDisAll();
    BSP_INT_VIC_REG->VIC_VectAddr = 0uL;

    for (int_src_nbr = BSP_INT_SRC_NBR_WDT; int_src_nbr < BSP_INT_SRC_NBR_MAX; int_src_nbr++) {         
         BSP_INT_VIC_REG->VIC_VectPriox[int_src_nbr] = 0uL;
         BSP_INT_VIC_REG->VIC_VectAddrx[int_src_nbr] = 0uL;             
    }     
}

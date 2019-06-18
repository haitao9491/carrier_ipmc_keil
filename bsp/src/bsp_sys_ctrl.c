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
*                                          (SYSTEM CONTROLLER)
*
* Filename      : bsp_sys_ctrl.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "ucos_ii.h"
#include "bsp.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* -------  EXTERNAL INTERRUP REGISTER DEFINEs ------ */
#define  BSP_SYS_CTRL_REG_EXT_INT_BASE_ADDR                           (INT32U)(0xE01FC140)
#define  BSP_SYS_CTRL_REG_EXT_INT                      (*(INT32U *)(BSP_SYS_CTRL_REG_EXT_INT_BASE_ADDR + 0x00))
#define  BSP_SYS_CTRL_REG_EXT_WAKE                     (*(INT32U *)(BSP_SYS_CTRL_REG_EXT_INT_BASE_ADDR + 0x04))
#define  BSP_SYS_CTRL_REG_EXT_MODE                     (*(INT32U *)(BSP_SYS_CTRL_REG_EXT_INT_BASE_ADDR + 0x08))
#define  BSP_SYS_CTRL_REG_EXT_POLAR                    (*(INT32U *)(BSP_SYS_CTRL_REG_EXT_INT_BASE_ADDR + 0x0C))

                                                                /* ----- MEMORY MAPPING CONTROL REGISTER DEFINES ---- */
#define  BSP_SYS_CTRL_REG_MEMAP                        (*(INT32U *)(0xE01FC040))

                                                                /* ------------- PLL REGISTER DEFINES --------------- */
#define  BSP_SYS_CTRL_REG_PLL0_BASE_ADDR                               (INT32U)(0xE01FC080)
#define  BSP_SYS_CTRL_REG_PLL0_CTRL                    (*(INT32U *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR + 0x00))
#define  BSP_SYS_CTRL_REG_PLL0_CFG                     (*(INT32U *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR + 0x04))
#define  BSP_SYS_CTRL_REG_PLL0_STAT                    (*(INT32U *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR + 0x08))
#define  BSP_SYS_CTRL_REG_PLL0_FEED                    (*(INT32U *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR + 0x0C))

                                                                /* --------- POWER CONTROL REGISTER DEFINES --------- */
#define  BSP_SYS_CTRL_REG_PWR_CTRL_BASE_ADDR                        (INT32U)(0xE01FC0C0)
#define  BSP_SYS_CTRL_REG_PCON                         (*(INT32U *)(BSP_SYS_CTRL_REG_PWR_CTRL_BASE_ADDR + 0x00))
#define  BSP_SYS_CTRL_REG_PCONP                        (*(INT32U *)(BSP_SYS_CTRL_REG_PWR_CTRL_BASE_ADDR + 0x04))

                                                                /* ------- CLOCK SOURCE SELECT REGISTER DEFINE ------ */
#define  BSP_SYS_CTRL_PCLKSRCSEL                       (*(INT32U *)(0xE01FC10C))

                                                                /* -------- POWER CONTROL REGISTER BIT DEFINES ------ */
                                                                /* Idle mode                                          */
#define  BSP_SYS_CTRL_REG_PCON_IDL                      (1uL<<0)

                                                                /* Power mode register                                */
#define  BSP_SYS_CTRL_REG_PCON_PD                       (1uL<<1)
#define  BSP_SYS_CTRL_REG_PCON_PM2                      (1uL<<7)

                                                                /* --- MEMORY MAPPING CONTROL REGISTER BIT DEFINES -- */
#define  BSP_SYS_CTRL_REG_MEMAP_MAP_MASK                DEF_BIT_FIELD(2, 0)
#define  BSP_SYS_CTRL_REG_MEMAP_MAP_BOOT                0uL
#define  BSP_SYS_CTRL_REG_MEMAP_MAP_FLASH               DEF_BIT_MASK(1, 0)
#define  BSP_SYS_CTRL_REG_MEMAP_MAP_IRAM                DEF_BIT_MASK(2, 0)
#define  BSP_SYS_CTRL_REG_MEMAP_MAP_XRAM                DEF_BIT_MASK(4, 0)

                                                                /* --------- PLL STATUS REGISTER BIT DEFINES -------- */
#define  BSP_SYS_CTRL_REG_PLLSTAT_MSEL_MASK             DEF_BIT_FIELD(14,  0)
#define  BSP_SYS_CTRL_REG_PLLSTAT_PSEL_MASK             DEF_BIT_FIELD(8 , 16)
#define  BSP_SYS_CTRL_REG_PLLSTAT_PLLE                  (1uL<<24)
#define  BSP_SYS_CTRL_REG_PLLSTAT_PLLC                  (1uL<<25)
#define  BSP_SYS_CTRL_REG_PLLSTAT_PLOCK                 (1uL<<26)

                                                                /* -------- PLL CONTROL REGISTER BIT DEFINES -------- */
#define  BSP_SYS_CTRL_REG_PLLCTRL_PLLE                  (1uL<<0)
#define  BSP_SYS_CTRL_REG_PLLCTRL_PLLC                  (1uL<<1)

                                                                /* ------- PLL FEED REGISTER REGISTER BIT DEFINES --- */
#define  BSP_SYS_CTRL_REG_PLLFEED_VAL0                       0xAA
#define  BSP_SYS_CTRL_REG_PLLFEED_VAL1                       0x55

                                                                /* -------- CLOCK DIVIDERS REGISTER DEFINITION ------ */
#define  BSP_SYS_CTRL_CCLKCFG                           (*(INT32U *)(0xE01FC104))
#define  BSP_SYS_CTRL_USBCLKCFG                         (*(INT32U *)(0xE01FC108))
#define  BSP_SYS_CTRL_IRCTRIM                           (*(INT32U *)(0xE01FC1A4))
#define  BSP_SYS_CTRL_PCLKSEL0                          (*(INT32U *)(0xE01FC1A8))
#define  BSP_SYS_CTRL_PCLKSEL1                          (*(INT32U *)(0xE01FC1AC))

                                                                /* ---------- APB DIVIDER REGISTER BIT DEFINES ------ */
#define  BSP_SYS_CTRL_REG_APBDIV_MASK                   DEF_BIT_FIELD(2, 0)
#define  BSP_SYS_CTRL_REG_APBDIV_4                      0uL
#define  BSP_SYS_CTRL_REG_APBDIV_1                      DEF_BIT_MASK(1, 0)
#define  BSP_SYS_CTRL_REG_APBDIV_2                      DEF_BIT_MASK(2, 0)

                                                                /* ---------- SYSTEM CONTROLLER CONSTRIAINS --------- */
#define  BSP_SYS_CTRL_PLL_MUL_MAX                       DEF_BIT_FIELD(15, 0)
#define  BSP_SYS_CTRL_PLL_DIV_MAX                              32
#define  BSP_SYS_CTRL_REG_TO_VAL                            0x1FF


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

typedef  struct bsp_sys_ctrl_pll_reg {
    INT32U  PLLCTRL;
    INT32U  PLLCFG;
    INT32U  PLLSTAT;
    INT32U  PLLFEED;
} BSP_SYS_CTRL_PLL_REG;

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
*                                              BSP_SysCtrl_CPU_FreqGet ()
*
* Description : This function return the CPU clk frequency
*
* Argument(s) : none.
*
* Return(s)   : The CPU clk frequency
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

INT32U  BSP_SysCtrl_CPU_FreqGet (void)
{
    INT32U  cpu_freq;
    INT32U  cpu_div;
    

    cpu_freq = BSP_SysCtrl_PLL_FreqGet(BSP_SYS_CTRL_PLL0_ID);
    cpu_div  = BSP_SYS_CTRL_CCLKCFG & DEF_BIT_FIELD(7, 0); 
    cpu_div++;
    
    if (cpu_div != 0) {
        cpu_freq /= cpu_div;
    }
    
    return (cpu_freq);
}


/*
*********************************************************************************************************
*                                              BSP_SysCtrl_CPU_FreqCfg ()
*
* Description : This function configures the frequency of the CPU
*
* Argument(s) : clk_div           The divider value to create the CPU clk form the PLL output
*                                     cpu_clk = pll_clk / clk_div

*                                 Only one and even values (2, 4, 8, ... etc) can be used
*
* Return(s)   : none
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

void  BSP_SysCtrl_CPU_FreqCfg (INT8U clk_div)
{
    if (clk_div == 0) {
        return;        
    }
    
    if (clk_div == 1) {
        BSP_SYS_CTRL_CCLKCFG = (clk_div - 1);
        return;
    }

    if (clk_div % 2 == 0) {
        BSP_SYS_CTRL_CCLKCFG = (clk_div - 1);
    }            
}


/*
*********************************************************************************************************
*                                          BSP_SysCtrl_CPU_ModeGet()
*
* Description : This function set the CPU to an specific mode.
*
* Argument(s) : none
*                         
* Return(s) : cpu_mode            The cpu mode to be set. (see note #1)
*
*                                      BSP_SYS_CTRL_CPU_MODE_NORMAL      Normal Operating mode
*                                      BSP_SYS_CTRL_CPU_MODE_IDLE        Direct RUN       mode                
*                                      BSP_SYS_CTRL_CPU_MODE_PWR_DOWN    STOP             mode    
*                                      BSP_SYS_CTRL_CPU_MODE_SLEEP       Sleep            mode
*
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT8U  BSP_SysCtrl_CPU_ModeGet (void)
{
    INT32U  pcon_reg;
    INT8U  cpu_mode;
    
    
    pcon_reg  = BSP_SYS_CTRL_REG_PCON;

    pcon_reg &= (BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PD | BSP_SYS_CTRL_REG_PCON_PM2);
    
    switch (pcon_reg) {
        case (0uL): 
            cpu_mode = BSP_SYS_CTRL_CPU_MODE_NORMAL;
            break;
        
        case (BSP_SYS_CTRL_REG_PCON_IDL): 
            cpu_mode = BSP_SYS_CTRL_CPU_MODE_IDLE ;
            break;

        case (BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2): 
            cpu_mode = BSP_SYS_CTRL_CPU_MODE_SLEEP;
            break;


        case (BSP_SYS_CTRL_REG_PCON_PD): 
        default:
            cpu_mode = BSP_SYS_CTRL_CPU_MODE_PWR_DOWN;
            break;
    }
    
    return (cpu_mode);    
}


/*
*********************************************************************************************************
*                                          BSP_SysCtrl_CPU_ModeSet()
*
* Description : This function set the CPU to a specific mode.
*
* Argument(s) : cpu_mode            The cpu mode to be set. 
*
*                                      BSP_SYS_CTRL_CPU_MODE_NORMAL      Normal Operating mode
*                                      BSP_SYS_CTRL_CPU_MODE_IDLE        Direct RUN       mode                
*                                      BSP_SYS_CTRL_CPU_MODE_PWR_DOWN    STOP             mode   
*                                      BSP_SYS_CTRL_CPU_MODE_SLEEP       Sleep            mode
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SysCtrl_CPU_ModeSet (INT8U  cpu_mode)
{
    switch (cpu_mode) {
        case BSP_SYS_CTRL_CPU_MODE_NORMAL:
             DEF_BIT_CLR(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_PD | BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2));
             break;
        
        case BSP_SYS_CTRL_CPU_MODE_PWR_DOWN:
             DEF_BIT_CLR(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_PD | BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2));
             DEF_BIT_SET(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_PD));                         
             break;             

        case BSP_SYS_CTRL_CPU_MODE_IDLE:
             DEF_BIT_CLR(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_PD | BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2));
             DEF_BIT_SET(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_IDL));
             break;

        case BSP_SYS_CTRL_CPU_MODE_SLEEP:
             DEF_BIT_CLR(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_PD | BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2));
             DEF_BIT_SET(BSP_SYS_CTRL_REG_PCON, (BSP_SYS_CTRL_REG_PCON_IDL | BSP_SYS_CTRL_REG_PCON_PM2));
             
             break;
             
        default:
             break;
    }    
}


/*
*********************************************************************************************************
*                                          BSP_SysCtrl_MemMapModeGet()
*
* Description : This function returns the memory map mode.
*
* Argument(s) : none
*
* Return(s)   : The memory map mode to be set
*
*                   BSP_SYS_CTRL_MEM_MAP_MODE_BOOT_LOADER  Interrupt vector are re-mapped to boot block
*
*                   BSP_SYS_CTRL_MEM_MAP_MODE_FLASH        Interrupt vector are not re-mapped and reside in Flash memory
*
*                   BSP_SYS_CTRL_MEM_MAP_MODE_IRAM         Interrupt vector are re-mapped to static RAM (internal RAM)
*
*                   BSP_SYS_CTRL_MEM_MAP_MODE_XRAM         Interrupt vector are re-mapped to external memory (external RAM)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT8U  BSP_SysCtrl_MemMapModeGet (void)
{
	INT32U  memap_reg;
	INT8U  mem_map_mode;

	memap_reg = BSP_SYS_CTRL_REG_MEMAP & BSP_SYS_CTRL_REG_MEMAP_MAP_MASK;
    
	switch (memap_reg) {
	case BSP_SYS_CTRL_REG_MEMAP_MAP_BOOT:
		mem_map_mode = BSP_SYS_CTRL_MEM_MAP_MODE_BOOT_LOADER;
		break;
	case BSP_SYS_CTRL_REG_MEMAP_MAP_FLASH:
		mem_map_mode = BSP_SYS_CTRL_MEM_MAP_MODE_FLASH;                         
		break;             
	case BSP_SYS_CTRL_REG_MEMAP_MAP_IRAM:
		mem_map_mode = BSP_SYS_CTRL_MEM_MAP_MODE_IRAM;
		break;
	case BSP_SYS_CTRL_REG_MEMAP_MAP_XRAM:
		mem_map_mode = BSP_SYS_CTRL_MEM_MAP_MODE_XRAM;
		break;
	default:
		
		break;
	}
	return mem_map_mode;        
}


/*
*********************************************************************************************************
*                                          BSP_SysCtrl_MemMapModeSet()
*
* Description : This function set the memory map mode.
*
* Argument(s) : mem_map_mode           The memory map mode to be set
*
*                                          BSP_SYS_CTRL_MEM_MAP_MODE_BOOT_LOADER  Interrupt vector are re-mapped 
*                                                                                 to boot block
*
*                                          BSP_SYS_CTRL_MEM_MAP_MODE_FLASH        Interrupt vector are not re-mapped 
*                                                                                 and reside in Flash memory
*
*                                          BSP_SYS_CTRL_MEM_MAP_MODE_IRAM         Interrupt vector are re-mapped to static
*                                                                                 RAM (internal RAM)
*
*                                          BSP_SYS_CTRL_MEM_MAP_MODE_XRAM         Interrupt vector are re-mapped to external
*                                                                                 memory (external RAM)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SysCtrl_MemMapModeSet (INT8U  mem_map_mode)
{
    switch (mem_map_mode) {
        case BSP_SYS_CTRL_MEM_MAP_MODE_BOOT_LOADER:
             BSP_SYS_CTRL_REG_MEMAP = BSP_SYS_CTRL_REG_MEMAP_MAP_BOOT;
             break;
        
        case BSP_SYS_CTRL_MEM_MAP_MODE_FLASH:
             BSP_SYS_CTRL_REG_MEMAP = BSP_SYS_CTRL_REG_MEMAP_MAP_FLASH;                         
             break;             

        case BSP_SYS_CTRL_MEM_MAP_MODE_IRAM:
             BSP_SYS_CTRL_REG_MEMAP = BSP_SYS_CTRL_REG_MEMAP_MAP_IRAM;
             break;

        case BSP_SYS_CTRL_MEM_MAP_MODE_XRAM:
             BSP_SYS_CTRL_REG_MEMAP = BSP_SYS_CTRL_REG_MEMAP_MAP_XRAM;
             break;
             
        default:
             break;
    }    
}


/*
*********************************************************************************************************
*                                              BSP_SysCtrl_PLL_Cfg()
*
* Description : This function configures and enable the PLL
*
* Argument(s) : pll_id                PLL Identifier
*                                         BSP_SYS_CTRL_PLL0_ID
*                                         BSP_SYS_CTRL_PLL1_ID
*                 
*               pll_mul               PLL multiplier value
*
*               pll_div               PLL divider value (max 32)
*
*               pll_clk_src           PLL Clock source
*                                         BSP_SYSCTRL_PLL_CLK_SRC_INT_RC  Selects the internal RC oscillator
*                                         BSP_SYSCTRL_PLL_CLK_SRC_MAIN    Selects the main oscillator as the PLL clock source.
*                                         BSP_SYSCTRL_PLL_CLK_SRC_RTC     Selects the RTC oscillator as the PLL clock source.
*
* Return(s)   : DEF_OK    if the PLL was enable and configured
*               DEF_FAIL  if the PLL could not be enable nor configured.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The PLL output frequency (when the PLL is both coneected and active) is given by
*                    Fcco = (2 x M x Fin) / N        M  = Multiplier
*                                                    N  = Divider
*                                                  Fin  = Input frequency (32 Khz t 25 Mhz)
*                                                  Fcco = PLL output
*
*               (2) The PLL inputs must meet the following:
*                     Fosc is in the range of 32Khz to 25 Mhz
*                     Fcco is in the range of 275 Mhz to 550 Mhz
*                
*********************************************************************************************************
*/

BOOLEAN  BSP_SysCtrl_PLL_Cfg (INT8U  pll_id,
                                  INT16U  pll_mul,
                                  INT8U  pll_div,
                                  INT8U  pll_clk_src)

{
    BSP_SYS_CTRL_PLL_REG  *p_pll_reg;
    INT32U             reg_val;
    INT32U             reg_to;    
#if OS_CRITICAL_METHOD == 3u
    OS_CPU_SR  cpu_sr = 0u;
#endif
        
                                                                /* ---------------- ARGUMENTS CHECKING -------------- */
    if (pll_mul > BSP_SYS_CTRL_PLL_MUL_MAX) {
        return (0);
    }
    
    if (pll_div > BSP_SYS_CTRL_PLL_DIV_MAX) {
        return (0);
    }
    
    if (pll_mul == 0) {
        return (0);
    }
    
    if (pll_div == 0) {
        return (0);
    }


    if (pll_id == BSP_SYS_CTRL_PLL0_ID) {
        p_pll_reg = (BSP_SYS_CTRL_PLL_REG  *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR);
    } else {
        return (0);               
    }
                                                                           /* Select the PLL clock source                        */
    switch (pll_clk_src) {
        case BSP_SYSCTRL_PLL_CLK_SRC_INT_RC:
             reg_val = 0x00;
             break;

        case BSP_SYSCTRL_PLL_CLK_SRC_MAIN:
             reg_val = 0x01;
             break;

        case BSP_SYSCTRL_PLL_CLK_SRC_RTC:
             reg_val = 0x02;
             break;

        default:
             return (0);
    }
    
    BSP_SYS_CTRL_PCLKSRCSEL = reg_val;
   
    
    OS_ENTER_CRITICAL();
    
    p_pll_reg->PLLCFG  = ((pll_mul - 1 << 0)  & DEF_BIT_FIELD(15,  0))
                       | ((pll_div - 1 << 16) & DEF_BIT_FIELD(8,  16));

    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL0;
    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL1;       
            
    p_pll_reg->PLLCTRL = BSP_SYS_CTRL_REG_PLLCTRL_PLLE;

    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL0;
    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL1;       
    
    OS_EXIT_CRITICAL();
    
    reg_to = BSP_SYS_CTRL_REG_TO_VAL;
    
    while (DEF_BIT_IS_CLR(p_pll_reg->PLLSTAT, BSP_SYS_CTRL_REG_PLLSTAT_PLOCK) &&
           (reg_to > 0)) {
        reg_to--;
    }
    
    if (reg_to == 0) {
        return (0);
    }

    OS_ENTER_CRITICAL();
    
    p_pll_reg->PLLCTRL = BSP_SYS_CTRL_REG_PLLCTRL_PLLE 
                       | BSP_SYS_CTRL_REG_PLLCTRL_PLLC;

    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL0;
    p_pll_reg->PLLFEED = BSP_SYS_CTRL_REG_PLLFEED_VAL1;       
        
    
    OS_EXIT_CRITICAL();
    
    while (DEF_BIT_IS_CLR_ANY(p_pll_reg->PLLSTAT, (BSP_SYS_CTRL_REG_PLLSTAT_PLLE | BSP_SYS_CTRL_REG_PLLSTAT_PLLC)) &&
           (reg_to > 0)) {
        reg_to--;
    }
    
    if (reg_to == 0) {
        return (0);
    }
        
    return (1);

}


/*
*********************************************************************************************************
*                                              BSP_SysCtrl_PLL_FreqGet()
*
* Description : This function returns the PLL's frequency
*
* Argument(s) :  pll_id                PLL Identifier
*                                         BSP_SYS_CTRL_PLL0_ID
*                                         BSP_SYS_CTRL_PLL1_ID
*                
* Return(s)   : The PLL frequency if the PLL is active and connected, otherwise 
*               0 if the PLL could not be enable nor configured.
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

INT32U  BSP_SysCtrl_PLL_FreqGet (INT8U pll_id)
{
	INT16U             pll_mul;
	INT8U             pll_div;
	INT32U             pll_freq;
	INT32U             reg_val;
	BSP_SYS_CTRL_PLL_REG  *p_pll_reg;

    
	if (pll_id == BSP_SYS_CTRL_PLL0_ID) {
		p_pll_reg = (BSP_SYS_CTRL_PLL_REG  *)(BSP_SYS_CTRL_REG_PLL0_BASE_ADDR);
	} else {
		return 0;
	}
    
	reg_val = BSP_SYS_CTRL_PCLKSRCSEL & DEF_BIT_FIELD(2, 0);
    
	switch (reg_val) {
	case 0x00:
		pll_freq = BSP_SYS_CTRL_OSC_INT_RC_FREQ_HZ;
		break;
	case 0x01:
		pll_freq = BSP_SYS_CTRL_OSC_MAIN_OSC_FREQ_HZ;
		break;
	case 0x02:
		pll_freq = BSP_SYS_CTRL_OSC_RTC_FREQ_HZ;
		break;
	default :
		return 0;        
	}    
           
    if (DEF_BIT_IS_CLR_ANY(p_pll_reg->PLLSTAT, (BSP_SYS_CTRL_REG_PLLSTAT_PLLE | 
                                                BSP_SYS_CTRL_REG_PLLSTAT_PLLC |
                                                BSP_SYS_CTRL_REG_PLLSTAT_PLOCK ))) {
        return 0;
    }
    
    pll_mul   = ((p_pll_reg->PLLSTAT & BSP_SYS_CTRL_REG_PLLSTAT_MSEL_MASK) + 1);
    pll_div   = ((((p_pll_reg->PLLSTAT & BSP_SYS_CTRL_REG_PLLSTAT_PSEL_MASK)) >> 16) + 1);
//    pll_freq  = ((pll_freq * 2 * pll_mul) / pll_div);
	pll_freq  = ((pll_freq * pll_mul) / pll_div) * 2;
	    
    return pll_freq;
}


/*
*********************************************************************************************************
*                                            BSP_SysCtrl_PerClkDis()
*
* Description : This function disables a specific peripheral clk/power
*
* Argument(s) : per_nbr       The peripheral  number
*
* Return(s)   : DEF_OK        if the peripheral clock/power was disabled
*               DEF_FAIL      if the peripheal  clock/power could not be disabled
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

BOOLEAN  BSP_SysCtrl_PerClkDis (INT8U  per_nbr)
{
    switch (per_nbr) {
        case BSP_SYS_CTRL_PER_NBR_RESERVED0:
        case BSP_SYS_CTRL_PER_NBR_RESERVED1:
        case BSP_SYS_CTRL_PER_NBR_RESERVED2:
        case BSP_SYS_CTRL_PER_NBR_RESERVED3:        
        case BSP_SYS_CTRL_PER_NBR_RESERVED4:        
             return (0);
    
        default:
             break;
    }
    
    DEF_BIT_CLR(BSP_SYS_CTRL_REG_PCONP, (1uL<<per_nbr));
    
    return (1);
}


/*
*********************************************************************************************************
*                                              BSP_SysCtrl_PerClkEn()
*
* Description : This function enables a specific peripheral clk/power
*
* Argument(s) : per_nbr      The peripheral  number
*
* Return(s)   : DEF_OK       if the peripheral clock/power was enabled
*               DEF_FAIL     if the peripheal  clock/power could not be enabled
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

BOOLEAN  BSP_SysCtrl_PerClkEn (INT8U  per_nbr)
{
    switch (per_nbr) {
        case BSP_SYS_CTRL_PER_NBR_RESERVED0:
        case BSP_SYS_CTRL_PER_NBR_RESERVED1:
        case BSP_SYS_CTRL_PER_NBR_RESERVED2:
        case BSP_SYS_CTRL_PER_NBR_RESERVED3:        
        case BSP_SYS_CTRL_PER_NBR_RESERVED4:        
             return (0);
    
        default:
             break;
    }
    
    DEF_BIT_SET(BSP_SYS_CTRL_REG_PCONP, (1uL<<per_nbr));
    
    return (1);
}


/*
*********************************************************************************************************
*                                              BSP_SysCtrl_PerClkFreqCfg()
*
* Description : This function configures the frequency of a specific peripheral clock
*
* Argument(s) : per_nbr       The peripheral  number
*
*               per_clk_div   Peripheral clock divider.
*
*                             BSP_SYS_CTRL_CLK_DIV_1
*                             BSP_SYS_CTRL_CLK_DIV_2
*                             BSP_SYS_CTRL_CLK_DIV_4
*                             BSP_SYS_CTRL_CLK_DIV_6
*
* Return(s)   : DEF_OK       if the peripheral clock could be configured
*               DEF_FAIL     if the peripheal  clock could not be enabled
*
* Caller(s)   : Application.
*
* Note(s)     : (1) For BSP_SYS_CTRL_PER_NBR_RTC the value of BSP_SYS_CTRL_CLK_DIV_1 is illegal.
*
*               (2) Only valid for BSP_SYS_CTRL_PER_NBR_CAN1, BSP_SYS_CTRL_PER_NBR_CAN2 or BSP_SYS_CTRL_PER_NBR_ACF.
*********************************************************************************************************
*/

BOOLEAN  BSP_SysCtrl_PerClkFreqCfg (INT8U  per_nbr,
                                        INT8U  per_clk_div)
{
    INT32U  reg_val;
    
                                                                /* ----------------- ARGUMENTS CHECKING ------------- */
    switch (per_nbr) {
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED0:
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED1:
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED2:        
             return (0);
    
        default:
             break;
    }
    
    switch (per_clk_div) {
        case BSP_SYS_CTRL_CLK_DIV_1:            
             reg_val = 0x01;
             break;
             
        case BSP_SYS_CTRL_CLK_DIV_2:
             reg_val = 0x02;
             break;
             
        case BSP_SYS_CTRL_CLK_DIV_4:            
             reg_val = 0x00;
             break;

        case BSP_SYS_CTRL_CLK_DIV_6:            
             if ((per_nbr != BSP_SYS_CTRL_PER_NBR_CAN1) &&
                 (per_nbr != BSP_SYS_CTRL_PER_NBR_CAN2) &&
                 (per_nbr != BSP_SYS_CTRL_PER_NBR_ACF )) {
                 return (0); 
             } else {
                 reg_val = 0x03;
             }
             break;

        case BSP_SYS_CTRL_CLK_DIV_8:
             if ((per_nbr == BSP_SYS_CTRL_PER_NBR_CAN1) ||
                 (per_nbr == BSP_SYS_CTRL_PER_NBR_CAN2) ||
                 (per_nbr == BSP_SYS_CTRL_PER_NBR_ACF )) {            
                 return (0);
             } else {
                 reg_val = 0x03;             
             }
             break;
             
        default:
             return (0);
    }
    
    if (per_nbr < BSP_SYS_CTRL_PER_NBR_BAT_RAM) {
        DEF_BIT_CLR(BSP_SYS_CTRL_PCLKSEL0, DEF_BIT_FIELD(2, per_nbr * 2));
        DEF_BIT_SET(BSP_SYS_CTRL_PCLKSEL0, DEF_BIT_MASK(reg_val, per_nbr * 2));                
    } else {
        DEF_BIT_CLR(BSP_SYS_CTRL_PCLKSEL1, DEF_BIT_FIELD(2, (per_nbr - 16) * 2));
        DEF_BIT_SET(BSP_SYS_CTRL_PCLKSEL1, DEF_BIT_MASK(reg_val, (per_nbr - 16) * 2));                        
    }
    
    return (1);
}


/*
*********************************************************************************************************
*                                           BSP_SysCtrl_PerClkFreqGet()
*
* Description : This function returns the frequency of a specic peripheral clock
*
* Argument(s) : per_nbr       The peripheral  number
*
* Return(s)   : The peripheral clock frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : none.               
*********************************************************************************************************
*/

INT32U  BSP_SysCtrl_PerClkFreqGet (INT8U  per_nbr)
                                        
{
    INT32U  per_clk_freq;
    INT32U  per_clk_div;
    INT32U  reg_val;
    
                                                                /* ----------------- ARGUMENTS CHECKING ------------- */
    switch (per_nbr) {
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED0:
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED1:
        case BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED2:        
             return (0);
    
        default:
             break;
    }
    
    if (per_nbr < BSP_SYS_CTRL_PER_NBR_BAT_RAM) {
        reg_val = (BSP_SYS_CTRL_PCLKSEL0 >> (per_nbr * 2)) & DEF_BIT_FIELD(2, 0);
    } else {
        reg_val = (BSP_SYS_CTRL_PCLKSEL1 >> ((per_nbr - 16) * 2)) & DEF_BIT_FIELD(2, 0);
    }
    
    switch (reg_val) {
        case 0x01:            
             per_clk_div = BSP_SYS_CTRL_CLK_DIV_1;
             break;
             
        case 0x02:
             per_clk_div = BSP_SYS_CTRL_CLK_DIV_2;
             break;
             
        case 0x00:            
             per_clk_div = BSP_SYS_CTRL_CLK_DIV_4;
             break;

        case 0x03:            
             if ((per_nbr == BSP_SYS_CTRL_PER_NBR_CAN1) ||
                 (per_nbr == BSP_SYS_CTRL_PER_NBR_CAN2) ||
                 (per_nbr == BSP_SYS_CTRL_PER_NBR_ACF )) {
                 per_clk_div = BSP_SYS_CTRL_CLK_DIV_6;
             } else {
                 per_clk_div = BSP_SYS_CTRL_CLK_DIV_8;
             }
             break;

        default:
             break;
    }
    
    per_clk_freq  = BSP_SysCtrl_CPU_FreqGet();
    per_clk_freq /= per_clk_div;
    
    return (per_clk_freq);
}


/*
*********************************************************************************************************
*                                               BSP_SysCtrl_USB_FreqCfg()
*
* Description : This function returns the frequency of a specic peripheral clock
*
* Argument(s) : per_nbr       The peripheral  number
*
* Return(s)   : The peripheral clock frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : none.               
*********************************************************************************************************
*/

BOOLEAN  BSP_SysCtrl_USB_FreqCfg (INT8U  clk_div)

{
    if (clk_div > DEF_BIT_FIELD(4, 0)) {
        return (0);
    }
    
    if (clk_div == 0) {
        return (0);
    }

    BSP_SYS_CTRL_USBCLKCFG = (clk_div - 1);

    return (1);
}

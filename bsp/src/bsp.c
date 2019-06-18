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
*                                        MICRIUM BOARD SUPPORT PACKAGE
*
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_MODULE
#include <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* ------ SYSTEM CONTROLS AND STATUS REGISTER ------- */
#define  BSP_REG_SCS                            (*(INT32U *)(0xE01FC1A0))
#define  BSP_REG_SCS_OSRANGE                     (1uL<<4)
#define  BSP_REG_SCS_OSCEN                       (1uL<<5)
#define  BSP_REG_SCS_OSCSTAT                     (1uL<<6)

#define  BSP_REG_TO_VAL                            0xFFF

                                                                /* ------ SYSTEM CONTROLS AND STATUS REGISTER ------- */
#define  BSP_REG_MAMCR                           (*(INT32U *)(0xE01FC000))      
#define  BSP_REG_MAMTIM                          (*(INT32U *)(0xE01FC004))      

#define  BSP_REG_MAMCR_DISABLE                   DEF_BIT_MASK(0, 0)
#define  BSP_REG_MAMCR_PARTIAL                   DEF_BIT_MASK(1, 0)
#define  BSP_REG_MAMCR_FULL                      DEF_BIT_MASK(2, 0)

#define  BSP_REG_MAMTIM_CLK_1                    DEF_BIT_MASK(1, 0)
#define  BSP_REG_MAMTIM_CLK_2                    DEF_BIT_MASK(2, 0)
#define  BSP_REG_MAMTIM_CLK_3                    DEF_BIT_MASK(3, 0)
#define  BSP_REG_MAMTIM_CLK_4                    DEF_BIT_MASK(4, 0)
#define  BSP_REG_MAMTIM_CLK_5                    DEF_BIT_MASK(5, 0)
#define  BSP_REG_MAMTIM_CLK_6                    DEF_BIT_MASK(6, 0)
#define  BSP_REG_MAMTIM_CLK_7                    DEF_BIT_MASK(7, 0)

                                                                /* ----------------- SDRAM PARAMETERS --------------- */
#define  BSP_SDRAM_BASE_ADDR                     0xA0000000     /* SDRAM start address = 0xA0000000                   */
#define  BSP_SDRAM_REFRESH                             7813
#define  BSP_SDRAM_TRP                                   20
#define  BSP_SDRAM_TRAS                                  45
#define  BSP_SDRAM_TAPR                                   1
#define  BSP_SDRAM_TDAL                                   3
#define  BSP_SDRAM_TWR                                    3
#define  BSP_SDRAM_TRC                                   65
#define  BSP_SDRAM_TRFC                                  66
#define  BSP_SDRAM_TXSR                                  67
#define  BSP_SDRAM_TRRD                                  15
#define  BSP_SDRAM_TMRD                                   3

                                                                /* -------------- SDRAM PINS DEFINES  -------------- */
#define  BSP_SDRAM_GPIO2_CAS                     (1uL<<16)
#define  BSP_SDRAM_GPIO2_RAS                     (1uL<<17)
#define  BSP_SDRAM_GPIO2_CLKOUT0                 (1uL<<18)
#define  BSP_SDRAM_GPIO2_DYCS0                   (1uL<<20)
#define  BSP_SDRAM_GPIO2_CKEOUT1                 (1uL<<24)
#define  BSP_SDRAM_GPIO2_DQMOUT0                 (1uL<<28)
#define  BSP_SDRAM_GPIO2_DQMOUT1                 (1uL<<29)

#define  BSP_SDRAM_GPIO2_GRP                    (DEF_BIT_FIELD(3, 16) | \
                                                 (1uL<<20)           | \
                                                 (1uL<<24)           | \
                                                 DEF_BIT_FIELD(2, 28))

#define  BSP_SDRAM_GPIO3_D_GRP                   DEF_BIT_FIELD(16, 0)
#define  BSP_SDRAM_GPIO3_GRP                     BSP_SDRAM_GPIO3_D_GRP

#define  BSP_SDRAM_GPIO4_A_GRP                   DEF_BIT_FIELD(15, 0)
#define  BSP_SDRAM_GPIO4_WE                      (1uL<<25)
#define  BSP_SDRAM_GPIO4_GRP                    (BSP_SDRAM_GPIO4_A_GRP | \
                                                 BSP_SDRAM_GPIO4_WE)

                                                                /* ------ EMC DYNAMIC CTRL REGISTER BIT DEFINES ----- */
#define  BSP_REG_EMC_DYNAMIC_CTRL_INIT_NORMAL    DEF_BIT_MASK(0x00, 7)
#define  BSP_REG_EMC_DYNAMIC_CTRL_INIT_MODE      DEF_BIT_MASK(0x01, 7)
#define  BSP_REG_EMC_DYNAMIC_CTRL_INIT_PALL      DEF_BIT_MASK(0x02, 7)
#define  BSP_REG_EMC_DYNAMIC_CTRL_INIT_NOP       DEF_BIT_MASK(0x03, 7)
#define  BSP_REG_EMC_DYNAMIC_CTRL_INIT_MASK      DEF_BIT_MASK(0x03, 7)


#define  BSP_REG_BASE_ADDR                      ( (INT32U )(0xFFE08000))
#define  BSP_REG_EMCCONTROL                     (*(INT32U *)(BSP_REG_BASE_ADDR + 0x000))
#define  BSP_REG_EMCDINAMICCTRL                 (*(INT32U *)(BSP_REG_BASE_ADDR + 0x020))
#define  BSP_REG_EMCDINAMICRFR                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x024))
#define  BSP_REG_EMCDINAMICRDCFG                (*(INT32U *)(BSP_REG_BASE_ADDR + 0x028))
#define  BSP_REG_EMCDYNAMICRP                   (*(INT32U *)(BSP_REG_BASE_ADDR + 0x030))
#define  BSP_REG_EMCDYNAMICRAS                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x034))
#define  BSP_REG_EMCDYNAMICSREX                 (*(INT32U *)(BSP_REG_BASE_ADDR + 0x038))
#define  BSP_REG_EMCDYNAMICAPR                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x03C))
#define  BSP_REG_EMCDYNAMICDAL                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x040))
#define  BSP_REG_EMCDYNAMICWR                   (*(INT32U *)(BSP_REG_BASE_ADDR + 0x044))
#define  BSP_REG_EMCDYNAMICRC                   (*(INT32U *)(BSP_REG_BASE_ADDR + 0x048))
#define  BSP_REG_EMCDYNAMICRFC                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x04C))
#define  BSP_REG_EMCDYNAMICXSR                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x050))
#define  BSP_REG_EMCDYNAMICRRD                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x054))
#define  BSP_REG_EMCDYNAMICMRD                  (*(INT32U *)(BSP_REG_BASE_ADDR + 0x058))
#define  BSP_REG_EMCDYNAMICCFG0                 (*(INT32U *)(BSP_REG_BASE_ADDR + 0x100))
#define  BSP_REG_EMCDYNAMICRASCAS0              (*(INT32U *)(BSP_REG_BASE_ADDR + 0x104))


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

void  BSP_CPU_Init  (void);

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
*                                             BSP_CPU_Init()
*
* Description : Initialize the CPU clks, memory map, etc
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : bsp_init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_CPU_Init (void)
{
    INT32U  reg_to;

    BSP_SysCtrl_CPU_ModeSet(BSP_SYS_CTRL_CPU_MODE_NORMAL);

    DEF_BIT_CLR(BSP_REG_SCS, BSP_REG_SCS_OSRANGE);              /* Set the main oscillator range (1Mhz to 20 Mhz)     */
    DEF_BIT_SET(BSP_REG_SCS, BSP_REG_SCS_OSCEN);                /* Set the main oscillator range (1Mhz to 20 Mhz)     */
    
    reg_to = BSP_REG_TO_VAL;
    
    while ((DEF_BIT_IS_CLR(BSP_REG_SCS, BSP_REG_SCS_OSCSTAT)) &&
           (reg_to > 0))  {
        reg_to--;
    }
                                 
    BSP_SysCtrl_CPU_FreqCfg(4);                                 /* Configure the CPU and PLL frequency                */
    BSP_SysCtrl_PLL_Cfg(BSP_SYS_CTRL_PLL0_ID, 125, 16, BSP_SYSCTRL_PLL_CLK_SRC_MAIN);
   
    BSP_SysCtrl_PerClkFreqCfg(BSP_SYS_CTRL_PER_NBR_UART0, BSP_SYS_CTRL_CLK_DIV_4);
    BSP_SysCtrl_PerClkFreqCfg(BSP_SYS_CTRL_PER_NBR_UART1, BSP_SYS_CTRL_CLK_DIV_4);
    BSP_SysCtrl_PerClkFreqCfg(BSP_SYS_CTRL_PER_NBR_UART2, BSP_SYS_CTRL_CLK_DIV_4);
    BSP_SysCtrl_PerClkFreqCfg(BSP_SYS_CTRL_PER_NBR_UART3, BSP_SYS_CTRL_CLK_DIV_4);    
                                                                /* - MEMORY ACCELERATION MODULE (MAM) CONFIGURATION - */
    BSP_REG_MAMCR  = BSP_REG_MAMCR_DISABLE;                     /* Disable  MAM                                       */
    BSP_REG_MAMTIM = BSP_REG_MAMTIM_CLK_3;                      /* Set 4 cycles to acces the Flash memory             */
    BSP_REG_MAMCR  = BSP_REG_MAMCR_PARTIAL;                     /* Enable FULL MAM                                    */    

    BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_USB);             /* (1) Enable USB Device clock                        */    
                                                                /* (2) Provide USB clock at 48 MHz. See Note #1       */                                                                
    BSP_SysCtrl_USB_FreqCfg(6);                                 /* USB Clock divider divides the PLL output to get... */
																/* the correct USB clock. 							  */
}

/*
*********************************************************************************************************
*                                             bsp_init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    BSP_CPU_Init();                                             /* Initialize the CPU's clocks                        */
    BSP_IntInit();                                              /* Initialize Interrupt controller                    */

#ifdef APP_CFG_VECT_FLASH_EN     
    BSP_SysCtrl_MemMapModeSet(BSP_SYS_CTRL_MEM_MAP_MODE_FLASH);
#endif
    
#ifdef APP_CFG_VECT_IRAM_EN      
    BSP_SysCtrl_MemMapModeSet(BSP_SYS_CTRL_MEM_MAP_MODE_IRAM);
#endif

	BSP_Uart_Init( BSP_UART_00,9600 );
    
}


/*
*********************************************************************************************************
*                                             BSP_SDRAM_Init()
*
* Description : Initialize external SDRAM..
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SDRAM_Init (void)
{
    INT32U  dummy;
    INT32U  i;

    BSP_REG_EMCCONTROL        = (1uL<<0);						/* Enable EMC                                         */
    BSP_REG_EMCDINAMICRDCFG   = (1uL<<0);
    BSP_REG_EMCDYNAMICRASCAS0 = (0x03uL<<0)|(0x03uL<<8);			/* RAS Latency=CAS Latency=0x3 : Three CCLK Cycles    */
   
    BSP_SysCtrl_PerClkEn(BSP_SYS_CTRL_PER_NBR_EMC);				/* Enable clock in the External Memory Controller EMC */

    BSP_GPIO_Cfg(BSP_GPIO_PORT2_FAST,
                 BSP_SDRAM_GPIO2_GRP,
                (BSP_GPIO_OPT_FNCT_2 | BSP_GPIO_OPT_MODE_NONE));
    
    BSP_GPIO_Cfg(BSP_GPIO_PORT3_FAST,
                 BSP_SDRAM_GPIO3_GRP,
                (BSP_GPIO_OPT_FNCT_2 | BSP_GPIO_OPT_MODE_NONE));
   
    BSP_GPIO_Cfg(BSP_GPIO_PORT4_FAST,
                 BSP_SDRAM_GPIO4_GRP,
                (BSP_GPIO_OPT_FNCT_2 | BSP_GPIO_OPT_MODE_NONE));

    BSP_REG_EMCDYNAMICRP      = 1;		                /* command period: 3(n+1) clock cycles                */
    BSP_REG_EMCDYNAMICRAS     = 2;	                    /* RAS command period: 4(n+1) clock cycles            */
    BSP_REG_EMCDYNAMICSREX    = 3;		                /* Self-refresh period: 8(n+1) clock cycles           */
    BSP_REG_EMCDYNAMICAPR     = 0;		                /* Data out to active: 3(n+1) clock cycles            */
    BSP_REG_EMCDYNAMICDAL     = 5;		                /* Data in to active: 5(n+1) clock cycles             */
    BSP_REG_EMCDYNAMICWR      = 2;		                /* Write recovery: 2(n+1) clock cycles                */
    BSP_REG_EMCDYNAMICRC      = 2;		                /* Active to Active cmd: 6(n+1) clock cycles          */
    BSP_REG_EMCDYNAMICRFC     = 2;		                /* Auto-refresh: 6(n+1) clock cycles                  */
    BSP_REG_EMCDYNAMICXSR     = 1;		                /* Exit self-refresh: 8(n+1) clock cycles             */
    BSP_REG_EMCDYNAMICRRD     = 0;		                /* Active bank A->B: 2(n+1) clock cycles              */
    BSP_REG_EMCDYNAMICMRD     = 2;		                /* Load Mode to Active cmd: 3(n+1) clock cycles       */
 
    BSP_REG_EMCDYNAMICCFG0    = 0x0000680;                      /* 13 row, 9 - col, SDRAM                             */
                                                                /* JEDEC General SDRAM Initialization Sequence        */
                                                                /* DELAY to allow power/clocks to stabilize ~100 us   */
                                                                /* NOP                                                */
    for (i=0u;i<100000u;i++) {
    }

    BSP_REG_EMCDINAMICCTRL    = 0x0183;
    BSP_REG_EMCDINAMICCTRL    = 0x00000103;                     /* Send command: PRECHARGE-ALL, shortest possible ... */
                                                                /* ... refresh period                                 */

    BSP_REG_EMCDINAMICRFR     = 0x00000004;                     /* set 32 CCLKs between SDRAM refresh cycles          */

    for (i=0u;i<100000u;i++) {
    }

    BSP_REG_EMCDINAMICRFR     = 23;                             /* set 28 x 16CCLKs=448CCLK=7us between SDRAM ...     */ 
                                                                /* ... refresh cycles                                 */

                                                                /* To set mode register in SDRAM, enter mode by ...   */
                                                                /* ... issue MODE command, after finishing, ...       */
                                                                /* ... bailout and back to NORMAL mode.  */

    BSP_REG_EMCDINAMICCTRL   = 0x00000083;                      /* Mem clock enable, CLKOUT runs, send command: MODE  */

                                                                /* Set mode register in SDRAM                         */
                                                                /* Mode regitster table for Micron's MT48LCxx         */
                                                                /* bit 9:   Programmed burst length(0)                */
                                                                /* ...bit 8~7: Normal mode(0)                         */
                                                                /* ...bit 6~4: CAS latency 3                          */
                                                                /* ...bit 3:   Sequential(0)                          */
                                                                /* ...bit 2~0: Burst length is 8                      */
                                                                /* ...row position is 12                              */

    dummy = *((volatile INT32U *)((INT32U)BSP_SDRAM_BASE_ADDR | (0x33 << 12)));
    dummy = dummy;    

    BSP_REG_EMCDINAMICCTRL   = 0x00000000;	                /* Send command: NORMAL                                          */
    BSP_REG_EMCDYNAMICCFG0  |= 0x00080000;	                /* Enable buffer                                                 */

    for (i=0u;i<100000u;i++) {
    }
}



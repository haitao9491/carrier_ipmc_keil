#ifndef  _BSP_SYS_CTRL_H_
#define  _BSP_SYS_CTRL_H_

#define  BSP_SYS_CTRL_OSC_MAIN_OSC_FREQ_HZ          20000000L
#define  BSP_SYS_CTRL_OSC_INT_RC_FREQ_HZ             4000000L
#define  BSP_SYS_CTRL_OSC_RTC_FREQ_HZ                   32768


                                                                /* ---------------- CPU PWR MODE DEFINES ------------ */
#define  BSP_SYS_CTRL_CPU_MODE_NORMAL                       0
#define  BSP_SYS_CTRL_CPU_MODE_PWR_DOWN                     1
#define  BSP_SYS_CTRL_CPU_MODE_IDLE                         2
#define  BSP_SYS_CTRL_CPU_MODE_SLEEP                        3

                                                                /* ---------------- MEMORY MAP DEFINES -------------- */
#define  BSP_SYS_CTRL_MEM_MAP_MODE_BOOT_LOADER              0
#define  BSP_SYS_CTRL_MEM_MAP_MODE_FLASH                    1
#define  BSP_SYS_CTRL_MEM_MAP_MODE_IRAM                     2
#define  BSP_SYS_CTRL_MEM_MAP_MODE_XRAM                     3

                                                                /* ------------- PERIPHEAL CLOCK DEFINES ------------ */
#define  BSP_SYS_CTRL_PER_NBR_WDT                           0   /* WatchDog Timer. This clock can not be turned off   */
#define  BSP_SYS_CTRL_PER_NBR_RESERVED0                     0

#define  BSP_SYS_CTRL_PER_NBR_TMR0                          1   /* Timer 0                                            */
#define  BSP_SYS_CTRL_PER_NBR_TMR1                          2   /* Timer 1                                            */
#define  BSP_SYS_CTRL_PER_NBR_UART0                         3   /* UART 0                                             */
#define  BSP_SYS_CTRL_PER_NBR_UART1                         4   /* UART 1                                             */

#define  BSP_SYS_CTRL_PER_NBR_PWM0                          5   /* PWM 0                                              */
#define  BSP_SYS_CTRL_PER_NBR_PWM1                          6   /* PWM1                                                */
#define  BSP_SYS_CTRL_PER_NBR_I2C0                          7   /* I2C 0                                               */
#define  BSP_SYS_CTRL_PER_NBR_SPI0                          8   /* SPI 0                                               */
#define  BSP_SYS_CTRL_PER_NBR_RTC                           9   /* RTC                                                 */
#define  BSP_SYS_CTRL_PER_NBR_SPI1                         10   /* SPI 1                                               */
#define  BSP_SYS_CTRL_PER_NBR_EMC                          11   /* External Memory Controller                          */
#define  BSP_SYS_CTRL_PER_NBR_AD0                          12   /* A/D converter                                       */
#define  BSP_SYS_CTRL_PER_NBR_CAN1                         13   /* CAN 1                                               */
#define  BSP_SYS_CTRL_PER_NBR_CAN2                         14   /* CAN 2                                               */

#define  BSP_SYS_CTRL_PER_NBR_ACF                          15   /* CAN filtering. This clock can not be turned off    */
#define  BSP_SYS_CTRL_PER_NBR_RESERVED1                    15

#define  BSP_SYS_CTRL_PER_NBR_BAT_RAM                      16   /* Battery Supported RAM. It can not be turned off    */
#define  BSP_SYS_CTRL_PER_NBR_RESERVED2                    16

#define  BSP_SYS_CTRL_PER_NBR_GPIO                         17   /* GPIOs. This clock can not be turned off            */
#define  BSP_SYS_CTRL_PER_NBR_RESERVED3                    17

#define  BSP_SYS_CTRL_PER_NBR_PCB                          18   /* Pin conn block. This clock can not be turned off   */
#define  BSP_SYS_CTRL_PER_NBR_RESERVED4                    18

#define  BSP_SYS_CTRL_PER_NBR_I2C1                         19   /* I2C1                                               */

#define  BSP_SYS_CTRL_PER_NBR_LCD                          20
#define  BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED0            20

#define  BSP_SYS_CTRL_PER_NBR_SSP0                         21   /* SSP0                                               */
#define  BSP_SYS_CTRL_PER_NBR_TMR2                         22   /* TIMER 2                                            */
#define  BSP_SYS_CTRL_PER_NBR_TMR3                         23   /* TIMER 3                                            */
#define  BSP_SYS_CTRL_PER_NBR_UART2                        24   /* UART 2                                             */
#define  BSP_SYS_CTRL_PER_NBR_UART3                        25   /* UART 3                                             */
#define  BSP_SYS_CTRL_PER_NBR_I2C2                         26   /* I2C 2                                              */

#define  BSP_SYS_CTRL_PER_NBR_I2S                          27   /* I2S                                                */

#define  BSP_SYS_CTRL_PER_NBR_SD                           28   /* SD card interface                                  */

#define  BSP_SYS_CTRL_PER_NBR_GPDMA                        29   /* GP DMA function                                    */
#define  BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED1            29

#define  BSP_SYS_CTRL_PER_NBR_ENET                         30   /* Ethernet Controller                                */
#define  BSP_SYS_CTRL_PER_NBR_SYSCON                       30

#define  BSP_SYS_CTRL_PER_NBR_USB                          31   /* USB                                                */
#define  BSP_SYS_CTRL_PER_NBR_PCLKSEL_RESERVED2            31

                                                                /* ---------------- CPU PWR MODE DEFINES ------------ */
#define  BSP_SYS_CTRL_PLL0_ID                               0
#define  BSP_SYS_CTRL_PLL1_ID                               1 

                                                                /* ------------- APB BUS DIVIDER DEFINES ------------ */
#define  BSP_SYS_CTRL_APB_DIV_1                             1
#define  BSP_SYS_CTRL_APB_DIV_2                             2
#define  BSP_SYS_CTRL_APB_DIV_4                             4

                                                                /* ------------- PLL CLOCK SOURCE DEFINES ----------- */
#define  BSP_SYSCTRL_PLL_CLK_SRC_INT_RC                     0
#define  BSP_SYSCTRL_PLL_CLK_SRC_MAIN                       1
#define  BSP_SYSCTRL_PLL_CLK_SRC_RTC                        2

                                                                /* ------------------ CLOCK DIVIDERS ---------------- */

#define  BSP_SYS_CTRL_CLK_DIV_1                             1
#define  BSP_SYS_CTRL_CLK_DIV_2                             2
#define  BSP_SYS_CTRL_CLK_DIV_4                             4
#define  BSP_SYS_CTRL_CLK_DIV_6                             6
#define  BSP_SYS_CTRL_CLK_DIV_8                             8


INT32U   BSP_SysCtrl_CPU_FreqGet         (void);
void     BSP_SysCtrl_CPU_FreqCfg         (INT8U  clk_div);

void    BSP_SysCtrl_CPU_ModeSet         (INT8U  cpu_mode);
INT8U   BSP_SysCtrl_CPU_ModeGet         (void);


void    BSP_SysCtrl_MemMapModeSet       (INT8U  mem_map_mode);
INT8U   BSP_SysCtrl_MemMapModeGet       (void);


BOOLEAN  BSP_SysCtrl_PerClkEn            (INT8U  per_nbr);
BOOLEAN  BSP_SysCtrl_PerClkDis           (INT8U  per_nbr);

BOOLEAN  BSP_SysCtrl_PerClkFreqCfg       (INT8U  per_nbr,
                                          INT8U  per_clk_div);
INT32U   BSP_SysCtrl_PerClkFreqGet       (INT8U  per_nbr);

BOOLEAN  BSP_SysCtrl_PLL_Cfg             (INT8U  pll_nbr,
                                          INT16U  pll_mul,
                                          INT8U  pll_div,
                                          INT8U  pll_clk_src);

INT32U   BSP_SysCtrl_PLL_FreqGet         (INT8U  pll_nbr);

BOOLEAN  BSP_SysCtrl_USB_FreqCfg         (INT8U  clk_div);


#endif


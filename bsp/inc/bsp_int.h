#ifndef  _BSP_INT_H_
#define  _BSP_INT_H_

#include "ucos_ii.h"

#define  BSP_INT_SRC_NBR_WDT                                0   /* Watchdog                                           */
#define  BSP_INT_SRC_NBR_SW                                 1   /* Software interrupts                                */
#define  BSP_INT_SRC_NBR_DBG_RX                             2   /* Embedded ICE, DbgCommRx                            */
#define  BSP_INT_SRC_NBR_DBG_TX                             3   /* Embedded ICE, DbgCommTx                            */
#define  BSP_INT_SRC_NBR_TMR0                               4   /* Timer 0 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR1                               5   /* Timer 1 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_UART0                              6   /* UART 0  (RLS, THRE, RDA, CTI)                      */
#define  BSP_INT_SRC_NBR_UART1                              7   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_PWM0                               8   /* PWM 0   (Match 0-6 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_PWM1                               8   /* PWM 1   (Match 0-6 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_I2C0                               9   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_SPI0                              10   /* SPI0    (SPIF, MODF)                               */
#define  BSP_INT_SRC_NBR_SPI1                              11   /* SPI1    (SPIF, MODF)                               */
#define  BSP_INT_SRC_NBR_PLL                               12   /* PLL lock (PLOCK)                                   */
#define  BSP_INT_SRC_NBR_RTC                               13   /* RTC     (RTCCIF, RTCALF)                           */
#define  BSP_INT_SRC_NBR_EINT0                             14   /* External interrupt 0 (EINT0)                       */
#define  BSP_INT_SRC_NBR_EINT1                             15   /* External interrupt 1 (EINT1)                       */
#define  BSP_INT_SRC_NBR_EINT2                             16   /* External interrupt 2 (EINT2)                       */
#define  BSP_INT_SRC_NBR_LCD                               16   /* LCD                                                */
#define  BSP_INT_SRC_NBR_EINT3                             17   /* External interrupt 3 (EINT3)                       */
#define  BSP_INT_SRC_NBR_ADC0                              18   /* A/D Converter 0 end of conversion                  */
#define  BSP_INT_SRC_NBR_I2C1                              19   /* SI (state change)                                  */
#define  BSP_INT_SRC_NBR_BOD                               20   /* Brown out detect                                   */
#define  BSP_INT_SRC_NBR_EMAC                              21   /* Ethernet Interrupt                                 */
#define  BSP_INT_SRC_NBR_USB                               22   /* USB Interrupts, DMA Interrupt                      */
#define  BSP_INT_SRC_NBR_CAN                               23   /* CAN Interrupt                                      */
#define  BSP_INT_SRC_NBR_SD_MMC                            24   /* SD card interrupt                                  */
#define  BSP_INT_SRC_NBR_GPDMA                             25   /* IntSattus of DMA channel 0/1                       */
#define  BSP_INT_SRC_NBR_TMR2                              26   /* Timer 0 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR3                              27   /* Timer 1 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_UART2                             28   /* UART 2  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_UART3                             29   /* UART 3  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_I2C2                              30   /* SI (state change)                                  */
#define  BSP_INT_SRC_NBR_I2S                               31   /* SI (state change)                                  */

#define  BSP_INT_SLOT_NBR_MAX                              32   /* Maximum number of IRQ slots                        */
#define  BSP_INT_SRC_NBR_MAX                               32   /* Maximum number of Interrupt source                 */ 

                                                                /* ------------ INTERRUPT PRIORITY DEFINES ---------- */
#define  BSP_INT_PRIO_HIGHEST                               0
#define  BSP_INT_PRIO_LOWEST                               15
                         
                                                                /* ---------------- INTERRUPT TYPE DEFINES ---------- */
#define  BSP_INT_SRC_TYPE_IRQ                               0
#define  BSP_INT_SRC_TYPE_FIQ                               1


BOOLEAN BSP_IntClr    ( INT8U int_src_nbr );
BOOLEAN BSP_IntDis    ( INT8U int_src_nbr );
void    BSP_IntDisAll ( void );
BOOLEAN BSP_IntEn     ( INT8U int_src_nbr );
void    BSP_IntInit   ( void );
void    BSP_IntSched  ( INT8U int_src_type );

BOOLEAN BSP_IntVectSet ( INT8U int_src_nbr,
                         INT8U int_src_prio,
						 INT8U int_src_type,
						 OS_FNCT_VOID int_isr_fnct );


#endif

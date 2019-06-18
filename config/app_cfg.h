
#ifndef __APP_CFG_H
#define __APP_CFG_H
/*configurations for ucos app */
/*********************************************************************************************************
   ∂®“Â∫Í
*********************************************************************************************************/

#define BTI_DRV_EN 1
#define BTI_SEM_EN 0
#define BTI_LOCK_EN 0

#define UART0_IRQ					0x06		/* UART0 IRQ NUM is 6 */
#define I2C0_IRQ					0x09		/* I2C0 IRQ NUM is 9 */
#define I2C1_IRQ					0x13		/* I2C1 IRQ NUM is 19 */
#define I2C2_IRQ					0x1E		/* I2C2 IRQ NUM is 30 */

#define I2C_EINT2_IRQ				0x10		/* MPCB PCA9665 extend I2c use EINT2 is 16*/
#define I2C_EINT1_IRQ				0x0f		/* MACB use PCA9665 EINT1 15*/
#define ADC_IRQ						0x12		/* ADC IRQ NUM is 18*/
#define BTI_IRQ						0x0f		/* use EINT1 NUM is 15	*/

#define I2C0_ISR_PRIORITY		4
#define I2C1_ISR_PRIORITY		5
#define I2C2_ISR_PRIORITY		6
#define EXI2C_ISR_PRIORITY		7
#define ADC_ISR_PRIORITY		8
#define BTI_TASK_IRQ_PRIORITY	9
#define UART0_ISR_PRIORITY		10

#define MPCB_TEMPERATURE_HIGH_THRESHOLD		85
#define MPCB_LOCAL_TEMP_HIGH_THRESHOLD		65
#define MACB_TEMPERATURE_HIGH_THRESHOLD		75
#define MPCB_TEMPERATURE_LOW_THRESHOLD		0
#define MACB_TEMPERATURE_LOW_THRESHOLD		0

#define IPMC_SOFTWARE_VERSION		"1.3.2"

extern void UART0_Printf(char *fmt,...);
extern void UART0_SendStr (char *str);

#define I2CMBOX
//#define I2CPOLLEND
//#define	MPCB_V2_0_0
//#define DEBUG
//#define DEBUG1
#define INFO_COLLECT
//#define TESTI2C
//#define MPCB_USE



#define SELF_DEBUG
#ifdef SELF_DEBUG
#define DEBUG(fmt, ...)     UART0_Printf(fmt,__VA_ARGS__)
#define DEBUGSTR(string)    UART0_SendStr(string)
#else
#define DEBUG(fmt, args...)     do { }while(0);
#define DEBUGSTR(char string)  do { }while(0);
#endif
#endif

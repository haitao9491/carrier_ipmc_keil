/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           LPC2400.h
** Last modified Date:  2007-01-09
** Last Version:        1.0
** Descriptions:        header file of LPC2400, user may modify it as needed
**--------------------------------------------------------------------------------------------------------
** Created by:          Chenmingji
** Created date:        2004-02-02
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:            
** Descriptions: 
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#ifndef     __LPC24XX_H_
#define     __LPC24XX_H_

#define     VIC_BASE_ADDR	        0xFFFFF000

#define     VICIRQStatus            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x000))
#define     VICFIQStatus            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x004))
#define     VICRawIntr              (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x008))
#define     VICIntSelect            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x00C))
#define     VICIntEnable            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x010))
#define     VICIntEnClr             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x014))
#define     VICSoftInt              (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x018))
#define     VICSoftIntClr           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x01C))
#define     VICProtection           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x020))
#define     VICSWPrioMask           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x024))

#define     VICVectAddr0            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x100))
#define     VICVectAddr1            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x104))
#define     VICVectAddr2            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x108))
#define     VICVectAddr3            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x10C))
#define     VICVectAddr4            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x110))
#define     VICVectAddr5            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x114))
#define     VICVectAddr6            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x118))
#define     VICVectAddr7            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x11C))
#define     VICVectAddr8            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x120))
#define     VICVectAddr9            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x124))
#define     VICVectAddr10           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x128))
#define     VICVectAddr11           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x12C))
#define     VICVectAddr12           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x130))
#define     VICVectAddr13           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x134))
#define     VICVectAddr14           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x138))
#define     VICVectAddr15           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x13C))
#define     VICVectAddr16           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x140))
#define     VICVectAddr17           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x144))
#define     VICVectAddr18           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x148))
#define     VICVectAddr19           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x14C))
#define     VICVectAddr20           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x150))
#define     VICVectAddr21           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x154))
#define     VICVectAddr22           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x158))
#define     VICVectAddr23           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x15C))
#define     VICVectAddr24           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x160))
#define     VICVectAddr25           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x164))
#define     VICVectAddr26           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x168))
#define     VICVectAddr27           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x16C))
#define     VICVectAddr28           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x170))
#define     VICVectAddr29           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x174))
#define     VICVectAddr30           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x178))
#define     VICVectAddr31           (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x17C))

/*********************************************************************************************************
  The name convention below is from previous LPC2000 family MCUs, in LPC230x,
  these registers are known as "VICVectPriority(x)".
*********************************************************************************************************/

#define     VICVectPri0             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x200))
#define     VICVectPri1             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x204))
#define     VICVectPri2             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x208))
#define     VICVectPri3             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x20C))
#define     VICVectPri4             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x210))
#define     VICVectPri5             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x214))
#define     VICVectPri6             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x218))
#define     VICVectPri7             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x21C))
#define     VICVectPri8             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x220))
#define     VICVectPri9             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x224))
#define     VICVectPri10            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x228))
#define     VICVectPri11            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x22C))
#define     VICVectPri12            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x230))
#define     VICVectPri13            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x234))
#define     VICVectPri14            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x238))
#define     VICVectPri15            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x23C))
#define     VICVectPri16            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x240))
#define     VICVectPri17            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x244))
#define     VICVectPri18            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x248))
#define     VICVectPri19            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x24C))
#define     VICVectPri20            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x250))
#define     VICVectPri21            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x254))
#define     VICVectPri22            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x258))
#define     VICVectPri23            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x25C))
#define     VICVectPri24            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x260))
#define     VICVectPri25            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x264))
#define     VICVectPri26            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x268))
#define     VICVectPri27            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x26C))
#define     VICVectPri28            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x270))
#define     VICVectPri29            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x274))
#define     VICVectPri30            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x278))
#define     VICVectPri31            (*(volatile unsigned long *)(VIC_BASE_ADDR + 0x27C))

#define     VICVectAddr             (*(volatile unsigned long *)(VIC_BASE_ADDR + 0xF00))

/*********************************************************************************************************
  Pin Connect Block
*********************************************************************************************************/

#define     PINSEL_BASE_ADDR	    0xE002C000

#define     PINSEL0                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x00))
#define     PINSEL1                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x04))
#define     PINSEL2                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x08))
#define     PINSEL3                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x0C))
#define     PINSEL4                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x10))
#define     PINSEL5                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x14))
#define     PINSEL6                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x18))
#define     PINSEL7                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x1C))
#define     PINSEL8                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x20))
#define     PINSEL9                 (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x24))
#define     PINSEL10                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x28))

#define     PINMODE0                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x40))            
#define     PINMODE1                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x44))
#define     PINMODE2                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x48))            
#define     PINMODE3                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x4C))
#define     PINMODE4                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x50))
#define     PINMODE5                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x54))
#define     PINMODE6                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x58))
#define     PINMODE7                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x5C))
#define     PINMODE8                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x60))
#define     PINMODE9                (*(volatile unsigned long *)(PINSEL_BASE_ADDR + 0x64))

/*********************************************************************************************************
  General Purpose Input/Output (GPIO)
*********************************************************************************************************/

#define     GPIO_BASE_ADDR		    0xE0028000

#define     IO0PIN                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x00))
#define     IO0SET                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x04))
#define     IO0DIR                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x08))
#define     IO0CLR                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x0C))
#define     IO1PIN                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x10))
#define     IO1SET                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x14))
#define     IO1DIR                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x18))
#define     IO1CLR                  (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x1C))
/*********************************************************************************************************
  GPIO Interrupt Registers
*********************************************************************************************************/

#define     IO0IntEnR               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x90)) 
#define     IO0IntEnF               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x94))
#define     IO0IntStatR             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x84))
#define     IO0IntStatF             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x88))
#define     IO0IntClr               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x8C))

#define     IO2IntEnR               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0xB0)) 
#define     IO2IntEnF               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0xB4))
#define     IO2IntStatR             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0xA4))
#define     IO2IntStatF             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0xA8))
#define     IO2IntClr               (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0xAC))

#define     IO_INT_STAT             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x80))
#define     IOIntStatus             (*(volatile unsigned long *)(GPIO_BASE_ADDR + 0x80))

#define     PARTCFG_BASE_ADDR	    0x3FFF8000
#define     PARTCFG                 (*(volatile unsigned long *)(PARTCFG_BASE_ADDR + 0x00)) 
/*********************************************************************************************************
  Fast I/O setup
*********************************************************************************************************/

#define     FIO_BASE_ADDR		    0x3FFFC000

#define     FIO0DIR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x00)) 
#define     FIO0MASK                (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x10))
#define     FIO0PIN                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x14))
#define     FIO0SET                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x18))
#define     FIO0CLR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x1C))

#define     FIO1DIR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x20)) 
#define     FIO1MASK                (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x30))
#define     FIO1PIN                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x34))
#define     FIO1SET                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x38))
#define     FIO1CLR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x3C))

#define     FIO2DIR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x40)) 
#define     FIO2MASK                (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x50))
#define     FIO2PIN                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x54))
#define     FIO2SET                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x58))
#define     FIO2CLR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x5C))

#define     FIO3DIR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x60)) 
#define     FIO3MASK                (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x70))
#define     FIO3PIN                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x74))
#define     FIO3SET                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x78))
#define     FIO3CLR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x7C))

#define     FIO4DIR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x80)) 
#define     FIO4MASK                (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x90))
#define     FIO4PIN                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x94))
#define     FIO4SET                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x98))
#define     FIO4CLR                 (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x9C))
/*********************************************************************************************************
  FIOs can be accessed through WORD, HALF-WORD or BYTE
*********************************************************************************************************/

#define     FIO0DIR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x00)) 
#define     FIO1DIR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x20)) 
#define     FIO2DIR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x40)) 
#define     FIO3DIR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x60)) 
#define     FIO4DIR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x80)) 

#define     FIO0DIR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x01)) 
#define     FIO1DIR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x21)) 
#define     FIO2DIR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x41)) 
#define     FIO3DIR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x61)) 
#define     FIO4DIR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x81)) 

#define     FIO0DIR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x02)) 
#define     FIO1DIR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x22)) 
#define     FIO2DIR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x42)) 
#define     FIO3DIR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x62)) 
#define     FIO4DIR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x82)) 

#define     FIO0DIR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x03)) 
#define     FIO1DIR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x23)) 
#define     FIO2DIR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x43)) 
#define     FIO3DIR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x63)) 
#define     FIO4DIR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x83)) 

#define     FIO0DIRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x00)) 
#define     FIO1DIRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x20)) 
#define     FIO2DIRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x40)) 
#define     FIO3DIRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x60)) 
#define     FIO4DIRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x80)) 

#define     FIO0DIRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x02)) 
#define     FIO1DIRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x22)) 
#define     FIO2DIRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x42)) 
#define     FIO3DIRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x62)) 
#define     FIO4DIRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x82)) 

#define     FIO0MASK0               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x10)) 
#define     FIO1MASK0               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x30)) 
#define     FIO2MASK0               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x50)) 
#define     FIO3MASK0               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x70)) 
#define     FIO4MASK0               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x90)) 

#define     FIO0MASK1               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x11)) 
#define     FIO1MASK1               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x31)) 
#define     FIO2MASK1               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x51)) 
#define     FIO3MASK1               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x71)) 
#define     FIO4MASK1               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x91)) 

#define     FIO0MASK2               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x12)) 
#define     FIO1MASK2               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x32)) 
#define     FIO2MASK2               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x52)) 
#define     FIO3MASK2               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x72)) 
#define     FIO4MASK2               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x92)) 

#define     FIO0MASK3               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x13)) 
#define     FIO1MASK3               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x33)) 
#define     FIO2MASK3               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x53)) 
#define     FIO3MASK3               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x73)) 
#define     FIO4MASK3               (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x93)) 

#define     FIO0MASKL               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x10)) 
#define     FIO1MASKL               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x30)) 
#define     FIO2MASKL               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x50)) 
#define     FIO3MASKL               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x70)) 
#define     FIO4MASKL               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x90)) 

#define     FIO0MASKU               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x12)) 
#define     FIO1MASKU               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x32)) 
#define     FIO2MASKU               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x52)) 
#define     FIO3MASKU               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x72)) 
#define     FIO4MASKU               (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x92)) 

#define     FIO0PIN0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x14)) 
#define     FIO1PIN0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x34)) 
#define     FIO2PIN0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x54)) 
#define     FIO3PIN0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x74)) 
#define     FIO4PIN0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x94)) 

#define     FIO0PIN1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x15)) 
#define     FIO1PIN1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x35)) 
#define     FIO2PIN1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x55)) 
#define     FIO3PIN1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x75)) 
#define     FIO4PIN1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x95)) 

#define     FIO0PIN2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x16)) 
#define     FIO1PIN2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x36)) 
#define     FIO2PIN2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x56)) 
#define     FIO3PIN2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x76)) 
#define     FIO4PIN2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x96)) 

#define     FIO0PIN3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x17)) 
#define     FIO1PIN3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x37)) 
#define     FIO2PIN3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x57)) 
#define     FIO3PIN3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x77)) 
#define     FIO4PIN3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x97)) 

#define     FIO0PINL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x14)) 
#define     FIO1PINL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x34)) 
#define     FIO2PINL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x54)) 
#define     FIO3PINL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x74)) 
#define     FIO4PINL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x94)) 

#define     FIO0PINU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x16)) 
#define     FIO1PINU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x36)) 
#define     FIO2PINU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x56)) 
#define     FIO3PINU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x76)) 
#define     FIO4PINU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x96)) 

#define     FIO0SET0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x18)) 
#define     FIO1SET0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x38)) 
#define     FIO2SET0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x58)) 
#define     FIO3SET0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x78)) 
#define     FIO4SET0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x98)) 

#define     FIO0SET1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x19)) 
#define     FIO1SET1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x39)) 
#define     FIO2SET1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x59)) 
#define     FIO3SET1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x79)) 
#define     FIO4SET1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x99)) 

#define     FIO0SET2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1A)) 
#define     FIO1SET2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3A)) 
#define     FIO2SET2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5A)) 
#define     FIO3SET2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7A)) 
#define     FIO4SET2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9A)) 

#define     FIO0SET3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1B)) 
#define     FIO1SET3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3B)) 
#define     FIO2SET3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5B)) 
#define     FIO3SET3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7B)) 
#define     FIO4SET3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9B)) 

#define     FIO0SETL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x18)) 
#define     FIO1SETL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x38)) 
#define     FIO2SETL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x58)) 
#define     FIO3SETL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x78)) 
#define     FIO4SETL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x98)) 

#define     FIO0SETU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x1A)) 
#define     FIO1SETU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x3A)) 
#define     FIO2SETU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x5A)) 
#define     FIO3SETU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x7A)) 
#define     FIO4SETU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x9A)) 

#define     FIO0CLR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1C)) 
#define     FIO1CLR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3C)) 
#define     FIO2CLR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5C)) 
#define     FIO3CLR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7C)) 
#define     FIO4CLR0                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9C)) 

#define     FIO0CLR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1D)) 
#define     FIO1CLR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3D)) 
#define     FIO2CLR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5D)) 
#define     FIO3CLR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7D)) 
#define     FIO4CLR1                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9D)) 

#define     FIO0CLR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1E)) 
#define     FIO1CLR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3E)) 
#define     FIO2CLR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5E)) 
#define     FIO3CLR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7E)) 
#define     FIO4CLR2                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9E)) 

#define     FIO0CLR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x1F)) 
#define     FIO1CLR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x3F)) 
#define     FIO2CLR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x5F)) 
#define     FIO3CLR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x7F)) 
#define     FIO4CLR3                (*(volatile unsigned char *)(FIO_BASE_ADDR + 0x9F)) 

#define     FIO0CLRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x1C)) 
#define     FIO1CLRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x3C)) 
#define     FIO2CLRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x5C)) 
#define     FIO3CLRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x7C)) 
#define     FIO4CLRL                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x9C)) 

#define     FIO0CLRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x1E)) 
#define     FIO1CLRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x3E)) 
#define     FIO2CLRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x5E)) 
#define     FIO3CLRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x7E)) 
#define     FIO4CLRU                (*(volatile unsigned short *)(FIO_BASE_ADDR + 0x9E)) 

/*********************************************************************************************************
   System Control Block(SCB) modules include Memory Accelerator Module,
   Phase Locked Loop, VPB divider, Power Control, External Interrupt, 
   Reset, and Code Security/Debugging 
*********************************************************************************************************/

#define     SCB_BASE_ADDR	        0xE01FC000
/*********************************************************************************************************
  Memory Accelerator Module 
*********************************************************************************************************/

#define     MAMCR                   (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x000))
#define     MAMTIM                  (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x004))
#define     MEMMAP                  (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x040))

/*********************************************************************************************************
  Phase Locked Loop (PLL)
*********************************************************************************************************/

#define     PLLCON                  (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x080))
#define     PLLCFG                  (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x084))
#define     PLLSTAT                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x088))
#define     PLLFEED                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x08C))

/*********************************************************************************************************
  Power Control
*********************************************************************************************************/

#define     PCON                    (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x0C0))
#define     PCONP                   (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x0C4))

/*********************************************************************************************************
  Clock Divider
*********************************************************************************************************/

#define     CCLKCFG                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x104))
#define     USBCLKCFG               (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x108))
#define     CLKSRCSEL               (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x10C))
#define     PCLKSEL0                (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x1A8))
#define     PCLKSEL1                (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x1AC))

/*********************************************************************************************************
  External Interrupts
*********************************************************************************************************/
	
#define     EXTINT                  (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x140))
#define     INTWAKE                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x144))
#define     EXTMODE                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x148))
#define     EXTPOLAR                (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x14C))
/*********************************************************************************************************
  Reset, reset source identification
*********************************************************************************************************/

#define     RSIR                    (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x180))
/*********************************************************************************************************
  RSID, code security protection
*********************************************************************************************************/

#define     CSPR                    (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x184))

#define     AHBCFG1                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x188))
#define     AHBCFG2                 (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x18C))

#define     SCS                     (*(volatile unsigned long *)(SCB_BASE_ADDR + 0x1A0))	

#define     EMC_BASE_ADDR		    0xFFE08000
#define     EMCControl			    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x000))
#define     EMCStatus			    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x004))
#define     EMCConfig			    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x008))

#define     EMCDynamicControl	    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x020))
#define     EMCDynamicRefresh	    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x024))
#define     EMCDynamicReadConfig    (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x028))
#define     EMCDynamictRP    		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x030))
#define     EMCDynamictRAS  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x034))
#define     EMCDynamictSREX 		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x038))
#define     EMCDynamictAPR   		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x03C))
#define     EMCDynamictDAL  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x040))
#define     EMCDynamictWR   		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x044))
#define     EMCDynamictRC   		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x048))
#define     EMCDynamictRFC  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x04C))
#define     EMCDynamictXSR  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x050))
#define     EMCDynamictRRD  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x054))
#define     EMCDynamictMRD  		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x058))

#define     EMCDynamicConfig0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x100))
#define     EMCDynamicContro1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x120))
#define     EMCDynamicContro2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x140))
#define     EMCDynamicContro3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x160))

#define     EMCDynamicRASCAS0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x104))
#define     EMCDynamicRASCAS1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x124))
#define     EMCDynamicRASCAS2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x144))
#define     EMCDynamicRASCAS3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x164))

#define     EMCStaticConfig0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x200))
#define     EMCStaticWaitWen0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x204))
#define     EMCStaticWaitOen0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x208))
#define     EMCStaticWaitRd0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x20C))
#define     EMCStaticWaitPage0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x210))
#define     EMCStaticWaitWr0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x214))
#define     EMCStaticWaitTurn0		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x218))

#define     EMCStaticConfig1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x220))
#define     EMCStaticWaitWen1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x224))
#define     EMCStaticWaitOen1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x228))
#define     EMCStaticWaitRd1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x22C))
#define     EMCStaticWaitPage1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x230))
#define     EMCStaticWaitWr1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x234))
#define     EMCStaticWaitTurn1		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x238))

#define     EMCStaticConfig2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x240))
#define     EMCStaticWaitWen2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x244))
#define     EMCStaticWaitOen2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x248))
#define     EMCStaticWaitRd2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x24C))
#define     EMCStaticWaitPage2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x250))
#define     EMCStaticWaitWr2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x254))
#define     EMCStaticWaitTurn2		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x258))

#define     EMCStaticConfig3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x260))
#define     EMCStaticWaitWen3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x264))
#define     EMCStaticWaitOen3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x268))
#define     EMCStaticWaitRd3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x26C))
#define     EMCStaticWaitPage3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x270))
#define     EMCStaticWaitWr3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x274))
#define     EMCStaticWaitTurn3		(*(volatile unsigned long *)(EMC_BASE_ADDR + 0x278))

#define     EMCStaticExtendedWait   (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x880))	

#define     TMR0_BASE_ADDR		    0xE0004000

#define     T0IR                    (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x00))
#define     T0TCR                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x04))
#define     T0TC                    (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x08))
#define     T0PR                    (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x0C))
#define     T0PC                    (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x10))
#define     T0MCR                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x14))
#define     T0MR0                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x18))
#define     T0MR1                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x1C))
#define     T0MR2                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x20))
#define     T0MR3                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x24))
#define     T0CCR                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x28))
#define     T0CR0                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x2C))
#define     T0CR1                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x30))
#define     T0CR2                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x34))
#define     T0CR3                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x38))
#define     T0EMR                   (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x3C))
#define     T0CTCR                  (*(volatile unsigned long *)(TMR0_BASE_ADDR + 0x70))

#define     TMR1_BASE_ADDR		    0xE0008000

#define     T1IR                    (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x00))
#define     T1TCR                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x04))
#define     T1TC                    (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x08))
#define     T1PR                    (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x0C))
#define     T1PC                    (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x10))
#define     T1MCR                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x14))
#define     T1MR0                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x18))
#define     T1MR1                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x1C))
#define     T1MR2                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x20))
#define     T1MR3                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x24))
#define     T1CCR                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x28))
#define     T1CR0                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x2C))
#define     T1CR1                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x30))
#define     T1CR2                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x34))
#define     T1CR3                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x38))
#define     T1EMR                   (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x3C))
#define     T1CTCR                  (*(volatile unsigned long *)(TMR1_BASE_ADDR + 0x70))

#define     TMR2_BASE_ADDR		    0xE0070000

#define     T2IR                    (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x00))
#define     T2TCR                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x04))
#define     T2TC                    (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x08))
#define     T2PR                    (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x0C))
#define     T2PC                    (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x10))
#define     T2MCR                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x14))
#define     T2MR0                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x18))
#define     T2MR1                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x1C))
#define     T2MR2                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x20))
#define     T2MR3                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x24))
#define     T2CCR                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x28))
#define     T2CR0                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x2C))
#define     T2CR1                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x30))
#define     T2CR2                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x34))
#define     T2CR3                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x38))
#define     T2EMR                   (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x3C))
#define     T2CTCR                  (*(volatile unsigned long *)(TMR2_BASE_ADDR + 0x70))

#define     TMR3_BASE_ADDR		    0xE0074000

#define     T3IR                    (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x00))
#define     T3TCR                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x04))
#define     T3TC                    (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x08))
#define     T3PR                    (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x0C))
#define     T3PC                    (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x10))
#define     T3MCR                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x14))
#define     T3MR0                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x18))
#define     T3MR1                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x1C))
#define     T3MR2                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x20))
#define     T3MR3                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x24))
#define     T3CCR                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x28))
#define     T3CR0                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x2C))
#define     T3CR1                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x30))
#define     T3CR2                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x34))
#define     T3CR3                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x38))
#define     T3EMR                   (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x3C))
#define     T3CTCR                  (*(volatile unsigned long *)(TMR3_BASE_ADDR + 0x70))


/*
#define     PWM0_BASE_ADDR		    0xE0014000
#define     PWM0IR                  (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x00))
#define     PWM0TCR                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x04))
#define     PWM0TC                  (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x08))
#define     PWM0PR                  (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x0C))
#define     PWM0PC                  (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x10))
#define     PWM0MCR                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x14))
#define     PWM0MR0                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x18))
#define     PWM0MR1                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x1C))
#define     PWM0MR2                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x20))
#define     PWM0MR3                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x24))
#define     PWM0CCR                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x28))
#define     PWM0CR0                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x2C))
#define     PWM0CR1                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x30))
#define     PWM0CR2                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x34))
#define     PWM0CR3                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x38))
#define     PWM0EMR                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x3C))
#define     PWM0MR4                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x40))
#define     PWM0MR5                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x44))
#define     PWM0MR6                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x48))
#define     PWM0PCR                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x4C))
#define     PWM0LER                 (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x50))
#define     PWM0CTCR                (*(volatile unsigned long *)(PWM0_BASE_ADDR + 0x70))
*/
#define     PWM1_BASE_ADDR		    0xE0018000

#define     PWM1IR                  (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x00))
#define     PWM1TCR                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x04))
#define     PWM1TC                  (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x08))
#define     PWM1PR                  (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x0C))
#define     PWM1PC                  (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x10))
#define     PWM1MCR                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x14))
#define     PWM1MR0                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x18))
#define     PWM1MR1                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x1C))
#define     PWM1MR2                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x20))
#define     PWM1MR3                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x24))
#define     PWM1CCR                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x28))
#define     PWM1CR0                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x2C))
#define     PWM1CR1                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x30))
#define     PWM1CR2                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x34))
#define     PWM1CR3                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x38))
#define     PWM1EMR                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x3C))
#define     PWM1MR4                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x40))
#define     PWM1MR5                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x44))
#define     PWM1MR6                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x48))
#define     PWM1PCR                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x4C))
#define     PWM1LER                 (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x50))
#define     PWM1CTCR                (*(volatile unsigned long *)(PWM1_BASE_ADDR + 0x70))

#define     UART0_BASE_ADDR		    0xE000C000

#define     U0RBR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x00))
#define     U0THR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x00))
#define     U0DLL                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x00))
#define     U0DLM                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x04))
#define     U0IER                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x04))
#define     U0IIR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x08))
#define     U0FCR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x08))
#define     U0LCR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x0C))

#define     U0LSR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x14))
#define     U0SCR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x1C))
#define     U0ACR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x20))

#define     U0FDR                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x28))
#define     U0TER                   (*(volatile unsigned long *)(UART0_BASE_ADDR + 0x30))

#define     UART1_BASE_ADDR		    0xE0010000

#define     U1RBR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x00))
#define     U1THR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x00))
#define     U1DLL                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x00))
#define     U1DLM                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x04))
#define     U1IER                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x04))
#define     U1IIR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x08))
#define     U1FCR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x08))
#define     U1LCR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x0C))
#define     U1MCR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x10))
#define     U1LSR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x14))
#define     U1MSR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x18))
#define     U1SCR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x1C))
#define     U1ACR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x20))

#define     U1FDR                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x28))
#define     U1TER                   (*(volatile unsigned long *)(UART1_BASE_ADDR + 0x30))

#define     UART2_BASE_ADDR		    0xE0078000

#define     U2RBR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x00))
#define     U2THR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x00))
#define     U2DLL                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x00))
#define     U2DLM                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x04))
#define     U2IER                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x04))
#define     U2IIR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x08))
#define     U2FCR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x08))
#define     U2LCR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x0C))

#define     U2LSR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x14))
#define     U2SCR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x1C))
#define     U2ACR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x20))

#define     U2FDR                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x28))
#define     U2TER                   (*(volatile unsigned long *)(UART2_BASE_ADDR + 0x30))

#define     UART3_BASE_ADDR		    0xE007C000

#define     U3RBR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x00))
#define     U3THR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x00))
#define     U3DLL                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x00))
#define     U3DLM                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x04))
#define     U3IER                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x04))
#define     U3IIR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x08))
#define     U3FCR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x08))
#define     U3LCR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x0C))

#define     U3LSR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x14))
#define     U3SCR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x1C))
#define     U3ACR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x20))
#define     U3ICR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x24))
#define     U3FDR                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x28))
#define     U3TER                   (*(volatile unsigned long *)(UART3_BASE_ADDR + 0x30))

#define     I2C_BASE_ADDR		    0xE001C000

#define     I2CONSET                (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x00))
#define     I2STAT                  (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x04))
#define     I2DAT                   (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x08))
#define     I2ADR                   (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x0C))
#define     I2SCLH                  (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x10))
#define     I2SCLL                  (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x14))
#define     I2CONCLR                (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x18))

#define     I2C0_BASE_ADDR		    0xE001C000

#define     I20CONSET               (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x00))
#define     I20STAT                 (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x04))
#define     I20DAT                  (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x08))
#define     I20ADR                  (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x0C))
#define     I20SCLH                 (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x10))
#define     I20SCLL                 (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x14))
#define     I20CONCLR               (*(volatile unsigned long *)(I2C0_BASE_ADDR + 0x18))

#define     I2C1_BASE_ADDR		    0xE005C000

#define     I21CONSET               (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x00))
#define     I21STAT                 (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x04))
#define     I21DAT                  (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x08))
#define     I21ADR                  (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x0C))
#define     I21SCLH                 (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x10))
#define     I21SCLL                 (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x14))
#define     I21CONCLR               (*(volatile unsigned long *)(I2C1_BASE_ADDR + 0x18))

#define     I2C2_BASE_ADDR		    0xE0080000

#define     I22CONSET               (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x00))
#define     I22STAT                 (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x04))
#define     I22DAT                  (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x08))
#define     I22ADR                  (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x0C))
#define     I22SCLH                 (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x10))
#define     I22SCLL                 (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x14))
#define     I22CONCLR               (*(volatile unsigned long *)(I2C2_BASE_ADDR + 0x18))

#define     SPI0_BASE_ADDR		    0xE0020000

#define     S0SPCR                  (*(volatile unsigned long *)(SPI0_BASE_ADDR + 0x00))
#define     S0SPSR                  (*(volatile unsigned long *)(SPI0_BASE_ADDR + 0x04))
#define     S0SPDR                  (*(volatile unsigned long *)(SPI0_BASE_ADDR + 0x08))
#define     S0SPCCR                 (*(volatile unsigned long *)(SPI0_BASE_ADDR + 0x0C))
#define     S0SPINT                 (*(volatile unsigned long *)(SPI0_BASE_ADDR + 0x1C))

#define     SSP0_BASE_ADDR		    0xE0068000

#define     SSP0CR0                 (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x00))
#define     SSP0CR1                 (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x04))
#define     SSP0DR                  (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x08))
#define     SSP0SR                  (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x0C))
#define     SSP0CPSR                (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x10))
#define     SSP0IMSC                (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x14))
#define     SSP0RIS                 (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x18))
#define     SSP0MIS                 (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x1C))
#define     SSP0ICR                 (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x20))
#define     SSP0DMACR               (*(volatile unsigned long *)(SSP0_BASE_ADDR + 0x24))

#define     SSP1_BASE_ADDR		    0xE0030000

#define     SSP1CR0                 (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x00))
#define     SSP1CR1                 (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x04))
#define     SSP1DR                  (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x08))
#define     SSP1SR                  (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x0C))
#define     SSP1CPSR                (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x10))
#define     SSP1IMSC                (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x14))
#define     SSP1RIS                 (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x18))
#define     SSP1MIS                 (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x1C))
#define     SSP1ICR                 (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x20))
#define     SSP1DMACR               (*(volatile unsigned long *)(SSP1_BASE_ADDR + 0x24))

#define     RTC_BASE_ADDR		    0xE0024000

#define     ILR                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x00))
#define     CTC                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x04))
#define     CCR                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x08))
#define     CIIR                    (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x0C))
#define     AMR                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x10))
#define     CTIME0                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x14))
#define     CTIME1                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x18))
#define     CTIME2                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x1C))
#define     SEC                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x20))
#define     MIN                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x24))
#define     HOUR                    (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x28))
#define     DOM                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x2C))
#define     DOW                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x30))
#define     DOY                     (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x34))
#define     MONTH                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x38))
#define     YEAR                    (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x3C))
#define     CISS                    (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x40))
#define     ALSEC                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x60))
#define     ALMIN                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x64))
#define     ALHOUR                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x68))
#define     ALDOM                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x6C))
#define     ALDOW                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x70))
#define     ALDOY                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x74))
#define     ALMON                   (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x78))
#define     ALYEAR                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x7C))
#define     PREINT                  (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x80))
#define     PREFRAC                 (*(volatile unsigned long *)(RTC_BASE_ADDR + 0x84))

#define     AD0_BASE_ADDR		    0xE0034000

#define     AD0CR                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x00))
#define     AD0GDR                  (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x04))
#define     AD0INTEN                (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x0C))
#define		ADDR(n)					(*(volatile unsigned long *)(AD0_BASE_ADDR + 0x10 + 4 * (n)))
#define     ADDR0                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x10))
#define     ADDR1                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x14))
#define     ADDR2                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x18))
#define     ADDR3                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x1C))
#define     ADDR4                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x20))
#define     ADDR5                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x24))
#define     ADDR6                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x28))
#define     ADDR7                   (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x2C))
#define     AD0STAT                 (*(volatile unsigned long *)(AD0_BASE_ADDR + 0x30))

#define     DAC_BASE_ADDR		    0xE006C000

#define     DACR                    (*(volatile unsigned long *)(DAC_BASE_ADDR + 0x00))

#define     WDG_BASE_ADDR		    0xE0000000

#define     WDMOD                   (*(volatile unsigned long *)(WDG_BASE_ADDR + 0x00))
#define     WDTC                    (*(volatile unsigned long *)(WDG_BASE_ADDR + 0x04))
#define     WDFEED                  (*(volatile unsigned long *)(WDG_BASE_ADDR + 0x08))
#define     WDTV                    (*(volatile unsigned long *)(WDG_BASE_ADDR + 0x0C))
#define     WDCLKSEL                (*(volatile unsigned long *)(WDG_BASE_ADDR + 0x10))

#define     CAN_ACCEPT_BASE_ADDR	0xE003C000

#define     CAN_AFMR 			    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x00))  	
#define     CAN_SFF_SA 			    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x04))  	
#define     CAN_SFF_GRP_SA 		    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x08))
#define     CAN_EFF_SA 			    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x0C))
#define     CAN_EFF_GRP_SA 		    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x10))  	
#define     CAN_EOT 			    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x14))
#define     CAN_LUT_ERR_ADR		    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x18))  	
#define     CAN_LUT_ERR 		    (*(volatile unsigned long *)(CAN_ACCEPT_BASE_ADDR + 0x1C))

#define     CAN_CENTRAL_BASE_ADDR	0xE0040000  
    	
#define     CAN_TX_SR 			    (*(volatile unsigned long *)(CAN_CENTRAL_BASE_ADDR + 0x00))  	
#define     CAN_RX_SR 			    (*(volatile unsigned long *)(CAN_CENTRAL_BASE_ADDR + 0x04))  	
#define     CAN_MSR 			    (*(volatile unsigned long *)(CAN_CENTRAL_BASE_ADDR + 0x08))

#define     CAN1_BASE_ADDR		    0xE0044000

#define     CAN1MOD 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x00))  	
#define     CAN1CMR 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x04))  	
#define     CAN1GSR         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x08))  	
#define     CAN1ICR 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x0C))  	
#define     CAN1IER 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x10))
#define     CAN1BTR 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x14))  	
#define     CAN1EWL 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x18))  	
#define     CAN1SR 		            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x1C))  	
#define     CAN1RFS 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x20))  	
#define     CAN1RID 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x24))
#define     CAN1RDA         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x28))  	
#define     CAN1RDB         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x2C))
  	
#define     CAN1TFI1         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x30))  	
#define     CAN1TID1         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x34))  	
#define     CAN1TDA1         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x38))
#define     CAN1TDB1         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x3C))  	
#define     CAN1TFI2         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x40))  	
#define     CAN1TID2 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x44))  	
#define     CAN1TDA2 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x48))  	
#define     CAN1TDB2 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x4C))
#define     CAN1TFI3         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x50))  	
#define     CAN1TID3         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x54))  	
#define     CAN1TDA3         	    (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x58))  	
#define     CAN1TDB3 	            (*(volatile unsigned long *)(CAN1_BASE_ADDR + 0x5C))

#define     CAN2_BASE_ADDR		    0xE0048000

#define     CAN2MOD 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x00))  	
#define     CAN2CMR 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x04))  	
#define     CAN2GSR 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x08))  	
#define     CAN2ICR 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x0C))  	
#define     CAN2IER 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x10))
#define     CAN2BTR 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x14))  	
#define     CAN2EWL                 (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x18))  	
#define     CAN2SR 		            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x1C))  	
#define     CAN2RFS 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x20))  	
#define     CAN2RID 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x24))
#define     CAN2RDA 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x28))  	
#define     CAN2RDB 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x2C))
              	
#define     CAN2TFI1 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x30))  	
#define     CAN2TID1 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x34))  	
#define     CAN2TDA1 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x38))
#define     CAN2TDB1 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x3C))  	
#define     CAN2TFI2 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x40))  	
#define     CAN2TID2 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x44))  	
#define     CAN2TDA2 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x48))  	
#define     CAN2TDB2 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x4C))
#define     CAN2TFI3 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x50))  	
#define     CAN2TID3 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x54))  	
#define     CAN2TDA3 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x58))  	
#define     CAN2TDB3 	            (*(volatile unsigned long *)(CAN2_BASE_ADDR + 0x5C))

#define     MCI_BASE_ADDR		    0xE008C000

#define     MCIPower                (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x00))
#define     MCIClock                (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x04))
#define     MCIArgument             (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x08))
#define     MCICommand              (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x0C))
#define     MCIRespCmd              (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x10))
#define     MCIResponse0            (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x14))
#define     MCIResponse1            (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x18))
#define     MCIResponse2            (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x1C))
#define     MCIResponse3            (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x20))
#define     MCIDataTimer            (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x24))
#define     MCIDataLength           (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x28))
#define     MCIDataCtrl             (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x2C))
#define     MCIDataCnt              (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x30))
#define     MCIStatus               (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x34))
#define     MCIClear                (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x38))
#define     MCIMask0                (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x3C))
#define     MCIMask1                (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x40))
#define     MCIFifoCnt              (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x48))
#define     MCIFIFO                 (*(volatile unsigned long *)(MCI_BASE_ADDR + 0x80))

#define     I2S_BASE_ADDR		    0xE0088000

#define     I2SDAO                  (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x00))
#define     I2SDAI                  (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x04))
#define     I2STXFIFO               (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x08))
#define     I2SRXFIFO               (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x0C))
#define     I2SSTATE                (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x10))
#define     I2SDMA1                 (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x14))
#define     I2SDMA2                 (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x18))
#define     I2SIRQ                  (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x1C))
#define     I2STXRATE               (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x20))
#define     I2SRXRATE               (*(volatile unsigned long *)(I2S_BASE_ADDR + 0x24))

#define     DMA_BASE_ADDR		    0xFFE04000

#define     DMACIntStatus           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x000))
#define     DMACIntTCStatus         (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x004))
#define     DMACIntTCClear          (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x008))
#define     DMACIntErrorStatus      (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x00C))
#define     DMACIntErrClr           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x010))
#define     DMACRawIntTCStatus      (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x014))
#define     DMACRawIntErrorStatus   (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x018))
#define     DMACEnbldChns           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x01C))
#define     DMACSoftBReq            (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x020))
#define     DMACSoftSReq            (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x024))
#define     DMACSoftLBReq           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x028))
#define     DMACSoftLSReq           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x02C))
#define     DMACConfiguration       (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x030))
#define     DMACSync                (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x034))

#define     DMACC0SrcAddr           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x100))
#define     DMACC0DestAddr          (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x104))
#define     DMACC0LLI               (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x108))
#define     DMACC0Control           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x10C))
#define     DMACC0Configuration     (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x110))

#define     DMACC1SrcAddr           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x120))
#define     DMACC1DestAddr          (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x124))
#define     DMACC1LLI               (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x128))
#define     DMACC1Control           (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x12C))
#define     DMACC1Configuration     (*(volatile unsigned long *)(DMA_BASE_ADDR + 0x130))


#define     USB_INT_BASE_ADDR	    0xE01FC1C0
#define     USB_BASE_ADDR		    0xFFE0C200	

#define      USBClkCtrl            	(*(volatile unsigned long *)(0xFFE0CFF4))  
#define      USBClkSt              	(*(volatile unsigned long *)(0xFFE0CFF8)) 
#define      USBPortSel            	(*(volatile unsigned long *)(0xFFE0C110))	


#define     USBIntSt			    (*(volatile unsigned long *)(USB_INT_BASE_ADDR + 0x00))

#define     USBDevIntSt			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x00))
#define     USBDevIntEn			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x04))
#define     USBDevIntClr		    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x08))
#define     USBDevIntSet		    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x0C))
#define     USBDevIntPri		    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x2C))

#define     USBEpIntSt			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x30))
#define     USBEpIntEn			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x34))
#define     USBEpIntClr			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x38))
#define     USBEpIntSet			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x3C))
#define     USBEpIntPri			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x40))

#define     USBReEp				    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x44))
#define     USBEpInd			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x48))
#define     USBMaxPSize			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x4C))

#define     USBCmdCode			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x10))
#define     USBCmdData			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x14))

#define     USBRxData			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x18))
#define     USBTxData			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x1C))
#define     USBRxPLen			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x20))
#define     USBTxPLen			    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x24))
#define     USBCtrl				    (*(volatile unsigned long *)(USB_BASE_ADDR + 0x28))

#define     USBDMARSt               (*(volatile unsigned long *)(USB_BASE_ADDR + 0x50))
#define     USBDMARClr              (*(volatile unsigned long *)(USB_BASE_ADDR + 0x54))
#define     USBDMARSet              (*(volatile unsigned long *)(USB_BASE_ADDR + 0x58))
#define     USBUDCAH                (*(volatile unsigned long *)(USB_BASE_ADDR + 0x80))
#define     USBEpDMASt              (*(volatile unsigned long *)(USB_BASE_ADDR + 0x84))
#define     USBEpDMAEn              (*(volatile unsigned long *)(USB_BASE_ADDR + 0x88))
#define     USBEpDMADis             (*(volatile unsigned long *)(USB_BASE_ADDR + 0x8C))
#define     USBDMAIntSt             (*(volatile unsigned long *)(USB_BASE_ADDR + 0x90))
#define     USBDMAIntEn             (*(volatile unsigned long *)(USB_BASE_ADDR + 0x94))
#define     USBEoTIntSt             (*(volatile unsigned long *)(USB_BASE_ADDR + 0xA0))
#define     USBEoTIntClr            (*(volatile unsigned long *)(USB_BASE_ADDR + 0xA4))
#define     USBEoTIntSet            (*(volatile unsigned long *)(USB_BASE_ADDR + 0xA8))
#define     USBNDDRIntSt            (*(volatile unsigned long *)(USB_BASE_ADDR + 0xAC))
#define     USBNDDRIntClr           (*(volatile unsigned long *)(USB_BASE_ADDR + 0xB0))
#define     USBNDDRIntSet           (*(volatile unsigned long *)(USB_BASE_ADDR + 0xB4))
#define     USBSysErrIntSt          (*(volatile unsigned long *)(USB_BASE_ADDR + 0xB8))
#define     USBSysErrIntClr         (*(volatile unsigned long *)(USB_BASE_ADDR + 0xBC))
#define     USBSysErrIntSet         (*(volatile unsigned long *)(USB_BASE_ADDR + 0xC0))

#define     USBHC_BASE_ADDR		    0xFFE0C000

#define     HcRevision              (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x00))
#define     HcControl               (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x04))
#define     HcCommandStatus         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x08))
#define     HcInterruptStatus       (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x0C))
#define     HcInterruptEnable       (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x10))
#define     HcInterruptDisable      (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x14))
#define     HcHcca                  (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x18))
#define     HcPeriodCurrentED       (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x1C))
#define     HcControlHeadED         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x20))
#define     HcControlCurrentED      (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x24))
#define     HcBulkHeadED            (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x28))
#define     HcBulkCurrentED         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x2C))
#define     HcDoneHead              (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x30))
#define     HcFmInterval            (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x34))
#define     HcFmRemaining           (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x38))
#define     HcFmNumber              (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x3C))
#define     HcPeriodicStart         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x40))
#define     HcLSThreshold           (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x44))
#define     HcRhDescriptorA         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x48))
#define     HcRhDescriptorB         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x4C))
#define     HcRhStatus              (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x50))
#define     HcRhPortStatus1         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x54))
#define     HcRhPortStatus2         (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0x58))
#define     Module_VerRev_ID        (*(volatile unsigned long *)(USBHC_BASE_ADDR + 0xFC))

#define     USBOTG_BASE_ADDR	    0xFFE0C100

#define     OTGIntSt                (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x00))
#define     OTGIntEn                (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x04))
#define     OTGIntSet               (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x08))
#define     OTGIntClr               (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x0C))

#define     OTGStCtrl               (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x10))
#define     OTGTmr                  (*(volatile unsigned long *)(USBOTG_BASE_ADDR + 0x14))

#define     USBOTG_I2C_BASE_ADDR	0xFFE0C300

#define     I2C_RX                  (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x00))
#define     I2C_TX                  (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x00))
#define     I2C_STS                 (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x04))
#define     I2C_CTL                 (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x08))
#define     I2C_CLKHI               (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x0C))
#define     I2C_CLKLO               (*(volatile unsigned long *)(USBOTG_I2C_BASE_ADDR + 0x10))

#define     USBOTG_CLK_BASE_ADDR	0xFFE0CFF0
#define     OTGClkCtrl              (*(volatile unsigned long *)(USBOTG_CLK_BASE_ADDR + 0x04))
#define     OTGClkSt                (*(volatile unsigned long *)(USBOTG_CLK_BASE_ADDR + 0x08))


#define     MAC_BASE_ADDR		    0xFFE00000 

#define     MAC_MAC1                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x000)) 
#define     MAC_MAC2                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x004)) 
#define     MAC_IPGT                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x008)) 
#define     MAC_IPGR                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x00C))
#define     MAC_CLRT                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x010))
#define     MAC_MAXF                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x014))
#define     MAC_SUPP                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x018))
#define     MAC_TEST                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x01C))
#define     MAC_MCFG                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x020))
#define     MAC_MCMD                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x024))
#define     MAC_MADR                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x028))
#define     MAC_MWTD                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x02C))
#define     MAC_MRDD                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x030))
#define     MAC_MIND                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x034))

#define     MAC_SA0                 (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x040)) 
#define     MAC_SA1                 (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x044)) 
#define     MAC_SA2                 (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x048)) 

#define     MAC_COMMAND             (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x100)) 
#define     MAC_STATUS              (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x104)) 
#define     MAC_RXDESCRIPTOR        (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x108)) 
#define     MAC_RXSTATUS            (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x10C)) 
#define     MAC_RXDESCRIPTORNUM     (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x110)) 
#define     MAC_RXPRODUCEINDEX      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x114)) 
#define     MAC_RXCONSUMEINDEX      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x118)) 
#define     MAC_TXDESCRIPTOR        (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x11C)) 
#define     MAC_TXSTATUS            (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x120)) 
#define     MAC_TXDESCRIPTORNUM     (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x124)) 
#define     MAC_TXPRODUCEINDEX      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x128)) 
#define     MAC_TXCONSUMEINDEX      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x12C)) 

#define     MAC_TSV0                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x158)) 
#define     MAC_TSV1                (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x15C)) 
#define     MAC_RSV                 (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x160)) 

#define     MAC_FLOWCONTROLCNT      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x170)) 
#define     MAC_FLOWCONTROLSTS      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x174)) 

#define     MAC_RXFILTERCTRL        (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x200))
#define     MAC_RXFILTERWOLSTS      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x204))
#define     MAC_RXFILTERWOLCLR      (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x208))

#define     MAC_HASHFILTERL         (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x210))
#define     MAC_HASHFILTERH         (*(volatile unsigned long *)(MAC_BASE_ADDR + 0x214))

#define     MAC_INTSTATUS           (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFE0))
#define     MAC_INTENABLE           (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFE4))
#define     MAC_INTCLEAR            (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFE8))
#define     MAC_INTSET              (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFEC))

#define     MAC_POWERDOWN           (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFF4))
#define     MAC_MODULEID            (*(volatile unsigned long *)(MAC_BASE_ADDR + 0xFFC))

#define     rm_init_entry()             ((void (*)())(0x7fffff91))()
#define     rm_undef_handler()          ((void (*)())(0x7fffffa0))()
#define     rm_prefetchabort_handler()  ((void (*)())(0x7fffffb0))()
#define     rm_dataabort_handler()      ((void (*)())(0x7fffffc0))()
#define     rm_irqhandler()             ((void (*)())(0x7fffffd0))()
#define     rm_irqhandler2()            ((void (*)())(0x7fffffe0))()
#define     iap_entry(a, b)             ((void (*)())(0x7ffffff1))(a, b)
#endif                                                                  /*  __LPC24XX_H_                */

/*********************************************************************************************************
**                            End Of File
*********************************************************************************************************/

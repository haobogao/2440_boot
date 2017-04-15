/*************************************************************************
	> File Name: clock.h
	> Author: 
	> Mail: 
	> Created Time: 2016骞�09鏈�22鏃� 鏄熸湡鍥� 01鏃�30鍒�07绉�
 ************************************************************************/

#ifndef _CLOCK_H
#define _CLOCK_H

//register define

#define REG_LOCKTIME  (*(volatile unsigned long *) 0x4c000000)
#define REG_MPLLCON   (*(volatile unsigned long *) 0x4c000004)
#define	REG_UPLLCON   (*(volatile unsigned long *) 0x4c000008)
#define REG_CLKCON    (*(volatile unsigned long *) 0x4c00000c)
#define REG_CLKDIVN   (*(volatile unsigned long *) 0x4c000014)

//perpheral clock refence define 
#define AC97    (1<<20)
#define Camera  (1<<19)
#define SPI     (1<<18)
#define IIS     (1<<17)
#define IIC     (1<<16)
#define ADC     (1<<15)
#define RTC     (1<<14)
#define GPIO    (1<<13)
#define UART2   (1<<12)
#define UART1   (1<<11)
#define UART0   (1<<10)
#define SDI     (1<<9)
#define PWMTIMER     (1<<8)
#define USB_device   (1<<7)
#define USB_host     (1<<6)
#define LCDC    (1<<5)
#define NAND_Flash_Controller    (1<<4)

//operate define
/*when you need use a perpheral you should open it's clock frist*/
#define use_perpheral(perpheral)   REG_CLKCON = REG_CLKCON | perpheral;
#define unuse_perpheral(perpheral)  REG_CLKCON = REG_CLKCON & (~perpheral);


#define FCLK 400000000
#define HCLK (int)FCLK/4
#define PCLK (int)HCLK/2
/*
  init the system clock at fclk = 400M mainwhile the hclk = 200M Pclk = 100M
*/
void clock_init(void);

void  wait(volatile unsigned long dly);
#endif

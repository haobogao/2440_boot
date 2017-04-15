/*************************************************************************
	> File Name: clock.c
	> Author: 
	> Mail: 
	> Created Time: 2016骞�09鏈�21鏃� 鏄熸湡涓� 02鏃�02鍒�40绉�
 ************************************************************************/
/*init the s3c2440's clock to make it run faster*/
#include "clock.h"
#include "my_type.h"
#include "LED.h"
/*
 * auther: haobo
 * brief : init the s3c2440's clock
 * set chip clock at :FCLK = 400M , HCLK =  100M, PCLK  = 50M
 *
 */
extern led_num_t    led1
				,led2
				,led3;
void clock_init(void)
{ 
	led_con(led1,ON);
    REG_LOCKTIME = 0x00ffffff; //locktime set as max reset value
     /* 濡傛灉HDIVN闈�0锛孋PU鐨勬�荤嚎妯″紡搴旇浠庘�渇ast bus mode鈥濆彉涓衡�渁synchronous bus mode鈥� */
 __asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        /* 璇诲嚭鎺у埗瀵勫瓨鍣� */
    "orr    r1, r1, #0xc0000000\n"          /* 璁剧疆涓衡�渁synchronous bus mode鈥� */
    "mcr    p15, 0, r1, c1, c0, 0\n"        /* 鍐欏叆鎺у埗瀵勫瓨鍣� */
    );
   REG_CLKDIVN = 0x05|REG_CLKDIVN;//when fclk = 400m mainwhile the hclk = 100M Pclk = 50

   /*
     jz2440 us inputfrequency 12Mhz ,i want to set arm920t run at 400M
        so MDIV: 0x52 PDIV: 1 SDIV:1
        following is the max value s3c2440 surported:
        •
 Fclk Up to 400MHz
•
 Hclk Up to 136MHz
•
 Pclk Up to 68MHz


     */
  REG_MPLLCON  = (0x5c<<12)|(1<<4)|1;
  led_con(led2,ON);
 
  
    /*
    * this decide which perpheral to use at this stage
    * we set it all closed 
    * when we us it ,we call the function:use_perpheral(RERPHER);
    * */

   REG_CLKCON = REG_CLKCON & 0x0;                    //disable all perpheral;
	use_perpheral(GPIO|NAND_Flash_Controller);        //open the GPIO and NAND_Flash_Controller's clock
 



}

void  wait(volatile unsigned long dly)
{
	for(; dly > 0; dly--);
}


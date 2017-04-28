/*************************************************************************
	> File Name: clock.c
	> Author: 
	> Mail: 
	> Created Time: 2016楠烇拷09閺堬拷21閺冿拷 閺勭喐婀℃稉锟� 02閺冿拷02閸掞拷40缁夛拷
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
     /* 婵″倹鐏塇DIVN闂堬拷0閿涘瓔PU閻ㄥ嫭锟借崵鍤庡Ο鈥崇础鎼存棁顕氭禒搴橈拷娓嘺st bus mode閳ユ繂褰夋稉琛★拷娓乻ynchronous bus mode閳ワ拷 */
 __asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        /* 鐠囪鍤幒褍鍩楃�靛嫬鐡ㄩ崳锟� */
    "orr    r1, r1, #0xc0000000\n"          /* 鐠佸墽鐤嗘稉琛★拷娓乻ynchronous bus mode閳ワ拷 */
    "mcr    p15, 0, r1, c1, c0, 0\n"        /* 閸愭瑥鍙嗛幒褍鍩楃�靛嫬鐡ㄩ崳锟� */
    );
   REG_CLKDIVN = 0x05|REG_CLKDIVN;//when fclk = 400m mainwhile the hclk = 100M Pclk = 50

   /*
     jz2440 us inputfrequency 12Mhz ,i want to set arm920t run at 400M
        so MDIV: 0x52 PDIV: 1 SDIV:1
        following is the max value s3c2440 surported:
        鈥�
 Fclk Up to 400MHz
鈥�
 Hclk Up to 136MHz
鈥�
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
	use_perpheral(GPIO|NAND_Flash_Controller|UART0);        //open the GPIO and NAND_Flash_Controller's clock
 



}

void  wait(volatile unsigned long dly)
{
	for(; dly > 0; dly--);
}


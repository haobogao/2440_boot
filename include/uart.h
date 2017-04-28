/*************************************************************************
	> File Name: uart.h
	> Author: haobo
	> Mail: haobo.gao@qq.com
	> Created Time: 2016楠烇拷09閺堬拷25閺冿拷 閺勭喐婀￠弮锟� 04閺冿拷13閸掞拷35缁夛拷
 ************************************************************************/

#ifndef _UART_H
#define _UART_H


/*
*the jz2440 use uart port 0,
* 
*/

//
#define     ULCON0      *(volatile unsigned long *)0x50000000          //UART channel 0 line control register 
#define     ULCON1      *(volatile unsigned long *)0x50004000          //UART channel 1 line control register
#define     ULCON2      *(volatile unsigned long *)0x50008000          //UART channel 2 line control register

#define     UCON0       *(volatile unsigned long *)0x50000004          //UART channel 0 control register
#define     UCON1       *(volatile unsigned long *) 0x50004004          //UART channel 1 control register
#define     UCON2      *(volatile unsigned long *) 0x50008004          //UART channel 2 control register

#define     UFCON0     *(volatile unsigned long *) 0x50000008          //UART channel 0 FIFO control register
#define     UFCON1     *(volatile unsigned long *) 0x50004008          //UART channel 1 FIFO control register
#define     UFCON2     *(volatile unsigned long *) 0x50008008          //UART channel 2 FIFO control register

#define     UMCON0      *(volatile unsigned long *)0x5000000c          //UART channel 0 Modem control register
#define     UMCON1     *(volatile unsigned long *) 0x5000400c          //UART channel 1 Modem control register

#define     UTRSTAT0    *(volatile unsigned long *)0x50000010          //UART channel 0 Tx/Rx status register
#define     UTRSTAT1   *(volatile unsigned long *) 0x50004010          //UART channel 1 Tx/Rx status register
#define     UTRSTAT2    *(volatile unsigned long *)0x50008010          //UART channel 2 Tx/Rx status register

#define     UERSTAT0   *(volatile unsigned long *) 0x50000014          //UART channel 0 Rx error status register
#define     UERSTAT1   *(volatile unsigned long *) 0x50004014          //UART channel 1 Rx error status register
#define     UERSTAT2    *(volatile unsigned long *)0x50008014          //UART channel 2 Rx error status register

//UART FIFO STATUS REGISTER
#define     UFSTAT0     *(volatile unsigned long *)0x50000018          //UART channel 0 FIFO status register
#define     UFSTAT1     *(volatile unsigned long *)0x50004018          //UART channel 1 FIFO status register
#define     UFSTAT2     *(volatile unsigned long *)0x50008018          //UART channel 2 FIFO status REGISTER

//UART MODEM STATUS REGISTER
#define     UMSTAT0     *(volatile unsigned long *)0x5000001C          //UART channel 0 modem status register
#define     UMSTAT1     *(volatile unsigned long *)0x5000401C          //UART channel 1 modem status register

//UART TRANSMIT BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
#define     UTXH0L      *(volatile unsigned long *)0x50000020       
#define     UTXH0B      *(volatile unsigned long *)0x50000023    
 
//UART RECEIVE BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
#define     URXH0L 	*(volatile unsigned long *)0x50000024     
#define     URXH0B 	*(volatile unsigned long *)0x50000027

//UART BAUD RATE DIVISOR REGISTER
#define 	UBRDIV0 *(volatile unsigned long *)0x50000028


/*	init the UART0	*/
void uart_init(void);

void uart_send_byte(unsigned char ch);

unsigned char uart_recive_byte(void);


char* scan(void);

void put_a_char(char ch);

void print(char * str);

int str_cmp(char * str1,char * str2);


int str_len(char * str);


/*
 * 	define GPIO_ports that we used as tx rx ports
 */
#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHDAT              (*(volatile unsigned long *)0x56000074)
#define GPHUP               (*(volatile unsigned long *)0x56000078)


#define UBRDIV_VAL(buad_rate) (int)( PCLK/( buad_rate*16) )-1
#define URT0_T_ok (UTRSTAT0 & (1<<2))
#define URT0_R_ok	(UTRSTAT0 & 1)

#endif

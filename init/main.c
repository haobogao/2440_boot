/*
 * main.c
 *
 *  Created on: Apr 14, 2017
 *      Author: haobogao
 */

#include <s3c2440.h>
#include <LED.h>
#include <clock.h>
#include <uart.h>
#include <CMD.h>
#include <nand1.h>
void main(void );

void entry(void)
{
	led_init();

    clock_init();

	uart_init();
	//print("This is the s3c2440 UART0 test\r\n pass '1' to open led1\r\n");
	while(1)
		main();
}
void main(void)
{
  cmd_excute();
}

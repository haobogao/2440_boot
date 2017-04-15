/*
 * led.c
 *
 *  Created on: Apr 11, 2017
 *      Author: haobogao
 */
/*
 * This is for the  absolute understand the arm bare computer program.
 *
 *JZ2440 v3 has three led following is some detials:
 *  when the io prots is reset to light on
 *  lednum    IOPorts
 *   1			GPF4
 *   2			GPF5
 *   4			GPF6
 */

#include <my_type.h>
#include <LED.h>
#include <my_type.h>
led_num_t    led1 = LEDNUM1
				,led2 = LEDNUM2
				,led3 = LEDNUM3;

//set GPF 4 5 6 as output mode


void led_init(void )
{

	GPF_LEDPorts_out;

		led_con(led1,OFF);
		led_con(led2,OFF);
		led_con(led3,OFF);

}
void led_con( led_num_t num,uchar stat)
{
	switch (num){
		case LEDNUM1:{
			if(stat)
				S3C2440_GPFDAT &= ~(1<<4);
			else
				S3C2440_GPFDAT |= 1<<4;
		}break;

		case LEDNUM2:{
			if(stat)
				S3C2440_GPFDAT &= ~(1<< 5);
			else
				S3C2440_GPFDAT |= 1<< 5;
		}break;

		case LEDNUM3:{
			 if(stat)
				 S3C2440_GPFDAT &= ~(1<< 6);
			 else
				 S3C2440_GPFDAT |= 1<< 6;
		}break;

		default:
			;
			break;
	}

}


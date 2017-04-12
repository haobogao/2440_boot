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
#include <s3c2440.h>
#include <my_type.h>
typedef enum led_num {
	 LEDNUM1 = 1,
	 LEDNUM2,
	 LEDNUM3
} led_num_t;


//set GPF 4 5 6 as output mode
#define GPF_LEDPorts_out {	 S3C2440_GPFCON &=  ~((0x3f)<<8); 	/*related bit reset*/ \
								S3C2440_GPFCON |= ((0x15)<<8);}		/*set what you want */

#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))


void led_con( led_num_t num,uchar stat);

void entry(void )
{
	led_num_t    led1 = LEDNUM1
				,led2 = LEDNUM2
				,led3 = LEDNUM3;
	GPF_LEDPorts_out;

	//GPFCON = GPF4_out|GPF5_out|GPF6_out;

		led_con(led1,ON);
		led_con(led2,OFF);
		led_con(led3,ON);
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


/*
 * LED.h
 *
 *  Created on: Apr 13, 2017
 *      Author: haobogao
 */

#ifndef INCLUDE_LED_H_
#define INCLUDE_LED_H_
#include <s3c2440.h>
#include <my_type.h>
#define GPF_LEDPorts_out {	 S3C2440_GPFCON &=  ~((0x3f)<<8); 	/*related bit reset*/ \
								S3C2440_GPFCON |= ((0x15)<<8);}		/*set what you want */
#define LED_ST_TURN(num) {	S3C2440_GPFDAT ^= (1<<(3+num));	}

void led_con( led_num_t num,uchar stat);

void led_init(void );

#endif /* INCLUDE_LED_H_ */

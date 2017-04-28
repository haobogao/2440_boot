/*
 * my_type.h
 *
 *  Created on: Apr 11, 2017
 *      Author: haobogao
 */

#ifndef INCLUDE_MY_TYPE_H_
#define INCLUDE_MY_TYPE_H_
#define  uchar  unsigned char
#define ON    	1
#define OFF 	0
#define ST_TURN 2

#define  KEY_STATUS_BP 0
#define  KEY_STATUS_PR 1
#define  KEY_STATUS_UP 2

typedef enum led_num {
	 LEDNUM1 = 1,
	 LEDNUM2,
	 LEDNUM3
} led_num_t;
#endif /* INCLUDE_MY_TYPE_H_ */

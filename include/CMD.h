/*
 * CMD.h
 *
 *  Created on: Apr 14, 2017
 *      Author: haobogao
 */

#ifndef INCLUDE_CMD_H_
#define INCLUDE_CMD_H_

/* 	some of CMD define in bootloader	*/
#define CMD_LED1_ON 			0
#define CMD_LED1_STATUS_TURN 	1
#define CMD_LED2_ON 			3
#define CMD_LED2_STATUS_TURN 	4
#define CMD_LED3_ON 			5
#define CMD_LED3_STATUS_TURN 	6
#define CMD_LED_ON 				7
#define CMD_NAND_TEST 			8

/* some useful define  */
#define EQ 		1
#define NO_EQ 	0




unsigned char cmd_analyze(char * cmd);
void cmd_excute(void);
#endif /* INCLUDE_CMD_H_ */

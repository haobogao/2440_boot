/*
 * CMD.c
 *
 *  Created on: 2016��9��30��
 *      Author: haobo
 */
#include "CMD.h"
#include "LED.h"
#include "uart.h"
extern led_num_t    led1
				,led2
				,led3;
	/*
	 * this is an important function
	 * when you need add a new cmd just add a if case in following
	 * and add some code in /init/CMD.c void cmd_excute(void)
	 */
	unsigned char cmd_analyze(char * cmd)
	{
		if(str_cmp("led on 1\r\n",cmd) == EQ || str_cmp("lo 1\r\n",cmd) == EQ){
	#ifdef DEBUG_PRINT
				print("find command led on 1\r\n");
	#endif

			return CMD_LED1_ON;
		}
		if(str_cmp("led on\r\n",cmd) == EQ || str_cmp("lo\r\n",cmd) == EQ){
			return CMD_LED_ON;
		}
		if(str_cmp("led on 2\r\n",cmd) == EQ || str_cmp("lo 2\r\n",cmd) == EQ){
			return CMD_LED2_ON;
		}
		if(str_cmp("led on 3\r\n",cmd) == EQ || str_cmp("lo 3\r\n",cmd) == EQ){
			return CMD_LED3_ON;
		}
		if(str_cmp("led status turn 1\r\n",cmd) == EQ || str_cmp("lst 1\r\n",cmd) == EQ){
			return CMD_LED1_STATUS_TURN;
		}
		if(str_cmp("led status turn 2\r\n",cmd) == EQ || str_cmp("lst 2\r\n",cmd) == EQ){
			return CMD_LED2_STATUS_TURN;
		}
		if(str_cmp("led status turn 3\r\n",cmd) == EQ || str_cmp("lst 3\r\n",cmd) == EQ){
			return CMD_LED3_STATUS_TURN;
		}

			print("wrong command!\r\n");
			return 255;

	}


void cmd_excute(void)
{

	unsigned char * cmd
	,which;
	while (1){
		print("input CMD! only led CMD support now! exp: \r\n**** led on [num]   or lo num  	to open led num.\r\n**** led status turn [num]    or  lst [num] 	to turn the num's led status\r\n ");
		cmd = scan();
#ifdef DEBUG_PRINT
		print("recived you input:\r\n");
#endif
	which = cmd_analyze(cmd);
		switch(which){
		  case CMD_LED1_ON:{
			  led_con(led1,ON);
			  print("Your command has been performed!\r\n");
			  break;
		  }
		  case CMD_LED2_ON:{
			  led_con(led2,ON);
			  print("Your command has been performed!\r\n");
			  break;
		  }
		  case CMD_LED3_ON:{
			  led_con(led3,ON);
			  print("Your command has been performed!\r\n");
			  break;
		  }
		  case CMD_LED1_STATUS_TURN:{
			  LED_ST_TURN(led1);
			  print("Your command has been performed!\r\n");
			  break;
		  }
		  case CMD_LED2_STATUS_TURN:{
			  LED_ST_TURN(led2);
			  print("Your command has been performed!\r\n");
			  break;
		  }
		  case CMD_LED3_STATUS_TURN:{
			  LED_ST_TURN(led3);
			  	  print("Your command has been performed!\r\n");
			  	  break;
		   }
		  case CMD_LED_ON:{
			  	  led_con(led1,ON);
			  	 led_con(led2,ON);
			  	 led_con(led3,ON);
			  	  print("Your command has been performed!\r\n");
			  	  break;
		   }

		}
	}
}


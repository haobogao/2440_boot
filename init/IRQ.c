/*
 * IRQ.c
 *
 *  Created on: Apr 13, 2017
 *      Author: haobogao
 */


#include <IRQ.h>
#include <my_type.h>
#include <LED.h>
 led_num_t    led1
				,led2
				,led3;
/*
 * every key has three status
 * status before pressed : KEY_STATUS_BP
 * pressed				 : KEY_STATUS_PR
 * up					 : KEY_STATUS_UP
 * */

 uchar key_status_judge(uchar num)
 {
	 static uchar current_status = KEY_STATUS_BP;
	 switch (current_status){
	 	 case KEY_STATUS_BP:{
	 		 current_status = KEY_STATUS_BP;
	// 		 if()
	 	 }break;
	 	 case KEY_STATUS_PR:{
	 		 if(current_status == KEY_STATUS_BP)
	 			 current_status = KEY_STATUS_PR;
	 		 else if(current_status == KEY_STATUS_UP)
	 			 current_status = KEY_STATUS_BP;
	 		 else
	 			current_status = KEY_STATUS_UP;
	 	 }break;
	 	case KEY_STATUS_UP:{
	 		if(current_status == KEY_STATUS_PR)
	 			current_status= KEY_STATUS_UP;
	 		else
	 			current_status = KEY_STATUS_BP;
	 	}break;
	 }
	 return current_status;
 }

/*
 * four key on board related with the eint line EINT0 EINT2 EINT11 EINT19
 *ARBITER6
 *EINT0 GPF0 EINT0
 *EINT2 GPF2 EINT1      ARB0 REQ0
 *EINT11 GPG3 EINT8-23
 *
 *EINT19 GPG11 EINT8-23 ARB1 REQ1
 *EINT19
 *ARB0 REQ 1-2-3-4
 *ARB1 REQ 0-1-2-3-4-5
 * */
void init_irq(void)
{
	//config pin as interrupt mode;
	S3C2440_GPFCON &=  ~(3);
	S3C2440_GPFCON &=  ~(3<<(2*2));
	S3C2440_GPFCON |=  (2)| (2<<(2*2));

	S3C2440_GPGCON &=  ~(3<<(2*3));
	S3C2440_GPGCON |=  (2)<<(2*3);

    S3C2440_EINTMASK &=  ~(1<<11);


    //ARB_SEL bits are 00b, the priority order is REQ0, REQ1, REQ2, REQ3, REQ4, and REQ5.
    //if ARB_MODE bit is set to 0, ARB_SEL bits doesn’t change automatically changed,
   S3C2440_PRIORITY &= ~1;



	//NOmask EIN0 2 11 19

	INTMSK_NO(EINT0);
	INTMSK_NO(EINT2);
	INTMSK_NO(EINT8_23);
}
void  IRQ_Handle(void)
{
	if(S3C2440_INTOFFSET == EINT0){
		INTMSK_ON(EINT0);
		CLR_INTPEND(0);
		CLR_SRCPEND(0);
	//	if(key_status_judge(KEY_STATUS_PR) == KEY_STATUS_UP)
		LED_ST_TURN(led1);
		INTMSK_NO(EINT0);

	}
	if(S3C2440_INTOFFSET == EINT2){
		CLR_INTPEND(2);
		CLR_SRCPEND(2);
			LED_ST_TURN(led2);

	}
	if(S3C2440_INTOFFSET == EINT8_23){

			LED_ST_TURN(led3);
			S3C2440_EINTPEND = 1<<11;
			CLR_INTPEND(5);
			CLR_SRCPEND(5);

	}

}

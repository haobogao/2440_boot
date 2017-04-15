/*************************************************************************
	> File Name: uart.c
	> Author: 
	> Mail: 
	> Created Time: ************************************************************************/


#include "uart.h"
#include "clock.h"
#include "CMD.h"
/*
 *In this step, set the uart0 to make it work
 */
void uart_init(void)
{
	/*
	* 	uart0 use the io port's GPH2: TXD  GPH3 :RXD
	* 	we set it works
	*/
	GPHCON = 0xa0;
	GPHUP   = 0x0c;     // GPH2,GPH3内部上拉

	//open the uart0's clock
	use_perpheral(UART0);
	/*UART LINE CONTROL REGISTER
	 * normal mode operation,no parity,one stop bits, data bits 8bit
   */
	ULCON0 = 0x03 | ULCON0;
	/*UART CONTROL REGISTER
	 *UBRDIVn= (int)( UART clock / ( buad rate x 16) ) –1
	 *
	 */
	UCON0 = 0x05;
	UBRDIV0 = UBRDIV_VAL(115200);  //set buad_rate = 115200
    UFCON0  = 0x00;     // 不使用FIFO
    UMCON0  = 0x00;     // 不使用流控

}

/*send a char from s3c2440*/
void uart_send_byte(unsigned char ch)
{
	while(!URT0_T_ok);
	UTXH0L = ch;
}

unsigned char uart_recive_byte(void)
{
	unsigned char ch;
	while (!URT0_R_ok);
	ch = URXH0L;
	return ch;
}

void print(char * str)
{
	while(*str != '\0')
	uart_send_byte(*str++);
	uart_send_byte('\n');
}


char* scan(void)
{
	//recive the input string
	static char input_buff[40];
	unsigned char i;

	for(i = 0;;){
		*(input_buff+i) = uart_recive_byte();
		uart_send_byte(*(input_buff+i));
		if(*(input_buff+i) == '\r')
			break;
		i++;
	}
	*(input_buff+i+1) = '\n';

	uart_send_byte('\r');
	uart_send_byte('\n');

#ifdef DEBUG_PRINT
	print(input_buff);
#endif

	return  input_buff;

}

int str_cmp(char * str1,char * str2)
{
	int i = 0,
		len1 = str_len(str1),
	    len2 = str_len(str2);
	if(len1 != len2 ){
#ifdef DEBUG_PRINT
		print("no eq\r\n");
#endif
		return NO_EQ;
	}
	while(*(str1+i) != '\n'){
		if(*(str1+i) != *(str2+i) ){
			return NO_EQ;
		}
		i++;
	}
#ifdef DEBUG_PRINT
	print("EQ\r\n");
#endif
	return EQ;
}

int str_len(char * str)
{
	unsigned int len = 0;
	while(*(str+len) != '\r'){
#ifdef DEBUG_PRINT
		print("len++\r\n");
#endif
		len++;
	}
	return len;
}


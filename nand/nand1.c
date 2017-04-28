/*
* nand.c
*
*  Created on: 2016年12月7日
*      Author: haobo
*/
#include <nand1.h>
#include <uart.h>
#include <CMD.h>
#include "stdio.h"
#include <s3c2440.h>
#define BUF_SIZE 2048*3
nand_reg_t *nand_reg = (nand_reg_t*) 0x4e000000;
nand_op_t  nand_op;

unsigned char rbuff[BUF_SIZE] = {1};
unsigned char wbuff[BUF_SIZE] = {0};
unsigned char id[5] = {0};
void nand_test(void)
{
	int i;
	unsigned long addr;
	nand_init();
	for (i = 0;i<BUF_SIZE;i++){
		wbuff[i] = 0x33;
	}
	for (i = 0;i<BUF_SIZE;i++){
		rbuff[i] = 0;
	}
	printf("init wbuff OK\n");
	read_id(id);
	print("read id OK\n");
	addr =  addr_maker(10,20,1);
	nand_read(addr,4097,rbuff);
	for (i = 0;i<BUF_SIZE;i++){
		if(i%5 == 0)
		printf(" %x ",rbuff[i]);
	}
	printf("erase....\n\n");
	block_erase(addr);
	printf("erase ok\n\n");
	nand_read(addr,BUF_SIZE,rbuff);
	for (i = 0;i<BUF_SIZE;i++){
		if(i%5 == 0)
		printf("%x ",rbuff[i]);
	}

	nand_write(addr,BUF_SIZE,wbuff);

	print("write OK \r\n");

	nand_read(addr,BUF_SIZE,rbuff);
	for (i = 0;i<BUF_SIZE;i++){
		if(i%5 == 0)
		printf("%x  ",rbuff[i]);
	}
	printf("In nand1 test:OK \nID：\n");

	for (i = 0; i < 5;i++ ){
		printf("  _%x_ ",id[i]);
	}
}

void read_id(unsigned char *buf)
{
	int  i;
	nand_op.chip_select();
	nand_op.send_command(CMD_Read_ID);

	nand_reg->NFADDR = 0;

	*buf =read_byte();
	*(buf+1) =read_byte();
	*(buf+2) =read_byte();
	*(buf+3) =read_byte();
	*(buf+4) =read_byte();
	for(i = 0;i<5;i++){
		printf("%x" ,*(buf+i));
	}
	nand_op.chip_disselect();

}

void nand_init(void)
{
	//op_list init

	nand_op.reset = nand_reset;

	nand_op.chip_select = nand_chip_select;
	nand_op.chip_disselect = nand_chip_disselect;
	nand_op.send_command = nand_send_cmd;
	nand_op.busy_wait = nand_wait_finsh;
	nand_op.mkaddr = addr_maker;
	nand_op.rd_byte = read_byte;
	nand_op.wr_byte = write_byte;
	nand_op.write_addr = send_addr;
	//base config
	print("nand_op Ok\r\n");
	nand_reg->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	nand_reg->NFCONT = (1<<4)|(1<<1)|(1<<0);
	//reset

	print("reset Ok\r\n");
}


void nand_reset(void)
{
	nand_op.chip_select();
	nand_op.busy_wait();
	nand_op.send_command(CMD_Reset);
	nand_op.chip_disselect();
}

void nand_chip_select(void)
{

	nand_reg->NFCONT = nand_reg->NFCONT & (~(1<<1));

}



void nand_chip_disselect(void)
{

	nand_reg->NFCONT = nand_reg->NFCONT | (1<<1);

}



void nand_send_cmd(int  cmd)
{
	int i;
	//nand_reg->NFCMMD = cmd;
	volatile unsigned char *p = (volatile unsigned char *)&nand_reg->NFCMMD;
	*p = cmd;
	for (i = 0; i<10; i++);
}

void nand_wait_finsh(void)
{
	volatile unsigned char * p = (volatile unsigned char *)&nand_reg->NFSTAT;
	int i = 10;// &&(nand_reg->NFSTAT & (1<<2)) == 0
	while( 0==((*p) & 1)   ){
		for (i = 10;i>0;i--);
	}
}


void write_byte(char ch)
{
	volatile unsigned char *p = (volatile unsigned char *)&nand_reg->NFDATA;
	*p = ch;
	//nand_reg->NFDATA = ch;
	//for (i  = 10;i>0;i--);
}

char read_byte(void)
{
	unsigned char ch;
	volatile unsigned char *p = (volatile unsigned char *)&nand_reg->NFDATA;
	ch = *p;
	//ch = nand_reg->NFDATA;
	//for (i  = 10;i>0;i--);
	return ch;
}


void send_addr(unsigned int addr,char cycle)
{
	int i;
	volatile unsigned char * p = (volatile unsigned char *)&nand_reg->NFADDR;
	//地址结构： 2048 block * 64page * 2048byte

	//先发送block 地址 选中一个block 最低8位 co.addr1


	/*start address of a page col
	*col .1    A0-A7
	*col .2	A8-A11
	*which page row
	*row .1	A12-A19
	*row .2	A20 - A27
	*row .3	A28
	*
	*/
	if(cycle == 5 || cycle == 2){
		//nand_reg->NFADDR = addr&0xff;
		*p = addr&0xff;
		i=10;
		while(i--);

		//接着发送A8-A11   co.addr2
		//nand_reg->NFADDR = addr>>8&0x0f;
		*p = (addr>>8)&0x0f;
		i=10;
		while(i--);
		if(cycle == 2)
			return;
	}

	//ro.addr1
	//nand_reg->NFADDR = addr>>12 & 0xff;
	*p = (addr>>12) & 0xff;
	i=10;
	while(i--);
	//ro.addr2
	*p = (addr>>20) & 0xff;
	//nand_reg->NFADDR = addr>>20 & 0xff;
	i=10;
	while(i--);
	//ro.addr3
//	nand_reg->NFADDR = addr>>28 & 0x1;
  *p = (addr>>28) & 0x1;
	i=10;
	while(i--);



}


/*													 		block    page   byte
	after addr_maker the address
 struct looks like ：					  2048  *  64	  * 2048
 */
unsigned int addr_maker(unsigned int num_block,unsigned int page,unsigned int num_byte)
{
	unsigned int address,coaddr,roaddr;
	coaddr = num_byte&0xfff;
	//address = (address & 0xFFFC0FFF) | paddr;
	roaddr = num_block<<18|page<<12;
	address = coaddr | roaddr;
	return address;
}



int nand_read(unsigned long start_addr,unsigned int size,char * buff)
{

	/*There maybe two case :
			1.page aligned read
			2.random read
	*/
 unsigned int *p,count = 0,j,i = 0;
 int numpage2read
	,currpage;


	//page aligned read
 	 start_addr &= 0xfffff000;
 	 if(size%2048 != 0){
 		 size = (size/2048 + 1) * 2048;
 	 }
			numpage2read = size/2048;
			currpage = 0;
			for(;currpage < numpage2read;currpage++){
				nand_op.chip_select();
				nand_op.send_command(CMD_Read_c1);
				nand_op.write_addr(start_addr+(currpage<<12),5);
				printf("in the page aligned read!");
				nand_op.send_command(CMD_Read_c2);
				nand_op.busy_wait();
				for(i = 0;i < 2048;i++,count++){
					*(buff+count) = nand_op.rd_byte();

				}
				nand_op.chip_disselect();
			}
				return count;
	}

int nand_write(unsigned long start_addr,unsigned int size,char * buff)
{

	int numpage2wr,currpage;
	unsigned int i= 0,count;
	start_addr &= 0xfffff000;
	 if(size%2048 != 0){
		 size = (size/2048 + 1) * 2048;
	 }
	numpage2wr = size/2048;
	currpage = 0;
	for(;currpage < numpage2wr;currpage++){
		nand_op.chip_select();
		nand_op.send_command(CMD_Page_program_c1);
		nand_op.write_addr(start_addr+(currpage<<12),5);
		for(i = 0;i <2048;i++,count++){
			nand_op.wr_byte(*buff);
			buff++;
		}
		nand_op.send_command(CMD_Page_program_c2);
		nand_op.busy_wait();
		nand_op.chip_disselect();
	}
	return 0;
}

int block_erase(int numblk)
{
	nand_op.chip_select();
	nand_op.send_command(CMD_Block_Erase_c1);
	nand_op.write_addr(numblk,3);
	nand_op.send_command(CMD_Block_Erase_c2);
	nand_op.busy_wait();
	nand_op.chip_disselect();

	return 0;
}

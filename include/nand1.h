/*
 * nand.h
 *
 *  Created on: 2016��10��7��
 *      Author: haobo
 */

#ifndef SOURCE_INCLUDE_NAND_H_
#define SOURCE_INCLUDE_NAND_H_

//timeing define
#define TACLS ((int)1)
#define TWRPH0 ((int)3)
#define TWRPH1 ((int)0)


#define CMD_Read_c1 				0x0
#define CMD_Read_c2					0x30
#define CMD_Read_Copy_Back_c1 		0x0
#define CMD_Read_Copy_Back_c2 		0x35
#define CMD_Read_ID 			0x90
#define CMD_Reset 				0xFF
#define CMD_Page_program_c1		0x80
#define CMD_Page_program_c2		0x10
#define	 CMD_Copy_Back_Program_c1  0x85
#define	 CMD_Copy_Back_Program_c2  0x10
#define	 CMD_Block_Erase_c1  		0x60
#define	 CMD_Block_Erase_c2  		0xD0


#define	 CMD_Random_Data_Input  		0x85
#define	 CMD_Random_Data_Onput_c1  		0x05
#define	 CMD_Random_Data_Onput_c2  		0xe0

#define CMD_READ_STATUS  				0x70
#define CMD_READ_STATUS2  				0xf1
typedef volatile unsigned int	S3C24X0_REG32;
typedef struct {
    S3C24X0_REG32 NFCONF; 	/*		NAND flash configuration register	*/
    S3C24X0_REG32 NFCONT;
    S3C24X0_REG32 NFCMMD;
    S3C24X0_REG32 NFADDR;
    S3C24X0_REG32 NFDATA;
    S3C24X0_REG32 NFMECCD0;
    S3C24X0_REG32 NFMECCD1;
    S3C24X0_REG32 NFSECCD;
    S3C24X0_REG32 NFSTAT;
    S3C24X0_REG32 NFESTAT0;
    S3C24X0_REG32 NFESTAT1;
    S3C24X0_REG32 NFMECC0;
    S3C24X0_REG32 NFMECC1;
    S3C24X0_REG32 NFSECC;
    S3C24X0_REG32 NFSBLK;
    S3C24X0_REG32 NFEBLK;
} nand_reg_t;


typedef struct{

	void (*reset)(void);
	void (*chip_select)(void);
	void (*chip_disselect)(void);
	void (*send_command)(int);
	void (*busy_wait)(void);
	char (*rd_byte)(void);
	void (*wr_byte)(char);
	unsigned int (*mkaddr)(unsigned int,unsigned int,unsigned int);
	void (*write_addr)(unsigned int,char);


} nand_op_t;

char read_byte(void);

unsigned int addr_maker(unsigned int num_block,unsigned int page,unsigned int num_byte);



void write_byte(char ch);

void nand_wait_finsh(void);

void nand_send_cmd(int cmd);

void nand_chip_select(void);

void nand_chip_disselect(void);

void nand_init(void);

void send_addr(unsigned int addr,char cycle);

void nand_reset(void);
void nand_test(void);
void read_id(unsigned char *buf);

int nand_read(unsigned long start_addr,unsigned int size,char * buff);
int nand_write(unsigned long start_addr,unsigned int size,char * buff);
int block_erase(int numblk);
#endif /* SOURCE_INCLUDE_NAND_H_ */

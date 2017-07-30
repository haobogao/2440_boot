/*
 * lcd.c
 *
 *  Created on: Apr 21, 2017
 *      Author: haobo
 */
#include <lcd.h>

#include <stdio.h>

#define LCD_VBPD 		1<<24
#define LCD_LINEVAL		(272-1)<<14
#define LCD_VFPD		1<<6
#define LCD_VSPW		9
#define ON 	1
#define OFF 0


#define gpb_con  *(volatile unsigned int *)0x56000010
#define gpb_dat  *(volatile unsigned int *)0x56000014


struct lcd_port_t{

	unsigned int * gpc_con;
	unsigned int * gpc_dat;

	unsigned int * gpd_con;
	unsigned int * gpd_dat;



	unsigned int *  gpg_con;
	unsigned int  * gpg_dat;

};

struct s3c2440_lcd_regs_t {
	/*lcdcon1  */
	unsigned int LCDCON1;
	unsigned int LCDCON2;		//0X4D000004
	unsigned int LCDCON3;
	unsigned int LCDCON4;		//0X4D00000C
	unsigned int LCDCON5;		//0X4D000010
	unsigned int LCDSADDR1;		//0X4D000014
	unsigned int LCDSADDR2;		//0X4D000018
	unsigned int LCDSADDR3;		//0X4D00001C
	unsigned int REDLUT;		//0X4D000020
	unsigned int GREENLUT;		//0X4D000024
	unsigned int BLUELUT;		//0X4D000028
	unsigned int dummy[0x4c-0x28-0x4];		//useless
    unsigned int DITHMODE;		//0X4D00004C
    unsigned int  TPAL;			//0X4D000050
    unsigned int LCDINTPND;		//0X4D000054
    unsigned int LCDSRCPND;		//0X4D000058
    unsigned int LCDINTMSK;		//0X4D00005C
    unsigned int TCONSEL;		//0X4D000060

};


struct s3clcd_device{
	struct s3c2440_lcd_regs_t * lcd_regs ;
	struct lcd_port_t 		  * lcd_port;

};

struct s3clcd_device s3clcd;

void lcd_background_led_switch(char stat)
{
	if(stat == ON){
		gpb_dat |= (0x01 << 0);
		print("led ON\r\n");
	}else if(stat == OFF){
		gpb_dat &= ~(0x01 << 0);
		print("led ON\r\n");
	}else
		printf("@ lcd_drv.c:lcd_background_led_switch dummy parameter!");
}

static inline void lcd_switch(char stat)
{
	if(stat == ON){
		s3clcd.lcd_regs->LCDCON1 |= (0x01 << 0);
		s3clcd.lcd_regs->LCDCON5 |= (0x01<<3);
		print("SWITCH ON\r\n");
	}else if(stat == OFF){
		s3clcd.lcd_regs->LCDCON1 &= ~(0x01 << 0);
		s3clcd.lcd_regs->LCDCON5 &= ~(0x01<<3);
		print("SWITCH OFF\r\n");
	}else
		printf("@ lcd_drv.c:lcd_switch dummy parameter!");
}



void lcd_init(void)
{
	/*
	 *
	 	lcd.lcd_port->gpb_con.phy =0x56000010;
	lcd.lcd_port->gpb_dat.phy =0x56000014;
	lcd.lcd_port->gpc_con.phy =0x56000020;
	lcd.lcd_port->gpc_dat.phy =0x56000024;
	lcd.lcd_port->gpd_con.phy =0x56000030;
	lcd.lcd_port->gpd_dat.phy =0x56000034;
	lcd.lcd_port->gpg_con.phy = 0x56000060;
	lcd.lcd_port->gpg_dat.phy = 0x56000064;
	printk(KERN_NOTICE"ready to ioremap!\n");
		//mmap all regs
	 **/

	s3clcd.lcd_port->gpc_con =  (volatile unsigned int *) 0x56000020;
	s3clcd.lcd_port->gpc_dat = (volatile unsigned int *) 0x56000024;
	s3clcd.lcd_port->gpd_con=  (volatile unsigned int *)0x56000030;
	s3clcd.lcd_port->gpd_dat =(volatile unsigned int *)0x56000034;
	s3clcd.lcd_port->gpg_con = (volatile unsigned int*)0x56000060;
	s3clcd.lcd_port->gpg_dat = (volatile unsigned int *)0x56000064;
	s3clcd.lcd_regs = (volatile struct s3c2440_lcd_regs_t *)0X4D000000;

	//set background led
	//configure gpb  to output mode
	gpb_con &= ~(3<<0);			//lowest two bit set to zero
	gpb_con |= 0x01;

	//set gpg4 to LCD_POWEN .output value of LCD_PWREN pin is controlled by ENVID
	*(s3clcd.lcd_port->gpg_con) &= ~(3<< (2*4) );
	*(s3clcd.lcd_port->gpg_con) |=	3<<(2*4);
	//set LCD specific pin
	*(s3clcd.lcd_port->gpd_con) = 0xaaaaaaaa;
	*(s3clcd.lcd_port->gpc_con) = 0xaaaaaaaa;

	/*set HW reg*/
	s3clcd.lcd_regs->LCDCON1 =4<<8|0x03<<5|0x0c<<1;
	s3clcd.lcd_regs->LCDCON2 = LCD_LINEVAL|LCD_VBPD|LCD_VFPD|LCD_VSPW;
	s3clcd.lcd_regs->LCDCON3 = 1<<19|479<<8|1;
	s3clcd.lcd_regs->LCDCON4 = 40;
	s3clcd.lcd_regs->LCDCON5 = 1<<11;
/*
 *         LCDSADDR1 = ((LCDFRAMEBUFFER>>22)<<21) | LOWER21BITS(LCDFRAMEBUFFER>>1);
        LCDSADDR2 = LOWER21BITS((LCDFRAMEBUFFER+ \
                    (480)*(272)*2)>>1);
        LCDSADDR3 = (0<<11) | (480*2/2);
 * */
	s3clcd.lcd_regs->LCDSADDR1 =	((LCD_FRAMEBUFF_ADDR>>22)<<21) | ( (LCD_FRAMEBUFF_ADDR) & 0x1fffff );
	s3clcd.lcd_regs->LCDSADDR2 =	( (LCD_FRAMEBUFF_ADDR) & 0x1fffff ) + ( (480)*(272)*2 )>>1;
	s3clcd.lcd_regs->LCDSADDR3 =  (0<<11) | (480*2/2);

	lcd_switch(ON);
	lcd_background_led_switch(ON);	//open the lcd light
}



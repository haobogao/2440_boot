/*
 * s3c2440.h
 *
 *  Created on: Apr 11, 2017
 *      Author: haobogao
 */

#ifndef INCLUDE_S3C2440_H_
#define INCLUDE_S3C2440_H_

#define S3C2440_GPFCON  *(volatile unsigned long*)0x56000050//(0xa0000050)//0x56000050
#define S3C2440_GPFDAT  *(volatile unsigned long*)0x56000054//(0xa0000054)//0x56000054
#define S3C2440_GPFUP   *(volatile unsigned long *)0x56000058
#define S3C2440_GPGCON  *(volatile unsigned long *)0x56000060//(0xa0000060) //0x56000060
#define S3c2440_GPGDAT	*(volatile unsigned long *)0x56000064//(0xa0000064)// 0x56000064


#define S3C2440_SRCPND 			*(volatile unsigned long *) 0x4a000000
#define S3C2440_INTMOD 			*(volatile unsigned long *) 0x4a000004
#define S3C2440_INTMSK 			*(volatile unsigned long *) 0x4a000008
#define S3C2440_PRIORITY 		*(volatile unsigned long *) 0x4a00000c
#define S3C2440_INTPND 			*(volatile unsigned long *) 0x4a000010
#define S3C2440_INTOFFSET 		*(volatile unsigned long *) 0x4a000014
#define S3C2440_SUBSRCPND		*(volatile unsigned long *) 0x4a000018
#define S3C2440_INTSUBMSK		*(volatile unsigned long *) 0x4a00001c

#define S3C2440_EINTMASK	*(volatile unsigned long *)0x560000a4//(0xa00000a4) //0x560000a4
#define S3C2440_EINTPEND	*(volatile unsigned long *)0x560000a8//(0xa00000a8)//0x560000a8
#endif /* INCLUDE_S3C2440_H_ */

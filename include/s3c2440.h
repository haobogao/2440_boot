/*
 * s3c2440.h
 *
 *  Created on: Apr 11, 2017
 *      Author: haobogao
 */

#ifndef INCLUDE_S3C2440_H_
#define INCLUDE_S3C2440_H_

#define S3C2440_GPFCON  *(volatile unsigned long*)(0xa0000050)//0x56000050
#define S3C2440_GPFDAT  *(volatile unsigned long*)(0xa0000054)//0x56000054
#define S3C2440_GPFUP   *(volatile unsigned long *)0x56000058

#endif /* INCLUDE_S3C2440_H_ */

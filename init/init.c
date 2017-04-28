/*
 * init.c
 *
 *  Created on: Apr 12, 2017
 *      Author: haobogao
 */
#include <s3c2440.h>
#include <stdio.h>
int raise(void)
{
	printf("OK");
	return 1;
}
void mmu_init(void)
{
	/*
	 *	 MRC p15, 0, Rd, c1, c0, 0; _R_ead _C_ontrol register   RC
		 MCR p15, 0, Rd, c1, c0, 0; write _C_ontrol _R_egister  CR
 	* */
	unsigned long ttb = 0x30000000;
	__asm__(
	    "mov    r0, #0\n"
	    "mcr    p15, 0, r0, c7, c7, 0\n"    /* 脢鹿脦脼脨搂ICaches潞脥DCaches */

	    "mcr    p15, 0, r0, c7, c10, 4\n"   /* drain write buffer on v4 */
	    "mcr    p15, 0, r0, c8, c7, 0\n"    /* 脢鹿脦脼脨搂脰啪脕卯隆垄脢媒鸥脻TLB */

	    "mov    r4, %0\n"                   /* r4 = 脪鲁卤铆禄霉脰路 */
	    "mcr    p15, 0, r4, c2, c0, 0\n"    /* 脡猫脰脙脪鲁卤铆禄霉脰路艗脛沤忙脝梅 */

	    "mvn    r0, #0\n"
	    "mcr    p15, 0, r0, c3, c0, 0\n"    /* 脫貌路脙脦脢驴脴脰脝艗脛沤忙脝梅脡猫脦陋0xFFFFFFFF拢卢
	                                         * 虏禄艙酶脨脨脠拧脧脼艗矛虏茅
	                                         */
	    /*
	     * 露脭脫脷驴脴脰脝艗脛沤忙脝梅拢卢脧脠露脕鲁枚脝盲脰碌拢卢脭脷脮芒禄霉沤隆脡脧脨脼啪脛啪脨脨脣脠鈧得劽幝宦Ｂ�
	     * 脠禄潞贸脭脵脨沤脠毛
	     */
	    "mrc    p15, 0, r0, c1, c0, 0\n"    /* 露脕鲁枚驴脴脰脝艗脛沤忙脝梅碌脛脰碌 */

	    /* 驴脴脰脝艗脛沤忙脝梅碌脛碌脥16脦禄潞卢脪氓脦陋拢潞.RVI ..RS B... .CAM
	     * R : 卤铆脢鸥禄禄鲁枚Cache脰脨碌脛脤玫脛驴脢卤脢鹿脫脙碌脛脣茫路拧拢卢
	     *     0 = Random replacement拢禄1 = Round robin replacement
	     * V : 卤铆脢鸥脪矛鲁拢脧貌脕驴卤铆脣霉脭脷碌脛脦禄脰脙拢卢
	     *     0 = Low addresses = 0x00000000拢禄1 = High addresses = 0xFFFF0000
	     * I : 0 = 鹿脴卤脮ICaches拢禄1 = 驴陋脝么ICaches
	     * R隆垄S : 脫脙脌沤脫毛脪鲁卤铆脰脨碌脛脙猫脢枚路没脪禄脝冒脠路露拧脛脷沤忙碌脛路脙脦脢脠拧脧脼
	     * B : 0 = CPU脦陋脨隆脳脰艙脷脨貌拢禄1 = CPU脦陋沤贸脳脰艙脷脨貌
	     * C : 0 = 鹿脴卤脮DCaches拢禄1 = 驴陋脝么DCaches
	     * A : 0 = 脢媒鸥脻路脙脦脢脢卤虏禄艙酶脨脨碌脴脰路露脭脝毛艗矛虏茅拢禄1 = 脢媒鸥脻路脙脦脢脢卤艙酶脨脨碌脴脰路露脭脝毛艗矛虏茅
	     * M : 0 = 鹿脴卤脮MMU拢禄1 = 驴陋脝么MMU
	     */

	    /*
	     * 脧脠脟氓鲁媒虏禄脨猫脪陋碌脛脦禄拢卢脥霉脧脗脠么脨猫脪陋脭貌脰脴脨脗脡猫脰脙脣眉脙脟
	     */
	                                        /* .RVI ..RS B... .CAM */
	    "bic    r0, r0, #0x3000\n"          /* ..11 .... .... .... 脟氓鲁媒V隆垄I脦禄 */
	    "bic    r0, r0, #0x0300\n"          /* .... ..11 .... .... 脟氓鲁媒R隆垄S脦禄 */
	    "bic    r0, r0, #0x0087\n"          /* .... .... 1... .111 脟氓鲁媒B/C/A/M */

	    /*
	     * 脡猫脰脙脨猫脪陋碌脛脦禄
	     */
	    "orr    r0, r0, #0x0002\n"          /* .... .... .... ..1. 驴陋脝么露脭脝毛艗矛虏茅 */
	    "orr    r0, r0, #0x0004\n"          /* .... .... .... .1.. 驴陋脝么DCaches */
	    "orr    r0, r0, #0x1000\n"          /* ...1 .... .... .... 驴陋脝么ICaches */
	    "orr    r0, r0, #0x0001\n"          /* .... .... .... ...1 脢鹿脛脺MMU */

	    "mcr    p15, 0, r0, c1, c0, 0\n"    /* 艙芦脨脼啪脛碌脛脰碌脨沤脠毛驴脴脰脝艗脛沤忙脝梅 */
	    : /* 脦脼脢盲鲁枚 */
	    : "r" (ttb) );

}
#define MMU_FULL_ACCESS     (3 << 10)   /*AP set as Manager*/
#define MMU_DOMAIN          (0 << 5)    /*first domain*/
#define MMU_SPECIAL         (1 << 4)    /* must be 1*/
#define MMU_CACHEABLE       (1 << 3)    /* cacheable */
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable */
#define MMU_SECTION         (2)         /* 卤铆脢鸥脮芒脢脟露脦脙猫脢枚路没 */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)
#define MMU_SECTION_SIZE    0x00100000

void page_table_create(void)
{
	unsigned long * mmu_tlb_base = (unsigned long *)0x30000000; //page table store at the begin of sdram
	unsigned long pa,va;
	//we define the frist 1M
	pa = 0;
	va = 0;
	*(mmu_tlb_base + (va>>20)) = (pa&0xfff00000)| MMU_SECDESC_WB;

	va = 0xa0000000;
	pa = 0x56000000;
	*(mmu_tlb_base + (va>>20)) = (pa&0xfff00000)| MMU_SECDESC;

	va = 0xb0000000;
	pa = 0x30000000;
	while(va<0xb4000000){
		*(mmu_tlb_base + (va>>20)) = (pa&0xfff00000)| MMU_SECDESC_WB;
		va = va + 0x100000;
		pa = pa + 0x100000;
	}
	mmu_init();
}

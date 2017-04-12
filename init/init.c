/*
 * init.c
 *
 *  Created on: Apr 12, 2017
 *      Author: haobogao
 */
void mmu_init(void)
{
	/*
	 *	 MRC p15, 0, Rd, c1, c0, 0; _R_ead _C_ontrol register   RC
		 MCR p15, 0, Rd, c1, c0, 0; write _C_ontrol _R_egister  CR
 	* */
	unsigned long ttb = 0x30000000;
	__asm__(
	    "mov    r0, #0\n"
	    "mcr    p15, 0, r0, c7, c7, 0\n"    /* Ê¹ÎÞÐ§ICachesºÍDCaches */

	    "mcr    p15, 0, r0, c7, c10, 4\n"   /* drain write buffer on v4 */
	    "mcr    p15, 0, r0, c8, c7, 0\n"    /* Ê¹ÎÞÐ§ÖžÁî¡¢ÊýŸÝTLB */

	    "mov    r4, %0\n"                   /* r4 = Ò³±í»ùÖ· */
	    "mcr    p15, 0, r4, c2, c0, 0\n"    /* ÉèÖÃÒ³±í»ùÖ·ŒÄŽæÆ÷ */

	    "mvn    r0, #0\n"
	    "mcr    p15, 0, r0, c3, c0, 0\n"    /* Óò·ÃÎÊ¿ØÖÆŒÄŽæÆ÷ÉèÎª0xFFFFFFFF£¬
	                                         * ²»œøÐÐÈšÏÞŒì²é
	                                         */
	    /*
	     * ¶ÔÓÚ¿ØÖÆŒÄŽæÆ÷£¬ÏÈ¶Á³öÆäÖµ£¬ÔÚÕâ»ùŽ¡ÉÏÐÞžÄžÐÐËÈ€µÄÎ»£¬
	     * È»ºóÔÙÐŽÈë
	     */
	    "mrc    p15, 0, r0, c1, c0, 0\n"    /* ¶Á³ö¿ØÖÆŒÄŽæÆ÷µÄÖµ */

	    /* ¿ØÖÆŒÄŽæÆ÷µÄµÍ16Î»º¬ÒåÎª£º.RVI ..RS B... .CAM
	     * R : ±íÊŸ»»³öCacheÖÐµÄÌõÄ¿Ê±Ê¹ÓÃµÄËã·š£¬
	     *     0 = Random replacement£»1 = Round robin replacement
	     * V : ±íÊŸÒì³£ÏòÁ¿±íËùÔÚµÄÎ»ÖÃ£¬
	     *     0 = Low addresses = 0x00000000£»1 = High addresses = 0xFFFF0000
	     * I : 0 = ¹Ø±ÕICaches£»1 = ¿ªÆôICaches
	     * R¡¢S : ÓÃÀŽÓëÒ³±íÖÐµÄÃèÊö·ûÒ»ÆðÈ·¶šÄÚŽæµÄ·ÃÎÊÈšÏÞ
	     * B : 0 = CPUÎªÐ¡×ÖœÚÐò£»1 = CPUÎªŽó×ÖœÚÐò
	     * C : 0 = ¹Ø±ÕDCaches£»1 = ¿ªÆôDCaches
	     * A : 0 = ÊýŸÝ·ÃÎÊÊ±²»œøÐÐµØÖ·¶ÔÆëŒì²é£»1 = ÊýŸÝ·ÃÎÊÊ±œøÐÐµØÖ·¶ÔÆëŒì²é
	     * M : 0 = ¹Ø±ÕMMU£»1 = ¿ªÆôMMU
	     */

	    /*
	     * ÏÈÇå³ý²»ÐèÒªµÄÎ»£¬ÍùÏÂÈôÐèÒªÔòÖØÐÂÉèÖÃËüÃÇ
	     */
	                                        /* .RVI ..RS B... .CAM */
	    "bic    r0, r0, #0x3000\n"          /* ..11 .... .... .... Çå³ýV¡¢IÎ» */
	    "bic    r0, r0, #0x0300\n"          /* .... ..11 .... .... Çå³ýR¡¢SÎ» */
	    "bic    r0, r0, #0x0087\n"          /* .... .... 1... .111 Çå³ýB/C/A/M */

	    /*
	     * ÉèÖÃÐèÒªµÄÎ»
	     */
	    "orr    r0, r0, #0x0002\n"          /* .... .... .... ..1. ¿ªÆô¶ÔÆëŒì²é */
	    "orr    r0, r0, #0x0004\n"          /* .... .... .... .1.. ¿ªÆôDCaches */
	    "orr    r0, r0, #0x1000\n"          /* ...1 .... .... .... ¿ªÆôICaches */
	    "orr    r0, r0, #0x0001\n"          /* .... .... .... ...1 Ê¹ÄÜMMU */

	    "mcr    p15, 0, r0, c1, c0, 0\n"    /* œ«ÐÞžÄµÄÖµÐŽÈë¿ØÖÆŒÄŽæÆ÷ */
	    : /* ÎÞÊä³ö */
	    : "r" (ttb) );

}
#define MMU_FULL_ACCESS     (3 << 10)   /*AP set as Manager*/
#define MMU_DOMAIN          (0 << 5)    /*first domain*/
#define MMU_SPECIAL         (1 << 4)    /* must be 1*/
#define MMU_CACHEABLE       (1 << 3)    /* cacheable */
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable */
#define MMU_SECTION         (2)         /* ±íÊŸÕâÊÇ¶ÎÃèÊö·û */
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

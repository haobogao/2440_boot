.equ MEM_CON_REG_ADDR,0x48000000
.equ SDRAM_BASE_ADDR,0x30004000
.equ WTCON_BASE_ADDR,0x53000000
.text
.global _start
_start:
    	b reset
    	ldr	pc, _undefined_instruction	
	ldr	pc, _software_interrupt		
	ldr	pc, _prefetch_abort			
	ldr	pc, _data_abort				
	ldr	pc, _not_used				
	ldr	pc, _irq					
	ldr	pc, _fiq
_undefined_instruction: .word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq
reset:

    bl disable_watch_dog /*close the watchdog*/

    bl mem_controller_setup

    bl copy_4096_to_sdram

    ldr sp,=4096

    bl page_table_create

    ldr sp,=0xb4000000

    ldr pc,=entry
loop:
	b loop

copy_4096_to_sdram:
    /* copy code from steppingstone to the sdram  */
    mov r1,#2048
    ldr r2,=SDRAM_BASE_ADDR
    mov r3,#4096
 b:
     ldr r4,[r1],#4
     str r4,[r2],#4
     cmp r1,r3
     bne b;
     mov pc,lr

mem_controller_setup:
    mov r1,#MEM_CON_REG_ADDR
    adrl r2,MEM_CON_REG_VAL
    add r3,r1,#52                       /* 13*4 = 52 */
 a:
     ldr r4,[r2],#4
     str r4,[r1],#4
     cmp r1,r3
     bne a
     mov pc,lr
    
disable_watch_dog:
    mov r1, #WTCON_BASE_ADDR
    adrl r2,WAT_CON_REG_VAL
    ldr r4,[r2]
    str r4,[r1]
    mov pc,lr


.align 4
WAT_CON_REG_VAL:
    .long 0
.align 4
MEM_CON_REG_VAL:
    .long 0x22011110 /*BWSCON val 0010 0010 0000 0001 0001 0001 0001 0000 */
    .long 0x00000700 /* bankcon0 */
    .long 0x00000700 @ 1
    .long 0x00000700 @ 2
    .long 0x00000700 @ 3
    .long 0x00000700 @ 4
    .long 0x00000700 @ 5
    .long 0x00018005 @ 6   1100 0000 0000 1001
    .long 0x00018005 @ bankcon7
    .long 0x008c07a3 @ REFRESH
    .long 0x000000b1 @ banksize
    .long 0x00000030
    .long 0x00000030




undefined_instruction:
		nop

software_interrupt:
		nop

prefetch_abort:
		nop

data_abort:
		nop

not_used:
		nop

irq:
		nop

fiq:
		nop

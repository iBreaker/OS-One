/*
*   	2014年12月30日16:20:25
*	V1.0 	By Breaker
*
*	文件名：Global.s
*	包含全局变量
*	
*/

.align 4
.global font
.global tasktable
font:			/*字体首地址*/
.incbin "./source/font0.bin"

tasktable:		/*任务状态*/
	.word		0x00		//	r0
	.word		0x00		//	r1
	.word		0x00		//	r2
	.word		0x00		//	r3
	.word		0x00		//	r4
	.word		0x00		//	r5	
	.word		0x00		//	r6
	.word		0x00		//	r7
	.word		0x00		//	r8
	.word		0x00		//	r9
	.word		0x00		//	r10
	.word		0x00		//	r11
	.word		0x00		//	r12
	.word		0x00		//	sp
	.word		0x00		//	lr
	.word		0x00		//	pc
	.word		0x00		//	cpsr
	.word		0x00		//	spsr


/*
*   	2014年12月30日16:20:25
*	V1.0 	By Breaker
*
*	文件名：Global.s
*	包含全局变量
*	
*/

.align 4
.global font , bmp, bg_bmp
.global tasktable, taskstack
font:			/*字体首地址*/
.incbin "./source/font0.bin"

bmp:
.incbin "./source/test.bmp"

bg_bmp:
.incbin "./source/bg.bmp"


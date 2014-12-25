/*
*	2014年12月25日17:08:20
*	V1.0 	By Breaker
*
*	文件名：time.h
*	定义time寄存器地址和time函数声明
*	
*/

#define TIMER_BASE 	0x20003000
#define TIMER_CS	0x20003000
#define TIMER_CLO	0x20003004
#define TIMER_CHI	0x20003008
#define TIMER_C0	0x2000300c
#define TIMER_C1	0x20003010
#define TIMER_C2	0x20003014
#define TIMER_C3	0x20003018



int sleep(int ms);





/*
*	2014年12月29日18:33:49
*	V1.0 	By Breaker
*
*	文件名：Global.h
*    	保存全局变量
*	
*/
#include "timer.h"

/*Graphic.c*/
extern unsigned int GpuInfoAddr;  			/*GPU信息首地址*/
extern volatile unsigned char *GpuBufAddr;  	/*GPU缓存首地址*/
extern unsigned char font[256];				/*字体首地址*/

/*timer.c*/

/*interupt.c*/
extern int TimerCounter;

/*timer.c*/
extern os_timer_ctrl_st os_timer_ctrl;

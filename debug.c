 /*
*	2014年12月31日16:11:30
*	V1.0 	By Breaker
*
*	文件名：debug.c
*      各个模块调试函数
*	
*/
#include "debug.h"
#include "gpio.h"
#include "time.h"
#include "Graphic.h"

/*
*	2014年12月31日16:12:49
*	V1.0 	By Breaker
*
*	void  deb_GPIO(void)
*      GPIO闪烁
*	return   void
*/
void  deb_GPIO(void)
 {
	 while(1)
	{	
		sleep(1000);
		GPIO_SET_GPCLR(16);			
		sleep(1000);
		GPIO_SET_GPSET(16);
	}
}

/*
*	2014年12月31日16:21:44
*	V1.0 	By Breaker
*
*	void  deb_screen(void)
*      画出图案
*	return   void
*/
void  deb_screen(void)
 {
	RGB_24Bit color;
	color.R = 0xFF;
	color.G = 0x00;
	color.B = 0x00;
	
	DrawBlock(color,0,0,800,1);
	DrawBlock(color,0,0,1,600);
	DrawBlock(color,0,800-1,1,600);
	DrawBlock(color,600-1,0,800,1);
	
	color.R = 0xFF;
	color.G = 0xFF;
	color.B = 0xFF;
	drawCharacter('A', color, 10, 10);
	drawString("123456??",color,40, 30);
 }
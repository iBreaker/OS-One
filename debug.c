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
#include "GPU.h"
#include "time.h"
#include "Graphic.h"
#include "Global.h"
 void test_drawFlt(int *x, int *y);
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
	double A = 3.14;
	int top,left;
	top = 40;
	left = 20;
	DrawBlock(color,0,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth) ,1);
	DrawBlock(color,0,0,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight) );
	DrawBlock(color,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth)-1,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight));
	DrawBlock(color,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight)-1,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth),1);
	
	color.R = 0xFF;
	color.G = 0xFF;
	color.B = 0xFF;
	
	/*2015年01月01日22:59:23  真是一个奇怪的bug，函数参数不能有double类型。Why*/
	test_drawFlt(&top, &left);
 }
 
 
 void test_drawFlt( int *x, int *y)
{	
	double  A = 3.14;
	int temp = 100;
	RGB_24Bit color;
	color.R = 0xFF;
	color.G = 0xFF;
	color.B = 0xFF;
	
	int icnt = 0;
	int tmpintA = 0;
	int tmpintB = 0;
	
	tmpintA = (int) A ;
	tmpintB =  (int )  ((A - tmpintA) * 100000) ;
	drawDec(tmpintA, color, x, y);
	drawDec(tmpintB, color, x, y);
}
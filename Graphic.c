/*
*   	2014年12月29日11:09:11
*	V1.0 	By Breaker
*
*	文件名：Graphic.c
*	定义所有图像处理相关的函数
*	
*/

#include "Global.h"
#include "Graphic.h"
#include "GPU.h" 
#include "stdarg.h"


/*****************************************************
*	2014年12月29日11:11:14
*	V2.0 	By Breaker
*
*	int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth)
*   	初始化桌面，显示任务栏等基本信息
*	return 0 成功  -1 失败	
*/

int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth)
{
	
	RGB_24Bit color;
	int top,left;
	
	GpuInfoAddr = init_GPU(width, height, bitDepth);

	if(GpuInfoAddr == 0)
	{
		return -1; /*初始化GPU发生错误*/
	}

	GpuBufAddr =  (volatile unsigned char *)(*(unsigned int *)(GpuInfoAddr + 32));

	color.R = 0x28;
	color.G = 0x82;
	color.B = 0xE6;
	DrawBlock(color, 0, 0, (((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth), (((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth));
}

/*****************************************************
*	2014年12月29日16:57:16
*	V1.0 	By Breaker
*
*	void DrawDot(RGB_24Bit color, int top, int left)
*   	画点
*	return void 超出显示范围退出	
*/

void DrawDot(RGB_24Bit color, int top, int left)
{
	/*检查*/
	if(top > (((struct FrameBufferInfoS *)GpuInfoAddr)->phyHeight) || top < 0)
	{
		return;
	}

	if(left > (((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) || left < 0)
	{
		return;
	}
	
	*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) * top + left) * 3 ))= color.R;
	*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) * top + left) * 3 + 1))= color.G;	
	*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth)* top + left) * 3 + 2))= color.B;	
}

int DrawLine(RGB_24Bit color, int x1, int y1, int x2, int y2)
{
	
}

/*****************************************************
*	2014年12月29日16:58:27
*	V1.0 	By Breaker
*
*	void DrawBlock(RGB_24Bit color, int top, int left, unsigned int width, unsigned int height)
*   	填充
*	return void 超出显示范围退出	
*/
void DrawBlock(RGB_24Bit color, int top, int left, unsigned int width, unsigned int height)
{
	int top_t,left_t;
	for(top_t=0; top_t < height; top_t++)
	{
		for(left_t=0; left_t < width; left_t++)
		{
			DrawDot(color, top+top_t, left+left_t);
		}
	}
}

int DrawBlockByMemory()
{
	
}



/*****************************************************
*	2014年12月29日16:58:27
*	V1.0 	By Breaker
*
*	void drawCharacter(unsigned char ASC2, RGB_24Bit color, int *top, int *left)
*   	显示字体
*	return void 	
*/
void drawCharacter(unsigned char ASC2, RGB_24Bit color, int *top, int *left)
{
	int row;
	char data;
	unsigned char *ASC2_addr;
	/*检查*/
	if( ASC2 > 128 )
	{
		return;
	}
	
	/*计算参数字符字体所在的首地址*/
	ASC2_addr = (unsigned char *)((unsigned int)font + (ASC2 * 16));
	for (row = 0; row < 16; row++)
	{
		data = ASC2_addr[row];
		if ((data & 0x80) != 0) DrawDot(color, *top+row, *left + 7);
		if ((data & 0x40) != 0) DrawDot(color, *top+row, *left + 6);
		if ((data & 0x20) != 0) DrawDot(color, *top+row, *left + 5);
		if ((data & 0x10) != 0) DrawDot(color, *top+row, *left + 4);
		if ((data & 0x08) != 0) DrawDot(color, *top+row, *left + 3);
		if ((data & 0x04) != 0) DrawDot(color, *top+row, *left + 2);
		if ((data & 0x02) != 0) DrawDot(color, *top+row, *left + 1);
		if ((data & 0x01) != 0) DrawDot(color, *top+row, *left + 0);
	}
	*left += 8;
}

/*****************************************************
*	2014年12月31日17:36:55
*	V1.0 	By Breaker
*
*	void drawString(char *string, RGB_24Bit color, int top, int left)
*   	显示字符串
*	return void 	
*/
void drawString(char *string, RGB_24Bit color, int top, int left)
{
	while(*string != 0)
	{
		drawCharacter(*string, color, &top, &left);
		
		string++;
		/*计算下次显示字符的位置*/
		//left = left + 8;
	}
}

/*****************************************************
*	2015年01月01日16:34:02
*	V1.0 	By Breaker
*
*	void drawDec(int dec, RGB_24Bit color, int *top, int *left)
*   	显示十进制数字，drawStringF()子函数
*	return void 	
*/
void drawDec(int dec, RGB_24Bit color, int *top, int *left)
{
	int times = 10;
	while( dec / times != 0)
	{
		times *= 10;
	}
	
	times /= 10;
	
	do {
		unsigned char num = 0;
		num = (unsigned char ) (dec / times);
		drawCharacter( (num + '0'), color, top, left );
		dec -=  num * times;
		times /= 10;
	}while(times != 0);
	
}

/*****************************************************
*	2015年01月01日16:36:14
*	V1.0 	By Breaker
*
*	void drawFlt(double flt, RGB_24Bit color, int *top, int *left);
*   	显示浮点数，drawStringF()子函数
*	return void 	
*/
/*2015年01月01日22:59:23  真是一个奇怪的bug，函数参数不能有double类型。Why?*/
void drawFlt(double flt, RGB_24Bit color, int *top, int *left)
{
	int icnt = 0;
	int tmpintA = 0;
	int tmpintB = 0;
	
	tmpintA = (int)flt ;
	//tmpintB = (int)((flt % (double)1)* 1000000);
	drawDec(tmpintA ,  color, top, left);
	drawCharacter( '.', color, top, left );
	drawDec(tmpintA, color, top, left);
}

/*****************************************************
*	2015年01月01日11:18:22
*	V1.0 	By Breaker
*
*	void drawStringF(char *string, RGB_24Bit color, int top, int left)
*   	格式化显示字符串
*	return void 	
*/
void drawStringF(char *fmt, RGB_24Bit color, int top, int left, ...)
{
	/*  */
	double vargflt = 0;
	int  vargint = 0;
	char* vargpch = 0;
	char vargch = 0;
	char* pfmt = 0;
	va_list vp;
	
	/*left 后第一个参数*/
	va_start(vp, left);
	
	 while(*pfmt)
	{
		if(*pfmt == '%')
		{
			switch(*(++pfmt))
			{
				case 'c':
					vargch = va_arg(vp, int); 
					drawCharacter(vargint, color, &top, &left);
					break;
				case 'd':
				case 'i':
					vargint = va_arg(vp, int);
					drawDec(vargint,color, &top, &left);
					break;
				case 'f':
					//vargflt = va_arg(vp, double);
					vargflt = 3.14;
					//drawFlt(vargflt,color, &top, &left);
					break;
				case 's':
					vargpch = va_arg(vp, char*);
					//printstr(vargpch);
					break;
				case 'b':
				case 'B':
					vargint = va_arg(vp, int);
					//printbin(vargint);
					break;
				case 'x':
				case 'X':
					vargint = va_arg(vp, int);
					//printhex(vargint);
					break;
				case '%':
					drawCharacter('%', color, &top, &left );
					break;
				default:
					break;
			}
			pfmt++;
		}
		else
		{
			drawCharacter(*pfmt++, color, &top, &left );
		}	
	}
	va_end(vp);
}



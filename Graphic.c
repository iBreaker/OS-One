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

/*
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

/*
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

/*
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

/*
*	2014年12月29日16:58:27
*	V1.0 	By Breaker
*
*	void drawCharacter(unsigned char ASC2, RGB_24Bit color, int top, int left)
*   	显示字体
*	return void 	
*/
void drawCharacter(unsigned char ASC2, RGB_24Bit color, int top, int left)
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
		if ((data & 0x80) != 0) DrawDot(color, top+row, left + 7);
		if ((data & 0x40) != 0) DrawDot(color, top+row, left + 6);
		if ((data & 0x20) != 0) DrawDot(color, top+row, left + 5);
		if ((data & 0x10) != 0) DrawDot(color, top+row, left + 4);
		if ((data & 0x08) != 0) DrawDot(color, top+row, left + 3);
		if ((data & 0x04) != 0) DrawDot(color, top+row, left + 2);
		if ((data & 0x02) != 0) DrawDot(color, top+row, left + 1);
		if ((data & 0x01) != 0) DrawDot(color, top+row, left + 0);
	}
}

/*
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
		drawCharacter(*string, color, top, left);
		
		string++;
		/*计算下次显示字符的位置*/
		left = left + 8;
	}
}



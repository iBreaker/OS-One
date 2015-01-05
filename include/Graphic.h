/*
*   	2014年12月29日11:09:11
*	V1.0 	By Breaker
*
*	文件名：Graphic.c
*	声明所有宏定义，图像处理相关的函数
*	定义相关结构体
*/

typedef struct RGB_24Bit_S
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}RGB_24Bit;


int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth);
void DrawDot(RGB_24Bit color, int top, int left);
void DrawBlock(RGB_24Bit color, int top, int left, unsigned int width, unsigned int height);
void drawCharacter(unsigned char ASC2, RGB_24Bit color, int *top, int *left);
void drawString(char *string, RGB_24Bit color, int *top, int *left);
void drawStringF(char *fmt, RGB_24Bit color, int top, int left, ...);

void drawDec(int dec, RGB_24Bit color, int *top, int *left);
void drawFlt(float  flt, RGB_24Bit color, int *x, int *y);
void drawHex(int hex, RGB_24Bit color, char IS_Big,int *top, int *left);
void drawBin(int bin, RGB_24Bit color, char IS_Big,int *top, int *left);



/*
*   	2014年12月29日11:09:11
*	V1.0 	By Breaker
*
*	文件名：Graphic.c
*	声明所有宏定义，图像处理相关的函数
*	定义相关结构体
*/

#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include "memory.h"
#include "stdtype.h"

// screen_width  screen_high  color_deep
#define screen_width	1440
#define screen_high	900
#define color_deep	24


typedef struct RGB_24Bit_S
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}RGB_24Bit;


int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth);
void DrawDot(RGB_24Bit * to_addr, RGB_24Bit color, int top, int left);
void DrawBlock(RGB_24Bit * to_addr, RGB_24Bit color, int top, int left, unsigned int width, unsigned int height);
void drawCharacter(RGB_24Bit * to_addr,unsigned char ASC2, RGB_24Bit color, int *top, int *left);
void drawString(RGB_24Bit * to_addr, char *string, RGB_24Bit color, int *top, int *left);
void drawStringF(RGB_24Bit * to_addr, char *fmt, RGB_24Bit color, int top, int left, ...);

void drawDec(RGB_24Bit * to_addr, int dec, RGB_24Bit color, int *top, int *left);
void drawFlt(float  flt, RGB_24Bit color, int *x, int *y);
void drawHex(RGB_24Bit * to_addr, int hex, RGB_24Bit color, char IS_Big,int *top, int *left);
void drawBin(RGB_24Bit * to_addr, int bin, RGB_24Bit color, char IS_Big,int *top, int *left);
void os_printf(char *fmt, ...);

/*-----------------------------------------------图层处理 Layer-----------------------------------------------------------------------*/


#define MaxPicLayer 256


struct position 	//位置
{
	int top;
	int left;
	int width;
	int hight;  
};

struct pic_layer	//每一个图层结构
{
	unsigned char PicIndex;
	//unsigned char Empty;	//pic_layer 是有序线性组，所以不需要标志位，LayerCount 就可以存储队尾信息
};

struct picture		//每一个图片结构
{
	unsigned char LayerIndex;
	struct position Position;
	RGB_24Bit *buf;
	unsigned char Empty;
};

struct pic_layer_table 		//图层表
{
	unsigned char LayerCount;
	unsigned char PicCount;
	struct pic_layer PicLayer[MaxPicLayer];
	struct picture Picture[MaxPicLayer];
};

struct pic_layer_table  *PicLayerTable_init();  //图层表初始化
unsigned char add_pic(struct picture NewPicture);	//添加图片
unsigned char add_pic_to_layer(unsigned char PicIndex) ; //放在当前最上层  
int rm_picture(unsigned char PicIndex);		//将图片从图层中移除
int rm_from_layer(unsigned char PicIndex);	//删除图像
unsigned char get_LayerIndex_by_PicIndex(unsigned char PicIndex);	//通过 LayerIndex获取 PicIndex
unsigned char get_PicIndex_by_LayerIndex(unsigned char LayerIndex);  //通过 PicIndex LayerIndex获取
int set_pic_layer(unsigned char PicIndex,unsigned char LayerIndex);	//改变图片图层
void pic_layer_reflash();

#endif


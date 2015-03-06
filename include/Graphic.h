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


//矩形
typedef struct{
	int top;
	int left;
	int width;
	int hight;
}rect;


struct pic_layer	//每一个图层结构
{
	unsigned char PicIndex;				//对应的图片号
	unsigned char Empty;					//是否被占用
};

struct picture		//每一个图片结构
{
	unsigned char LayerIndex;		//对应的图层号
	rect Position;										//位置大小
	RGB_24Bit *buf;									//颜色
	unsigned char Empty;					//是否被占用
};

struct pic_layer_table 		//图层表
{
	unsigned char LayerCount;
	unsigned char PicCount;
	struct pic_layer PicLayer[MaxPicLayer];
	struct picture Picture[MaxPicLayer];
};



//点是否在矩形中以及点的坐标
typedef struct{
	int x;
	int y;
	char is_in;
}point_msg;

typedef enum{
	null,
	absolute,
	relative
}move_type;

struct pic_layer_table  *PicLayerTable_init();  //图层表初始化
int add_pic(struct picture NewPicture);	//添加图片
int add_pic_to_layer(unsigned char PicIndex) ; //放在当前最上层
int rm_picture(unsigned char PicIndex);		//将图片从图层中移除
int rm_from_layer(unsigned char PicIndex);	//删除图像
unsigned char get_LayerIndex_by_PicIndex(unsigned char PicIndex);	//通过 LayerIndex获取 PicIndex
unsigned char get_PicIndex_by_LayerIndex(unsigned char LayerIndex);  //通过 PicIndex LayerIndex获取
int set_pic_to_top(unsigned char PicIndex);
void pic_layer_reflash_rect(s32 top, s32 left, s32 width, s32 hight);
void pic_layer_reflash();
void move_pic_layer(u32 top, u32 left, u32 haldle, move_type mt);
bool is_inside (int topa, int lefta, int widtha, int higha, int x, int y);
rect inside_rect(int topa, int lefta, int widtha, int higha, int topb, int leftb, int widthb, int highb);
void copy_bmp_to_piclayer(u32 bmp_, u32 to);

#endif


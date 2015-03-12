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


int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth);			//初始化


/**
 * 									2015-03-12 11:27:06
 * 这些函数都都直接将数据现实到显示器上, 在图层中并没有备份.所以刷新的时候
 * 使用这些函数绘制的图形会消失
 * */
void DrawDot(RGB_24Bit color, int top, int left);
void DrawBlock(RGB_24Bit color, int top, int left, unsigned int width, unsigned int height);
void drawCharacter(unsigned char ASC2, RGB_24Bit color, int *top, int *left);
void drawString(char *string, RGB_24Bit color, int *top, int *left);
void drawStringF(char *fmt, RGB_24Bit color, int top, int left, ...);
void drawDec( int dec, RGB_24Bit color, int *top, int *left);
void drawFlt(float  flt, RGB_24Bit color, int *x, int *y);
void drawHex( int hex, RGB_24Bit color, char IS_Big,int *top, int *left);
void drawBin(int bin, RGB_24Bit color, char IS_Big,int *top, int *left);
void os_printf(char *fmt, ...);

/**
 * 这些函数会将数据画到相应的缓冲区内存中, 并不会立即显示到显示器.只有刷新图层的时候,才会
 * 将缓冲区的数据显示到屏幕..
 * */
void DrawDot_to_layer(RGB_24Bit * to_addr, RGB_24Bit color ,int width, int top, int left);
void DrawBlock_to_layer(RGB_24Bit * to_addr, RGB_24Bit color, unsigned int layer_width, int top, int left, unsigned int width, unsigned int height);
void drawCharacter_to_layer(RGB_24Bit * to_addr, unsigned char ASC2, RGB_24Bit color, u32 width, int *top, int *left);
void drawString_to_layer(RGB_24Bit * to_addr, char *string, RGB_24Bit color,u32 width,  int *top, int *left);
void drawStringF_to_layer(RGB_24Bit * to_addr, char *fmt, RGB_24Bit color, u32 width, int top, int left, ...);
void drawDec_to_layer(RGB_24Bit * to_addr, int dec, RGB_24Bit color, u32 width, int *top, int *left);
void drawHex_to_layer(RGB_24Bit * to_addr, int hex, RGB_24Bit color, char IS_Big, u32 width, int *top, int *left);

/*-----------------------------------------------图层处理 -----------------------------------------------------------------------*/

#define MaxPicLayer 256		//最大图层数量

//矩形
typedef struct{
	int top;
	int left;
	int width;
	int hight;
}rect;

/*
 * 每一个图层有图层的id 每一个图片有图片的id ,要把一个图片放入到一个图层, 只要将picture结构里的
 * LayerIndex 指向图层的id, 并且将pic_layer结构里的PicIndex 指向picture的id
 *
 * 图层就像是一个"抽屉", 图片就是要放入"抽屉"的物品.抽屉和picture的index相关联的动作就相当于
 * 将物品放入某一层"抽屉". 我给这个模型起名字叫"抽屉模型"
 * */

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

// 图层表中保存了所有的图层和图片
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

//图层移动的参数, 相对坐标 还是绝对坐标
typedef enum{
	null,
	absolute,
	relative
}move_type;

struct pic_layer_table  *PicLayerTable_init();  //图层表初始化
int add_pic(struct picture NewPicture);	//添加图片
int add_pic_to_layer(unsigned char PicIndex) ; //放在当前最上层
int rm_picture(unsigned char PicIndex);		//将图片从图层中移除
int rm_from_layer(unsigned char PicIndex);	//删除图片,同时清空相应图层
unsigned char get_LayerIndex_by_PicIndex(unsigned char PicIndex);	//通过 LayerIndex获取 PicIndex
unsigned char get_PicIndex_by_LayerIndex(unsigned char LayerIndex);  //通过 PicIndex LayerIndex获取
int set_pic_to_top(unsigned char PicIndex);  //将相应图层置顶
void pic_layer_reflash_rect(s32 top, s32 left, s32 width, s32 hight);	//将所给矩形范围内的图像按照图层顺序显示到屏幕
void pic_layer_reflash();																					//所有图层信息按照顺序现实到屏幕
void move_pic_layer(u32 top, u32 left, u32 haldle, move_type mt);		//移动图层并且刷新
bool is_inside (int topa, int lefta, int widtha, int higha, int x, int y);	//判断一个点是否在所给矩形中
rect inside_rect(int topa, int lefta, int widtha, int higha, int topb, int leftb, int widthb, int highb);		//将两个矩形重叠部分计算出来,并且返回这个重叠部分的矩形
void copy_bmp_to_piclayer(u32 bmp_, u32 to);										//将bmp图片复制到一块图层的缓冲区 bmp_ 是bmp图片的起始地址. to是缓冲区的起始地址

extern char bg_bmp;						//背景图片的起始地址, 在global.s中定义

#endif


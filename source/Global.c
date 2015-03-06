/*
*	2014年12月29日18:36:49
*	V1.0 	By Breaker
*
*	文件名：Global.c
*    	保存全局变量
*	
*/

#include "Global.h"


/*Graphic.c*/
unsigned int GpuInfoAddr;  		/*GPU信息首地址*/
volatile unsigned char *GpuBufAddr;  	/*GPU缓存首地址*/

RGB_24Bit colorF;
RGB_24Bit colorB;

RGB_24Bit colorBlack;
RGB_24Bit colorWrite;
RGB_24Bit colorRed;
RGB_24Bit colorGreen;
RGB_24Bit colorBule;
RGB_24Bit  transparent;

s32 os_top = 0;					//全局位置指针（屏幕显示）
s32 os_left = 0;

struct pic_layer_table *PicLayerTable;
 int MouseHaldle;
 int DesktopHandle;
 
/*timer.c*/
arm_timer_t *ArmTimer = (arm_timer_t *)ARMTIMER_BASE;		//ArmTimer首地址
os_timer_ctrl_st os_timer_ctrl;		//timer ctrl

/*debug.c*/

/*task.c*/
TASK_GLOBAL task_global;

/*UART.c*/
char input_buf_p[input_size];
char * input_buf = input_buf_p;
FIFO8  input_p;
FIFO8  * input = & input_p;

/*memory.c*/
struct free_memory_table_s  FreeMemoryTables_p;
struct free_memory_table_s  *FreeMemoryTables = &FreeMemoryTables_p;



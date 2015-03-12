/***
*	2014年12月29日18:33:49
*	V1.0 	By Breaker
*
*	文件名：Global.h
*    	保存全局变量
*	
* OS One - A simple OS for Raspberry Pi
* Copyright (C) 2014 - 2015  Breaker  <791628659@qq.com>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
 * **/
#ifndef _GLOBAL_H 
#define _GLOBAL_H

#include "timer.h"
#include "stdtype.h"
#include "task.h"
#include "Graphic.h"
#include "fifo.h"
#include "input.h"
#include "memory.h"

/*Graphic.c*/
extern unsigned int GpuInfoAddr;  			/*GPU信息首地址*/
extern volatile unsigned char *GpuBufAddr;  	/*GPU缓存首地址*/
extern unsigned char font[256];				/*字体首地址*/

//系统定义的颜色

extern RGB_24Bit colorF;				//前景色 = 白色
extern RGB_24Bit colorB;				//background color
extern RGB_24Bit colorBlack;		//黑色
extern RGB_24Bit colorWrite;		//白色
extern RGB_24Bit colorRed;			//红色
extern RGB_24Bit colorGreen;		//绿色
extern RGB_24Bit colorBule;		//蓝色
extern RGB_24Bit  transparent;	//透明

extern s32 os_top ;					//全局位置指针（屏幕显示）os_printf 的指针.这两个全局变量指向os_printf的位置
extern s32 os_left ;

extern struct pic_layer_table *PicLayerTable;
extern int MouseHaldle;													//鼠标句柄,可以通过这个全局变量移动鼠标显示的位置
extern int DesktopHandle;												//背景桌面的句柄(用作对背景图层的操作)

/*timer.c*/
extern os_timer_ctrl_st os_timer_ctrl;		//timer ctrl
extern arm_timer_t *ArmTimer;

extern char timer_time_out_p[5];						//系统最多可设置255个timer, 设置的timer到了预定时间就会向这个缓冲区发送timer的id
extern char * timer_time_out ;
extern FIFO8  time_out_p;
extern FIFO8  * time_out ;										//fifo缓冲区

/*debug.c*/
extern u32 form1_handle ;

/*task.c*/
extern TASK_GLOBAL task_global;						//任务管理的全局变量, 调度函数会

/*UART.c*/
//extern char input_buf_p[input_size];
extern char * input_buf ;									//input fifo缓冲区
extern FIFO8  input_p;
extern FIFO8  * input;

/*memory.c*/
extern struct free_memory_table_s  FreeMemoryTables_p;			//管理内存的结构体
extern struct free_memory_table_s  *FreeMemoryTables;

#endif

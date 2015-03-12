 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.h
*   鼠标键盘
*
* * OS One - A simple OS for Raspberry Pi
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
 

#ifndef _INPUT_H
#define _INPUT_H

#include "stdtype.h"
#include "Global.h"
#include "Graphic.h"
#include "UART.h"

#define input_size 64						//input缓冲区

typedef enum{
	fifo_null,
	fifo_key,
	fifo_mouse
}input_fifo_msg;

typedef struct{
	u8 key;						//键盘按键码
	u8 button;				//鼠标按键 1 左键  2 右键
	s8 x;							//鼠标left
	s8 y;							//鼠标top
}input_status_s;

input_status_s input_status;		//input状态

struct picture MousePic;			//鼠标指针图片
RGB_24Bit mcursor[256];			//鼠标指针图片缓冲区

void input_fifo_dispose(void);		//输入信号处理  (暂时没有完成, 也没有被调用)
void init_mouse_cursor(RGB_24Bit * to_addr, u32 top, u32 left);	//鼠标指针画到所给图层
void input_mouse_init(void);			//初始化鼠标


#endif

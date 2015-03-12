/*
*	2014年12月27日09:35:46
*	V1.0 	By Breaker
*
*	文件名：GPU.h
*    	定义GPU相关的地址 声明结构体 声明相关函数
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

#define GPU_BASE 	0x2000B880
#define GPU_Read	0x2000B880	
#define GPU_Poll 	0x2000B890
#define GPU_Sender 	0x2000B894
#define GPU_Status 	0x2000B898
#define GPU_Config 	0x2000B89C
#define GPU_Write 	0x2000B8A0

struct FrameBufferInfoS
{
	unsigned int phyWidth; 				/* #0 Physical Width */
	unsigned int phyHeight;  			/* #4 Physical Height */
	unsigned int virWidth; 					/* #8 Virtual Width */
	unsigned int virHeight; 				/* #12 Virtual Height */
	volatile unsigned int Pitch; 		/* #16 GPU - Pitch */
	unsigned int bitDepth; 				/* #20 Bit Depth */
	volatile unsigned int x; 				/* #24 X */
	volatile unsigned int y; 				/* #28 Y */
	volatile unsigned int bufPointer; 		/* #32 GPU - Pointer， GPU会更改此值，GPU为缓冲区分配的首地址*/
	volatile unsigned int bufSize; 				/* #36 GPU - Size ， GPU会更改此值，GPU为缓冲区分配内存的大小*/
};



extern struct FrameBufferInfoS FrameBufferInfo;

unsigned int init_GPU(unsigned int width, unsigned int height, unsigned int bitDepth);			//初始化

int GPU_SendMail(unsigned int GPU_MSG, unsigned int channel);														//发送mail
unsigned int GPU_RecMail(unsigned int channel);																						//接受mail



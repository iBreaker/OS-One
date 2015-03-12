 /****
*	2015年02月26日18:39:30
*	V1.0 	By Breaker
*
*	文件名：fifo.h
*      队列
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

 
#ifndef _FIFO_H
#define _FIFO_H

//管理fifo的结构体
typedef struct
{
	char *buf;
	int  put_p,get_p,size,free,count;
}FIFO8;


void fifo_init( FIFO8 * fifo8,char * buf,int size);		//初始化
void fifo_put( FIFO8 * fifo8,char data);						//如队列
char fifo_get( FIFO8 * fifo8);											//出队列

#endif

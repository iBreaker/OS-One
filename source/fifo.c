 /*
*	2015年02月26日18:39:30
*	V1.0 	By Breaker
*
*	文件名：fifo.c
*   队列
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
 

#include "fifo.h"

/*****************************************************
*	2015年03月11日16:58:41
*	V1.0 	By Breaker
*
*	 void fifo_init( FIFO8 * fifo8,char * buf,int size)
*      fifo初始化
*	return   void
*/

/*****************************************************
*	2015年03月11日16:58:41
*	V1.0 	By Breaker
*
*	 void fifo_init( FIFO8 * fifo8,char * buf,int size)
*      fifo初始化
*	return   void
*/
void fifo_init( FIFO8 * fifo8,char * buf,int size)
{
	fifo8->buf = buf;
	fifo8->put_p = 0;
	fifo8->get_p = 0;
	fifo8->size = size;
	fifo8->count = 0;
	fifo8->free = fifo8->size - fifo8->count;
}

/*****************************************************
*	2015年03月11日16:58:41
*	V1.0 	By Breaker
*
*	 void fifo_put( FIFO8 * fifo8,char * buf,int size)
*      放入队列
*	return   void
*/
void fifo_put( FIFO8 * fifo8,char  data)
{
	//binfo = (struct BOOTINFO *) ADR_BOOTINFO;

	if(fifo8->free <= 0)  //队列满则不添加新的元素
	{
		return;
	}

	fifo8->buf[fifo8->put_p] = data;  //先添加数据，然后移动指针
	if(fifo8->put_p >= (fifo8-> size-1))
	{
		fifo8->put_p = 0;
	}
	else
	{
		fifo8->put_p++;
	}
	fifo8->count++;
	fifo8->free = fifo8->size - fifo8->count;

}

/*****************************************************
*	2015年03月11日16:58:41
*	V1.0 	By Breaker
*
*	 void fifo_get( FIFO8 * fifo8)
*      获取一个char类型的值
*	return   void
*/
char fifo_get( FIFO8 * fifo8)
{
	if(fifo8->count <= 0)	//队列空则返回0，调用get函数值钱必须检查count是否为零，否则会一直返回
	{
		os_printf("error");
		return 0;
	}

	char temp = fifo8->buf[fifo8->get_p];  //先保存数据，然后移动指针
	if(fifo8->get_p >= (fifo8->size-1))
	{
		fifo8->get_p = 0;
	}
	else
	{
		fifo8->get_p++;
	}

	fifo8->count--;
	fifo8->free = fifo8->size - fifo8->count;
	return temp;
}

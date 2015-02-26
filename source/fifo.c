 /*
*	2015年02月26日18:39:30
*	V1.0 	By Breaker
*
*	文件名：fifo.c
*   队列
*/

#include "fifo.h"

void fifo_init( FIFO8 * fifo8,char * buf,int size)
{
	fifo8->buf = buf;
	fifo8->put_p = 0;
	fifo8->get_p = 0;
	fifo8->size = size;
	fifo8->count = 0;
	fifo8->free = fifo8->size - fifo8->count;
}
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

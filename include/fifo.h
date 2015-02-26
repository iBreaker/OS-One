 /*
*	2015年02月26日18:39:30
*	V1.0 	By Breaker
*
*	文件名：fifo.h
*   队列
*/

#ifndef _FIFO_H
#define _FIFO_H

typedef struct
{
	char *buf;
	int  put_p,get_p,size,free,count;
}FIFO8;


void fifo_init( FIFO8 * fifo8,char * buf,int size);
void fifo_put( FIFO8 * fifo8,char data);
char fifo_get( FIFO8 * fifo8);

#endif

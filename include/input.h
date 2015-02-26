 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.h
*   鼠标键盘
*/

#ifndef _INPUT_H
#define _INPUT_H

#include "UART.h"
#include "Global.h"

#define input_size 64

typedef struct{
	u8 key;
	u8 button;
	s8 x;
	s8 y;
}input_status_s;

input_status_s input_status;

void input_fifo_dispose(void);

#endif

 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.h
*   鼠标键盘
*/

#ifndef _INPUT_H
#define _INPUT_H

#include "stdtype.h"
#include "Global.h"
#include "Graphic.h"
#include "UART.h"

#define input_size 64

typedef enum{
	fifo_null,
	fifo_key,
	fifo_mouse

}input_fifo_msg;

typedef struct{
	u8 key;
	u8 button;
	s8 x;
	s8 y;
}input_status_s;

input_status_s input_status;

struct picture MousePic;
RGB_24Bit mcursor[256];

void input_fifo_dispose(void);
void init_mouse_cursor(RGB_24Bit * to_addr, u32 top, u32 left);
void input_mouse_init(void);


#endif

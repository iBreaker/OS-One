 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.c
*   鼠标键盘
*/

#include "input.h"
#include "UART.h"

/*
*	2015年02月26日20:22:05
*	V1.0 	By Breaker
*
*	void input_fifo_dispose(void)
*   	处理input信息
*	return
*/

void input_fifo_dispose(void)
{
	while(1)
	{
			/*
			while(input->count <= 0){}
			char rx =  fifo_get(input);

			//若0 =< temp <= 3 则为鼠标button 后两个为x y
			if( rx == 255)
			{
					while(input->count <= 0){}
					input_status.button =  fifo_get(input);

					while(input->count <=  0){}
					input_status.x = fifo_get(input);

					while(input->count <=  0){}
					input_status.y = fifo_get(input);

					DrawBlock(colorB,26, 0, 400,16);
					drawStringF("btn:%d x:%d y:%d key:%d ", colorF, 26, 10, input_status.button, input_status.x, input_status.y, input_status.key, input->count);
			}
			//否则是键盘数据
			else
			{
					input_status.key = rx;
					uart_putc(rx);
			}
			DrawBlock(colorB,26, 0, 400,16);
			drawStringF("btn:%d x:%d y:%d key:%d count:%d", colorF, 26, 10, input_status.button, input_status.x, input_status.y, input_status.key);
			*/
		sleep(100);
		DrawBlock(colorB,26, 0, 300,16);
		drawStringF("btn:%d x:%d y:%d key:%d ", colorF, 26, 10, input_status.button, input_status.x, input_status.y,  input_status.key);
		//fifo_get(input);
	}
}

void input_keyboard(void)
{

}

void input_mouse(void)
{

}


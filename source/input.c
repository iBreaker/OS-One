 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.c
*   鼠标键盘
*/

#include "input.h"
#include "stdtype.h"
#include "Global.h"
#include "Graphic.h"
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
		DrawBlock((RGB_24Bit * )GpuBufAddr, colorB,26, 0, 300,16);
		drawStringF((RGB_24Bit * )GpuBufAddr, "btn:%d x:%d y:%d key:%d ", colorF, 26, 10, input_status.button, input_status.x, input_status.y,  input_status.key);
		//fifo_get(input);
	}
}

void input_keyboard(void)
{

}


void init_mouse_cursor(RGB_24Bit * to_addr, u32 top, u32 left)
{

	char cursor[16][16] = {
		"**..............",
		"*O*.............",
		"*OO*............",
		"*OOO*...........",
		"*OOOO*..........",
		"*OOOOO*.........",
		"*OOOOOO*........",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOOOOOOO*.....",
		"*OOOOOO****.....",
		"*OO**OO*........",
		"*O*..*O*........",
		"**...*O*........",
		"*.....*O*.......",
		"......***.......",
	};
	int x, y;
	for (y = 0; y < 16; y++)
	{
		for (x = 0; x < 16; x++)
		{
			if (cursor[y][x] == '.')
			{
				DrawDot_to_layer(to_addr, transparent, 16, y, x);
			}
			else if (cursor[y][x] == '*')
			{
				DrawDot_to_layer(to_addr, colorWrite,16, y, x);
			}
			else if (cursor[y][x] == 'O')
			{
				DrawDot_to_layer(to_addr, colorBlack, 16, y, x);
			}
		}
	}
}
void input_mouse_init(void)
{
		MousePic.Position.top =  (screen_high / 2) - 16;
		MousePic.Position.left =  (screen_width / 2) - 16;
		MousePic.Position.width = 16;
		MousePic.Position.hight = 16;
		init_mouse_cursor((RGB_24Bit * )mcursor, 0, 0);
		MousePic.buf =  mcursor;

		int layer_index ;
		MouseHaldle = add_pic(MousePic);
		if(MouseHaldle != -1)
		{
			layer_index = add_pic_to_layer(MouseHaldle);
			os_printf("%n%d%n",layer_index );
			//pic_layer_reflash();
		}

		//set_pic_layer(MouseHaldle, MaxPicLayer - 3);
		//PicLayerTable->PicLayer[PicLayerTable->LayerCount].Empty = 0;
		//PicLayerTable->LayerCount++;

}


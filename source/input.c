 /*
*	2015年02月26日20:13:46
*	V1.0 	By Breaker
*
*	文件名：input.c
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
		sleep(100);
		DrawBlock(colorB,26, 0, 300,16);
		drawStringF("btn:%d x:%d y:%d key:%d ", colorF, 26, 10, input_status.button, input_status.x, input_status.y,  input_status.key);
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
		}
}


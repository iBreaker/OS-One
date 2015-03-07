/*
*	2015年03月06日15:57:01
*	V1.0 	By Breaker
*
*	文件名：form.c
*    	窗体
*/
#include "form.h"

/*****************************************************************
*	2015年03月06日16:04:50
*	V1.0 	By Breaker
*
*		void form1()
*
*		return void
*/
void form1()
{
	char x[9][9] = {
			"OO@@@@@OO",
			"OOO@@@OOO",
			"@OOO@OOO@",
			"@@OOOOO@@",
			"@@@OOO@@@",
			"@@OOOOO@@",
			"@OOO@OOO@",
			"OOO@@@OOO",
			"OO@@@@@OO",
	};

	rect frect;
	RGB_24Bit fcolor;
	struct picture	 fpic;

	//设定窗体大小
	fpic.Position.top = 200;
	fpic.Position.left = 200;
	fpic.Position.width = 300;
	fpic.Position.hight = 200;
	fpic.buf = os_malloc( 200 * 300 * 3);

	form1_handle = add_pic(fpic);
	add_pic_to_layer(form1_handle);
	//set_pic_to_top(MouseHaldle);

	DrawBlock_to_layer(fpic.buf, colorWrite, 300, 0, 0, 300, 200);
	RGB_24Bit color;
	color.R = 0;
	color.G = 200;
	color.B = 0;
	DrawBlock_to_layer(fpic.buf, color, 300, 0, 0, 300, 30);
	DrawBlock_to_layer(fpic.buf, colorRed, 300, 0, 300 - 5 - 25, 25, 20);
	//DrawBlock_to_layer(fpic.buf, colorBlack, 300, 6, 300 - 5 - 25 + 8, 9, 9);
	int top = 7;
	int left = 20;
	char str[10] = "360 Safe";

	drawString_to_layer(fpic.buf , str , colorWrite , 300, &top, &left);

	int i ,j ;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
				if(x[i][j] == 'O')
				{
					DrawDot_to_layer(fpic.buf , colorWrite, 300, 6 + i, 278 + j);
				}
		}
	}
	//pic_layer_reflash_rect(200, 200, 300, 200);
	//while(is_inside(frect.top, frect.left, frect.width, frect.hight, input_status.y, input_status.x))
}

void form1_dispose()
{
	static u8 mouse_status = 0;
	static u32 top, left;
	if( input_status.button == 0)
	{
			if(mouse_status == 1)
			{
				//os_printf("@%d %d %d", PicLayerTable->Picture[MouseHaldle].Position.top, top,  PicLayerTable->Picture[MouseHaldle].Position.top - top);
				move_pic_layer( PicLayerTable->Picture[MouseHaldle].Position.top - top,  PicLayerTable->Picture[MouseHaldle].Position.left - left, form1_handle, absolute);

			}
			mouse_status = 0;
	}

	bool is = is_inside (PicLayerTable->Picture[form1_handle].Position.top, PicLayerTable->Picture[form1_handle].Position.left, PicLayerTable->Picture[form1_handle].Position.width, PicLayerTable->Picture[form1_handle].Position.hight, PicLayerTable->Picture[MouseHaldle].Position.left, PicLayerTable->Picture[MouseHaldle].Position.top );

	if(is)
	{
		//os_printf("%d %d %d %d %d %d %d %d %n", is, PicLayerTable->Picture[form1_handle].Position.top, PicLayerTable->Picture[form1_handle].Position.left, PicLayerTable->Picture[form1_handle].Position.width, PicLayerTable->Picture[form1_handle].Position.hight, PicLayerTable->Picture[MouseHaldle].Position.left, PicLayerTable->Picture[MouseHaldle].Position.top, input_status.button);
			if(input_status.button == 1)
			{
				if(mouse_status == 0)
				{

					top = PicLayerTable->Picture[MouseHaldle].Position.top - PicLayerTable->Picture[form1_handle].Position.top;
					//os_printf("+%d", top);
					left = PicLayerTable->Picture[MouseHaldle].Position.left - PicLayerTable->Picture[form1_handle].Position.left;
				}
				mouse_status = 1 ;
			}

	}
}

bool textbox()
{
	return true;
}

bool button()
{
	return true;
}

bool ctrlbox()
{
	return true;
}


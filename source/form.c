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
	//右上角x的图像
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

	rect frect;												//窗口矩形
	struct picture	 fpic;

	//设定窗体大小
	fpic.Position.top = 200;
	fpic.Position.left = 200;
	fpic.Position.width = 300;
	fpic.Position.hight = 200;
	fpic.buf = os_malloc( 200 * 300 * 3);			//申请内存存放窗体图像信息

	form1_handle = add_pic(fpic);
	add_pic_to_layer(form1_handle);					//将fpic加入最上层

	DrawBlock_to_layer(fpic.buf, colorWrite, 300, 30, 0, 300, 200);	//白色底色

	RGB_24Bit color;																						//标题栏,暗绿色
	color.R = 0;
	color.G = 200;
	color.B = 0;

	DrawBlock_to_layer(fpic.buf, color, 300, 0, 0, 300, 30);					//画出标题栏
	DrawBlock_to_layer(fpic.buf, colorRed, 300, 0, 300 - 5 - 25, 25, 20);		//画出关闭按钮底色
	DrawBlock_to_layer(fpic.buf, colorRed, 300, 200 - 46 , 200 , 37 , 37);		//reboot按钮底色

	//写标题
	int top = 7;
	int left = 20;
	char str[14] = "Kernel status";
	drawString_to_layer(fpic.buf , str , colorWrite , 300, &top, &left);
	top = 35; left = 5;

	//窗体内容
	drawString_to_layer(fpic.buf , "Task status" , colorRed , 300, &top, &left);
	top += 5;
	int current_TRID  = ll_get_head_id(task_ready);
	while(0  != current_TRID  )
	{
			top += 16; left = 10;
			u8 TID = task_ready->node[current_TRID].value;
			current_TRID = ll_get_next_id(task_ready, current_TRID);
	}

	top += 5;
	top += 16, left = 5;
	drawString_to_layer(fpic.buf , "Input status" , colorRed , 300, &top, &left);

	top += 5;
	top += 16, left = 10;
	top += 5;
	top += 16, left = 5;
	drawString_to_layer(fpic.buf , "Memory status" , colorRed , 300, &top, &left);



	//画出关闭按钮("X")
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

	//刷新窗体(将内存中的图像信息线输出来)
	pic_layer_reflash_rect(PicLayerTable->Picture[form1_handle].Position.top, PicLayerTable->Picture[form1_handle].Position.left, PicLayerTable->Picture[form1_handle].Position.width, PicLayerTable->Picture[form1_handle].Position.hight);

	//当接收到Task1的消息, 就刷新
	while(true)
	{
		top = 35; left = 5;
		top += 5;
		int current_TRID  = ll_get_head_id(task_ready);		//第一个任务的TRID
		while(0  != current_TRID  )
		{
				top += 16; left = 10;
				u8 TID = task_ready->node[current_TRID].value;
				DrawBlock_to_layer(fpic.buf, color, 300, top,  left, 280, 16);
				if( current_TRID == 1)
				{
					drawStringF_to_layer(fpic.buf , "TASK%d stack: */1024 Byte free", colorBlack , 300, top, left, TID );
				}
				else
				{
					drawStringF_to_layer(fpic.buf , "TASK%d stack: %d/1024 Byte free", colorBlack , 300, top, left, TID, (u32)(  (u32)task_table[TID].sp - (u32)task_stack[TID] )  );
				}
				pic_layer_reflash_rect(PicLayerTable->Picture[form1_handle].Position.top + top, PicLayerTable->Picture[form1_handle].Position.left + left, 280, 16);
				current_TRID = ll_get_next_id(task_ready, current_TRID);
		}

		top += 5;
		top += 16, left = 5;
		top += 5;
		top += 16, left = 10;
		DrawBlock_to_layer(fpic.buf, color, 300, top,  left, 280, 16);
		drawStringF_to_layer(fpic.buf , "top:%d left:%d Button:%d Key:%d", colorBlack , 300, top, left, PicLayerTable->Picture[MouseHaldle].Position.top, PicLayerTable->Picture[MouseHaldle].Position.left, input_status.button, input_status.key );
		pic_layer_reflash_rect(PicLayerTable->Picture[form1_handle].Position.top + top, PicLayerTable->Picture[form1_handle].Position.left + left, 280, 16);


		top += 5;
		top += 16, left = 5;
		top += 5;
		top += 16, left = 10;
		DrawBlock_to_layer(fpic.buf, color, 300, top,  left, 100, 16);
		drawStringF_to_layer(fpic.buf , "%d/%d M ", colorBlack , 300, top, left, total_free_memory_size()/(1024 * 1024), FreeMemoryTables->size/(1024 * 1024));
		pic_layer_reflash_rect(PicLayerTable->Picture[form1_handle].Position.top + top, PicLayerTable->Picture[form1_handle].Position.left + left, 100, 16);


		MSG_s _msg = task_recevie_msg();
		DrawBlock_to_layer(PicLayerTable->Picture[DesktopHandle].buf  , colorB, screen_width, 0,  5 + 150, 150, 16);
		drawStringF_to_layer(PicLayerTable->Picture[DesktopHandle].buf , "Task2 Rev %d" , colorWrite , screen_width, 0,  5 + 150 , _msg.value);
		pic_layer_reflash_rect(0, 5 + 150, 150, 32);

	}
}

extern void reboot(void);

//窗体队鼠标的响应
void form1_dispose()
{
	static u8 mouse_status = 255;
	static u32 top, left;
	if( input_status.button == 0)
	{
			if(mouse_status == 1)
			{
				//拖放操作松开的处理->移动窗体
				move_pic_layer( PicLayerTable->Picture[MouseHaldle].Position.top - top,  PicLayerTable->Picture[MouseHaldle].Position.left - left, form1_handle, absolute);
			}
			mouse_status = 0;
	}

	//判断鼠标是否在标题栏
	bool is = is_inside (PicLayerTable->Picture[form1_handle].Position.top, PicLayerTable->Picture[form1_handle].Position.left, PicLayerTable->Picture[form1_handle].Position.width, 30, PicLayerTable->Picture[MouseHaldle].Position.left, PicLayerTable->Picture[MouseHaldle].Position.top );
	if(is) //鼠标在窗体标题栏上
	{
			if(input_status.button == 1)
			{
				if(mouse_status == 0)
				{
					//拖放开始
					top = PicLayerTable->Picture[MouseHaldle].Position.top - PicLayerTable->Picture[form1_handle].Position.top;
					left = PicLayerTable->Picture[MouseHaldle].Position.left - PicLayerTable->Picture[form1_handle].Position.left;
				}
				mouse_status = 1 ;
			}
	}
	//else if(is_inside (PicLayerTable->Picture[form1_handle].Position.top + 200 - 46, PicLayerTable->Picture[form1_handle].Position.left + 200, 37, 37, PicLayerTable->Picture[MouseHaldle].Position.left, PicLayerTable->Picture[MouseHaldle].Position.top ));
	//鼠标在重启按钮上
	/*
	{
			if(input_status.button == 1)
			{
				if(mouse_status == 0)
				{
						reboot();
				}
				mouse_status = 1 ;
			}
	}*/
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


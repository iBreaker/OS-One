 /*
*	2014年12月31日16:11:30
*	V1.0 	By Breaker
*
*	文件名：debug.c
*      各个模块调试函数
*	
** OS One - A simple OS for Raspberry Pi
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
 
#include "debug.h"
#include "gpio.h"
#include "GPU.h"
#include "time.h"
#include "Graphic.h"
#include "Global.h"
#include "linkedlist.h"
#include "task.h"
#include "UART.h"
#include "memory.h"
#include "input.h"
#include "form.h"


void deb_linedlist_reflash(LinkedList *Task);
void task1();
void task2();

/*debug.c 全局变量*/
u32 form1_handle;

/*
*	2014年12月31日16:12:49
*	V1.0 	By Breaker
*
*	void  deb_GPIO(void)
*      GPIO闪烁
*	return   void
*/
void  deb_GPIO(void)
 {
	//使LED灯闪烁
	 while(1)
	{
		sleep(1000);
		blink_GPIO19();
		sleep(1000);
		blink_GPIO16();
	}
}

/*
*	2014年12月31日16:21:44
*	V1.0 	By Breaker
*
*	void  deb_screen(void)
*      画出图案
*	return   void
*/
void  deb_screen(void)
 {
	RGB_24Bit color; //定义颜色
	color.R = 0xFF;
	color.G = 0x00;
	color.B = 0x00;

	int top,left;
	top = 40;
	left = 20;
	DrawBlock(color,0,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth) ,1);
	DrawBlock(color,0,0,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight) );
	DrawBlock(color,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth)-1,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight));
	DrawBlock( color,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight)-1,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth),1);
	
	color.R = 0xFF;
	color.G = 0xFF;
	color.B = 0xFF;
	
	/*2015年01月01日22:59:23  真是一个奇怪的bug，函数参数不能有double类型。Why*/
	drawStringF("123:%%d%d,%%x%x,%%b%b",color,  top, left ,123,123,123);

}
 
/*
*	2014年1月3日16:21:44
*	V1.0 	By Breaker
*
*	void  deb_os_printf(void)
*      格式化输出
*	return   void
*/
 void  deb_os_printf (void)
 {
	 os_printf ("123:%%d%d,%%x%x,%%b%b",123,123,123);
	 os_printf ("%n");
	os_printf ("123:%%d%d,%%x%x,%%b%b",123,123,123); 
 }


 
/*****************************************************
*	2015年01月14日14:24:53
*	V1.0 	By Breaker
*
*	 void  deb_timer(void)
*      定时器
*	return   void
**/
void  deb_timer(void)
{
	init_os_timer_ctrl();
	set_os_timer(2000,1100);						//首次20秒, 之后每隔11秒
	set_os_timer(1100,1200);						//首次11秒, 之后每隔12秒
	set_os_timer(2000,0);							//一次性定时器, 20秒
	set_os_timer(1100,0);							//一次性定时器, 11秒
}

void deb_timer_refalsh(void)
{
	RGB_24Bit color_b;
	color_b.R = 0x28;
	color_b.G = 0x82;
	color_b.B = 0xE6;
	
	DrawBlock( color_b, 0, 0 , 1440, 900);
	
	RGB_24Bit color;
	color.R = 0xFF;
	color.G = 0x00;
	color.B = 0x00;
	
	int i;
	int left,top;
	left = 0; top = 0;
	
	drawStringF("value:%d", color, 0, 700, os_timer_ctrl.value);
	
	for(i=0; i<256; i++)
	{
		drawStringF( "> %d", color, top, left, i);
		left += 48;
		drawStringF("%d", color,top, left, os_timer_ctrl.os_timer_t[i].value);
		left += 64;
		drawStringF("%d", color,top, left , os_timer_ctrl.os_timer_t[i].load);
		left += 64;
		drawStringF( "%d", color,top, left, os_timer_ctrl.os_timer_t[i].next_os_timer_id);
		
		left = 0;
		top += 16;
	}
}

 /*****************************************************
*	2015年01月22日09:18:15
*	V1.0 	By Breaker
*
*	 void  deb_linedlist(void)
*      调试链表
*	return   void
*/
 void  deb_linedlist(void)
 {
	 LinkedList task;										//定义一个名为task的链表
	 LinkedList *Task = & task;
	 ll_init(Task);												//初始化
	 
	 ll_add_to_head(Task,1);						//像task链表头部加入1
	 ll_add_to_head(Task, 2);
	 ll_add_to_head(Task, 3);
	 ll_add_to_head(Task, 5);
	 ll_add_to_tail(Task, 6);							//像task链表尾部加入6
	 ll_add_to_tail(Task, 7);
	 
	 ll_add_by_order(Task, 8, 4);
	 ll_add_after_id(Task, 9, 3);					//加到9号后面
	 
	 ll_add_to_head(Task, 0);
	 ll_add_to_head(Task, 0);
	 ll_add_to_head(Task, 0);
	 ll_add_by_order(Task, 8, 4);
	 
	 ll_remove_by_id(Task, 4);
	 ll_remove_tail(Task);
	 ll_remove_head(Task);
	
	 deb_linedlist_reflash(Task);
 }
 
 void deb_linedlist_reflash(LinkedList *Task)
 {
	 int i = 0;
	  os_printf("%n");
	 while(0 != Task->node[i].next ||  0 != Task->node[i].prior || 0 != Task->node[i].value)
	 {
		os_printf("%d - %d   %d   %d   %d   %d   %d   %d   %d   %n", i,Task->node[i].prior, Task->node[i].next, Task->node[i].value, Task->ctrl.count, Task->ctrl.head, Task->ctrl.tail, Task->ctrl.min, Task->ctrl.max);
		i = ll_get_next_id(Task, i);
	 }
 }
 
 /*****************************************************
*	2015年01月24日10:13:29
*	V1.0 	By Breaker
*
*	 void  deb_task(void)
*      调试多任务
*	return   void
*/


void  deb_task(void)
{
		u8 rank = 3;
		u32 func = (u32) dbg_UART;
		u8 TID = task_create(rank , func);					//获取TID
		task_run(TID);														//加入就绪表


		func = (u32) deb_GPIO;
		TID = task_create(rank , func);
		task_run(TID);

		while(1);
}

void task1()
{
	RGB_24Bit colorF;
	colorF.R = 0xff;
	colorF.G = 0xff;
	colorF.B = 0xff;
	RGB_24Bit colorB;
	colorB.R = 0x28;
	colorB.G = 0x82;
	colorB.B = 0xE6;

		while(1)
		{
				static u32 task1u32 = 0;
				os_printf("-sleep start-");
				sleep(1000);
				os_printf("-sleep end-");
				//GPIO_SET_GPSET(16);
				//blink_GPIO16();
				task_send_msg(3, MSG_NORMAL, task1u32);
				task1u32 ++;
				//DrawBlock(colorB,10, 0, 200,16);
				//drawStringF("Task1:%d", colorF, 10, 10, task1u32 ++ );
		}
}

void task2()
{
		RGB_24Bit colorF;
		colorF.R = 0x00;
		colorF.G = 0x00;
		colorF.B = 0x00;
		RGB_24Bit colorB;
		colorB.R = 0x28;
		colorB.G = 0x82;
		colorB.B = 0xE6;

		while(1)
		{
				//static u32 task2u32 = 0;
			 	 u32 task2u32;
				//GPIO_SET_GPCLR(16);
			 	blink_GPIO16();
			 	os_printf("-receive start-");
				MSG_s  _MSG = task_recevie_msg();
				os_printf("-receive end-");
				task2u32 = _MSG.value ;
				DrawBlock(colorB,10, 0, 200,16);
				drawStringF( "Task1:%d", colorF, 10, 10, task2u32 );
		}
}


/*****************************************************
*	2015年02月24日18:03:44
*	V1.0 	By Breaker
*
*	 void  UART_dbg(void)
*      调试UART
*	return   void
*/
void dbg_UART()
{
	input_fifo_dispose();
}
 
/*****************************************************
*	2015年02月27日11:30:18
*	V1.0 	By Breaker
*
*	 void  UART_dbg(void)
*      调试UART
*	return   void
*/
void dbg_memory(void)
{
	os_printf("init:%d%n",total_free_memory_size());
	
	os_printf("GpuBufAddr:%d%n",(u32)GpuBufAddr / (1024 *1024));
	os_printf("free all:%d%n",total_free_memory_size()/ (1024 *1024));
	os_malloc(0x100);
	os_printf("malloc 0x100:%d%n",total_free_memory_size() / (1024 *1024));
	os_malloc(0x100000);
	os_printf("malloc 0x100000:%d%n",total_free_memory_size() / (1024 *1024));
	os_malloc(0x1000000);
	os_printf("malloc 0x1000000:%d%n",total_free_memory_size() / (1024 *1024));
	
}

/*****************************************************
*	2015年02月27日13:00:46
*	V1.0 	By Breaker
*
*	 void  dbg_input(void)
*      调试鼠标键盘
*	return   void
*/
void dbg_input(void)
{
		input_mouse_init();
		input_fifo_msg input_msg;

		while( 1)
		{
			if(input->count == 0 )
				continue;
			input_msg =  fifo_get(input) ;
			if( input_msg != fifo_mouse)
				continue;
			move_pic_layer( -(s8)input_status.y, (s8)input_status.x, MouseHaldle, relative);				//移动鼠标
			form1_dispose();   //将鼠标信号传入form1,让form1处理
		}

}

/*****************************************************
*	2015年03月06日17:59:26
*	V1.0 	By Breaker
*
*	 void  dbg_bmp(void)
*      显示bmp文件
*	return   void
*/
void dbg_bmp(void)
{
	extern char bmp;
	struct picture bmp_pic;

	bmp_pic.Position.hight = 16;
	bmp_pic.Position.width = 16;
	bmp_pic.Position.top = 300;
	bmp_pic.Position.left = 300;

	u32 to = (u32)os_malloc(16 * 16 * 3);
	copy_bmp_to_piclayer((u32)&bmp, to);

	bmp_pic.buf = (RGB_24Bit *)to;
	u32 handle = add_pic(bmp_pic);
	add_pic_to_layer(handle);
	pic_layer_reflash_rect(bmp_pic.Position.top,bmp_pic.Position.left,bmp_pic.Position.width, bmp_pic.Position.hight);
}




/*****************************************************
*	2015年03月07日16:54:05
*	V1.0 	By Breaker
*
*	 void  dbg_form(void)
*      窗口
*	return   void
*/
void dbg_form(void)
{
	form1();
}

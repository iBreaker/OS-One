 /*
*	2014年12月31日16:11:30
*	V1.0 	By Breaker
*
*	文件名：debug.c
*      各个模块调试函数
*	
*/
#include "debug.h"
#include "gpio.h"
#include "GPU.h"
#include "time.h"
#include "Graphic.h"
#include "Global.h"
#include "csud.h"
#include "linkedlist.h"
#include "task.h"

void deb_linedlist_reflash(LinkedList *Task);
void task1();
void task2();
void task3();

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
	 while(1)
	{	
		sleep(1000);
		GPIO_SET_GPCLR(16);
		sleep(1000);
		GPIO_SET_GPSET(16);
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
	RGB_24Bit color;
	color.R = 0xFF;
	color.G = 0x00;
	color.B = 0x00;
	float A = 3.14;
	int top,left;
	top = 40;
	left = 20;
	DrawBlock(color,0,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth) ,1);
	DrawBlock(color,0,0,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight) );
	DrawBlock(color,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth)-1,1,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight));
	DrawBlock(color,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyHeight)-1,0,(((struct FrameBufferInfoS *)GpuInfoAddr) -> phyWidth),1);
	
	color.R = 0xFF;
	color.G = 0xFF;
	color.B = 0xFF;
	
	/*2015年01月01日22:59:23  真是一个奇怪的bug，函数参数不能有double类型。Why*/
	drawStringF("123:%%d%d,%%x%x,%%b%b",color,  top, left ,123,123,123);

}
 
 void  deb_os_printf (void)
 {
	 os_printf ("123:%%d%d,%%x%x,%%b%b",123,123,123);
	 os_printf ("%n");
	os_printf ("123:%%d%d,%%x%x,%%b%b",123,123,123); 
 }
/*****************************************************
*	2015年01月03日14:38:20
*	V1.0 	By Breaker
*
*	 void  deb_keyboard(void)
*      usb键盘
*	return   void
**/
 void  deb_keyboard(void)
 {
	RGB_24Bit color;
	color.R = 0xFF;
	color.G = 0x00;
	color.B = 0x00;
	unsigned int top, left;
	top = 400;
	left = 0;
	
	while(1)
	 {
		char unsigned key = 0;
		//KeyboardUpdate();
		//key = KeyboardGetChar();
		 if(key != 0)
		 {
			GPIO_SET_GPCLR(16);
		 }
		 else
		 {
			 
		 }
		 
	 }
 }
 
/*****************************************************
*	2015年01月14日14:24:53
*	V1.0 	By Breaker
*
*	 void  deb_timer(void)
*      画出图案
*	return   void
**/
void  deb_timer(void)
{
	init_os_timer_ctrl();
	set_os_timer(2000,1100);
	set_os_timer(1100,1200);
	set_os_timer(2000,0);
	set_os_timer(1100,0);
}

void deb_timer_refalsh(void)
{
	RGB_24Bit color_b;
	color_b.R = 0x28;
	color_b.G = 0x82;
	color_b.B = 0xE6;
	
	DrawBlock(color_b, 0, 0 , 1440, 900);
	
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
		drawStringF("> %d", color, top, left, i);
		left += 48;
		drawStringF("%d", color,top, left, os_timer_ctrl.os_timer_t[i].value);
		left += 64;
		drawStringF("%d", color,top, left , os_timer_ctrl.os_timer_t[i].load);
		left += 64;
		drawStringF("%d", color,top, left, os_timer_ctrl.os_timer_t[i].next_os_timer_id);
		
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
	 LinkedList task;
	 LinkedList *Task = & task;
	 ll_init(Task);
	 
	 ll_add_to_head(Task,1);
	 ll_add_to_head(Task, 2);
	 ll_add_to_head(Task, 3);
	 ll_add_to_head(Task, 5);
	 ll_add_to_tail(Task, 6);
	 ll_add_to_tail(Task, 7);
	 
	 ll_add_by_order(Task, 8, 4);
	 ll_add_after_id(Task, 9, 3);
	 
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
		u32 func = (u32) task1;
		u8 TID = task_create(rank , func);
		task_run(TID);

		func = (u32) task2;
		TID = task_create(rank , func);
		task_run(TID);

		//func = (u32) task3;
		//TID = task_create(rank , func);
		//task_run(TID);

		//task3();
		//task_manager();
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
				drawStringF("Task1:%d", colorF, 10, 10, task2u32 );
		}
}

void task3()
{

}

 

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
		KeyboardUpdate();
		key = KeyboardGetChar();
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
void task1_func(void);
void task2_func(void);

void  deb_task(void)
{
	 //TS task1,task2;
	 //task1.pc = (u32)(&task1);
	 //task1.sp = (256 * (1024 * 1024));
	 u32 sp = 256 * (1024 * 1024);
	 task_init(&task1, sp, &task1_func);
	 
	 sp -=  (1024 * 1024);
	 task_init(&task2, sp, &task2_func);
	  //asm("nop");
	 task1_func();
}

void task1_func(void)
{
	while(1)
	{
		asm("LDR r0, %[cpsr]" :  : [cpsr]"m"(task1.cpsr)); 
		asm("MSR cpsr, r0"); 
		asm("LDR r0, %[spsr]" :  : [spsr]"m"(task1.spsr)); 
		asm("MSR spsr, r0"); 
		asm("LDR r0, %[r0]" :  : [r0]"m"(task1.r0));
		asm("LDR r1, %[r1]" :  : [r1]"m"(task1.r1)); 
		asm("LDR r2, %[r2]" :  : [r2]"m"(task1.r2)); 
		asm("LDR r3, %[r3]" :  : [r3]"m"(task1.r3)); 
		asm("LDR r4, %[r4]" :  : [r4]"m"(task1.r4)); 
		asm("LDR r5, %[r5]" :  : [r5]"m"(task1.r5)); 
		asm("LDR r6, %[r6]" :  : [r6]"m"(task1.r6)); 
		asm("LDR r7, %[r7]" :  : [r7]"m"(task1.r7)); 
		asm("LDR r8, %[r8]" :  : [r8]"m"(task1.r8)); 
		asm("LDR r9, %[r9]" :  : [r9]"m"(task1.r9)); 
		asm("LDR r10, %[r10]" :  : [r10]"m"(task1.r10)); 
		asm("LDR r11, %[r11]" :  : [r11]"m"(task1.r11)); 
		asm("LDR r12, %[r12]" :  : [r12]"m"(task1.r12)); 
		asm("LDR sp, %[sp]" :  : [sp]"m"(task1.sp)); 
		asm("LDR lr, %[lr]" :  : [lr]"m"(task1.lr)); 
		
		GPIO_SET_GPCLR(16);
		sleep(1000);
		
		asm("STR r0, %[r0]" :  : [r0]"m"(task1.r0));
		asm("STR r1, %[r1]" :  : [r1]"m"(task1.r1)); 
		asm("STR r2, %[r2]" :  : [r2]"m"(task1.r2)); 
		asm("STR r3, %[r3]" :  : [r3]"m"(task1.r3)); 
		asm("STR r4, %[r4]" :  : [r4]"m"(task1.r4)); 
		asm("STR r5, %[r5]" :  : [r5]"m"(task1.r5)); 
		asm("STR r6, %[r6]" :  : [r6]"m"(task1.r6)); 
		asm("STR r7, %[r7]" :  : [r7]"m"(task1.r7)); 
		asm("STR r8, %[r8]" :  : [r8]"m"(task1.r8)); 
		asm("STR r9, %[r9]" :  : [r9]"m"(task1.r9)); 
		asm("STR r10, %[r10]" :  : [r10]"m"(task1.r10)); 
		asm("STR r11, %[r11]" :  : [r11]"m"(task1.r11)); 
		asm("STR r12, %[r12]" :  : [r12]"m"(task1.r12)); 
		asm("STR sp, %[sp]" :  : [sp]"m"(task1.sp)); 
		asm("STR lr, %[lr]" :  : [lr]"m"(task1.lr)); 
		
		asm("LDR r0, %[cpsr]" :  : [cpsr]"m"(task2.cpsr)); 
		asm("MRS r0, cpsr"); 
		asm("LDR r0, %[spsr]" :  : [spsr]"m"(task2.spsr)); 
		asm("MRS r0, spsr"); 
		
		asm("LDR pc, %[pc]" :  : [pc]"m"(task2.pc)); 
	}
	
	//STR r1, *r1
	
}

void task2_func(void)
{
	while(1)
	{
		asm("LDR r0, %[cpsr]" :  : [cpsr]"m"(task2.cpsr)); 
		asm("MSR cpsr, r0"); 
		asm("LDR r0, %[spsr]" :  : [spsr]"m"(task2.spsr)); 
		asm("MSR spsr, r0"); 
		asm("LDR r0, %[r0]" :  : [r0]"m"(task2.r0));
		asm("LDR r1, %[r1]" :  : [r1]"m"(task2.r1)); 
		asm("LDR r2, %[r2]" :  : [r2]"m"(task2.r2)); 
		asm("LDR r3, %[r3]" :  : [r3]"m"(task2.r3)); 
		asm("LDR r4, %[r4]" :  : [r4]"m"(task2.r4)); 
		asm("LDR r5, %[r5]" :  : [r5]"m"(task2.r5)); 
		asm("LDR r6, %[r6]" :  : [r6]"m"(task2.r6)); 
		asm("LDR r7, %[r7]" :  : [r7]"m"(task2.r7)); 
		asm("LDR r8, %[r8]" :  : [r8]"m"(task2.r8)); 
		asm("LDR r9, %[r9]" :  : [r9]"m"(task2.r9)); 
		asm("LDR r10, %[r10]" :  : [r10]"m"(task2.r10)); 
		asm("LDR r11, %[r11]" :  : [r11]"m"(task2.r11)); 
		asm("LDR r12, %[r12]" :  : [r12]"m"(task2.r12)); 
		asm("LDR sp, %[sp]" :  : [sp]"m"(task2.sp)); 
		asm("LDR lr, %[lr]" :  : [lr]"m"(task2.lr));  
	
		GPIO_SET_GPSET(16);
		sleep(1000);
		
		asm("STR r0, %[r0]" :  : [r0]"m"(task2.r0));
		asm("STR r1, %[r1]" :  : [r1]"m"(task2.r1)); 
		asm("STR r2, %[r2]" :  : [r2]"m"(task2.r2)); 
		asm("STR r3, %[r3]" :  : [r3]"m"(task2.r3)); 
		asm("STR r4, %[r4]" :  : [r4]"m"(task2.r4)); 
		asm("STR r5, %[r5]" :  : [r5]"m"(task2.r5)); 
		asm("STR r6, %[r6]" :  : [r6]"m"(task2.r6)); 
		asm("STR r7, %[r7]" :  : [r7]"m"(task2.r7)); 
		asm("STR r8, %[r8]" :  : [r8]"m"(task2.r8)); 
		asm("STR r9, %[r9]" :  : [r9]"m"(task2.r9)); 
		asm("STR r10, %[r10]" :  : [r10]"m"(task2.r10)); 
		asm("STR r11, %[r11]" :  : [r11]"m"(task2.r11)); 
		asm("STR r12, %[r12]" :  : [r12]"m"(task2.r12)); 
		asm("STR sp, %[sp]" :  : [sp]"m"(task2.sp)); 
		asm("STR lr, %[lr]" :  : [lr]"m"(task2.lr)); 

		asm("MRS r0, cpsr"); 
		asm("STR r0, %[cpsr]" :  : [cpsr]"m"(task2.cpsr)); 
		asm("MRS r0, spsr"); 
		asm("STR r0, %[spsr]" :  : [spsr]"m"(task2.spsr)); 
		
		asm("LDR pc, %[pc]" :  : [pc]"m"(task1.pc));
	}
	
}
 

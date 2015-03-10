/*
*   	2014年12月25日10:58:18
*	V1.0 	By Breaker
*
*	文件名：main.c
*	程序的主函数，永远不返回
*	
*/

#include "gpio.h"
#include "timer.h"
#include "Graphic.h"
#include "debug.h"
#include "memory.h"
#include "Global.h"

/*这里不加volatile LED不会闪烁 Why？*/
volatile unsigned int tmp = 0;
	
/*程序的主函数，永远不返回*/
void os_main(void)
{
	/* init */
	momory_init(20 * (1024 * 1024), 490 * (1024 * 1024));		//堆内存从20M开始,共490M
	os_free(20 * (1024 * 1024), 490 * (1024 *1024));
	gpio_init();
	uart_init();
	task_init();
	init_arm_timer(Kernrl_100Hz);
	init_os_timer_ctrl();


	// 2014年12月13日18:13:10  刚才还没有初始化就开始使用图层表，结果发生了不可预知的错误，第二次犯这样的错误了。
	//init_screen(screen_width, screen_high, color_deep);
	PicLayerTable = PicLayerTable_init();  //初始化图层表
	init_screen_layer();
	_enable_interrupts();


	/* debug */
	
	//deb_screen();
	//deb_os_printf();
	//deb_GPIO();
	//deb_keyboard();
	//deb_timer();
	//deb_linedlist();
	//deb_task();
	//dbg_UART();
	//dbg_memory();
	
	pic_layer_reflash_rect(0,0,screen_width, screen_high);

	u8 rank = 3;
	u32 func = (u32) dbg_form;
	u8 TID = task_create(rank , func);
	task_run(TID);

	func = (u32) dbg_input;
	TID = task_create(rank , func);
	task_run(TID);

	//设置几个timer
	set_os_timer(2000,1100);			//20秒后触发一次, 之后每11秒触发一次
	set_os_timer(1100,1200);			//11秒后触发一次, 之后每12秒触发一次
	set_os_timer(2100,0);				//21秒后触发一次,然后被回收
	set_os_timer(1200,0);				//12秒后触发一次,然后被回收



	while(1)
	{
		static u32 task1u32 = 0;
		sleep(1000);
		blink_GPIO16();
		task_send_msg(2, MSG_NORMAL, task1u32);
		DrawBlock_to_layer(PicLayerTable->Picture[DesktopHandle].buf  , colorB, screen_width, 0,  5, 150, 16);
		drawStringF_to_layer(PicLayerTable->Picture[DesktopHandle].buf , "Task1 Send %d" , colorWrite , screen_width, 0, 5, task1u32);
		pic_layer_reflash_rect(0, 5, 150, 32);
		task1u32 ++;


		while(time_out->count != 0)
		{
				DrawBlock_to_layer(PicLayerTable->Picture[DesktopHandle].buf  , colorB, screen_width, 0,  screen_width - 150, 150, 16);
				drawStringF_to_layer(PicLayerTable->Picture[DesktopHandle].buf , "Timer%d Time Out" , colorRed , screen_width, 0, screen_width - 150, fifo_get(time_out) );
				pic_layer_reflash_rect(0, screen_width - 150, 150, 32);
		}

	}
	;
}

void exit(int code)
{
	while(1)
	;
}

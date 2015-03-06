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
	momory_init(20 * (1024 * 1024), 490 * (1024 * 1024));		//堆内存从1M开始,共500M
	os_free(20 * (1024 * 1024), 490 * (1024 *1024));
	gpio_init();
	
	// 2014年12月13日18:13:10  刚才还没有初始化就开始使用图层表，结果发生了不可预知的错误，第二次犯这样的错误了。
	PicLayerTable = PicLayerTable_init();  //初始化图层表
	//init_screen(screen_width, screen_high, color_deep);
	init_screen_layer();
	uart_init();
	//task_init();
	//init_arm_timer(Kernrl_100Hz);
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
	
	//
	 dbg_bmp();
	 dbg_input();
	while(1)
	{
		sleep(1000);
		blink_GPIO16();
	}
	;
}

void exit(int code)
{
	while(1)
	;
}

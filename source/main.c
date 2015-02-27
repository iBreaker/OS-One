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

/*这里不加volatile LED不会闪烁 Why？*/
volatile unsigned int tmp = 0;


/*程序的主函数，永远不返回*/
void os_main(void)
{
	/* init */
	momory_init(0x100000, 500 * (1024 * 1024));
	gpio_init();
	init_screen(screen_width, screen_high, color_deep);
	
	
	//堆内存从1M开始,共500M
	
	
	//uart_init();
	//task_init();
	//init_arm_timer(Kernrl_100Hz);
	// _enable_interrupts();
	
	/* debug */
	
	//deb_screen();
	//deb_os_printf();
	//deb_GPIO();
	//deb_keyboard();
	//deb_timer();
	//deb_linedlist();
	//deb_task();
	//dbg_UART();
	dbg_memory();
	while(1)
	{
		blink_GPIO16();
	}
	;
}

void exit(int code)
{
	while(1)
	;
}

/*
*   	2014年12月25日10:58:18
*	V1.0 	By Breaker
*
*	文件名：main.c
*	程序的主函数，永远不返回
*	
*/

#include <string.h>
#include <stdlib.h>

#include "gpio.h"
#include "time.h"
/*这里不加volatile LED不会闪烁 Why？*/
volatile unsigned int tmp = 0;


/*程序的主函数，永远不返回*/
void main(void)
{
	//malloc( 1024 * sizeof( unsigned int ) );

	
	 
	GPIO_SET_GPFSEL(16,1);	//GPIO16设置为output
	while(1)
	{	
		sleep(1000);
		GPIO_SET_GPSET(16);
		sleep(1000);
		GPIO_SET_GPCLR(16);
	}

	while(1)
	;
}

void exit(int code)
{
	while(1)
	;
}

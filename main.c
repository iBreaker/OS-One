/*
*   	2014年12月25日10:58:18
*	V1.0 	By Breaker
*
*	文件名：main.h
*	程序的主函数，永远不返回
*	
*/

#include "gpio.h"

void main(void)
{
	unsigned int tmp = 0; 
	GPIO_SET_GPFSEL(16,1);	//GPIO16设置为output
	while(1)
	{
		GPIO_SET_GPCLR(16);
		for(tmp=0; tmp<50000; tmp++)
		;
		GPIO_SET_GPCLR(16);
		
	}
}

void exit(int code)
{
	while(1)
	;
}

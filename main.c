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
#include "GPU.h"

/*这里不加volatile LED不会闪烁 Why？*/
volatile unsigned int tmp = 0;
volatile unsigned char *pointer = 0;
unsigned char color = 0;

/*程序的主函数，永远不返回*/
void main(void)
{
	unsigned int x,y;
	unsigned int addr = 0;
	//malloc( 1024 * sizeof( unsigned int ) );

	GPIO_SET_GPFSEL(16,1);	//GPIO16设置为output
	GPIO_SET_GPSET(16);
	


	addr = init_GPU(1024, 768, 16);
	pointer =  (unsigned char *) (addr + 32);
	if(addr != 0)
		GPIO_SET_GPCLR(16);



	while(1)
	{	
		sleep(1000);
		GPIO_SET_GPCLR(16);

		for(y=0; y<768; y++)
		{
			for(x=0; x<1024; x++)
			{
				pointer[y*1024+x] = color;
				color ++;
			}
		}
			
		sleep(1000);
		GPIO_SET_GPSET(16);
	}

	while(1)
	;
}

void exit(int code)
{
	while(1)
	;
}

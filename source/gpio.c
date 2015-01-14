/*
*	2014年12月24日14:18:33
*	V1.0 	By Breaker
*
*	文件名：GPIO.c
*    GPIO函数
*	
*/

#include "gpio.h"

/*这里声明私有函数 共有函数在头文件中声明 */
unsigned long GET_GPFSEL_ADDR(int pin);
unsigned long GET_GPSET_ADDR(int pin);
unsigned long GET_GPCLR_ADDR(int pin);

/*
*	2014年12月24日14:27:29
*	V1.0 	By Breaker
*
*	int GPIO_SET_GPFSEL(int pin, int func)
*   设置第pin个GPIO的功能(func)
*	return 0 成功  -1 失败	
*/

int GPIO_SET_GPFSEL(int pin, int func)
{
	volatile unsigned long *point = 0 ;
	unsigned long mask = 0;
	int bit_num = 0;
	bit_num = pin % 10;
	
	//检查
	
	if(pin > 53 || pin < 0)
	{
		return -1;
	}
	
	if(func > 7 || func < 0)
	{
		return -1;
	}
	
	//赋值
	
	point = (unsigned long*)GET_GPFSEL_ADDR(pin);
	//point = (unsigned long*)GPFSEL1;
	switch(func)
	{
		case 0:
			mask |=  1 << (bit_num * 3);
			mask |=  1 << ((bit_num * 3) + 1) ;
			mask |=  1 << ((bit_num * 3) + 2) ;
			//^ 异或
			~mask; 				
			*point &= mask;
			break;
		case 1:
			mask |= 1 << ((bit_num * 3) + 2);
			mask |= 1 << (bit_num * 3) + 1;
			~mask;
			*point &= mask;
			*point |= 1 << (bit_num * 3);
			break;
		default:
			break;
	}
	return 0;
} 

/*
*	2014年12月24日15:32:05
*	V1.0 	By Breaker
*
*	void GPIO_SET_GPSET(int pin)
*   第pin个置1，高电位
*	return 0 成功  -1 失败
*/

int GPIO_SET_GPSET(int pin)
{
	volatile unsigned long *point = 0 ;
	int bit_num = 0;
	
	//检查
	
	if(pin > 53 || pin < 0)
	{
		return -1;
	}
	
	bit_num = pin % 32;
	point = (unsigned long*)GET_GPSET_ADDR(pin);
	
	if(point == 0)
	{
		return -1;
	}
	
	*point |= (1 << bit_num);
}

/*
*	2014年12月24日15:34:59
*	V1.0 	By Breaker
*
*	void GPIO_SET_GPCLR(int pin)
*   第pin个置1，低电位
*	return 0 成功  -1 失败
*/

int GPIO_SET_GPCLR(int pin)
{
	volatile unsigned long *point = 0 ;
	int bit_num = 0;
	
	//检查
	
	if(pin > 53 || pin < 0)
	{
		return -1;
	}
	
	bit_num = pin % 32;
	point = (unsigned long*)GET_GPCLR_ADDR(pin);
	
	if(point == 0)
	{
		return -1;
	}
	
	*point |= (1 << bit_num);
}


/*
*	2014年12月24日14:39:42
*	V1.0 	By Breaker
*
*	unsigned long GET_GPFSEL_ADDR(int pin)
*   获取管脚GPFSEL地址
*	return地址	
*/

unsigned long GET_GPFSEL_ADDR(int pin)
{
	int reg_num = 0;
	reg_num = pin/10;
	
	switch (reg_num)
	{
		case 0:
			return GPFSEL0;
			break;
		case 1:
			return GPFSEL1;
			break;
		case 2:
			return GPFSEL2;
			break;
		case 3:
			return GPFSEL3;
			break;
		case 4:
			return GPFSEL4;
			break;
		case 5:
			return GPFSEL5;
			break;
		default:
			return 0;
			break;
	}
}

/*
*	2014年12月24日14:40:38
*	V1.0 	By Breaker
*
*	unsigned long GET_GPSET_ADDR(int pin)
*   获取管脚GPSET地址
*	return地址
*/

unsigned long GET_GPSET_ADDR(int pin)
{
	if(pin < 29)
	{
		return GPSET0;
	}
	else 
	{
		return GPSET1;
	}
	return 0;
}

/*
*	2014年12月24日14:41:46
*	V1.0 	By Breaker
*
*	unsigned long GET_GPCLR_ADDR(int pin)
*   获取管脚GPCLR地址
*	return地址
*/
unsigned long GET_GPCLR_ADDR(int pin)
{
	if(pin < 29)
	{
		return GPCLR0;
	}
	else 
	{
		return GPCLR1;
	}
	return 0;
}

void blink_GPIO16(void)
{
	static int lit = 0;
	
	if( lit )
	{
		GPIO_SET_GPSET(16);
		lit = 0;
	}
	else
	{
		GPIO_SET_GPCLR(16);
		lit = 1;
	}
}

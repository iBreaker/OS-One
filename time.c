/*
*	2014年12月25日17:12:02
*	V1.0 	By Breaker
*
*	文件名：time.c
*	定义time相关的函数
*	
*/

#include "time.h"

/*
*	2014年12月25日21:01:06
*	V1.0 	By Breaker
*
*	int sleep(int ms)
*   	休眠ms毫秒
*	return 0 成功  -1 失败	
*/

int sleep(int ms)
{
	/* 2014年12月26日21:25:14 又是没有加volatile
	关键字惹的祸，编译器把算法优化了，之应该存在cache中 */
	volatile unsigned int *TIMER_CLO_P = (unsigned int *)TIMER_CLO;
	unsigned long current_time = 0;
	unsigned long us = 0;

	//检查
	if(ms < 0)
	{
		return -1;
	}
	
	/* 毫秒转化为微秒 */
	us = ms * 1000; 
	current_time = *TIMER_CLO_P;
	
	while((*TIMER_CLO_P - current_time) < us);
	{

	}

	return 0;
}

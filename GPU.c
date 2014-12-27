/*
*	2014年12月27日18:16:31
*	V1.0 	By Breaker
*
*	文件名：GPU.c
*    	定义GPU函数
*	
*/

#include "GPU.h"

/*
*	2014年12月27日18:38:32
*	V1.0 	By Breaker
*
*	int GPU_SendMail(unsigned int width, unsigned int height, unsigned int bitDepth, unsigned int channel)
*   	将图像参数发送到给GPU
*	return 0 成功  -1 失败
*/

int GPU_SendMail(unsigned int width, unsigned int height, unsigned int bitDepth, unsigned int channel)
{
	volatile unsigned int *Status = (unsigned int *)CPU_Status;
	unsigned int *Write = (unsigned int *) CPU_Write;
	unsigned int GPU_MSG = 0;
	unsigned int address = (unsigned int)&FrameBufferInfo;
	struct FrameBufferInfoS *bufInfo = 0;

	bufInfo = (struct FrameBufferInfoS *) address;
	
	/*参数检查*/
	if(((unsigned int)bufInfo & 0xFFFFFFF0) != 0)
	{
		return -1;
	}

	if((channel > 8) || (channel < 1))
	{
		return -1;
	}

	/*循环等待状态寄存器的最高为为0.则可以发送消息*/
	do{
		Status = (unsigned int *)CPU_Status;
	}while((*Status & 0x80000000) != 0);
	
	bufInfo->phyWidth = width;
	bufInfo->phyHeight = height;
	bufInfo->virWidth = width;
	bufInfo->virHeight = height;
	bufInfo->bitDepth = bitDepth;
	
	/*禁用cache，读取内存值，防止产生误差。0x40000000 */
	address += 0x40000000;
	bufInfo = (struct FrameBufferInfoS *) address;

	/*按照格式发送消息到GPU*/
	GPU_MSG = (unsigned int)bufInfo & channel;
	*Write = GPU_MSG;

	return 0;
}

/*
*	2014年12月27日19:39:32
*	V1.0 	By Breaker
*
*	int GPU_RecMail(unsigned int channel)
*   	确认是否发送成功
*	return 返回FrameBufferInfo地址
*/

unsigned int GPU_RecMail(unsigned int channel)
{
	volatile unsigned int *Status = (unsigned int *)CPU_Status;
	unsigned int *Read = (unsigned int *) CPU_Read;
	unsigned int GPU_MSG = 0;

	/*参数检查*/
	if((channel > 8) || (channel < 1))
	{
		return 0;
	}

	
	do{
		Status = (unsigned int *)CPU_Status;

		/*循环等待状态寄存器30bit为0.则可以接收消息*/
		if((*Status & 0x40000000) == 0)
		{
			GPU_MSG = *Read;

			/*通过channel判断是否是所需的消息*/
			if((GPU_MSG & 0xF) == channel)
			{
				/*GPU_MSG = 0 表示成功发送消息，否则失败*/
				GPU_MSG = (GPU_MSG & 0xFFFFFFF0);
				if(GPU_MSG == 0)
				{
					return (unsigned int)&FrameBufferInfo;
				}
				else
				{
					return 0;
				}
				
			}
		}
	}while(1);
}


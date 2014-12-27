/*
*	2014年12月27日09:35:46
*	V1.0 	By Breaker
*
*	文件名：GPU.h
*    	定义GPU相关的地址 声明结构体 声明相关函数
*	
*/

#define CPU_BASE 	0x2000B880
#define CPU_Read	0x2000B880	
#define CPU_Poll 	0x2000B890
#define CPU_Sender 	0x2000B894
#define CPU_Status 	0x2000B89C
#define CPU_Config 	0x2000B8A0
#define CPU_Write 	0x2000B8AC

struct FrameBufferInfoS
{
	unsigned int phyWidth; 			/* #0 Physical Width */
	unsigned int phyHeight;  		/* #4 Physical Height */
	unsigned int virWidth; 			/* #8 Virtual Width */
	unsigned int virHeight; 		/* #12 Virtual Height */
	volatile unsigned int Pitch; 		/* #16 GPU - Pitch */
	unsigned int bitDepth; 			/* #20 Bit Depth */
	volatile unsigned int x; 		/* #24 X */
	volatile unsigned int y; 		/* #28 Y */
	volatile unsigned int bufPointer; 	/* #32 GPU - Pointer， GPU会更改此值，GPU为缓冲区分配的首地址*/
	volatile unsigned int bufSize; 		/* #36 GPU - Size ， GPU会更改此值，GPU为缓冲区分配内存的大小*/ 
};

extern struct FrameBufferInfoS FrameBufferInfo;

int GPU_SendMail(unsigned int width, unsigned int height, unsigned int bitDepth, unsigned int channel);
unsigned int GPU_RecMail(unsigned int channel);



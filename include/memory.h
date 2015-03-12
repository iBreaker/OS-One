/**
*	2015年02月27日11:02:23
*	V1.0 	By Breaker
*
*	文件名：memory.h
*    	内存相关
**/ 

#ifndef _MEMORY_H
#define _MEMORY_H

#include "stdtype.h"

#define MAX_MEMORY_T 4096		//允许最多free内存块数

//free内存结构
struct free_memory_s
{
	unsigned int addr;
	unsigned int size;
};

//管理
struct free_memory_table_s
{
	unsigned int max_count;
	struct free_memory_s FreeMemory[MAX_MEMORY_T];
	unsigned int free_count;
	unsigned int max_free_size;
	unsigned int addr,size;  //要管理的内存的范围
}; 
 

void momory_init(unsigned int addr,unsigned int size);				//初始化
unsigned int total_free_memory_size();												//返回free内存大小
void *os_malloc(unsigned int size);															//申请内存
int os_free (unsigned int addr,unsigned int size);							//释放内存
void os_memcpy(u32 from_addr, u32 to_addr, u32 size);					//复制内存

#endif

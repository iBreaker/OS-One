/**
*	2015年02月27日11:02:23
*	V1.0 	By Breaker
*
*	文件名：memory.h
*    	内存相关
**/ 

#ifndef _MEMORY_H
#define _MEMORY_H

#define MAX_MEMORY_T 4096
#define FreeMemoryTables_addr 0x003c0000
struct free_memory_s
{
	unsigned int addr;
	unsigned int size;
};

struct free_memory_table_s
{
	unsigned int max_count;
	struct free_memory_s FreeMemory[MAX_MEMORY_T];
	unsigned int free_count;
	unsigned int max_free_size;
	unsigned int addr,size;  //要管理的内存的范围
}; 
 
void momory_init(unsigned int addr,unsigned int size);
unsigned int total_free_memory_size();
void *os_malloc(unsigned int size);
int os_free (unsigned int addr,unsigned int size);

#endif
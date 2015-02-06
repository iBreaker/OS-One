/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.c
*    	多任务相关
**/ 

#include "task.h"
#include "Global.h"

/*****************************************************************
*	2015年01月24日10:03:22
*	V1.0 	By Breaker
*
*	void task_init(LinkedList *ll)
*   	任务初始化
*	return void
*/
u8 task_init(TS *ts, u32 sp, void *pc)
{
	asm volatile("MRS r0, cpsr"); 
	asm volatile("STR r0, %[r0]" :  : [r0]"m"(ts->cpsr));
	
	asm volatile("MRS r0, spsr"); 
	asm volatile("STR r0, %[r0]" :  : [r0]"m"(ts->spsr));
	
	ts->r0 = 0;
	ts->r1 = 0;
	ts->r2 = 0;
	ts->r3 = 0;
	ts->r4 = 0;
	ts->r5 = 0;
	ts->r6 = 0;
	ts->r7 = 0;
	ts->r8 = 0;
	ts->r9 = 0;
	ts->r10 = 0;
	ts->r11 = 0;
	ts->r12 = 0;
	ts->sp = sp;
	ts->lr = 0;
	ts->pc = (u32)pc;
	
	
	//ts->spsr = 0;
}
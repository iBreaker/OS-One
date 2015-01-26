/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.h
*    	多任务相关
**/ 

#include "stdtype.h"

#ifndef _TASK_H
#define _TASK_H

/*Task Status*/
typedef struct {
	u32  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc, cpsr, spsr;
	u8 pid;
}TS;

u8 task_init(TS *ts, u32 sp, void *pc);
#endif


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
	u32 r4_to_r11[8];		// lower address
	u32 r0;
	u32 r1;
	u32 r2;
	u32 r3;
	u32 r12;
	u32 lr;
	u32 pc;
	u32 xpsr;			// higher address
}TS;

u8 task_init(TS *ts, u32 sp, void *pc);
#endif


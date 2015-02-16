/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.h
*    	多任务相关
**/ 
#ifndef _TASK_H
#define _TASK_H

#include "stdtype.h"
#include "linkedlist.h"



#define	MAX_rank	3		//	共四个优先级: 0 1 2 3

typedef enum
{
	READY = 200 ,RUN,WAIT,SUSPEND,DEAD
}TASK_STATUS_ENUM;

/*Task info*/
typedef struct {
		u8	rank;										/*优先级*/
		TASK_STATUS_ENUM status;	/*任务状态*/
		 void *task_func;						/*函数地址*/
		 u8	TRID;										/*Task Ready ID*/
}TASK_INFO;

TASK_INFO task_info[17];			    /*任务信息*/
LinkedList task_ready_ll;
LinkedList * task_ready;						/*就绪表*/
LinkedList MSG;									/*消息控制*/
LinkedList SEM;									/*信号量控制*/

typedef struct {
		u32 r0;
		u32 r1;
		u32 r2;
		u32 r3;
		u32 r4;
		u32 r5;
		u32 r6;
		u32 r7;
		u32 r8;
		u32 r9;
		u32 r10;
		u32 r11;
		u32 r12;
		u32 sp;
		u32 lr;
		u32 pc;
		u32 cpsr;
		u32 spsr;
}TASK_TABLE;

TASK_TABLE   task_table[16];
u8   task_stack[16][1024];

typedef struct {
		u32	current_tasktable;
		u8	current_TID;
		u8 	schedule_lock ;
}TASK_GLOBAL;

u8 task_creat(u8 rank, void *task_func);
u8 task_create(u8 rank, void *task_func);
u8  task_run(u8 TID);

#endif


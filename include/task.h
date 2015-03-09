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
	STATUS_NULL ,READY , RUN, WAIT4MSG, WAIT, SUSPEND, DEAD
}TASK_STATUS_ENUM;

typedef enum
{
	MSG_NULL, MSG_WAIT4MSG,MSG_SEND,  MSG_SUSPEND, MSG_RESUME, MSG_NORMAL
}MSG_TYPE_ENUM;

typedef struct {
	u8 from;
	u8 to;
	MSG_TYPE_ENUM  type;
	u32 value;
}MSG_s;

/*Task info*/
typedef struct {
		u8	rank;										/*优先级*/
		TASK_STATUS_ENUM status;	/*任务状态*/
		 u32 task_func;						/*函数地址*/
		 u8	TRID;										/*Task Ready ID*/
		 MSG_s MSG;								/*每个任务的消息缓冲*/
}TASK_INFO;

TASK_INFO task_info[17];			    /*任务信息*/

LinkedList task_ready_ll;
LinkedList * task_ready;					/*就绪表*/

LinkedList MSG_list_ll;						/*消息ID控制*/
LinkedList * MSG_list;

MSG_s MSG[64];									/*消息真正存储的地方*/

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

TASK_TABLE   task_table[17];
u8   task_stack[17][1024];

typedef struct {
		u32	current_tasktable;
		u8	current_TID;
		u8 	schedule_lock ;
		u8  is_uart_irq;
}TASK_GLOBAL;

u8 task_create(u8 rank, u32 task_func);
u8  task_run(u8 TID);
void task_lock_schedule(void);
void task_unlock_schedule(void);
u8  task_send_msg(u8 to, MSG_TYPE_ENUM  type, u32 value);
MSG_s  task_recevie_msg(void);
void task_manager();

#endif


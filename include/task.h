/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.h
*    	多任务相关
* 
** OS One - A simple OS for Raspberry Pi
* Copyright (C) 2014 - 2015  Breaker  <791628659@qq.com>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
 * **/

#ifndef _TASK_H
#define _TASK_H

#include "stdtype.h"
#include "linkedlist.h"



#define	MAX_rank	 3		//	共四个优先级: 0 1 2 3

//任务状态
typedef enum
{
	STATUS_NULL ,		//空
	READY,						//就绪
	RUN, 							//正在运行
	WAIT4MSG, 				//wite for MSG 等待消息
	WAIT,							//阻塞
	SUSPEND,				//挂起
	DEAD							//未加入调度函数管理
}TASK_STATUS_ENUM;

typedef enum
{
	MSG_NULL, 					//空
	MSG_WAIT4MSG,		//wite for MSG
	MSG_SEND,  				//发送
	MSG_SUSPEND, 			//
	MSG_RESUME, 			//
	MSG_NORMAL			//普通消息
}MSG_TYPE_ENUM;

//消息结构
typedef struct {
	u8 from;
	u8 to;
	MSG_TYPE_ENUM  type;
	u32 value;
}MSG_s;

/*Task info*/
//任务信息
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

//存储任务寄存器
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

//任务全局变量
typedef struct {
		u32	current_tasktable;		//当前任务寄存器存放的首地址(切换任务的时候需要)
		u8	current_TID;				//当前TID
		u8 	schedule_lock ;			//是否锁定调度函数(不进行任务调度)
}TASK_GLOBAL;

u8 task_create(u8 rank, u32 task_func);							//创建任务
u8  task_run(u8 TID);																//加入调度管理
void task_lock_schedule(void);										//锁定调度函数
void task_unlock_schedule(void);								//解锁
u8  task_send_msg(u8 to, MSG_TYPE_ENUM  type, u32 value);		//发送消息
MSG_s  task_recevie_msg(void);																//接收消息, 执行这个函数后进入阻塞状态
void task_manager();																					//调试的时候用   显示任务状态

#endif


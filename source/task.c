/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.c
*    	多任务相关
*
* * OS One - A simple OS for Raspberry Pi
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

/**
 *    任务信息存放在task_table, task_stack, task_ready, task_gable task_info 五种数据结构中
 * 	task_table 是任务切换的时候寄存器保存的地方
 *     task_stack 任务栈
 *     task_ready 任务队列, 只保存任务的关系,调度函数可以快速的计算出合适的任务
 *		task_gable  其他的全局变量, 因为创建任务以及调度函数不接受参数也没有返回值.所以用全局变量传递计算结果以及保存状态
 * */


#include "task.h"
#include "Global.h"
#include "linkedlist.h"
#include  "gpio.h"

u8 task_get_id();				/*申请id*/
void task_delete();
void task_idle(void);
void MSG_dispose();

/*task.c*/
TASK_GLOBAL task_global;

/*****************************************************************
*	2015-02-16 18:34:32
*	V1.0 	By Breaker
*
*		void task_init(LinkedList *ll)
*   	初始化系统任务管理机制
*		return void
*/
void task_init()
{
		//初始化 task_ready
		task_ready = &task_ready_ll;
		ll_init(task_ready);

		//初始化 MSG_list
		MSG_list = & MSG_list_ll;
		ll_init(MSG_list);

		//创建一个默认任务, 当前的代码将会以任务的方式执行
		u8 rank = MAX_rank ;
		u32 task_func = (u32)task_idle;
		u8 TID = task_create( rank , task_func);
		task_run(TID);

		//初始化task_global
		task_global.schedule_lock = false;
		task_global.current_TID = TID;
		task_global.current_tasktable = (u32) &task_table[TID];
}

void task_idle(void)
{
	while(1);
}
/*****************************************************************
*	2015年01月24日10:03:22
*	V1.0 	By Breaker
*
*		u8 task_create(u8 rank, u32 task_func)
*   	任务初始化
*		return 返回任务ID,返回0任务创建失败
*/
u8 task_create(u8 rank, u32 task_func)
{
		/*1.检查参数合法性*/
		if( rank > MAX_rank + 1)
		{
				return NULL;
		}

		/*2.设置TASK_INFO*/
		u8 TID = task_get_id();
		if( NULL == TID )
		{
				return NULL;
		}

		TASK_INFO task_info_this;
		task_info_this.rank = rank;
		task_info_this.status = DEAD ;
		task_info_this.task_func = task_func ;
		task_info[TID] = task_info_this;
		//task_info.TRID 到 task_run 中设置


		/*3.设置tasktable*/
		task_table[TID].sp = (u32)task_stack[TID] + 1024;
		task_table[TID].lr = (u32)task_delete;
		task_table[TID].pc =(u32) task_func;
		task_table[TID].cpsr = 0x53;	//禁止fiq , svc模式
		task_table[TID].spsr = 0x53;
		return TID;
}

u8 task_get_id()
{
		int id = 1;
		for(id = 1; id < 17; id++)
		{
			if( (task_info[id].rank == NULL) && (task_info[id].status == NULL) && (task_info[id].task_func == NULL ) && (task_info[id].TRID == NULL ) )
			{
				return id;
			}
		}
		return 0;
}
/*****************************************************************
*		2015年02月15日14:41:14
*		V1.0 	By Breaker
*
*		u8  task_run(u8 TID)
*   	将任务加入任务调度函数的管理
*		return
*/
u8  task_run(u8 TID)
{
		/*1.参数验证, run 的进程状态必须是DEAD,其他状态的进程不可以被run*/
		if(task_info[TID].status != DEAD)
		{
				return NULL;
		}

		/*2.1 申请加入task_ready链表, 返回0失败*/
		task_info[TID].TRID = ll_add_by_order(task_ready, TID, task_info[TID].rank);

		/*2.2 验证返回值是否有效*/
		if( NULL == task_info[TID].TRID)
		{
				task_info[TID].TRID = NULL;
				task_info[TID].rank = NULL ;
				task_info[TID].status = NULL;
				task_info[TID].task_func = NULL;
		}
		else
		{
				task_info[TID].status = READY;
		}
		return task_info[TID].TRID;
}



/*****************************************************************
*		2015年02月15日14:30:32
*		V1.0 	By Breaker
*
*		void  task_schedule(void)
*   	任务调度函数
*		return void
*/
void  task_schedule(void)
{
	//static int i =0;
		//os_printf("+");


		u8 current_TID , current_TRID;
		current_TRID = task_info[task_global.current_TID].TRID;										//获取当前TRID

		/* 1.处理消息发送,消息接收等请求 */
		MSG_dispose();

		do{
			current_TRID = ll_get_next_id(task_ready , current_TRID);										//得到下一个TRID
			current_TID = (u8) task_ready->node[current_TRID].value;
			//os_printf("->NEXT TID %d RTID : %d status %d", current_TID, current_TRID,  task_info[current_TID].status);
		}while(0  == current_TRID || task_info[current_TID].status !=  READY);

		task_global.current_TID = current_TID;			//设置当前TID													//
		task_global.current_tasktable = (u32) &task_table[task_global.current_TID];	//设置当前tasktable
		//os_printf("%n CURRENT TID: %d", task_global.current_TID);
		return ;
}


/*****************************************************************
*		2015年02月15日14:30:37
*		V1.0 	By Breaker
*
*		void task_delete(u8 TID)
*   	任务结束释放资源
*		return void
*/
void task_delete()
{
	u8 TID = task_global.current_TID;
	task_info[TID].TRID = NULL;
	task_info[TID].rank = NULL ;
	task_info[TID].status = NULL;
	task_info[TID].task_func = NULL;

	task_table[TID].r0 = 0;
	task_table[TID].r1 = 0;
	task_table[TID].r2 = 0;
	task_table[TID].r3 = 0;
	task_table[TID].r4  = 0;
	task_table[TID].r5 = 0;
	task_table[TID].r6 = 0;
	task_table[TID].r7 = 0;
	task_table[TID].r8 = 0;
	task_table[TID].r9 = 0;
	task_table[TID].r10 = 0;
	task_table[TID].r11 = 0;
	task_table[TID].r12 = 0;
	task_table[TID].sp = 0;
	task_table[TID].lr = 0;
	task_table[TID].pc = 0;
	task_table[TID].cpsr = 0;
	task_table[TID].spsr = 0;

	 ll_remove_by_id(task_ready ,  task_info[TID].TRID);
}

void task_lock_schedule(void)
{
	task_global.schedule_lock = true;
}

void task_unlock_schedule(void)
{
	task_global.schedule_lock = false;
}

void task_wait(void)
{

}

void task_wait_abort(void)
{

}

void task_suspend(void)
{

}

void task_resume(void)
{

}

u8  task_send_msg(u8 to, MSG_TYPE_ENUM  type, u32 value)
{
	/*1.将消息添加到系统的消息缓冲区*/
		/*1.1 申请消息ID*/
	u8 MSG_ID = ll_add_to_tail(MSG_list , value);
	if( 0 == MSG_ID)
	{
			return false;
	}

		/*1.2 填充消息*/
	MSG_s _MSG;
	_MSG.from = task_global.current_TID;
	_MSG.to = to;
	_MSG.type = type;
	_MSG.value = value;
	MSG[MSG_ID] = _MSG;

	/*2. 通知内核将消息发送到指定task*/
	_MSG.from = task_global.current_TID;
	_MSG.to = 0;
	_MSG.type = MSG_SEND;
	_MSG.value = MSG_ID;
	task_info[0].MSG = _MSG;

	/*进入死循环判断是否发送成功*/
	u32 timer_value = os_timer_ctrl.value;
	while( timer_value == os_timer_ctrl.value ){}

	return true;
}


/*****************************************************************
*		2015年02月18日12:57:23
*		V1.0 	By Breaker
*
*		void MSG_dispose()
*   	消息等请求处理函数
*		return
*/
void MSG_dispose()
{
	u8 MSG_ID = task_info[0].MSG.value;
	u8 to = MSG[MSG_ID].to;
	switch(task_info[0].MSG.type)
	{
			case MSG_SEND:
				if(task_info[to].status != WAIT4MSG)
				{
						//os_printf(" %n status != WAIT4MSG  TASK%d   MSG_ID:%d  ", to, MSG_ID);
						break;
				}
				task_info[to].MSG = MSG[MSG_ID];
				task_info[to].status = READY;

				// os_printf("%n SEND to %d    ", to);
				break;

			case MSG_WAIT4MSG:
				task_info[task_global.current_TID].status = WAIT4MSG;
				break;

			case MSG_SUSPEND:
				task_info[task_global.current_TID].status = SUSPEND;
				break;

			//这里还是有点问题的, 挂起的进程恢复后不一定是READY
			case MSG_RESUME:
				task_info[task_global.current_TID].status = READY;
				break;

			default:
			case MSG_NULL:
				break;
	}
	task_info[0].MSG.value = NULL;
	task_info[0].MSG.type = MSG_NULL;
	ll_remove_by_id(MSG_list, MSG_ID);
}


MSG_s  task_recevie_msg(void)
{
		MSG_s _MSG;
		/*1. 通知内核自己进入等待消息状态 */
		_MSG.from = task_global.current_TID;
		_MSG.to = 0;
		_MSG.type = MSG_WAIT4MSG;
		_MSG.value = NULL;
		task_info[0].MSG = _MSG;

		/*进入死循环接收消息*/
		u32 timer_value = os_timer_ctrl.value;
		while( timer_value == os_timer_ctrl.value ){}

		return  task_info[task_global.current_TID].MSG;
}



void task_recevie_msg_abort(void)
{

}

void task_semaphore_cteate(void)
{

}

void task_semaphore_wait(void)
{

}

void task_semaphore_wait_abort(void)
{

}

void task_semaphore_post(void)
{

}

void task_semaphore_delete(void)
{

}


void task_manager()
{
				int current_TRID  = ll_get_head_id(task_ready);

				while(0  != current_TRID  )
				{
					u8 TID = task_ready->node[current_TRID].value;
					os_printf("%nTASK%d: RTID[%d] status[%d]  Rank[%d]  func[%d]", TID, task_info[TID].TRID, task_info[TID].status, task_info[TID].rank, task_info[TID].task_func);
					os_printf(" Reg %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", task_table[TID].r0 , task_table[TID].r1, task_table[TID].r2, task_table[TID].r3, task_table[TID].r4, task_table[TID].r5, task_table[TID].r6, task_table[TID].r7, task_table[TID].r8, task_table[TID].r9, task_table[TID].r10, task_table[TID].r11, task_table[TID].r12, task_table[TID].sp, task_table[TID].lr, task_table[TID].pc, task_table[TID].cpsr, task_table[TID].spsr );
					os_printf("-|%d|%d|%d| ", task_global.current_TID, task_global.current_tasktable, task_global.schedule_lock ,task_table[TID].pc );
					current_TRID = ll_get_next_id(task_ready, current_TRID);
				}
}


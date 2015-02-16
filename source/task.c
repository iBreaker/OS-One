/**
*	2015年01月23日10:25:23
*	V1.0 	By Breaker
*
*	文件名：task.c
*    	多任务相关
**/ 

/**
 *    任务信息存放在task_table, task_stack, task_ready, task_gable 四种数据结构中
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

/*****************************************************************
*	2015-02-16 18:34:32
*	V1.0 	By Breaker
*
*		void task_init(LinkedList *ll)
*   	初始化
*		return void
*/
void task_init()
{
		task_ready = &task_ready_ll;
		ll_init(task_ready);


		//创建一个空闲任务
		u8 rank = 3;
		void * task_func = task_idle;
		u8 TID = task_create( rank , task_func);
		task_run(TID);

		task_global.schedule_lock = false;
		task_global.current_TID = TID;
		task_global.current_tasktable = &task_table[TID];
}

void task_idle(void)
{
		while(true)
		{
				blink_GPIO16();
				sleep(1000);
		}
}
/*****************************************************************
*	2015年01月24日10:03:22
*	V1.0 	By Breaker
*
*		u8 task_create(u8 rank, void *task_func)
*   	任务初始化
*		return 返回任务ID,返回0任务创建失败
*/
u8 task_create(u8 rank, void *task_func)
{
		/*1.检查参数合法性*/
		if( rank > MAX_rank)
		{
				return NULL;
		}

		if( rank  ==  NULL)
		{
				return NULL;
		}

		/*2.设置TASK_INFO*/
		u8 TID = task_get_id();

		if( NULL ==TID )
		{
				return NULL;
		}

		TASK_INFO task_info_this;
		task_info_this.rank = rank;
		task_info_this.status = DEAD ;
		task_info_this.task_func = task_func ;

		task_info[TID] = task_info_this;

		/*3.设置tasktable*/
		task_table[TID].sp = (u32)task_stack[TID] + 1024;
		task_table[TID].lr = (u32)task_delete;
		task_table[TID].pc =(u32) task_func;
		task_table[TID].cpsr = 0x13;
		task_table[TID].spsr = 0x13;
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
*		void  task_run(void)
*   	将任务加入任务调度函数的管理
*		return
*/
u8  task_run(u8 TID)
{
		if(task_info[TID].status != DEAD)
		{
				return NULL;
		}

		task_info[TID].TRID = ll_add_by_order(task_ready, TID, task_info[TID].rank);

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
		u8 TID;
		task_global.current_TID  = ll_get_next_id(task_ready , task_global.current_TID);
		TID = task_global.current_TID ;
		task_global.current_tasktable =(u32) &task_table[TID];

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

void task_send_msg(void)
{

}

void task_recevie_msg(void)
{

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



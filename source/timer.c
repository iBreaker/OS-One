  /*
*	2015年01月06日15:34:45
*	V1.0 	By Breaker
*
*	文件名：timer.c
*    	系统时钟相关函数
*/
 
#include "timer.h"
#include "interrupt.h"
#include "Global.h"
#include "Graphic.h"

unsigned char get_os_timer_id( void);
void os_timer_insert_pointer(unsigned int value, unsigned char os_timer_id);
void os_timer_remove_pointer(void);
void time_out_msg (unsigned char os_timer_id);

/*timer.c*/
arm_timer_t *ArmTimer = (arm_timer_t *)ARMTIMER_BASE;		//ArmTimer首地址
os_timer_ctrl_st os_timer_ctrl;		//timer ctrl

char timer_time_out_p[5];
char * timer_time_out = timer_time_out_p;
FIFO8  time_out_p;
FIFO8  * time_out = & time_out_p;

/*
*	2014年12月25日21:01:06
*	V1.0 	By Breaker
*
*	int sleep(int ms)
*   	休眠ms毫秒
*	return 0 成功  -1 失败	
*/

int sleep(int ms)
{
	/* 2014年12月26日21:25:14 又是没有加volatile
	关键字惹的祸，编译器把算法优化了，之应该存在cache中 */
	volatile unsigned int *TIMER_CLO_P = (unsigned int *)TIMER_CLO;
	unsigned long current_time = 0;
	unsigned long us = 0;

	//检查
	if(ms < 0)
	{
		return -1;
	}
	
	/* 毫秒转化为微秒 */
	us = ms * 1000; 
	current_time = *TIMER_CLO_P;
	
	while((*TIMER_CLO_P - current_time) < us);
	{
		
	}

	return 0;
}

/*****************************************************************
*	2015年01月13日14:24:16
*	V1.0 	By Breaker
*
*	void init_timer(void)
*   	初始化时钟中断，默认100HZ
*	return void
*/
void init_arm_timer(unsigned int Load)
{
	arm_timer_t *ArmTimer = (arm_timer_t *)ARMTIMER_BASE;		/*ArmTimer首地址*/
	irq_controller_t *IRQcontroller = (irq_controller_t *)INTERRUPT_CONTROLLER_BASE; /*中断控制器首地址*/
	
	IRQcontroller->Enable_Basic_IRQs = BASIC_ARM_TIMER_IRQ;
	
	/*内核频率，100Hz*/
	ArmTimer->Load = Load;
	ArmTimer->Control = 	ARMTIMER_CTRL_23BIT |
							ARMTIMER_CTRL_ENABLE |
							ARMTIMER_CTRL_INT_ENABLE |
							ARMTIMER_CTRL_PRESCALE_1;
	fifo_init(time_out, timer_time_out, 5);
 }
 
 /*****************************************************************
*	2015年01月13日15:21:41
*	V1.0 	By Breaker
*
*	void init_os_timer_ctrl (void)
*   	初始化 os timer ctrl
*	return void
*/
 void init_os_timer_ctrl (void)
 {
	 int i = 0;
	 for(i =0; i < 256; i++)
	 {
		 os_timer_ctrl.os_timer_t[i].load = 0;
		 os_timer_ctrl.os_timer_t[i].value = 0;
		 os_timer_ctrl.os_timer_t[i].next_os_timer_id = 0;
	}
	/*0号os timer 被系统占用
	 是一个特殊的timer，它是最后一个超时的os timer
	 它的next_os_timer_id指向即将超时的os timer*/
	os_timer_ctrl.os_timer_t[0].load = 0xffffffff;
	os_timer_ctrl.os_timer_t[0].value = 0xffffffff;
 }
 

 
  /*****************************************************************
*	2015年01月13日15:56:02
*	V1.0 	By Breaker
*
*	 unsigned char set_os_timer(unsigned int ms, unsigned int load)
*   	初始化 os timer ctrl
*	return  os timer id
*/
 unsigned char set_os_timer(unsigned int ms, unsigned int load)
 {	 
	 unsigned long sum = 0;
	 sum = ms + os_timer_ctrl.value ;
	 if(sum > 0xFFFFFFFF)
	 {
		 return 0;
	 }
	 
	 //申请一个os timer id 
	 unsigned char os_timer_id = get_os_timer_id();
	 
	 //若未申请到退出函数
	if( os_timer_id == 0)
	{
		return 0;
	}
	
	//申请到id ,设置os timer
	os_timer_ctrl.os_timer_t[os_timer_id].value = sum;
	os_timer_ctrl.os_timer_t[os_timer_id].load = load;
	os_timer_insert_pointer(os_timer_ctrl.os_timer_t[os_timer_id].value, os_timer_id);
	return os_timer_id;
 }
 
/*****************************************************************
*	2015年01月13日16:01:24
*	V1.0 	By Breaker
*
*	unsigned char get_os_timer_id( void)
*   	申请一个os timer id 
*	return os timer id ,返回0申请失败
*/
 unsigned char get_os_timer_id( void)
 {
	 int i = 0;
	 for(i =0; i < 256; i++)
	 {
		 if( os_timer_ctrl.os_timer_t[i].value == 0 )
		 {
			 return i;
		 }
	 }
	 return 0;
 }
 
 /*****************************************************************
*	2015年01月13日16:30:45
*	V1.0 	By Breaker
*
*	void os_timer_insert_pointer(unsigned int value, unsigned char os_timer_id)
*   	增加新os timer 的时候调指针
*	return void
*/
void os_timer_insert_pointer(unsigned int value, unsigned char os_timer_id)
{
	unsigned char  next_id = os_timer_ctrl.os_timer_t[0].next_os_timer_id; //即将超时的os timer
	unsigned char  last_id = 0;		//自己指向自己
	while( value > os_timer_ctrl.os_timer_t[next_id].value )
	{
		last_id = next_id;
		next_id = os_timer_ctrl.os_timer_t[next_id].next_os_timer_id;
	}
	
	//调整指针
	os_timer_ctrl.os_timer_t[last_id].next_os_timer_id = os_timer_id;
	os_timer_ctrl.os_timer_t[os_timer_id].next_os_timer_id = next_id;
}

/*****************************************************************
*	2015年01月14日12:54:45
*	V1.0 	By Breaker
*
*	void free_os_timer_id( void )
*   	释放一个os timer id 
*	return 0 失败
*/
void free_os_timer( void )
{
	unsigned char os_timer_id = os_timer_ctrl.os_timer_t[0].next_os_timer_id;
	
	if(os_timer_id != 0)
	{
		os_timer_ctrl.os_timer_t[os_timer_id].value =0;
		os_timer_ctrl.os_timer_t[os_timer_id].load = 0;
		os_timer_remove_pointer();
	}
}

/*****************************************************************
*	2015年01月14日12:52:25
*	V1.0 	By Breaker
*
*	void os_timer_remove_pointer(void )
*   	删除os timer的时候调整指针
*	return void
*/
void os_timer_remove_pointer(void)
{
	unsigned char os_timer_id = os_timer_ctrl.os_timer_t[0].next_os_timer_id;
	os_timer_ctrl.os_timer_t[0].next_os_timer_id = os_timer_ctrl.os_timer_t[os_timer_id].next_os_timer_id ;
	os_timer_ctrl.os_timer_t[os_timer_id].next_os_timer_id  = 0;
	
}


/*****************************************************************
*	2015年01月14日13:22:30
*	V1.0 	By Breaker
*
*	void os_timer_ctrl_reflash(void)
*   	每过既定时间检查是否有超时的os timer
*	return void
*/
 void os_timer_ctrl_reflash(void)
 {
	os_timer_ctrl.value ++;
	
	unsigned char os_timer_id ;
	u8 next_os_timer_id;
	
	os_timer_id = os_timer_ctrl.os_timer_t[0].next_os_timer_id;
	
	
	if ( os_timer_ctrl.value  <  os_timer_ctrl.os_timer_t[os_timer_id].value )
	{
		return ;
	}
	
	if(os_timer_id == 0)
	{
		return;
	}
	u8 times = 1;
	u8 temp_id = os_timer_id; //4
	u32 temp_value = os_timer_ctrl.os_timer_t[temp_id].value;
	u8 temp_next_id  = os_timer_ctrl.os_timer_t[temp_id].next_os_timer_id;  //2
	u32 temp_next_value = os_timer_ctrl.os_timer_t[temp_next_id].value;
	
	while (( temp_value == temp_next_value)  && (temp_id != temp_next_id))
	{
		times ++;
		temp_id = temp_next_id; 
		temp_value = os_timer_ctrl.os_timer_t[temp_id].value;
		temp_next_id = os_timer_ctrl.os_timer_t[temp_id].next_os_timer_id;
		temp_next_value = os_timer_ctrl.os_timer_t[temp_next_id].value;
	}
	
	
	
	for(times ; times > 0; times--)
	{
		os_timer_id = os_timer_ctrl.os_timer_t[0].next_os_timer_id;
		next_os_timer_id = os_timer_ctrl.os_timer_t[os_timer_id].next_os_timer_id;
		
		time_out_msg (os_timer_id);
		
		if (os_timer_ctrl.os_timer_t[os_timer_id].load == 0)
		{
			free_os_timer();
		}
		else
		{
			os_timer_ctrl.os_timer_t[os_timer_id].value += os_timer_ctrl.os_timer_t[os_timer_id].load ;
			os_timer_remove_pointer();
			os_timer_insert_pointer(os_timer_ctrl.os_timer_t[os_timer_id].value , os_timer_id);
		}
		//os_timer_id = next_os_timer_id;
	}
 }
 
 /*****************************************************************
*	2015年01月14日13:35:10
*	V1.0 	By Breaker
*
*	 void time_out_msg (unsigned char os_timer_id)
*   	将超时计时器的id发送到fifo
*	return void
*/
void time_out_msg (unsigned char os_timer_id)
{
	//用户可以更改这里
	//blink_GPIO16();
	//DrawBlock_to_layer(PicLayerTable->Picture[DesktopHandle].buf  , colorB, screen_width, 0,  screen_width - 150, 150, 16);
	//drawStringF_to_layer(PicLayerTable->Picture[DesktopHandle].buf , "Timer%d Time Out" , colorRed , screen_width, 0, screen_width - 150, os_timer_id);
	//pic_layer_reflash_rect(0, screen_width - 150, 150, 32);
	fifo_put(time_out, os_timer_id);
}
  

  
 

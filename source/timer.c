  /*
*	2015年01月06日15:34:45
*	V1.0 	By Breaker
*
*	文件名：timer.c
*    	系统时钟相关函数
*/
 
#include "timer.h"
#include "interrupt.h"

void init_timer(void)
{
	arm_timer_t *ArmTimer = (arm_timer_t *)ARMTIMER_BASE;		/*ArmTimer首地址*/
	irq_controller_t *IRQcontroller = (irq_controller_t *)INTERRUPT_CONTROLLER_BASE; /*中断控制器首地址*/
	
	IRQcontroller->Enable_Basic_IRQs = BASIC_ARM_TIMER_IRQ;
	ArmTimer->Load = 0x400;
	ArmTimer->Control = 	ARMTIMER_CTRL_23BIT |
							ARMTIMER_CTRL_ENABLE |
							ARMTIMER_CTRL_INT_ENABLE |
							ARMTIMER_CTRL_PRESCALE_256;
	_enable_interrupts();
  }
 
/*
*	2015年01月05日21:57:51
*	V1.0 	By Breaker
*
*	文件名：interrupt.c
*    	中断处理函数
*	
*/
#include "interrupt.h"
#include "timer.h"
#include "gpio.h"


static irq_controller_t *irq_controller = (irq_controller_t *) INTERRUPT_CONTROLLER_BASE;




void  __attribute__((interrupt("UNDEF")))undifined_instruction_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("SWI")))software_interrupt_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("ABORT")))prefetch_abort_vector(void)
{
	
}

void  __attribute__((interrupt("ABORT")))data_abort_vector(void)
{
	
}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
	arm_timer_t *ArmTimer = (arm_timer_t *)ARMTIMER_BASE;		/*ArmTimer首地址*/
	static int lit = 0;
		
	/* Clear the ARM Timer interrupt - it's the only interrupt we have
	enabled, so we want don't have to work out which interrupt source
	caused us to interrupt */
	ArmTimer->IRQClear = 1;
	
	/* Flip the LED */
	if( lit )
	{
		GPIO_SET_GPSET(16);
		lit = 0;
	}
	else
	{
		GPIO_SET_GPCLR(16);
		lit = 1;
	}
}

void  __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
	
}


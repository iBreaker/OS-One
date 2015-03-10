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
#include "Global.h"
#include "UART.h"


//static irq_controller_t *irq_controller = (irq_controller_t *) INTERRUPT_CONTROLLER_BASE;




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
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("ABORT")))data_abort_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
	
	
	//static int lit = 0;
		
	/* Clear the ARM Timer interrupt - it's the only interrupt we have
	enabled, so we want don't have to work out which interrupt source
	caused us to interrupt */
	
	//ArmTimer->IRQClear = 1;
	//os_timer_ctrl_reflash();

	if(  * (u32*) IRQ_BASIC & 1 != 0 ) //timer
	{
		ArmTimer->IRQClear = 1;
		os_timer_ctrl_reflash();
		task_schedule();
	}
	else if( ((* (u32*) IRQ_PEND1) & ( 1 << 29)) != 0 )
	{
		//os_printf("! ");
		UART_irq_handler();
	}
		//GPIO_SET_GPCLR(16);
		//sleep(50);
	
	/***********************************
	 * 调试代码*
	if( os_timer_ctrl.value  % 1000 == 500 )
	{
		deb_timer_refalsh();
	}
	************************************/
}

void  __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void irq_dispose()
{
	static int  irqqqqq = 0, timerrrr=0, uarttttt=0, irq_enddd=0;
	 //os_printf("+");

	irqqqqq ++;


	if(  * (u32*) IRQ_BASIC & 1 != 1 ) //timer
	{
		timerrrr ++;
		ArmTimer->IRQClear = 1;
		os_timer_ctrl_reflash();
		task_schedule();
		task_global.is_uart_irq = false;
	}
	else if( ((* (u32*) IRQ_PEND1) & ( 1 << 29)) != 0 )
	{
		uarttttt++;
		//UART_irq_handler();
		task_global.is_uart_irq = true;


		 //os_printf("%d", GET32(AUX_MU_IIR_REG));
	    while((GET32(AUX_MU_IIR_REG)&6) == 4) //resolve all interrupts to uart
	    {
	            //receiver holds a valid byte
	         GET32(AUX_MU_IO_REG); //read byte from rx fifo
	        // PUT32(AUX_MU_IIR_REG,0xC6);
	         os_printf("*%d", GET32(AUX_MU_IIR_REG));
	    }
	    sleep(500);
	}
	irq_enddd ++;
	DrawBlock((RGB_24Bit *) GpuBufAddr,colorBlack , 50, 50, 200, 16);
	drawStringF((RGB_24Bit *) GpuBufAddr, "%d %d %d %d", colorWrite , 50, 50,  irqqqqq, timerrrr , uarttttt, irq_enddd);
	//os_printf("-");
}

void uart_test()
{
	//if(task_global.is_uart_irq == true)
		os_printf(".");
}

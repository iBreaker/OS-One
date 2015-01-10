/*
*	2015年01月06日14:00:08
*	V1.0 	By Breaker
*
*	文件名：interrupt.h
*    	中断相关声明
*/
#define   	INTERRUPT_CONTROLLER_BASE	0x2000B200

#define BASIC_ARM_TIMER_IRQ			(1 < < 0)
#define BASIC_ARM_MAILBOX_IRQ	 	(1 << 1)
#define BASIC_ARM_DOORBELL_0_IRQ	(1 << 2)
#define BASIC_ARM_DOORBELL_1_IRQ	(1 << 3)
#define BASIC_GPU_0_HALTED_IRQ		(1 << 4)
#define BASIC_GPU_1_HALTED_IRQ		(1 << 5)
#define BASIC_ACCESS_ERROR_1_IRQ		(1 << 6)
#define BASIC_ACCESS_ERROR_0_IRQ		(1 << 7)



typedef struct {
	volatile unsigned int IRQ_basic_pending;
	volatile unsigned int IRQ_pending_1;
	volatile unsigned int IRQ_pending_2;
	volatile unsigned int FIQ_control;
	volatile unsigned int Enable_IRQs_1;
	volatile unsigned int Enable_IRQs_2;
	volatile unsigned int Enable_Basic_IRQs;
	volatile unsigned int Disable_IRQs_1;
	volatile unsigned int Disable_IRQs_2;
	volatile unsigned int Disable_Basic_IRQs;
}irq_controller_t;

void _enable_interrupts(void);

	
	
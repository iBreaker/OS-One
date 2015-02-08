 /*
*	2015年01月06日15:34:17
*	V1.0 	By Breaker
*
*	文件名：timer.h
*    	系统时钟相关声明
*/ 
#ifndef _TIMER_H
#define _TIMER_H

#include "stdtype.h"
/****
 1. bcm2835 system  timer 
 */
#define TIMER_BASE 	0x20003000
#define TIMER_CS	0x20003000
#define TIMER_CLO	0x20003004
#define TIMER_CHI	0x20003008
#define TIMER_C0	0x2000300c
#define TIMER_C1	0x20003010
#define TIMER_C2	0x20003014
#define TIMER_C3	0x20003018

int sleep(int ms);


/****
 2.ARM timer 
 */
#define ARMTIMER_BASE	0x2000B400

/** @brief 0 : 16-bit counters - 1 : 23-bit counter */
#define ARMTIMER_CTRL_23BIT			( 1 << 1 )

#define ARMTIMER_CTRL_PRESCALE_1	( 0 << 2 )
#define ARMTIMER_CTRL_PRESCALE_16	( 1 << 2 )
#define ARMTIMER_CTRL_PRESCALE_256	( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define ARMTIMER_CTRL_INT_ENABLE	( 1 << 5 )
#define ARMTIMER_CTRL_INT_DISABLE	( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define ARMTIMER_CTRL_ENABLE		( 1 << 7 )
#define ARMTIMER_CTRL_DISABLE		( 0 << 7 )


typedef struct {
	/* timer load 寄存器设置计数器的值。当timer load 寄存器重写或者 
	 timer value 寄存器被减到0的时候，timer load 中的值会写入
	 timer value 寄存器  */
	volatile unsigned int Load;

	/* timer value 寄存器保存当前时间值，并且当计数器运行的时候
	 递减. It is counted down each timer clock until the
	value 0 is reached. Then the value register is re-loaded from the
	timer load register and the interrupt pending bit is set. The timer
	count down speed is set by the timer pre-divide register. */
	volatile unsigned int Value;

	/** The standard SP804 timer control register consist of 8 bits but in the
	BCM implementation there are more control bits for the extra features.
	Control bits 0-7 are identical to the SP804 bits, albeit some
	functionality of the SP804 is not implemented. All new control bits
	start from bit 8 upwards. */
	volatile unsigned int Control;

	/**timer IRQ clear 寄存器是只写寄存器. 当写这个寄存器，未决中断
	 位清零. 读这个寄存器返回 0x544D5241 （"ARMT" 的 ASCII 码）*/
	volatile unsigned int IRQClear;
	
	/** raw IRQ 寄存器是只读寄存器. 这个寄存器显示了未决中断寄存器
	 位。 0：未决终端位为0. 1：未决中断位位1
	The interrupt pending bits is set each time the value register is
	counted down to zero. The interrupt pending bit can not by itself
	generates interrupts. Interrupts can only be generated if the
	interrupt enable bit is set. */
	volatile unsigned int RAWIRQ;
	
	/** masked IRQ 寄存器是只读寄存器. 显示中断信号。
	  It is simply a logical AND of the interrupt
	pending bit and the interrupt enable bit. 0 : Interrupt line not
	asserted. 1 :Interrupt line is asserted, (the interrupt pending and
	the interrupt enable bit are set.)*/
	volatile unsigned int MaskedIRQ;
	
	/** 是timer load 寄存器的备份寄存器，不同点是Reload寄存器写入后
	 值不会立即写入 time value 寄存器。之后当timer value 寄存器值为0
	 的时候才写入timer value。 */
	volatile unsigned int Reload;

	/** The Pre-divider 寄存器 is not present in the SP804. The pre-divider
	寄存器10 bit宽，可读可写。 This
	register has been added as the SP804 expects a 1MHz clock which we do
	not have. Instead the pre-divider takes the APB clock and divides it
	down according to:
	
	timer_clock = apb_clock/(pre_divider+1)
	
	The reset value of this register is 0x7D so gives a divide by 126. */
	volatile unsigned int PreDivider;
	
	/** The free running counter is not present in the SP804. The free running
	counter 32位宽只读寄存器 。这个寄存器通过使能 timer control register bit 9.
	The free running counter is incremented immediately after it is enabled. The timer can
	not be reset but when enabled, will always increment and roll-over.
	
	The free running counter is also running from the APB clock and has
	its own clock pre-divider controlled by bits 16-23 of the timer
	control register.

	This register will be halted too if bit 8 of the control register is
	set and the ARM is in Debug Halt mode. */
	volatile unsigned int FreeRunningCounter;
} arm_timer_t;

/*设置arm timer中断频率*/
void init_arm_timer(unsigned int Load);

/****
 3. os timer
 */

/*内核频率*/
#define Kernrl_1Hz 		1000000
#define Kernrl_10Hz 		100000
#define Kernrl_100Hz 		10000
#define Kernrl_1000Hz 	1000

/*每个os timer的结构*/
typedef struct{
		
	/*os timer 周期*/
	unsigned int load;
	
	/*下次提醒的时间，以os_timer_ctrl 中的value作比较*/
	unsigned int value;
	
	/*下个时钟的id*/
	unsigned char next_os_timer_id;
	
}os_timer_st;


/*os timer ctrl 用来管理os timer 。记录了os timer 的所有信息*/
typedef struct{
	
	/*os timer ctrl 的value，每秒钟100递增*/
	unsigned int value;
	
	/*最多支持256个 os timer*/
	os_timer_st os_timer_t[256];
	
}os_timer_ctrl_st;



 unsigned char set_os_timer(unsigned int ms, unsigned int load);
 void free_os_timer( void );

#endif


/*
*   	2015年02月08日10:57:25
*	V1.0 	By Breaker
*
*	文件名：task.s
*	多任务
*	
*/
.global _interrupt_vector_


/*****************************************************
*	2015年02月08日11:38:45
*	V1.0 	By Breaker
*
*	 _interrupt_vector_
*      中断函数
*	
*/
_interrupt_vector_:
	sub		lr, lr, #4
	push	{r0-r12, lr}
	mrs  	r0, spsr 
	push	{r0}
	mov	ip, sp
	add 		sp, sp, #60
	
	//切换到svc
	mrs  r0, cpsr
	orr	r0, r0, #0x1
	msr cpsr, r0
	
	sub 		sp, sp, #60
	ldmia	ip!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10} 
	stmia	sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	ldmia	ip!, {r1, r2, r3, r4, r5} 
	stmia	sp!, {r1, r2, r3, r4, r5}
	sub 		sp, sp, #60
	
	bl		os_timer_ctrl_reflash
	
	mov	r2, #1
	.word	0x2000B400
	ldr		r3, [pc, #-12]
	str		r2, [r3, #12]

	mov	r0, #16
	bl		GPIO_SET_GPCLR
	mov 	r0, #50
	bl		sleep
	
	ldm		sp!, {r0}
	msr 	cpsr, r0
	
	bl 		_enable_interrupts
	ldm		sp!, {r0-r12, pc}

	

/*------------------可以正常闪烁
	sub		lr, lr, #4
	push	{r0-r12, lr}
	mov	r2, #1
	.word	0x2000B400
	ldr		r3, [pc, #-12]
	str		r2, [r3, #12]

	mov	r0, #16
	bl		GPIO_SET_GPCLR
	mov 	r0, #100
	bl		sleep
	
	ldm		sp!, {r0-r12, pc}^
*/
	
	
/* -------------------------一开始设计的
	sub		lr, lr, #4
	stmfd	sp!, {r0-r12, lr}
	
 	//mrs  	r0, spsr 
	stmfd	sp!, {r0}
	//mov	r0, sp
	//add 		sp, sp, #60
	
	//切换到svc
	//mrs  r0, cpsr
	//orr	r0, r0, #0x02
	//msr cpsr, r0
	
	//复制栈
	//sub 		sp, sp, #60
	//ldmia	r0!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10} 
	//stmia	sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
	//ldmia	r0!, {r1, r2, r3, r4, r5} 
	//stmia	sp!, {r1, r2, r3, r4, r5}
	//sub 		sp, sp, #60
	
	//保存r14 spsr
	//push 	{lr}
	//mrs  	r0, spsr
	//push	{r0}
	
	//bl		os_timer_ctrl_reflash
	mov 	r0, #16
	bl		GPIO_SET_GPCLR
	mov 	r0, #1000
	bl		sleep	
	
	ldmfd 	sp!, {r0}
	//msr 	spsr, r0
	//pop 	{lr}
	
	//pop 	{r0}
	//msr 	cpsr, r0
	
	ldmfd	sp!, {r0-r12, pc}^
	*/
	
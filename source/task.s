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
	//stmfd	sp!,{r0-r12, lr}
	
// 保存
	str		r0, [sp, #-4]
	str		r1, [sp, #-8]
	.word	tasktable
	ldr		r0, [pc, #-12]
	
	ldr		r1, [sp, #-4]
	str		r1, [r0, #(0 * 4)]
	ldr		r1, [sp, #-8]
	str		r1, [r0, #(1 * 4)]
	
	str		r2, [r0, #(2 * 4)]
	str		r3, [r0, #(3 * 4)]
	str		r4, [r0, #(4 * 4)]
	str		r5, [r0, #(5 * 4)]
	str		r6, [r0, #(6 * 4)]
	str		r7, [r0, #(7 * 4)]
	str		r8, [r0, #(8 * 4)]
	str		r9, [r0, #(9 * 4)]
	str		r10, [r0, #(10 * 4)]
	str		r11, [r0, #(11 * 4)]
	str		r12, [r0, #(12 * 4)]
	str		r14, [r0, #(15 * 4)]
	mrs		r1, spsr		
	str		r1, [r0, #(16 * 4)]

	mrs		r1, cpsr
	bic 		r1, r1, #0x1F
	orr		r1, r1, # 0x13
	msr		cpsr, r1

	str		r13,[r0, #(13 * 4)]
	str		r14,[r0, #(14 * 4)]
	mrs		r1, spsr		
	str		r1, [r0, #(17 * 4)]
// 保存
	
	mov	r2, #1
	.word	0x2000B400
	ldr		r3, [pc, #-12]
	str		r2, [r3, #12]

	mov	r0, #16
	bl		GPIO_SET_GPCLR
	mov 	r0, #50
	bl		sleep
	
//恢复
	.word	tasktable
	ldr		r0, [pc, #-12]
	
	ldr		r2, [r0, #(2 * 4)]
	ldr		r3, [r0, #(3 * 4)]
	ldr		r4, [r0, #(4 * 4)]
	ldr		r5, [r0, #(5 * 4)]
	ldr		r6, [r0, #(6 * 4)]
	ldr		r7, [r0, #(7 * 4)]
	ldr		r8, [r0, #(8 * 4)]
	ldr		r9, [r0, #(9 * 4)]
	ldr		r10, [r0, #(10 * 4)]
	ldr		r11, [r0, #(11 * 4)]
	ldr		r12, [r0, #(12 * 4)]
	ldr		r13, [r0, #(13 * 4)]
	ldr		r14, [r0, #(14 * 4)]
	
	ldr		r1,[r0, #(15 * 4)]
	str		r1, [sp, #-4]
	
	ldr		r1, [r0, #(16 * 4)]
	msr		cpsr, r1
	ldr		r1, [r0, #(17 * 4)]
	msr		spsr, r1
	
	ldr		r0, [r0, #(0 * 4)]
	ldr		r1, [r0, #(1 * 4)]
	
	ldr		r15, [sp, #-4]
	
//恢复
	//ldmfd	sp!, {r0-r12, pc}^

	

/*------------------可以正常闪烁
	sub		lr, lr, #4
	push	{r0-r12, lr}
	mov	r2, #1
	.word	0x2000B400
	ldr		r3, [pc, #-12]
	str		r2, [r3, #12]

	mov	r0, #16
	bl		GPIO_SET_GPCLR
	mov 	r0, #50
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
	

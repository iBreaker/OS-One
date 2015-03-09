/*
*   	2015年02月08日10:57:25
*	V1.0 	By Breaker
*
*	文件名：task.s
*	多任务
*	
*/
.global _interrupt_vector_
.extern task_stack , task_global

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
	
	//保存所有的寄存器状态,要把寄存器保存到内存中.先用sp作为临时的基地址
	str		r0, [sp, #-4]
	str		r1, [sp, #-8]
	
	.word	task_global			//加载任务状态内存基地址
	ldr		r1, [pc, #-12]
	ldr		r0, [r1]

	ldr		r1, [sp, #-4]
	str		r1, [r0, #(0 * 4)]	//r0
	ldr		r1, [sp, #-8]
	str		r1, [r0, #(1 * 4)]	//r1
	
	str		r2, [r0, #(2 * 4)]	//r2
	str		r3, [r0, #(3 * 4)]
	str		r4, [r0, #(4 * 4)]
	str		r5, [r0, #(5 * 4)]
	str		r6, [r0, #(6 * 4)]
	str		r7, [r0, #(7 * 4)]
	str		r8, [r0, #(8 * 4)]
	str		r9, [r0, #(9 * 4)]
	str		r10, [r0, #(10 * 4)]
	str		r11, [r0, #(11 * 4)]
	str		r12, [r0, #(12 * 4)]		//r12
	str		r14, [r0, #(15 * 4)]		//r15

	mrs		r1, spsr		
	str		r1, [r0, #(16 * 4)]			//cpsr
	
	mrs		r1, cpsr					//从irq切换到svc
	bic 		r1, r1, #0x1F				// 不可以 bic 	r1, r1, #0xFF,  不知道原因
	orr		r1, r1, # 0x13			
	msr		cpsr, r1

	str		r13,[r0, #(13 * 4)]		//13
	str		r14,[r0, #(14 * 4)]		//14
	mrs		r1, spsr		
	str		r1, [r0, #(17 * 4)]			//spsr
	
//==========================================
	//mov	r2, #1					//清除timer irq
	//.word	0x2000B400
	//ldr		r3, [pc, #-12]
	//str		r2, [r3, #12]

	//bl		UART_irq_handler			//UART中断
	//bl		os_timer_ctrl_reflash		//系统时钟
	//bl		task_schedule					//任务调度
	bl 		irq_dispose

	//在这里添加任务调度函数              
	//终于把任务切换调好了  ;-)  2015年02月11日20:59:00
	
//==========================================
	.word	task_global			//加载任务状态内存基地址
	ldr		r1, [pc, #-12]

	//ldr      r0,[r1, #48]				//（读取task_global.is_uart_irq）如果是UART中断，返回方式和任务切换中断的方式不同
	//cmps r0, #0;
	//bne    uart_irq_return		//UART中断

	ldr		r0, [r1]
      
    ldr		r2, [r0, #(2 * 4)]			//r2
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
	ldr		r14, [r0, #(14 * 4)]		//r14
	
	ldr		r1,[r0, #(15 * 4)]			//将pc的值临时放在sp-4中,因为寄存器都恢复后只有sp指向的内存是安全的
	str		r1, [sp, #-4]
		
	ldr		r1, [r0, #(16 * 4)]			//cpsr
	msr		cpsr, r1					//这里也就打开中断了

	ldr		r1, [r0, #(1 * 4)]			//r1
	ldr		r0, [r0, #(0 * 4)]			//r2			//之前将r0 先回复,r1后恢复.将代码放到ads中才发现这个错误
		
	ldr		pc,[sp, #-4]				//最后恢复pc,跳转


uart_irq_return:



	

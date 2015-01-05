/*
*	2015年01月05日21:57:51
*	V1.0 	By Breaker
*
*	文件名：interrupt.c
*    	中断处理函数
*	
*/

void  __attribute__((interrupt("UNDEF")))undifined_instruction_vector(void)
{
	
}

void  __attribute__((interrupt("SWI")))software_interrupt_vector(void)
{
	
}

void  __attribute__((interrupt("ABORT")))prefetch_abort_vector(void)
{
	
}

void  __attribute__((interrupt("ABORT")))data_abort_vector(void)
{
	
}

void  __attribute__((interrupt("UNDEF")))interrupt_vector(void)
{
	
}

void  __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
	
}


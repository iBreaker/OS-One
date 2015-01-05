/*
*   	2014年12月25日21:09:43
*	V1.0 	By Breaker
*
*	文件名：start.s
*	程序起始点
*	
*/

.section ".text.startup"
.global _start
.global _get_stack_pointer
 
_start:

	ldr pc, _reset_h
	ldr pc, _undifined_instruction_vector_h
	ldr pc, _software_interrupt_vector_h
	ldr pc, _prefetch_abort_vector_h
	ldr pc, _data_abort_vector_h
	ldr pc, _unused_hander_h
	ldr pc, _interrupt_vector_h
	ldr pc, _fast_interrupt_vector_h

_reset_h:								.word		_reset_
_undifined_instruction_vector_h:		.word		undifined_instruction_vector
_software_interrupt_vector_h:		.word		software_interrupt_vector
_prefetch_abort_vector_h:				.word		prefetch_abort_vector
_data_abort_vector_h:					.word		data_abort_vector
_unused_hander_h:					.word		_reset_
_interrupt_vector_h:					.word		interrupt_vector
_fast_interrupt_vector_h:				.word		fast_interrupt_vector

_reset_:
	mov 	r0, #0x8000
	mov	r1, #0x0000
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	
	// Set the stack pointer at the end of RAM.
	// Keep it within the limits and also keep it aligned to a 32-bit
	// boundary!
	ldr     sp, =(128 * (1024 * 1024))
	//ldr     sp, =(256 * (1024 * 1024))
	//ldr     sp, =(512 * (1024 * 1024))
	sub     sp, sp, #0x4
 
	// The c-startup
	b       _cstartup
 
_inf_loop:
	b       _inf_loop
 
_get_stack_pointer:
    // Return the stack pointer value
    str     sp, [sp]
    ldr     r0, [sp]
 
    // Return from the function
    mov     pc, lr

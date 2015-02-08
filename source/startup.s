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
.global _exception_table
.global _enable_interrupts
 
.equ    CPSR_MODE_USER,         		0x10
.equ    CPSR_MODE_FIQ,          		0x11
.equ    CPSR_MODE_IRQ,          		0x12
.equ    CPSR_MODE_SVR,          		0x13
.equ    CPSR_MODE_ABORT,        		0x17
.equ    CPSR_MODE_UNDEFINED,    	0x1B
.equ    CPSR_MODE_SYSTEM,       		0x1F

// See ARM section A2.5 (Program status registers)
.equ    CPSR_IRQ_INHIBIT,       		0x80
.equ    CPSR_FIQ_INHIBIT,       		0x40
.equ    CPSR_THUMB,             			0x20

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
_software_interrupt_vector_h:			.word		software_interrupt_vector
_prefetch_abort_vector_h:				.word		prefetch_abort_vector
_data_abort_vector_h:					.word		data_abort_vector
_unused_hander_h:						.word		_reset_
//_interrupt_vector_h:					.word		interrupt_vector
_interrupt_vector_h:					.word 		_interrupt_vector_
_fast_interrupt_vector_h:				.word		fast_interrupt_vector

_reset_:
	mov 	r0, #0x8000
	mov	r1, #0x0000
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	
	// We're going to use interrupt mode, so setup the interrupt mode
	// stack pointer which differs to the application stack pointer:
	mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
	msr cpsr_c, r0
	mov sp, #0x8000

	// Switch back to supervisor mode (our application mode) and
	// set the stack pointer towards the end of RAM. Remember that the
	// stack works its way down memory, our heap will work it's way
	// up memory toward the application stack.
	mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
	msr cpsr_c, r0
	
	mov     sp, #0x4000
	//ldr     sp, =(128 * (1024 * 1024))
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
    

_enable_interrupts:
    mrs	r0, cpsr
    bic	r0, r0, #0x80
    msr	cpsr_c, r0

    mov     pc, lr


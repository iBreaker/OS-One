.section ".text.startup"
.global _start
.global _get_stack_pointer
 
_start:
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

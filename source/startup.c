/*
*	2014年12月25日21:04:50
*	V1.0 	By Other
*
*	文件名：start.c
*
*	
*/
extern int __bss_start__;
extern int __bss_end__;
 
extern void main( unsigned int r0, unsigned int r1, unsigned int atags );
 
/*
*	2014年12月25日21:06:14
*	V1.0 	By Breaker
*
*	void _cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
*   	初始化bss段
*	return 
*/

void _cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
{

	int* bss = &__bss_start__;
	int* bss_end = &__bss_end__;
 
    	/*
        	Clear the BSS section
 
        	See http://en.wikipedia.org/wiki/.bss for further information on the
            	BSS section
 
        	See https://sourceware.org/newlib/libc.html#Stubs for further
            	information on the c-library stubs
    	*/
    	while( bss < bss_end )
        	*bss++ = 0;
 
    	/* We should never return from main ... */
    	main( r0, r1, r2 );
 
    	/* ... but if we do, safely trap here */
    	while(1)
    	{
        	/* EMPTY! */
    	}
}

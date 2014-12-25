#include <sys/stat.h>
 
/* A helper function written in assembler to aid us in allocating memory */
extern caddr_t _get_stack_pointer(void);
 
/* Increase program data space. As malloc and related functions depend on this,
   it is useful to have a working implementation. The following suffices for a
   standalone system; it exploits the symbol _end automatically defined by the
   GNU linker. */
caddr_t _sbrk( int incr )
{
    extern char _end;
    static char* heap_end;
    char* prev_heap_end;
 
    if( heap_end == 0 )
        heap_end = &_end;
 
     prev_heap_end = heap_end;
 
     if( ( heap_end + incr) > _get_stack_pointer() )
     {
        while(1)
        {
            /* TRAP HERE! */
        }
     }
 
     heap_end += incr;
     return (caddr_t)prev_heap_end;
}

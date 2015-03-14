/*
*	2014年12月25日21:04:50
*	V1.0 	By Other
*
*	文件名：start.c
*
* OS One - A simple OS for Raspberry Pi
* Copyright (C) 2014 - 2015  Breaker  <791628659@qq.com>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
 * **/

extern int __bss_start__;
extern int __bss_end__;
 
extern void os_main( unsigned int r0, unsigned int r1, unsigned int atags );
 
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
 
  
    	while( bss < bss_end )
        	*bss++ = 0;
 

    	os_main( r0, r1, r2 );
 

    	while(1)
    	{
        	/* EMPTY! */
    	}
}

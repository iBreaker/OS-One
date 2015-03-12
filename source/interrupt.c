/*
*	2015年01月05日21:57:51
*	V1.0 	By Breaker
*
*	文件名：interrupt.c
*    	中断处理函数
*	
** OS One - A simple OS for Raspberry Pi
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

#include "interrupt.h"
#include "timer.h"
#include "gpio.h"
#include "Global.h"
#include "UART.h"


void  __attribute__((interrupt("UNDEF")))undifined_instruction_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("SWI")))software_interrupt_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("ABORT")))prefetch_abort_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}

void  __attribute__((interrupt("ABORT")))data_abort_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}


void  __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
	while( 1 )
	{
		/* Do Nothing! */
	}
}


/* **
 * 
* debug.h
* 这里的函数都是开发过程中留下的代码的调试代码, debug.c中的代码也是很好的示例程序
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

void  deb_GPIO(void);															//调试GPIO
void  deb_screen(void);														//调试GPU, 基本的图像输出
void deb_timer(void);															//时钟
void deb_timer_refalsh(void);
void  deb_task(void);															//调试多任务
void deb_os_printf(void);													//调试格式化输出函数
void  deb_linedlist(void);													//调试链表
void dbg_UART(void);															//调试串口
void dbg_memory(void);													//调试内存管理
void dbg_input(void);															//调试鼠标键盘入
void dbg_bmp(void);															//显示bmp
void dbg_form(void);															//窗口

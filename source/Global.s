/*
*   	2014年12月30日16:20:25
*	V1.0 	By Breaker
*
*	文件名：Global.s
*	包含全局变量
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
 

.align 4
.global font , bmp, bg_bmp, color_bmp
.global tasktable, taskstack
font:			/*字体首地址*/
.incbin "./source/font0.bin"

bmp:
.incbin "./bmp/test.bmp"

bg_bmp:
.incbin "./bmp/bg.bmp"

color_bmp:
.incbin "./bmp/color.bmp"

//在这里添加bmp图片



/*
*	2014年12月24日14:16:03
*	V1.0 	By Breaker
*
*	文件名：GPIO.h
*	定义GPIO寄存器地址和GPIO函数声明
*	
*/

#ifndef _GPIO_H_
#define _GPIO_H_
#include "stdtype.h"

#define GPIO_BASE  0x20200000
#define GPFSEL0    0x20200000
#define GPFSEL1    0x20200004UL
#define GPFSEL2    0x20200008UL
#define GPFSEL3    0x2020000cUL
#define GPFSEL4    0x20200010UL
#define GPFSEL5    0x20200014UL   
#define GPSET0     0x2020001CUL
#define GPSET1     0x20200020UL
#define GPCLR0     0x20200028UL
#define GPCLR1     0x2020002cUL
#define GPLEV0     0x20200034UL
#define GPLEV1     0x20200038UL
#define GPEDS0     0x20200040UL
#define GPEDS1     0x20200044UL
#define GPREN0     0x2020004CUL
#define GPREN1     0x20200050UL
#define GPFEN0     0x20200058UL
#define GPFEN1     0x2020005CUL
#define GPHEN0     0x20200064UL
#define GPHEN1     0x20200068UL
#define GPLEN0     0x20200070UL
#define GPLEN1     0x20200074UL
#define GPAREN0    0x2020007CUL
#define GPAREN1    0x20200080UL
#define GPAFEN0    0x20200088UL
#define GPAFEN1    0x2020008CUL
#define GPPUD      0x20200094UL
#define GPPUDCLK0  0x20200098UL
#define GPPUDCLK1  0x2020009CUL

void gpio_init(void);																			//初始化
void GPIO_SET_GPFSEL(u8 pin, u8 mode);								//设置GPIO功能
int GPIO_SET_GPSET(int pin);														//set
int GPIO_SET_GPCLR(int pin);														//clear

//闪烁
void blink_GPIO16(void);
void blink_GPIO19(void);

#endif

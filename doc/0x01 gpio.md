 Raspberry Pi GPIO
========
*2015-3-13 19:17:50*

![B+ GPIO](/IMG/Raspberry_Pi_B+_GPIO.png)

###函数
`void gpio_init(void)`	初始化   
`void GPIO_SET_GPFSEL(u8 pin, u8 mode)` 设置GPIO的功能   
`int GPIO_SET_GPSET(int pin)` set 高电压   
`int GPIO_SET_GPCLR(int pin)` clear   低电压


`void blink_GPIO16(void)` GPIO16闪烁  
`void blink_GPIO19(void)` GPIO19闪烁
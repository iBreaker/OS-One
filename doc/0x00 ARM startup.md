Raspberry Pi 启动 
=========   
*2015年3月13日18:32:10*

###中断向量
* 树莓派B+搭载的是BCM2835的处理器。BMC2835 ARM1176 是ARMv6版本的。在默认条件下，处理器加电后会自动加载SD卡中的kernel.img到内存0x8000处。
* ARM的中断向量是在地址0x00 - 0x20  
	* 0x00 	复位 reset
	* 0x04	未定义指令 
	* 0x08	软终端 SWI
	* 0x0c	指令预取指
	* 0x10	数据访问中止
	* 0x14	保留
	* 0x18	IRQ
	* 0x1c	FIQ  
所以内核加载到内存做的第一件事应该是设置好中断向量。


###ARM处理器模式
ARM处理器共有7中模式，每种模式的寄存器会有些不同。OS One默认运行在SUPERVISOR模式下，当IRQ中断发生时运行在IRQ模式。OS One只使用了这两种模式。  

CPSR中[4:0]表示处理器所处的模式

* 0b10000 USER 
* 0b10001 FIQ 
* 0b10010 IRQ 
* 0B10011 SUPERVISOR 
* 0b10111 ABORT 
* 0b11011 UNDEFINEED 
* 0b11111 SYSTEM 

设置中断向量和sp寄存器后，`b _cstartup` 进入 startup.c中的`_cstartup` 函数。`_cstartup`最终会调用内核主函数 `os_main()`
 
###中断
CPSR第7位是IRQ中断禁止位。两个相关函数`_enable_interrupts`和`_enable_interrupts` 

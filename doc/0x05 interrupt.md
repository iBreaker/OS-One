###树莓派 interrupt
####1.Introduction
>#####ARM 共有两种中断源  
>>1.来自GPU外设的中断  
>>2.来自ARM控制外设  

>#####ARM有三种中断  
>>1.来自ARM特殊外设  
>>2.来自GPU外设的中断  
>>3.特殊事件中断

>#####ARM特殊事件中断:  
>>1.一个定时器   
>>2.一个邮箱（GPU）  
>>3.两个门铃  
>>4.两个GPU空闲中断   
>>5.两个地址/访问错误中断  
>#####邮箱和门铃寄存器不是通用的

>每一个中断源(GPU/ARM)都有一个使能位(R/W)和未决位(RO)  

>默认门铃中断0,1和邮箱0只可被GPU写，ARM读。门铃中断2,3和邮箱中断1相反。

####2. Interrupt pending.
>ARM有三个中断未决寄存器，一个basic pending register 两个 GPU pending registers.
>#####Basic pending register.
>>The basic pending register has interrupt pending bits for the ARM specific interrupts .  

>#####GPU pending registers.      
>>There are two GPU pending registers with one bit per GPU interrupt source.

####3 Fast Interrupt (FIQ).   
>
The ARM also supports a Fast Interrupt (FIQ). One interrupt sources can be selected to be connected
to the ARM FIQ input. There is also one FIQ enable. An interrupt which is selected as FIQ should have
its normal interrupt enable bit cleared. Otherwise an normal and a FIQ interrupt will be fired at the
same time. Not a good idea!    

####4 Interrupt priority.
>
There is no priority for any interrupt. If one interrupt is much more important then all others it can
be routed to the FIQ. Any remaining interrupts have to be processed by polling the pending registers. 
It is up to the ARM software to device a strategy. e.g. First start looking for specific pending
bits or process them all shifting one bit at a time.

####5 Registers
>The base address for the ARM interrupt register is 0x7E00B000.    
>
>
Registers overview:  
>
0x200   IRQ basic pending  
0x204    IRQ pending 1  
0x208   IRQ pending 2   
0x20C     FIQ control   
0x210    Enable IRQs 1  
0x214   Enable IRQs 2  
0x218   Enable Basic IRQs  
0x21C   Disable IRQs 1  
0x220   Disable IRQs 2  
0x224   Disable Basic IRQs

>#####Basic pending register.
>>
The basic pending register shows which interrupt are pending. To speed up interrupts processing, a
number of 'normal' interrupt status bits have been added to this register. This makes the 'IRQ
pending base' register different from the other 'base' interrupt registers

>>######GPU IRQ x (10,11..20)  
>>>
These bits are direct interrupts from the GPU. They have been selected as interrupts which are most
likely to be useful to the ARM. The GPU interrupt selected are 7, 9, 10, 18, 19, 53,54,55,56,57,62. For
details see the GPU interrupts table.

>>######Bits set in pending registers (8,9)
>>>
These bits indicates if there are bits set in the pending 1/2 registers. The pending 1/2 registers hold
ALL interrupts 0..63 from the GPU side. Some of these 64 interrupts are also connected to the basic
pending register. Any bit set in pending register 1/2 which is NOT connected to the basic pending
register causes bit 8 or 9 to set. Status bits 8 and 9 should be seen as "There are some interrupts
pending which you don't know about. They are in pending register 1 /2."  

>>######Illegal access type-0 IRQ (7)
>>>
This bit indicate that the address/access error line from the ARM processor has generated an
interrupt. That signal is asserted when either an address bit 31 or 30 was high or when an access was
06 February 2012 Broadcom Europe Ltd. 406 Science Park Milton Road Cambridge CB4 0WW
© 2012 Broadcom Corporation. All rights reserved
Page 11seen on the ARM Peripheral bus. The status of that signal can be read from Error/HALT status
register bit 2.

>>######Illegal access type-1 IRQ (6)
>>>
This bit indicates that an address/access error is seen in the ARM control has generated an interrupt.
That can either be an address bit 29..26 was high or when a burst access was seen on the GPU
Peripheral bus. The status of that signal can be read from Error/HALT status register bits 0 and 1.

>>######GPU-1 halted IRQ (5)
>>>
This bit indicate that the GPU-1 halted status bit has generated an interrupt. The status of that signal
can be read from Error/HALT status register bits 4.

>>######GPU-0 (or any GPU) halted IRQ (4)
>>>
This bit indicate that the GPU-0 halted status bit has generated an interrupt. The status of that signal
can be read from Error/HALT status register bits 3.
In order to allow a fast interrupt (FIQ) routine to cope with GPU 0 OR GPU-1 there is a bit in control
register 1 which, if set will also route a GPU-1 halted status on this bit.

>>######Standard peripheral IRQs (0,1,2,3)
>>>
These bits indicate if an interrupt is pending for one of the ARM control peripherals.


>#####GPU pending 1 register.
>>
This register holds ALL interrupts 0..31 from the GPU side. Some of these interrupts are also
connected to the basic pending register. Any interrupt status bit in here which is NOT connected to
the basic pending will also cause bit 8 of the basic pending register to be set. That is all bits except 7,
9, 10, 18, 19.

>#####GPU pending 2 register.
>>
This register holds ALL interrupts 32..63 from the GPU side. Some of these interrupts are also
connected to the basic pending register. Any interrupt status bit in here which is NOT connected to
the basic pending will also cause bit 9 of the basic pending register to be set. That is all bits except .
register bits 21..25, 30 (Interrupts 53..57,62).

>#####FIQ register.
>>
The FIQ register control which interrupt source can generate a FIQ to the ARM. Only a single
interrupt can be selected.
>>
FIQ Source.
The FIQ source values 0-63 correspond to the GPU interrupt table. (See above)
The following values can be used to route ARM specific interrupts to the FIQ vector/routine:


>#####Interrupt enable register 1.
>>
Writing a 1 to a bit will set the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected. Only bits which are enabled can be seen in the interrupt pending registers. There is no
provision here to see if there are interrupts which are pending but not enabled.

>#####Interrupt enable register 2
>>
Writing a 1 to a bit will set the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected. Only bits which are enabled can be seen in the interrupt pending registers. There is no
provision here to see if there are interrupts which are pending but not enabled.

>#####Base Interrupt enable register.
>>
Writing a 1 to a bit will set the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected. Again only bits which are enabled can be seen in the basic pending register. There is no
provision here to see if there are interrupts which are pending but not enabled.

>#####Interrupt disable register 1.
>>
Writing a 1 to a bit will clear the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected.

>#####Interrupt disable register 2
>>
Writing a 1 to a bit will clear the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected.

>#####Base disable register.
>>
Writing a 1 to a bit will clear the corresponding IRQ enable bit. All other IRQ enable bits are
unaffected.



























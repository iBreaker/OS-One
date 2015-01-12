###Timer
####Introduction
>
The ARM Timer is based on a ARM AP804, but it has a number of differences with the standard 
SP804:  
>>
• There is only one timer.  
• It only runs in continuous mode.  
• It has a extra clock pre-divider register.  
• It has a extra stop-in-debug-mode control bit.  
• It also has a 32-bit free running counter.  
>
The clock from the ARM timer is derived from the system clock. This clock can change dynamically
e.g. if the system goes into reduced power or in low power mode. Thus the clock speed adapts to
the overal system performance capabilities. For accurate timing it is recommended to use the
system timers.

####Timer Registers:
>
0x400   Load   
0x404   Value                   (Read Only)  
0x408   Control  
0x40C   IRQ Clear/Ack   (Write only)  
0x410   RAW IRQ            (Read Only)  
0x414   Masked IRQ       (Read Only)  
0x418   Reload  
0x41C   Pre-divider (Not in real 804!)  
0x420   Free running counter (Not in real 804!)  

>#####Timer Load register
>>
The timer load register sets the time for the timer to count down. This value is loaded into the timer
value register after the load register has been written or if the timer-value register has counted
down to 0.

>#####Timer Value register:
>>
This register holds the current timer value and is counted down when the counter is running. It is
counted down each timer clock until the value 0 is reached. Then the value register is re-loaded from
the timer load register and the interrupt pending bit is set. The timer count down speed is set by the
timer pre-divide register.

>#####Timer control register:
>>
The standard SP804 timer control register consist of 8 bits but in the BCM implementation there are
more control bits for the extra features. Control bits 0-7 are identical to the SP804 bits, albeit some
functionality of the SP804 is not implemented. All new control bits start from bit 8 upwards.
Differences between a real 804 and the BCM implementation are shown in italics.

>#####Timer IRQ clear register:
>>
The timer IRQ clear register is write only. When writing this register the interrupt-pending bit is
cleared.
When reading this register it returns 0x544D5241 which is the ASCII reversed value for "ARMT".

>#####Timer Raw IRQ register
>>
The raw IRQ register is a read-only register. It shows the status of the interrupt pending bit.
The interrupt pending bits is set each time the value register is counted down to zero. The interrupt
pending bit can not by itself generates interrupts. Interrupts can only be generated if the interrupt
enable bit is set.

>#####Timer Masked IRQ register:
>>
The masked IRQ register is a read-only register. It shows the status of the interrupt signal. It is simply
a logical AND of the interrupt pending bit and the interrupt enable bit.

>#####Timer Reload register:
>>
This register is a copy of the timer load register. The difference is that a write to this register does
not trigger an immediate reload of the timer value register. Instead the timer load register value is
only accessed if the value register has finished counting down to zero.

>#####The timer pre-divider register:
>>
The Pre-divider register is not present in the SP804.
The pre-divider register is 10 bits wide and can be written or read from. This register has been added
as the SP804 expects a 1MHz clock which we do not have. Instead the pre-divider takes the APB
clock and divides it down according to:
timer_clock = apb_clock/(pre_divider+1)
The reset value of this register is 0x7D so gives a divide by 126.

>#####Free running counter
>>
The free running counter is not present in the SP804.
The free running counter is a 32 bits wide read only register. The register is enabled by setting bit 9
of the Timer control register. The free running counter is incremented immediately after it is
enabled. The timer can not be reset but when enabled, will always increment and roll-over. The free
running counter is also running from the APB clock and has its own clock pre-divider controlled by
bits 16-23 of the timer control register.
This register will be halted too if bit 8 of the control register is set and the ARM is in Debug Halt
mode.

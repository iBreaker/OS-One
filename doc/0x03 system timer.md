Raspberry Pi System Timer
=====
*2015-3-13 19:34:29*

###CS Register

System Timer Control / Status.
This register is used to record and clear timer channel comparator matches. The system timer match bits
are routed to the interrupt controller where they can generate an interrupt.
The M0-3 fields contain the free-running counter match status. Write a one to the relevant bit to clear the
match detect status bit and the corresponding interrupt request line.
###CLO Register

System Timer Counter Lower bits.
The system timer free-running counter lower register is a read-only register that returns the current value
of the lower 32-bits of the free running counter.

###CHI Register

 System Timer Counter Higher bits.
The system timer free-running counter higher register is a read-only register that returns the current value
of the higher 32-bits of the free running counter.

###C0 C1 C2 C3 Register

System Timer Compare.
The system timer compare registers hold the compare value for each of the four timer channels.
Whenever the lower 32-bits of the free-running counter matches one of the compare values the
corresponding bit in the system timer control/status register is set.
Each timer peripheral (minirun and run) has a set of four compare registers.

###详见
[BCM2835-ARM-Peripherals](BCM2835-ARM-Peripherals.pdf) 第172页
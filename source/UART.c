
#include "UART.h"
#include "gpio.h"

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );
//GPIO14  TXD0 and TXD1
//GPIO15  RXD0 and RXD1
//alt function 5 for uart1
//alt function 0 for uart0

//((250,000,000/115200)/8)-1 = 270
//------------------------------------------------------------------------
void uart_init ( void )
{
    PUT32(IRQ_DISABLE1,1<<29);

    unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0x5); //enable rx interrupts
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);

    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    PUT32(GPFSEL1,ra);

    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);

    PUT32(AUX_MU_CNTL_REG,3);

    PUT32(IRQ_ENABLE1,1<<29);
}
//------------------------------------------------------------------------
void uart_putc ( unsigned int c )
{
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    PUT32(AUX_MU_IO_REG,c);
}
//------------------------------------------------------------------------
void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_putc(rc);
        if(rb==0) break;
    }
    uart_putc(0x20);
}
//------------------------------------------------------------------------
void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_putc(0x0D);
    uart_putc(0x0A);
}
volatile unsigned int rxhead;
volatile unsigned int rxtail;
#define RXBUFMASK 0xFFF
volatile unsigned char rxbuffer[RXBUFMASK+1];
//-------------------------------------------------------------------------
void UART_irq_handler ( void )
{
    unsigned int rb,rc;

    //an interrupt has occurred, find out why
    rb=GET32(AUX_MU_IIR_REG);
    while((rb&6) == 4) //resolve all interrupts to uart
    {

            //receiver holds a valid byte
         rc=GET32(AUX_MU_IO_REG); //read byte from rx fifo
         rxbuffer[rxhead]=rc&0xFF;
         os_printf("%d-%c", rxbuffer[rxhead], rxbuffer[rxhead]);
         uart_putc(rxbuffer[rxhead]);
         rxhead=(rxhead+1)&RXBUFMASK;
         rb=GET32(AUX_MU_IIR_REG);
    }

}
//------------------------------------------------------------------------

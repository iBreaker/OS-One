/*
*	2015年02月26日18:42:56
*	V1.0 	By Breaker
*
*	文件名：uart.c
*  串口
*/

#include "Global.h"
#include "UART.h"
#include "gpio.h"
#include "fifo.h"
#include "input.h"

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

/*UART.c*/
char input_buf_p[input_size];
char * input_buf = input_buf_p;
FIFO8  input_p;
FIFO8  * input = & input_p;

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

    fifo_init(input, input_buf, input_size);
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

volatile unsigned int rxhead;
volatile unsigned int rxtail;
#define RXBUFMASK 0xFFF
volatile unsigned char rxbuffer[RXBUFMASK+1];
//-------------------------------------------------------------------------
void UART_irq_handler ( void )
{
    unsigned int rb,rc;
    static mouse_status = 0;
    u8 error = false;
    u8  rx;

    //an interrupt has occurred, find out why
    //os_printf("- ");
    rb=GET32(AUX_MU_IIR_REG);
   // os_printf("+");
    while((rb&6) == 4) //resolve all interrupts to uart
    {

            //receiver holds a valid byte
         rc=GET32(AUX_MU_IO_REG); //read byte from rx fifo
         rx = rc&0xFF;

         if( rx==255)
         {
        	 	 //准备接收鼠标信号
        	 	 mouse_status = 1;
        	 	 rx = rc&0xFF;
        	 	 break;
         }

         switch( mouse_status)
         {
         	 	 case 0:		//键盘
     	 		 	 	 if(( rx > 127 ) || (rx < 0))		//非法按键,出错重来
     	 		 	 	 {
     	 		 		 	 error = true;
     	 		 		 	 break;
     	 		 	 	 }
         	 		 	 input_status.key  = rx;
         	 		 	fifo_put(input, fifo_key);
         	 		 	 break;
         	 	 case 1:		//button
         	 		 	 if( (rx < 0) ||  (rx > 3) )			//非法值, 出错重来
         	 		 	 {
         	 		 		 error = true;
         	 		 		 break;
         	 		 	 }
         	 		 	 input_status.button  = rx ;
         	 		 	mouse_status = 2;
         	 	 	 	 break;
         	 	 case 2:		//x
         	 		 	 input_status.x = rx;
          	 		 	mouse_status = 3;
         	 	 	 	 break;
         	 	 case 3:		//y
     	 		 	 	input_status.y = rx;
          	 		 	mouse_status = 0;
          	 		 	fifo_put(input, fifo_mouse);
         	 	 	 	 break;
         }
         //															//加入fifo

         if(error == true)
         {
        	 mouse_status = 0;
        	 break;
         }
         rb=GET32(AUX_MU_IIR_REG);
    }
    //_enable_interrupts();
}
//------------------------------------------------------------------------

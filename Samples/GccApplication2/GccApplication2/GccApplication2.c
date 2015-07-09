
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "uart/uart.h"


#define F_CPU 12.000E6
#define UART_BAUD_RATE      9600      


int main(void)
{
 
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	
	_delay_ms(2000);
 
 
	while(1){
		uart_puts("String stored in SRAM\n");
    

		uart_puts_P("String stored in FLASH\n");
		
		_delay_ms(1000);
	}
	
    
}

#include <avr/io.h>
#include <util/delay.h>

#define BV(bit)               (1 << bit)
#define set_bit(byte, bit)    (byte |= BV(bit))  // old sbi()
#define clear_bit(byte, bit)  (byte &= ~BV(bit)) // old cbi()
#define toggle_bit(byte, bit) (byte ^= BV(bit))

#define LED_Green	PC2
#define LED_Red		PC3
#define LED_PORT	PORTC
#define LED_DDR		DDRC

// Frequenz bestimmung:
#define F_CPU		8000000
#define BAUD		9600

// Bandbreite Berechnungen:
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.


void uart_init(void){
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;
	UCSRB |= (1<<TXEN);								// UART TX einschalten
	UCSRC = (1<<URSEL)|(1 << UCSZ1)|(1 << UCSZ0);	// Asynchron 8N1
}


int uart_putc(unsigned char c)
{
	while (!(UCSRA & (1<<UDRE)))  /* warten bis Senden moeglich */
	{
	}
	UDR = c;                      /* sende Zeichen */
	return 0;
}


void uart_puts (char *s)
{
	while (*s)
	{   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
		uart_putc(*s);
		s++;
	}
}

int main(void)
{
	uart_init();
	set_bit(LED_DDR,LED_Green);
	set_bit(LED_DDR,LED_Red);

    while(1)
    {
		//_delay_ms(20);
		//set_bit(LED_PORT, LED_Green);
		//clear_bit(LED_PORT,LED_Red);
		uart_putc(0b11001100);
		
		_delay_ms(200);
		clear_bit(LED_PORT,LED_Green);
		set_bit(LED_PORT, LED_Red);
		//uart_puts(a);
		
    }
}



#define F_CPU 1000000UL //define clock speed
#include <avr/io.h> //include input/output header file
#include <util/delay.h> //includes delay header file

int main(void)
{
	
	DDRD=0b11000000;
	PORTD=0b00100000;
	while(1)
	{
		if(bit_is_clear(PIND, 5)){
			PORTD |= (1<<6);
			PORTD &= ~(1<<7);
			_delay_ms(100);
			PORTD |= (1<<7);
			PORTD &= ~(1<<6);
			_delay_ms(100);
		}
		else{
			PORTD |= (1<<6);
			PORTD &= ~(1<<7);
			_delay_ms(500);
			PORTD |= (1<<7);
			PORTD &= ~(1<<6);
			_delay_ms(500);
		}
	}
	
}


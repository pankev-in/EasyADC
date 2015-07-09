/*
 * adc.c
 *
 * Created: 5/1/2015 10:33:32 AM
 *  Author: kpan
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned int analog_value=0;
	
	DDRD =0xFF;
	DDRC = 0x00;
	PORTD =0b00000000;
	
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
	// ADEN: Set to turn on ADC , by default it is turned off
	//ADPS2: ADPS2 and ADPS0 set to make division factor 32
	
	ADMUX=0x05; // ADC input channel set to PC5
	
	
	PORTD |= (1<<6);	
	_delay_ms(1000);
	PORTD &= ~(1<<6);
	_delay_ms(1000);
	
    while(1)
    {
		ADCSRA |= (1<<ADSC); // Start conversion
		while (ADCSRA & (1<<ADSC)); // wait for conversion to complete
		analog_value = ADCW; //Store ADC value
		
		if(analog_value < 700){
			PORTD &= ~(1<<6);
		}
		else{
			PORTD |= (1<<6);	
		}
    }
}
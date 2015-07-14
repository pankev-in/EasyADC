#include <avr/io.h>

void ADCinit(){
	//Enable with ADEN and set prescaler to 128:
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

int ADCread(int channel){
	//Clearing the output:
	ADMUX &= 0b11110000;
	
	switch(channel){
		case 0:
		break;
		case 1:
		ADMUX |= (1<<MUX0);
		break;
		case 2:
		ADMUX |= (1<<MUX1);
		break;
		case 3:
		ADMUX |= (1<<MUX0);
		ADMUX |= (1<<MUX1);
		break;
		case 4:
		ADMUX |= (1<<MUX2);
		break;
		case 5:
		ADMUX |= (1<<MUX0);
		ADMUX |= (1<<MUX2);
		break;
		default:
		ADMUX |= (1<<MUX0);
		ADMUX |= (1<<MUX2);
		break;
	}
	
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADCW);
}

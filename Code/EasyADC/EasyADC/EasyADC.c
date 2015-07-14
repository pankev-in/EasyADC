#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "lcd.h"
#include "serial.h"
#include "adc.h"

void show(char data[6][4]){
	lcd_clear();
	
	lcd_setcursor( 1, 1 );
	lcd_string(data[4]);
	
	lcd_setcursor( 6, 1 );
	lcd_string(data[3]);
	
	lcd_setcursor( 11, 1 );
 	lcd_string(data[2]);

	lcd_setcursor( 1, 2 );
	lcd_string(data[1]);
	
	lcd_setcursor( 6, 2 );
	lcd_string(data[0]);
	
	//PWM Signal:
	lcd_setcursor( 11, 2 );
	lcd_string(data[5]);
}

void pwm(int data){
	OCR1A = data;
}

void pwm_init(){
	DDRB |= (1 << DDB1);
	// PB1 as output
	TCCR1A |= (1 << COM1A1);
	// set non-inverting mode
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	// set 10bit phase corrected PWM Mode
	TCCR1B |= (1 << CS11);
	// set prescaler to 8 and starts PWM
}

int main(void)
{
	
	//Initial Serial, ADC & LCD Display:
	USARTInit(52);
	lcd_init();
	ADCinit();
	pwm_init();
	
	char adc_output[6][4];	
	int adc_value[6]; // Variable to hold ADC result
	
    while(1)
   {	
	   for(int i=0;i<6;i++){
		   adc_value[i] = ADCread(i);
		   itoa(adc_value[i],adc_output[i],10);
		   USARTWriteString(adc_output[i]);
		   if(i!=5){USARTWriteChar(';');}
	   }
	   
		//Sending a new line:
	   	USARTWriteChar('\r');
	   	USARTWriteChar('\n');
		
		//Set PWM:
		pwm(adc_value[5]);
		
		//Show data on the lcd display   
		show(adc_output);
		
		//Delay:
		_delay_ms(500);
   }
}





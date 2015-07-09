#include <avr/io.h>
#include <inttypes.h>



void USARTInit(uint16_t ubrr_value)
{

   //Set Baud rate
  UBRRL = ubrr_value;
  UBRRH = (ubrr_value>>8);

   /*Set Frame Format

   
   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit
   >> char size 8

   */

   //Enable The receiver and transmitter
   UCSRB=(1<<RXEN)|(1<<TXEN);
   UCSRC = (1<<URSEL)|(1 << UCSZ1)|(1 << UCSZ0);


}

char USARTReadChar()
{
	//Wait untill a data is available

	while(!(UCSRA & (1<<RXC)))
	{
		//Do nothing
	}

	//Now USART has got data from host
	//and is available is buffer

	return UDR;
}

void USARTWriteChar(char data)
{
	//Wait until the transmitter is ready

	while(!(UCSRA & (1<<UDRE)))
	{
		//Do nothing
	}

	//Now write the data to USART buffer

	UDR=data;
}

void USARTWriteString(char data[]){
	int i =0;
	while (data[i] != 0x00)
	{
		USARTWriteChar(data[i]);
		i++;
	}
	
	//Starting new line for next output:
	USARTWriteChar('\r');
	USARTWriteChar('\n');
}

void ADCinit(){
	
	//selecting ADC5 as my channel:
	ADMUX |= (1<<MUX0);
	ADMUX |= (1<<MUX2);
	
	//Enable with ADEN and set prescaler to 128:
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

int ADCread(){
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}

int main(void)
{
	USARTInit(52);
	
	char output[4];	
	int adc_value; // Variable to hold ADC result
	ADCinit();
	
    while(1)
   {
	   
		adc_value = ADCread(0);
		itoa(adc_value,output,10);	

		//Now write the data to USART buffer
		USARTWriteString(output);
   }
}
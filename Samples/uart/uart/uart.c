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

int main(void)
{
	
	char data;
	USARTInit(52);
	DDRD = 0XFF;
	
    while(1)
   {
		//Read data
		data=USARTReadChar();


		//Now write the data to USART buffer
		USARTWriteChar('[');
		USARTWriteChar(data);
		USARTWriteChar(']');
		USARTWriteChar('\n');

   }
}
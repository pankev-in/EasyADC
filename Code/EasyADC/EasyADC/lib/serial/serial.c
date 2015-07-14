#include <avr/io.h>
#include "serial.h"

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
}

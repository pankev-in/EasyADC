#ifndef SERIAL_H
#define SERIAL_H

void USARTInit(uint16_t ubrr_value);

char USARTReadChar();

void USARTWriteChar(char data);

void USARTWriteString(char data[]);

#endif
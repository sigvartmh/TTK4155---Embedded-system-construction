#ifndef UART_H_
#define UART_H_

#include <stdio.h>

#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1) // defines BAUD
#define BUFFER_SIZE 80 //sets ringbuffer size

int UART_init(unsigned int baudrate);
int UART_putchar(char c, FILE *f);
char UART_recchar(void);
int UART_print(char * str);
extern FILE *uart;

#endif 
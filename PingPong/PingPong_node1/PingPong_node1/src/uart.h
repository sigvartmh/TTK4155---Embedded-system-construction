#ifndef UART_H_
#define UART_H_

#include <stdio.h>

int UART_init(unsigned int baudrate);
int UART_putchar(char c, FILE *f);
unsigned char UART_recchar(void);
int UART_print(char * str);
extern FILE *uart;

#endif 
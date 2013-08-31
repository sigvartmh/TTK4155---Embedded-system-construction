#ifndef UART_H_
#define UART_H_
#include<stdio.h>

uint8_t uart_init(unsigned int baudrate);
uint8_t uart_putchar(char c, FILE *f);
unsigned char uart_recchar();
void uart_print(char * str);
extern FILE *uart;


#endif 
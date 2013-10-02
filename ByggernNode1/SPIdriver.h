#pragma once

int SPI_init();
int SPI_transmit(char data);
char SPI_receive();

void SPI_selected();
void SPI_deselected();
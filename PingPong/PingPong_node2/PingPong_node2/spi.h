#ifndef SPI_H_
#define SPI_H_

int SPI_init(void);

int SPI_send(char data);
uint8_t SPI_read(void);

void SPI_select(void);
void SPI_deselect(void);

#endif
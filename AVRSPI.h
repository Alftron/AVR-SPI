/*
A simple SPI library written in C for personal use
This was written with ATMega328P in mind but SPI is pretty portable across the range
We're going to assume that the user is handling the chip/slave selects.

Author: Martin Haycock 2020
*/

#ifndef SPI_H
#define SPI_H

#define SPI_SS		PB2
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5

void spi_master_init();
void spi_slave_init();
void spi_transmit(char data);
char spi_receive();

#endif

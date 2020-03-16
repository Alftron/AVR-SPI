/*
A simple SPI library written in C for personal use
This was written with ATMega328P in mind but SPI is pretty portable across the range
We're going to assume that the user is handling the chip/slave selects.

Author: Martin Haycock 2020
*/

#include "SPI.h"

#include <avr/io.h>

void spi_master_init(void) {
	// Set SCK, MOSI and SS as outputs (DDR_SPI might be faster but not as readable)
	DDRB |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);
	// MISO as input
	DDRB &= ~(1 << SPI_MISO);
	// Set chip as master
	SPCR |= (1 << MSTR);
	// Enable SPI
	SPCR |= (1 << SPE);

}

void spi_slave_init(void) {
	// Set SCK, MOSI and SS as inputs (DDR_SPI might be faster but not as readable)
	DDRB &= ~(1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);
	// MISO as output
	DDRB |= (1 << SPI_MISO);
}

void spi_transmit(char data) {
	// Start transmission by loading data into SPI data register
	SPDR = data;
	/* Wait for transmission to complete by reading interrupt flag
		which is set by the hardware when an SPI transfer is complete
	*/
	while (!(SPSR & (1 << SPIF)));
}

char spi_receive(void) {
	// Wait for receive to finish
	while (!(SPSR & (1 << SPIF)));
	// Return the data
	return SPDR;
}

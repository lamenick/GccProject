
#include "UARTDriver.h"
extern "C" {
	#include <asf.h>
	};



#define USART_SERIAL &AVR32_USART2
#define USART_SERIAL_BAUDRATE 9600
#define USART_SERIAL_CHAR_LENGTH 8
#define USART_SERIAL_PARITY USART_NO_PARITY
#define USART_SERIAL_STOP_BITS USART_1_STOPBIT

using namespace Empty;

EmptyUARTDriver::EmptyUARTDriver() {}

void EmptyUARTDriver::begin(uint32_t b) {
	static usart_serial_options_t usart_options;
	usart_options.baudrate = USART_SERIAL_BAUDRATE;
	usart_options.charlength = USART_SERIAL_CHAR_LENGTH;
	usart_options.paritytype = USART_SERIAL_PARITY;
	usart_options.stopbits = USART_SERIAL_STOP_BITS;
	usart_serial_init(USART_SERIAL, &usart_options);
}
void EmptyUARTDriver::begin(uint32_t b, uint16_t rxS, uint16_t txS) {}
void EmptyUARTDriver::end() {}
void EmptyUARTDriver::flush() {}
bool EmptyUARTDriver::is_initialized() { return false; }
void EmptyUARTDriver::set_blocking_writes(bool blocking) {}
bool EmptyUARTDriver::tx_pending() { return false; }

/* Empty implementations of Stream virtual methods */
int16_t EmptyUARTDriver::available() { return 0; }
int16_t EmptyUARTDriver::txspace() { return 1; }
int16_t EmptyUARTDriver::read() { return -1; }

/* Empty implementations of Print virtual methods */
size_t EmptyUARTDriver::write(uint8_t c) { 
	 usart_serial_putchar(&AVR32_USART2,c);
	return 1;
	}

size_t EmptyUARTDriver::write(const uint8_t *buffer, size_t size)
{
	size_t n = 0;
	while (size--) {
		n += write(*buffer++);
	}
	return n;
}




//BURDAN ITIBAREN COPY PASTE

size_t EmptyUARTDriver::print(const char str[])
{
	return write(str);
}

size_t EmptyUARTDriver::print(char c)
{
	return write(c);
}

size_t EmptyUARTDriver::print(unsigned char b, int base)
{
	return print((unsigned long) b, base);
}

size_t EmptyUARTDriver::print(int n, int base)
{
	return print((long) n, base);
}

size_t EmptyUARTDriver::print(unsigned int n, int base)
{
	return print((unsigned long) n, base);
}

size_t EmptyUARTDriver::print(long n, int base)
{
	if (base == 0) {
		return write(n);
		} else if (base == 10) {
		if (n < 0) {
			int t = print('-');
			n = -n;
			return printNumber(n, 10) + t;
		}
		return printNumber(n, 10);
		} else {
		return printNumber(n, base);
	}
}

size_t EmptyUARTDriver::print(unsigned long n, int base)
{
	if (base == 0) return write(n);
	else return printNumber(n, base);
}

size_t EmptyUARTDriver::print(float n, int digits)
{
	return printFloat(n, digits);
}

// the compiler promotes to double if we do arithmetic in the
// argument, but we only actually want float precision, so just wrap
// it with a double method
size_t EmptyUARTDriver::print(double n, int digits)
{
	return print((float)n, digits);
}

size_t EmptyUARTDriver::println(void)
{
	size_t n = print('\r');
	n += print('\n');
	return n;
}

size_t EmptyUARTDriver::println(const char c[])
{
	size_t n = print(c);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(char c)
{
	size_t n = print(c);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(unsigned char b, int base)
{
	size_t n = print(b, base);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(int num, int base)
{
	size_t n = print(num, base);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(unsigned int num, int base)
{
	size_t n = print(num, base);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(long num, int base)
{
	size_t n = print(num, base);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(unsigned long num, int base)
{
	size_t n = print(num, base);
	n += println();
	return n;
}

size_t EmptyUARTDriver::println(float num, int digits)
{
	size_t n = print(num, digits);
	n += println();
	return n;
}

// the compiler promotes to double if we do arithmetic in the
// argument, but we only actually want float precision, so just wrap
// it with a double method
size_t EmptyUARTDriver::println(double num, int digits)
{
	return println((float)num, digits);
}

// Private Methods /////////////////////////////////////////////////////////////

size_t EmptyUARTDriver::printNumber(unsigned long n, uint8_t base) {
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	if (base < 2) base = 10;

	do {
		unsigned long m = n;
		n /= base;
		char c = m - base * n;
		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	return write(str);
}

size_t EmptyUARTDriver::printFloat(float number, uint8_t digits)
{
	size_t n = 0;
	
	// Handle negative numbers
	if (number < 0.0f)
	{
		n += print('-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	float rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
	rounding /= 10.0f;
	
	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	float remainder = number - (float )int_part;
	n += print(int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0) {
		n += print(".");
	}

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0f;
		int toPrint = int(remainder);
		n += print(toPrint);
		remainder -= toPrint;
	}
	
	return n;
}

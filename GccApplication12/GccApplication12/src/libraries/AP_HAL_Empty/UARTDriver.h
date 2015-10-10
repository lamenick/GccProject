
#ifndef __AP_HAL_EMPTY_UARTDRIVER_H__
#define __AP_HAL_EMPTY_UARTDRIVER_H__

#include "AP_HAL_Empty.h"

class Empty::EmptyUARTDriver : public AP_HAL::UARTDriver {
public:
    EmptyUARTDriver();
    /* Empty implementations of UARTDriver virtual methods */
    void begin(uint32_t b);
    void begin(uint32_t b, uint16_t rxS, uint16_t txS);
    void end();
    void flush();
    bool is_initialized();
    void set_blocking_writes(bool blocking);
    bool tx_pending();

    /* Empty implementations of Stream virtual methods */
    int16_t available();
    int16_t txspace();
    int16_t read();

    /* Empty implementations of Print virtual methods */

	
	enum flow_control {
        FLOW_CONTROL_DISABLE=0, FLOW_CONTROL_ENABLE=1, FLOW_CONTROL_AUTO=2
    };
    virtual void set_flow_control(enum flow_control flow_control_setting) {};
    virtual enum flow_control get_flow_control(void) { return FLOW_CONTROL_DISABLE; };

    /* Implementations of BetterStream virtual methods. These are
     * provided by AP_HAL to ensure consistency between ports to
     * different boards
     */
    void print_P(const  prog_char_t *s);
    void println_P(const prog_char_t *s);
    void printf(const char *s, ...);
            __attribute__ ((format(__printf__, 2, 3)));
    void _printf_P(const prog_char *s, ...)
           __attribute__ ((format(__printf__, 2, 3)));

	#define printf_P(fmt, ...) _printf_P((const prog_char *)fmt, ## __VA_ARGS__)

    //void vprintf(const char *s, va_list ap);
    //void vprintf_P(const prog_char *s, va_list ap);
	

	#define printf_P(fmt, ...) _printf_P((const prog_char *)fmt, ## __VA_ARGS__)


	
	/*PRINT.H CLASS METHODS*/
	enum {
		BASE_DEFAULT = 0,
		BASE_BIN     = 2,
		BASE_OCT     = 8,
		BASE_DEC     = 10,
		BASE_HEX     = 16
	};
	
	   virtual size_t write(uint8_t) ;
	   virtual size_t write(const uint8_t *buffer, size_t size) ;

	   size_t write(const char *str) { return write((const uint8_t *)str, strlen(str)); }
	   size_t print(const char[]);
	   size_t print(char);
	   size_t print(unsigned char, int = BASE_DEC);
	   size_t print(int, int = BASE_DEC);
	   size_t print(unsigned int, int = BASE_DEC);
	   size_t print(long, int = BASE_DEC);
	   size_t print(unsigned long, int = BASE_DEC);
	   size_t print(float , int = 2);
	   size_t print(double , int = 2);

	   size_t println(const char[]);
	   size_t println(char);
	   size_t println(unsigned char, int = BASE_DEC);
	   size_t println(int, int = BASE_DEC);
	   size_t println(unsigned int, int = BASE_DEC);
	   size_t println(long, int = BASE_DEC);
	   size_t println(unsigned long, int = BASE_DEC);
	   size_t println(float , int = 2);
	   size_t println(double , int = 2);
	   size_t println(void);
	   
	   //STREAM.H METHODS
	   
	  size_t printNumber(unsigned long n, uint8_t base);
	  size_t printFloat(float number, uint8_t digits);
};

#endif // __AP_HAL_EMPTY_UARTDRIVER_H__

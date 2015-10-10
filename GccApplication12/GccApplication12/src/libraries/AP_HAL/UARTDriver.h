
#ifndef __AP_HAL_UART_DRIVER_H__
#define __AP_HAL_UART_DRIVER_H__

#include <stdint.h>
#include <inttypes.h>
#include <string.h>


#include "libraries/AP_HAL/AP_HAL_Namespace.h"
#include "libraries/AP_Progmem/AP_Progmem.h"


/* Pure virtual UARTDriver class */
class AP_HAL::UARTDriver {
public:
    UARTDriver() {}
    virtual void begin(uint32_t baud) = 0;
	/// Extended port open method
	///
	/// Allows for both opening with specified buffer sizes, and re-opening
	/// to adjust a subset of the port's settings.
	///
	/// @note	Buffer sizes greater than ::_max_buffer_size will be rounded
	///			down.
	///
	/// @param	baud		Selects the speed that the port will be
	///						configured to.  If zero, the port speed is left
	///						unchanged.
	/// @param rxSpace		Sets the receive buffer size for the port.  If zero
	///						then the buffer size is left unchanged if the port
	///						is open, or set to ::_default_rx_buffer_size if it is
	///						currently closed.
	/// @param txSpace		Sets the transmit buffer size for the port.  If zero
	///						then the buffer size is left unchanged if the port
	///						is open, or set to ::_default_tx_buffer_size if it
	///						is currently closed.
	///
    virtual void begin(uint32_t baud, uint16_t rxSpace, uint16_t txSpace) = 0;
    virtual void end() = 0;
    virtual void flush() = 0;
    virtual bool is_initialized() = 0;
    virtual void set_blocking_writes(bool blocking) = 0;
    virtual bool tx_pending() = 0;
	

    enum flow_control {
        FLOW_CONTROL_DISABLE=0, FLOW_CONTROL_ENABLE=1, FLOW_CONTROL_AUTO=2
    };
    virtual void set_flow_control(enum flow_control flow_control_setting) {};

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
	
	   virtual size_t write(uint8_t) = 0;
	   virtual size_t write(const uint8_t *buffer, size_t size) = 0;

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
	   
	virtual int16_t available() = 0;
    /* NB txspace was traditionally a member of BetterStream in the
     * FastSerial library. As far as concerns go, it belongs with available() */
    virtual int16_t txspace() = 0;

    /* return value for read():
     * -1 if nothing available, uint8_t value otherwise. */
    virtual int16_t read() = 0;
	
	
	//BETTERSTREAM.H METHODS
	   
	
};

#endif // __AP_HAL_UART_DRIVER_H__


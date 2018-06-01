#include <stdint.h> // uints types
#include <stdbool.h> // bool tyoe
#include <system.h>

#include "altera_avalon_spi.h" // alt_avalon_spi_command()
#include "sys/alt_stdio.h" //**
// Reduced library similar to stdio.h
// alt_getchar(), alt_putchar(), alt_putstr(), alt_printf()

#define WRITE_BUFFER 50 // buffer para la fn write_add_bulk(), cantidad de
  // bits maximos a escribir


// ****************************************************************************
// *                              MAIN INTERFACE                              *
// ****************************************************************************

// -- MACROS --

#define BIT(x,n) (((x) >> (n)) & 1) // USEFUL MACRO to extract bit

// __ main functions __

void read_id();
void sector_erase(uint32_t add);
void write_memory(uint32_t add, uint8_t value);
uint8_t read_add(uint32_t add);
void read_add_bulk(uint32_t add, uint32_t num_data, uint8_t * data);
void write_add_bulk(uint32_t add, uint32_t num_data, uint8_t * data);
void reset_command();
void read_autoboot(uint32_t num_data, uint8_t * data);

// __ status register related functions __

void write_enable(); // ** write enable se deshabilita después de cada
// funcion de escritura (revisar 8.2 write enable command en 8. Data Protection)
void write_disable();
void clear_status_register();
uint8_t read_status_register();
void check_write_enable(bool value_target);
void check_write_in_progress();

// __ auxiliary functions __
void split_32_to_8_bits(uint32_t number, uint8_t * pointer);


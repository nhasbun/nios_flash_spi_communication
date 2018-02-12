#include <stdint.h> // uints types
#include <stdbool.h> // bool tyoe
#include <system.h>

#include "altera_avalon_spi.h" // alt_avalon_spi_command()
#include "sys/alt_stdio.h" //**
// Reduced library similar to stdio.h
// alt_getchar(), alt_putchar(), alt_putstr(), alt_printf()

// USEFUL MACRO to extract bit
#define BIT(x,n) (((x) >> (n)) & 1)

// *** MAIN INTERFACE ***

// main functions
void read_id();
void write_enable();
void write_disable();
void sector_erase(uint32_t add);
void write_memory(uint32_t add, uint8_t value);
uint8_t read_add(uint32_t add);

// status register related functions
void clear_status_register();
uint8_t read_status_register();
void check_write_enable(bool value_target);
void check_write_in_progress();

// auxiliary functions
void split_32_to_8_bits(uint32_t number, uint8_t * pointer);


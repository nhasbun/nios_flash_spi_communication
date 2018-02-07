#include <stdint.h> // uints types

#include "altera_avalon_spi.h" // alt_avalon_spi_command()

uint32_t spi_mediator_base_address = 0x0;
// change this to the corresponding address

uint8_t flash_spi_input[20] = { 0 }; // **
// Idealmente aca iría un malloc(), pero esto permite ahorrar esa librería
// sin mayores problemas.

void read_id();


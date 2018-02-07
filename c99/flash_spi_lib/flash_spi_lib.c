#include "flash_spi_lib.h"

void read_id()
{
  uint8_t comando[4] = {0x90, 0, 0, 0};
  uint32_t * com_p = (uint32_t*)comando;

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 4, (alt_u8*)com_p, 2, input, 0);
  alt_printf("%x %x %x %x \n", comando[0], comando[1], comando[2], comando[3]);
  alt_printf("%x %x \n", input[0], input[1]);
}
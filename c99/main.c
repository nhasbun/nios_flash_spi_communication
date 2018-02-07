#include "main.h"

#ifdef SPI_MEDIATOR_BASE
// #elif
#endif

int main()
{
  uint8_t input[20] = { 0 }; // **
  // Idealmente aca iría un malloc(), pero esto permite ahorrar esa librería
  // sin mayores problemas.

  alt_putstr("Hello from Nios II!\n");

  uint8_t comando[4] = {0x90, 0, 0, 0};
  uint32_t * com_p = (uint32_t*)comando;

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 4, (alt_u8*)com_p, 2, input, 0);
  alt_printf("%x %x %x %x \n", comando[0], comando[1], comando[2], comando[3]);
  alt_printf("%c %c \n", input[0], input[1]);
  alt_printf("%x %x \n", input[0], input[1]);
  alt_getchar();


  while(1);
  return 0;
}


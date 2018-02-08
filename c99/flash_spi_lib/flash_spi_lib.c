#include "flash_spi_lib.h"

#ifdef SPI_MEDIATOR_BASE
#endif

uint32_t spi_mediator_base_address = SPI_MEDIATOR_BASE;
// change this to the corresponding address

uint8_t input[20] = { 0 }; // **
// Idealmente aca iría un malloc(), pero esto permite ahorrar esa librería
// sin mayores problemas.



void read_id()
{
  alt_putstr("\n");
  alt_putstr("*** READ_ID ***\n");

  uint8_t comando[4] = {0};
  split_32_to_8_bits(0x90000000, comando);

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 4, (alt_u8*)comando, 2, input, 0);
  alt_printf("%x %x %x %x \n", comando[0], comando[1], comando[2], comando[3]);
  alt_printf("%x %x \n", input[0], input[1]);
}

void write_enable()
{
  alt_putstr("\n");
  alt_putstr("*** Write enable ***\n");

  // write enable
  uint8_t wren = 0x06;
  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 1, (alt_u8*) &wren, 0, input, 0);
}

void write_disable()
{
  // write disable
  uint8_t wrdi = 0x04;
  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 1, (alt_u8*) &wrdi, 0, input, 0);

}

void sector_erase(uint32_t add)
{
  alt_putstr("\n");
  alt_putstr("*** Clear memory sector ***\n");

  // Sector erase, necesita write enable activado
  uint8_t address_splitted[4] = {0};
  split_32_to_8_bits(add, address_splitted);

  uint8_t comando[5] = {0xdc, address_splitted[0], address_splitted[1],
    address_splitted[2], address_splitted[3]};

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 5, (alt_u8*)comando, 0, input, 0);
  alt_printf("%x\n %x %x %x %x\n",
    comando[0],
    comando[1],
    comando[2],
    comando[3],
    comando[4],
    comando[5]);
}

void write_memory(uint32_t add, uint8_t value)
{
  alt_putstr("\n");
  alt_putstr("*** Write to memory ***\n");

  // page programming (write action)
  uint8_t address_splitted[4] = {0};
  split_32_to_8_bits(add, address_splitted);

  uint8_t comando[6] = {0x12, address_splitted[0], address_splitted[1],
    address_splitted[2], address_splitted[3], value};

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 6, (alt_u8*)comando, 0, input, 0);
  alt_printf("%x\n %x %x %x %x\n %x\n",
    comando[0],
    comando[1],
    comando[2],
    comando[3],
    comando[4],
    comando[5],
    comando[6]);
}

uint8_t read_add(uint32_t add)
{
  alt_putstr("\n");
  alt_putstr("*** READ ADDRESS ***\n");

  uint8_t address[4] = { 0 };
  split_32_to_8_bits(add, address);

  // Construccion de comando
  uint8_t comando[5] = {0x13, address[0], address[1], address[2], address[3]};

  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 5, (alt_u8*)comando, 1, input, 0);
  alt_printf("%x %x %x %x %x\n",
    comando[0], comando[1], comando[2], comando[3], comando[4]);

  return input[0];
}

void split_32_to_8_bits(uint32_t number, uint8_t * pointer)
{
  // Descomposicion del address en numeros de 8 bits
  uint32_t mask = 0xff; // mascara de 8'b 1111_1111
  uint8_t number_split[4] =
    {(number >> 24) & mask, (number >> 16) & mask, (number >> 8) & mask,
      number & mask};

  // Memcpy function not available
  int i = 0;
  for (i = 0; i < 4; i++) {
    *pointer = number_split[i]; pointer++;
  }
}

uint8_t read_status_register()
// Read status register 1
{
  // alt_putstr("\n");
  // alt_putstr("*** READ STATUS REGISTER ***\n");

  uint8_t comando = 0x05;
  alt_avalon_spi_command(SPI_MEDIATOR_BASE, 0, 1, &comando, 1, input, 0);
  // alt_printf("%x\n", input[0]);

  return input[0];
}

void check_status_register_safe()
// Funcion que bloquea el avance del programa hasta que la memoria flash
// este lista.
{
  while(1) {
    uint8_t status = read_status_register();
    if (status == 0) break;
    if (status == 2) break;
  }
}

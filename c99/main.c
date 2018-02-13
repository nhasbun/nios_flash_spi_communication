#include "main.h"

#define TEST_ADD 0x01FFF000

// Pequeña rutina para testear la librería de escritura y lectura
// a memoria flash

int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");

  uint8_t value = 0x23;

  clear_status_register();

  while(1) {

    read_id();
    uint8_t test = read_add(TEST_ADD);
    alt_printf("%x\n", test);
    write_memory(TEST_ADD, value);
    test = read_add(TEST_ADD);
    alt_printf("%x\n", test);

    uint8_t status = read_status_register();
    alt_printf("Status Register: %x\n", status);

    alt_getchar();
    value++;
  }

  return 0;
}


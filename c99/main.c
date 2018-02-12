#include "main.h"

#define TEST_ADD 0x00020000

int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");

  uint8_t value = 23;

  clear_status_register();

  while(1) {

    read_id();
    write_enable();
    sector_erase(TEST_ADD);
    write_memory(TEST_ADD, value);
    write_disable();
    uint8_t test = read_add(TEST_ADD);
    alt_printf("%x\n", test);

    uint8_t status = read_status_register();
    alt_printf("Status Register: %x\n", status);

    alt_getchar();
    value++;
  }

  return 0;
}


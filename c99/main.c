#include "main.h"

#define TEST_ADD 0x01FD0000

int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");

  uint8_t value = 0;

  while(1) {

    read_id();
    write_enable();

    check_status_register_safe();
    sector_erase(TEST_ADD);

    check_status_register_safe();
    write_memory(TEST_ADD, value);

    check_status_register_safe();
    write_memory(TEST_ADD, value);

    check_status_register_safe();
    write_disable();

    check_status_register_safe();
    uint8_t test = read_add(TEST_ADD);

    check_status_register_safe();
    alt_printf("%x\n", test);
    check_status_register_safe();

    read_status_register();

    alt_getchar();
    value++;
  }

  return 0;
}


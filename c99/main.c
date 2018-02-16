#include "main.h"

#define TEST_ADD 0x01FFF000 // Sector SA541 64kbyte

// Pequeña rutina para testear la librería de escritura y lectura
// a memoria flash

int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");

  test2();

  while(1);

  return 0;
}

void test1()
{
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
}

void test2()
{
  uint8_t value = 0x23;

  write_enable();
  sector_erase(TEST_ADD);

  write_enable();
  write_memory(TEST_ADD, value);

  write_enable();
  write_memory(TEST_ADD + 1, value + 1);

  uint8_t data[2] = {0};
  read_add_bulk(TEST_ADD, 2, data);

  alt_printf("Datos en memoria\n");
  alt_printf("%x\n", data[0]);
  alt_printf("%x\n", data[1]);
}

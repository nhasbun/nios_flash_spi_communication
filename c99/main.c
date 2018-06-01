#include "main.h"

#define TEST_ADD 0x01FFF000 // Sector SA541 64kbyte
#define N_DATA 64 // Cantidad de datos para probar rutinas de lectura

// Rutina para testear la librería de escritura y lectura
// a memoria flash.

/*
int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");

  read_id();

  uint8_t numeros[5] = {1, 2, 3, 4, 5};

  write_enable();
  sector_erase(TEST_ADD);

  write_enable();
  write_add_bulk(TEST_ADD, 5, numeros);

  uint8_t data[5] = {0};
  read_add_bulk(TEST_ADD, 5, data);

  alt_printf("Datos en memoria\n");
  alt_printf("%x\n", data[0]);
  alt_printf("%x\n", data[1]);
  alt_printf("%x\n", data[2]);
  alt_printf("%x\n", data[3]);
  alt_printf("%x\n", data[4]);

  while(1);

  return 0;
}
*/


// Rutina para testear el comando de software-reset y los datos entregados
// por autoboot.

int main()
{
  alt_putstr("SPI FLASH INTERFACE!\n");
  read_id();

  uint8_t data[5] = {0};

  reset_command();

  alt_getchar();

  read_autoboot(50, data);

  alt_printf("Datos en memoria\n");

  uint8_t i = 0;
  for (i = 0; i < 50; i++) {
    alt_printf("%x - ", data[i]);
  }

  alt_getchar();
  reset_command();
  alt_getchar();
  read_autoboot(50, data);

  alt_printf("Datos en memoria\n");
  for (i = 0; i < 50; i++) {
    alt_printf("%x - ", data[i]);
  }

  while(1);
  return 0;
}









module top_module (
  input CLOCK_EXT_100,

  // LEDS
  output [7:0] LED_ARRAY,

  // FLASH MEMORY INTERFACE (SPI)
  output      FLASH_CE,         //FLASH Chip Enable
  output      FLASH_MOSI_IO0,   //FLASH SI o IO0 mosi
  input       FLASH_MISO_IO1,   //FLASH SO o IO1 miso
  inout       FLASH_WP_IO2,     //FLASH WP o IO2
  inout       FLASH_HOLD_IO3,   //FLASH HOLD o IO3
  output      FLASH_CLK         //FLASH Clock
  );

parameter GROUND = 1'b0;
////////////////////////////////

// PLL AND CLOCK CONFIGURATIONS
wire clock_50, reset_n;
pll_50 inst_pll_50 (.inclk0(CLOCK_EXT_100), .c0(clock_50), .locked(reset_n));

///////////////////////////////

// NIOS CONTROL OF SPI FLASH

nios_flash_interface nios_flash_spi (
  .clock_50_clk               (clock_50),
  .reset_n_reset_n            (reset_n),
  .spi_mediator_external_MISO (FLASH_MISO_IO1),
  .spi_mediator_external_MOSI (FLASH_MOSI_IO0),
  .spi_mediator_external_SCLK (FLASH_CLK),
  .spi_mediator_external_SS_n (FLASH_CE)
);

// SPI DEBUG
wire SPI_MOSI, SPI_MISO;

assign SPI_MOSI = FLASH_MOSI_IO0;
assign SPI_MISO = FLASH_MISO_IO1;
assign SPI_CS   = FLASH_CE;
assign SPI_CLK  = FLASH_CLK;

////////////////////////////////

// LED ASSIGNMENT

assign LED_ARRAY = {SPI_MISO, SPI_MOSI, FLASH_CE, FLASH_CLK, {4{GROUND}}};

endmodule





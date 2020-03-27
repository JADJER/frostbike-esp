//
// Created by jadjer on 3/27/20.
//

#include "spi.hpp"
#include <cstring>

SPI::SPI(int miso, int mosi, int clk, int cs, int size) {
  spi_device_handle_ = new spi_device_handle_t();

  spi_bus_config_t spi_bus_config;
  spi_bus_config.miso_io_num = miso;
  spi_bus_config.mosi_io_num = mosi;
  spi_bus_config.sclk_io_num = clk;
  spi_bus_config.quadwp_io_num = -1;
  spi_bus_config.quadhd_io_num = -1;
  spi_bus_config.max_transfer_sz = size;

  spi_device_interface_config_t spi_device_interface_config;
  spi_device_interface_config.clock_speed_hz = 10 * 1000 * 1000;
  spi_device_interface_config.mode = 0;
  spi_device_interface_config.spics_io_num = cs;
  spi_device_interface_config.queue_size = 7;

  esp_err_t ret;

  //Initialize the SPI bus
  ret = spi_bus_initialize(HSPI_HOST, &spi_bus_config, 2);
  ESP_ERROR_CHECK(ret);

  //Attach the LCD to the SPI bus
  ret = spi_bus_add_device(HSPI_HOST, &spi_device_interface_config, spi_device_handle_);
  ESP_ERROR_CHECK(ret);
}

SPI::~SPI() {
  delete spi_device_handle_;
}

void SPI::writeCommand(uint8_t cmd) {
  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));       //Zero out the transaction
  t.length = 8;                     //Command is 8 bits
  t.tx_buffer = &cmd;               //The data is the cmd itself
  t.user = (void *) 0;                //D/C needs to be set to 0
  ret = spi_device_polling_transmit(*spi_device_handle_, &t);  //Transmit!
  assert(ret == ESP_OK);            //Should have had no issues.
}

void SPI::writeData(const uint8_t *data, int len) {
  esp_err_t ret;
  spi_transaction_t t;
  if (len == 0) return;             //no need to send anything
  memset(&t, 0, sizeof(t));       //Zero out the transaction
  t.length = len * 8;                 //Len is in bytes, transaction length is in bits.
  t.tx_buffer = data;               //Data
  t.user = (void *) 1;                //D/C needs to be set to 1
  ret = spi_device_polling_transmit(*spi_device_handle_, &t);  //Transmit!
  assert(ret == ESP_OK);            //Should have had no issues.
}
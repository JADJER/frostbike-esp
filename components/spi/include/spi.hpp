//
// Created by jadjer on 3/27/20.
//

#ifndef FROSTBIKE_ESP_COMPONENTS_SPI_INCLUDE_SPI_HPP_
#define FROSTBIKE_ESP_COMPONENTS_SPI_INCLUDE_SPI_HPP_

#include <driver/spi_master.h>

class SPI {
 public:
  explicit SPI(int miso, int mosi, int clk, int cs, int size);
  ~SPI();

  void writeCommand(uint8_t cmd);
  void writeData(const uint8_t *data, int len);

 private:
  spi_device_handle_t * spi_device_handle_;
};

#endif  // FROSTBIKE_ESP_COMPONENTS_SPI_INCLUDE_SPI_HPP_

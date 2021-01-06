/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>

#include <metal/spi.h>

int main() {
	printf("METAL SPI Driver Demo\n");

	struct metal_spi *spi;

	/* Get SPI 1 */
	spi = metal_spi_get_device(1);

	/* Fallback to SPI 0 */
	if(spi == NULL) {
		spi = metal_spi_get_device(0);
	}

	if(spi == NULL) {
		printf("Failed to get spi device\n");
		return 1;
	}

	/* Initialize the SPI device to 100_000 baud */
	metal_spi_init(spi, 100000);

	/* CPOL = 0, CPHA = 0, MSB-first, CS active low */
	struct metal_spi_config config = {
		.protocol = METAL_SPI_SINGLE,
		.polarity = 0,
		.phase = 0,
		.little_endian = 0,
		.cs_active_high = 0,
		.csid = 0,
	};

	/* Transfer three bytes */
	char tx_buf[3] = {0x55, 0xAA, 0xA5};
	char rx_buf[3] = {0};

	metal_spi_transfer(spi, &config, 3, tx_buf, rx_buf);

	return 0;
}

#include <stdio.h>

#include <mee/spi.h>
#include <mee/machine.h>

/* Choose SPI 1 if available, else choose SPI 0 */
#ifdef __MEE_DT_SPI_1_HANDLE
#define SPI_HANDLE __MEE_DT_SPI_1_HANDLE
#elif __MEE_DT_SPI_0_HANDLE
#define SPI_HANDLE __MEE_DT_SPI_0_HANDLE
#else
#error "No SPI device handle is provided by mee/machine.h"
#endif

int main() {
	printf("MEE SPI Driver Demo\n");

	/* Initialize the SPI device to 100_000 baud */
	mee_spi_init(SPI_HANDLE, 100000);

	/* CPOL = 0, CPHA = 0, MSB-first, CS active low */
	struct mee_spi_config config = {
		.protocol = SPI_SINGLE,
		.polarity = 0,
		.phase = 0,
		.little_endian = 0,
		.cs_active_high = 0,
		.csid = 0,
	};

	/* Transfer three bytes */
	char tx_buf[3] = {0x55, 0xAA, 0xA5};
	char rx_buf[3] = {0};

	mee_spi_transfer(SPI_HANDLE, &config, 3, tx_buf, rx_buf);

	return 0;
}

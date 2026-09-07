/*
 * 003SPI_Tx_Testing.c
 *
 *  Created on: 06-Sept-2026
 *      Author: Manikanta Kore
 */


#include "stm32f446.h"

/*
 * Pins used
 *
 * We are using SPI2 Peripheral for this implementation
 *
 * PB15 ----> SPI2_MOSI
 * PB14 ----> SPI2_MISO
 * PB13 ----> SPI2_SCLK
 * PB12 ----> SPI2_NSS
 * ALT Funtion Mode : 5
 *
 */


/*
 * @brief This function initializes GPIO pins for SPI peripheral
 */
void SPI_GPIOInits(void)
{
	//configuring GPIO pin

	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Enabling SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}


/*
 * @brief This function initializes SPI peripherals
 */

void SPI_Inits(void)
{
	SPI_Handle_t SPIHandle;

	SPIHandle.pSPIx = SPI2;
	SPIHandle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPIHandle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPIHandle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPIHandle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPIHandle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPIHandle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPIHandle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPIHandle);
}
int main(void)
{
	//user buffer
	char user_data[] = "Hello World";

	// initializing gpio pins
	SPI_GPIOInits();

	// initializing spi peripheral
	SPI_Inits();

	// Send Data
	SPI_SendData(SPI2, user_data, strlen(user_data));
	return 0;
}

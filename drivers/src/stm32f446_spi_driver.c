/*
 * stm32f446_spi_driver.c
 *
 *  Created on: Sep 5, 2026
 *      Author: Manikanta Kore
 */

#include "stm32f446.h"
#include "stm32f446_spi_driver.h"

/**

@brief Controls the peripheral clock for an SPI peripheral.


@details
This function enables or disables the APB peripheral clock
corresponding to the specified SPI peripheral.


The STM32F446RE provides four SPI peripherals:
SPI1, SPI2, SPI3, and SPI4.


SPI1 and SPI4 are connected to the APB2 bus, while SPI2 and
SPI3 are connected to the APB1 bus. The corresponding clock
enable and disable bits are controlled through the RCC
peripheral clock enable registers.


@param[in] pSPIx




         Pointer to the SPI peripheral.




         Valid values:




         - SPI1




         - SPI2




         - SPI3




         - SPI4


@param[in] EnorDi




         Peripheral clock control state:




         - ENABLE  : Enable the SPI peripheral clock.




         - DISABLE : Disable the SPI peripheral clock.


@return None.


@note The SPI peripheral clock must be enabled before




         accessing or configuring the SPI registers.


@example




         SPI_PeriClockControl(SPI1, ENABLE);






         // Configure SPI1...






         SPI_PeriClockControl(SPI1, DISABLE);

*/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){

	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
    		SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
    	{
			SPI3_PCLK_DI();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_DI();
		}
    }	
}

/**

@brief Initializes the specified SPI peripheral.


@details
This function configures the SPI peripheral according to the
parameters specified in the SPI handle.


The configuration includes SPI bus configuration such as:


SPI device mode (master/slave)


Bus configuration (full-duplex, half-duplex, simplex)


Clock speed / baud-rate prescaler


Clock polarity (CPOL)


Clock phase (CPHA)


Software/hardware slave management


DFF (8-bit/16-bit data frame format)


The SPI peripheral clock must be enabled before calling this
function.


@param[in] pSPIHandle




         Pointer to the SPI handle containing the SPI




         peripheral instance and its configuration.


@return None.


@note The SPI peripheral should be disabled before




         modifying its configuration registers.

*/

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	// enable spi clk
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	// configure the SPI_CR1 register
	uint32_t tempreg = 0;

	// 1. configure device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	// 2. configure bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//clear BiDi mode
		tempreg &= ~( 1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//Set BiDi mode
		tempreg |= ~( 1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//clear BiDi mode
		tempreg &= ~( 1 << 15);
		//Set RxOnly
		tempreg |= ~( 1 << 10);
	}	

	//3. configure spi serial clock speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	//4. configure DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;

	//5. configure CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	//6. configure CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	pSPIHandle->pSPIx->CR1 = tempreg;

}

/**

@brief De-initializes the specified SPI peripheral.


@details
This function resets the selected SPI peripheral to its
default reset state using the corresponding RCC peripheral
reset register.


Resetting the SPI peripheral clears its configuration and
returns the SPI registers to their reset values.


@param[in] pSPIx




         Pointer to the SPI peripheral to be reset.




         Valid values:




         - SPI1




         - SPI2




         - SPI3




         - SPI4


@return None.


@note This function resets the SPI peripheral but does




         not necessarily disable the peripheral clock.




         Use SPI_PeriClockControl() with DISABLE separately




         if the SPI peripheral clock also needs to be disabled.

*/

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
	else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/**

@brief Sends data over the specified SPI peripheral.


@details
This function transmits a sequence of data bytes through the
SPI peripheral. It monitors the SPI status register and waits
until the transmit buffer is empty before writing each byte
to the SPI data register.


The function supports both 8-bit and 16-bit data-frame
configurations and adjusts the data transmission accordingly.


@param[in] pSPIx




         Pointer to the SPI peripheral used for




         transmission.




         Valid values:




         - SPI1




         - SPI2




         - SPI3




         - SPI4


@param[in] pTxBuffer




         Pointer to the transmit data buffer.


@param[in] Len




         Number of data elements to be transmitted.


@return None.


@note The SPI peripheral must be configured and enabled




         before calling this function.

*/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t Len)
{
	// Checck if length is greater than 0
	while(Len > 0)
	{
		// wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET );

		// check the DFF bit in CR1
		if( pSPIx->CR1 & ( 1 << SPI_CR1_DFF ) )
		{
			// 16 bit DFF
			// 1. load the data in to the DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			// 8 bit
			pSPIx->DR = *(pTxBuffer);
			Len--;
			pTxBuffer++;
		}
	}
}

/**

@brief Receives data from the specified SPI peripheral.


@details
This function receives a sequence of data elements from the
SPI peripheral. It monitors the SPI status register and waits
until received data is available in the SPI data register
before reading it into the receive buffer.


The function supports both 8-bit and 16-bit data-frame
configurations and adjusts the data reception accordingly.


@param[in] pSPIx




         Pointer to the SPI peripheral used for




         reception.




         Valid values:




         - SPI1




         - SPI2




         - SPI3




         - SPI4


@param[out] pRxBuffer




         Pointer to the receive data buffer where the




         received data will be stored.


@param[in] Len




         Number of data elements to be received.


@return None.


@note The SPI peripheral must be configured and enabled




         before calling this function.

*/

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint8_t Len)
{
	// Checck if length is greater than 0
	while(Len > 0)
	{
		// wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET );

		// check the DFF bit in CR1
		if( pSPIx->CR1 & ( 1 << SPI_CR1_DFF ) )
		{
			// 16 bit DFF
			// 1. load the data in to the pRxBuffer
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}
		else
		{
			// 8 bit
			*(pRxBuffer) = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

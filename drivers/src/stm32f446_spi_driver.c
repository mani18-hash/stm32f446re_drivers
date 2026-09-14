/*
 * stm32f446_spi_driver.c
 *
 *  Created on: Sep 5, 2026
 *      Author: Manikanta Kore
 */

#include "stm32f446.h"
#include "stm32f446_spi_driver.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);
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


uint8_t SPI_SendDataWithIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint8_t Len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		//1. Save the Tx buffer address and Len information in some global variables
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;

		//2. Mark the SPI state as busy in transmission so that no other code can take over same SPI peripheral until transmission is over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		//3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_TXEIE );

		//4. Data Transmission will be handled by the ISR code
	}

	return state;
}

uint8_t SPI_ReceiveDataWithIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint8_t Len)
{
	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1. Save the Tx buffer address and Len information in some global variables
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;

		//2. Mark the SPI state as busy in transmission so that no other code can take over same SPI peripheral until transmission is over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		//3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE );

		//4. Data Transmission will be handled by the ISR code
	}

	return state;
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

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF ))
	{
		//16 bit
		//1. load data into DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}
	else
	{
		//8 bit DFF
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}

	if( !pSPIHandle->TxLen )
	{
		//if TxLen is zero, close the spi transmission and inform application that Tx is over

		//this prevents interrupts from setting up of TXE flag
		pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE );
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxLen = 0;
		pSPIHandle->TxState = SPI_READY;
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}

}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF ))
	{
		//16 bit
		//1. load data into DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pRxBuffer);
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer++;
	}
	else
	{
		//8 bit DFF
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pRxBuffer);
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer++;
	}

	if( !pSPIHandle->RxLen )
	{
		//if TxLen is zero, close the spi transmission and inform application that Tx is over

		//this prevents interrupts from setting up of TXE flag
		pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE );
		pSPIHandle->pRxBuffer = NULL;
		pSPIHandle->RxLen = 0;
		pSPIHandle->RxState = SPI_READY;
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}

}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	//clear OVR flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	//inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_CMPLT);

}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{

}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{

}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;
	//check for TXE interrupt
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_TXE );
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIXE );

	if( temp1 && temp2 )
	{
		spi_txe_interrupt_handle();
	}

	//check for RXNE
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE );
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIXE );

	if( temp1 && temp2 )
	{
		spi_rxne_interrupt_handle();
	}

	//check for ovr flag
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_OVR );
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE );

	if( temp1 && temp2)
	{
		spi_ovr_err_interrupt_handle();
	}
}


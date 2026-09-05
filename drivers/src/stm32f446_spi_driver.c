/*
 * stm32f446_spi_driver.c
 *
 *  Created on: Sep 5, 2026
 *      Author: Manikanta Kore
 */


#include "stm32f446_spi_driver.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pSPIx, uint8_t EnorDi){

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

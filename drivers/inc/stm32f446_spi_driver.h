/*
 * stm32f446.h
 *
 *  Created on: 08-Aug-2026
 *      Author: Manikanta Kore
 */


#ifndef INC_STM32F446_SPI_DRIVER_H_
#define INC_STM32F446_SPI_DRIVER_H_


#include "stm32f446.h"

/*************************Peripheral Register definition structure for SPIx***************************/

typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
}SPI_Config_t;

/*
* Peripheral Handle for SPIx
*/

typedef struct 
{
    SPI_RegDef_t    *pSPIx;
    SPI_Config_t     SPIConfig;
}SPI_Handle_t;


/******************************************************************************************************************
 * 									APIs supported by this driver
 *****************************************************************************************************************/

 /* Peripheral clock setup*/

void GPIO_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/* Initialize and De-innitialize*/

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx); 


/* Data Send and Receive */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *TxBuffer, uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *RxBuffer, uint32_t Len);

/* IRQ config and ISR handling */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t);


#endif
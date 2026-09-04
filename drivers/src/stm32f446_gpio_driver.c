/*
 * stm32f446_gpio.c
 *
 *  Created on: 08-Aug-2026
 *      Author: Manikanta Kore
 */

#include "stm32f446_gpio_driver.h"



/**
 * @brief       Controls the peripheral clock for a GPIO port.
 *
 * @details
 * This function enables or disables the AHB1 peripheral clock
 * corresponding to the specified GPIO port.
 *
 * The STM32F446RE contains GPIO ports GPIOA through GPIOH.
 * All GPIO peripheral clocks are controlled through the RCC
 * AHB1 peripheral clock enable register (AHB1ENR).
 *
 * @param[in]   pGPIOx
 *              Pointer to the GPIO peripheral.
 *              Valid values:
 *              - GPIOA
 *              - GPIOB
 *              - GPIOC
 *              - GPIOD
 *              - GPIOE
 *              - GPIOF
 *              - GPIOG
 *              - GPIOH
 *
 * @param[in]   EnorDi
 *              Peripheral clock control state:
 *              - ENABLE  : Enable GPIO peripheral clock.
 *              - DISABLE : Disable GPIO peripheral clock.
 *
 * @return      None.
 *
 * @note        GPIO peripheral clock must be enabled before
 *              accessing the GPIO registers.
 *
 * @example
 *              GPIO_PeriClockControl(GPIOA, ENABLE);
 *
 *              // Configure GPIOA...
 *
 *              GPIO_PeriClockControl(GPIOA, DISABLE);
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){

	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
				if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				else if(pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}
				else if(pGPIOx == GPIOC)
				{
					GPIOC_PCLK_DI();
				}
				else if(pGPIOx == GPIOD)
				{
					GPIOD_PCLK_DI();
				}
				else if(pGPIOx == GPIOE)
				{
					GPIOE_PCLK_DI();
				}
				else if(pGPIOx == GPIOF)
				{
					GPIOF_PCLK_DI();
				}
				else if(pGPIOx == GPIOG)
				{
					GPIOG_PCLK_DI();
				}
				else if(pGPIOx == GPIOH)
				{
					GPIOH_PCLK_DI();
				}
	}
}

/**
 * @brief  Initializes a GPIO pin according to the specified configuration.
 *
 * @details
 * Configures the selected GPIO pin by updating the corresponding
 * peripheral registers. The function configures:
 *
 *          1. GPIO pin mode
 *          2. GPIO output speed
 *          3. Pull-up / pull-down configuration
 *          4. Output type
 *          5. Alternate-function selection (when applicable)
 *
 * @param  pGPIOHandle  Pointer to the GPIO handle containing:
 *                      - GPIO peripheral address
 *                      - Pin number
 *                      - Pin mode
 *                      - Pin speed
 *                      - Pull-up / pull-down configuration
 *                      - Output type
 *                      - Alternate-function selection
 *
 * @return None.
 *
 * @note   For alternate-function mode, the corresponding alternate
 *         function must be configured using GPIO_PinAltFunMode.
 *
 * @note   The GPIO peripheral clock must be enabled before calling
 *         this function.
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    /* 1. Configure GPIO pin mode */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        /* Non-interrupt mode */

        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<
                (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

        /* Clear the 2 bits corresponding to the pin */
        pGPIOHandle->pGPIOx->MODER &=
                ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

        /* Set the required mode */
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        /* Interrupt mode */
    	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
    	{
    		//1. configure FTSR
    		EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    		//Clear the RTSR bit
    		EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    	}
    	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
    	{
    		//1. configure RTSR
    		EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    		//Clear the FTSR bit
       		EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    	}
    	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
    	{
    		//1. configure both RTSR and FTSR
    		EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    		//Clear the RTSR bit
    		EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    	}

    	//2. configure the GPIO port selection in SYSCFG_EXTICR
    	uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
    	uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
    	uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

    	SYSCFG_PCLK_EN();
    	SYSCFG->EXTICR[temp1] = portcode << ( temp2 * 4);

    	//3. enable the exti interrupt delivery using IMR
    	EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;

    /* 2. Configure GPIO speed */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<
            (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

    pGPIOHandle->pGPIOx->OSPEEDER &=
            ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

    pGPIOHandle->pGPIOx->OSPEEDER |= temp;

    temp = 0;

    /* 3. Configure GPIO pull-up / pull-down */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl <<
            (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

    pGPIOHandle->pGPIOx->PUPDR &=
            ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = 0;

    /* 4. Configure GPIO output type */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<
            pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

    pGPIOHandle->pGPIOx->OTYPER &=
            ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;

    /* 5. Configure alternate function */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

        /* Clear the 4 bits corresponding to the pin */
        pGPIOHandle->pGPIOx->AFR[temp1] &=
                ~(0xF << (4 * temp2));

        /* Set the alternate function */
        pGPIOHandle->pGPIOx->AFR[temp1] |=
                (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <<
                 (4 * temp2));
    }
}

/**
 * @brief  De-initializes the specified GPIO peripheral.
 *
 * @details
 * Resets all registers of the selected GPIO peripheral to their
 * reset/default values by asserting the corresponding GPIO reset
 * signal through the RCC peripheral.
 *
 * @param  pGPIOx  Pointer to the GPIO peripheral to be de-initialized.
 *                 Valid values include GPIOA, GPIOB, GPIOC, GPIOD,
 *                 GPIOE, GPIOF, GPIOG, and GPIOH.
 *
 * @return None.
 *
 * @note   The GPIO peripheral clock/reset control must be available
 *         through the RCC peripheral.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

		if(pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_REG_RESET();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_REG_RESET();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_REG_RESET();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_REG_RESET();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_REG_RESET();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_REG_RESET();
		}
}

/**
 * @brief  Reads the input logic level of a specific GPIO pin.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral register structure.
 *                    Example: GPIOA, GPIOB, GPIOC, etc.
 *
 * @param  PinNumber  GPIO pin number to be read.
 *                    Valid values depend on the MCU, typically 0 to 15.
 *
 * @return uint8_t
 *         0 : GPIO pin is LOW
 *         1 : GPIO pin is HIGH
 *
 * @note   The function reads the selected pin from the GPIO Input Data
 *         Register (IDR). The selected bit is shifted to bit 0 and
 *         masked to obtain only the pin's logic state.
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;

	value = (uint8_t )( (pGPIOx->IDR >> PinNumber ) & 0x00000001 );

	return value;
}

/**
 * @brief  Reads the input data from the specified GPIO port.
 *
 * @details
 * Reads the complete 16-bit Input Data Register (IDR) of the
 * specified GPIO peripheral and returns its current value.
 *
 * @param  pGPIOx  Pointer to the GPIO peripheral whose input port
 *                 is to be read.
 *
 * @return uint16_t
 *         16-bit value representing the logic state of all GPIO
 *         pins in the selected port.
 *
 * @note   Each bit in the returned value corresponds to the
 *         respective GPIO pin:
 *         Bit 0  -> Pin 0
 *         Bit 1  -> Pin 1
 *         ...
 *         Bit 15 -> Pin 15
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;

	value = (uint16_t )pGPIOx->IDR;

	return value;
}

/**
 * @brief  Writes a logic level to a specific GPIO output pin.
 *
 * @details
 * Sets or clears the corresponding bit in the GPIO Output Data
 * Register (ODR) based on the specified value.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral.
 * @param  PinNumber  GPIO pin number to be written.
 *                    Valid values are typically 0 to 15.
 * @param  Value      Output value to be written.
 *                    GPIO_PIN_SET  -> Pin is driven HIGH.
 *                    GPIO_PIN_RESET -> Pin is driven LOW.
 *
 * @return None.
 *
 * @note   The specified GPIO pin must be configured as an output
 *         before calling this function.
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// Write 1 to output data register to corresponding pin number
		pGPIOx->ODR |= ( 1 << PinNumber);
	}
	else
	{
		//Write 0 to output data register to corresponding pin number
		pGPIOx->ODR &= ~( 1 << PinNumber);
	}
}

/**
 * @brief  Writes a 16-bit value to the specified GPIO output port.
 *
 * @details
 * Writes the provided 16-bit value directly to the GPIO Output Data
 * Register (ODR). Each bit of the value corresponds to the output
 * state of the respective GPIO pin.
 *
 * @param  pGPIOx  Pointer to the GPIO peripheral.
 *
 * @param  Value   16-bit value to be written to the GPIO output port.
 *                 Bit 0  -> GPIO Pin 0
 *                 Bit 1  -> GPIO Pin 1
 *                 ...
 *                 Bit 15 -> GPIO Pin 15
 *
 * @return None.
 *
 * @note   The GPIO pins should be configured as output pins before
 *         calling this function.
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/**
 * @brief  Toggles the output state of a specific GPIO pin.
 *
 * @details
 * Toggles the corresponding bit in the GPIO Output Data Register (ODR)
 * using the XOR operation.
 *
 * If the pin is currently HIGH, it will be changed to LOW.
 * If the pin is currently LOW, it will be changed to HIGH.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral.
 *
 * @param  PinNumber  GPIO pin number to be toggled.
 *                    Valid values are typically 0 to 15.
 *
 * @return None.
 *
 * @note   The specified GPIO pin must be configured as an output
 *         before calling this function.
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= ( 1 << PinNumber);
}

/* IRQ config and ISR handling */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber < 31)
		{
			//program ISER0 reg
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 reg
			*NVIC_ISER1 |= ( 1 << IRQNumber % 32);
		}
		else if(IRQNumber > 64 && IRQNumber < 96)
		{
			//program ISER2 reg
			*NVIC_ISER2 |= ( 1 << IRQNumber % 64);
		}
	}
	else
	{
		if(IRQNumber < 31)
		{
			//program ICER0 reg
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ICER1 reg
			*NVIC_ICER1 |= ( 1 << IRQNumber % 32);
		}
		else if(IRQNumber > 64 && IRQNumber < 96)
		{
			//program ICER2 reg
			*NVIC_ICER2 |= ( 1 << IRQNumber % 64);
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//1. Find out IPR register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED );

	*(NVIC_PR_BASE_ADDR + ( iprx * 4 ) ) |= ( IRQPriority <<  shift_amount);

}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the exti pr resgister
	if( EXTI->PR & ( 1 << PinNumber ) )
	{
		//clear
		EXTI->PR |= ( 1 << PinNumber );
	}
}

/*
 * stm32f446_gpio_driver.h
 *
 *  Created on: 08-Aug-2026
 *      Author: Manikanta Kore
 */

/*
 ******************************************************************************
 * @file        stm32f446_gpio_driver.h
 * @author      Kore Manikanta
 * @version     1.0
 * @date        08-Aug-2026
 * @brief       GPIO driver header file for STM32F446RE.
 *
 * @details
 * This file contains:
 *   - GPIO configuration structures
 *   - GPIO handle structure
 *   - GPIO configuration macros
 *   - GPIO driver API declarations
 *
 * Target MCU:
 *   STM32F446RE
 *
 * GPIO Features:
 *   - GPIO input
 *   - GPIO output
 *   - Alternate function
 *   - Analog mode
 *   - Pull-up / pull-down configuration
 *   - Output speed configuration
 *   - Output type configuration
 *   - GPIO interrupts
 *
 ******************************************************************************
 */

#ifndef INC_STM32F446_GPIO_DRIVER_H_
#define INC_STM32F446_GPIO_DRIVER_H_


#include "stm32f446.h"

/*
 * Configuration structure for a GPIO pin
 */
/**
 * @brief GPIO pin configuration structure.
 *
 * @details
 * This structure contains all configuration parameters required
 * to initialize a GPIO pin.
 */
typedef struct
{
    uint8_t GPIO_PinNumber;        /**< GPIO pin number: 0-15 */
    uint8_t GPIO_PinMode;         /**< GPIO pin mode */
    uint8_t GPIO_PinSpeed;        /**< GPIO output speed */
    uint8_t GPIO_PinPuPdControl;  /**< Pull-up / pull-down configuration */
    uint8_t GPIO_PinOPType;       /**< Output type */
    uint8_t GPIO_PinAltFunMode;   /**< Alternate function selection */
} GPIO_PinConfig_t;


/**
 * @brief GPIO handle structure.
 *
 * @details
 * Contains the GPIO peripheral base address and the
 * configuration parameters for the selected GPIO pin.
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx;						/* This holds the base address of GPIO port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;			/* This holds the GPIO pin configuration settings */
}GPIO_Handle_t;


/*
 * GPIO Pin numbers
 */

#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15


/*
 * GPIO POSSIBLE MODES
 */

#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANALOG		3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6


/*
 * GPIO pin possible output types
 */

#define GPIO_OP_TYPE_PP			0
#define GPIO_OP_TYPE_OD			1

/*
 * GPIO pin possible output speeds
 */

#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3

/*
 * GPIO pin pull up and pull down configuration macros
 */

#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2
/******************************************************************************************************************
 * 									APIs supported by this driver
 *****************************************************************************************************************/


/* Peripheral clock setup*/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Initialize and De-innitialize*/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Read and Write */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/* IRQ config and ISR handling */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
















#endif /* INC_STM32F446_GPIO_DRIVER_H_ */

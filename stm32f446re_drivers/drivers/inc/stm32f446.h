/*
 * stm32f446.h
 *
 *  Created on: 08-Aug-2026
 *      Author: user
 */

#ifndef INC_STM32F446_H_
#define INC_STM32F446_H_

#include <stdint.h>
#define _vo volatile

/*
 * ARM cortex Mx processor NVIC ISERx register base address
 */

#define NVIC_ISER0					( (_vo uint32_t*)0xE000E100)
#define NVIC_ISER1					( (_vo uint32_t*)0xE000E104)
#define NVIC_ISER2					( (_vo uint32_t*)0xE000E108)
#define NVIC_ISER3					( (_vo uint32_t*)0xE000E10C)


/*
 * ARM cortex Mx processor NVIC ICERx register base address
 */

#define NVIC_ICER0					( (_vo uint32_t*)0xE000E180)
#define NVIC_ICER1					( (_vo uint32_t*)0xE000E184)
#define NVIC_ICER2					( (_vo uint32_t*)0xE000E188)
#define NVIC_ICER3					( (_vo uint32_t*)0xE000E18C)


/*
 * ARM cortex Mx processor priority register base address calculation
 */

#define NVIC_PR_BASE_ADDR			( (_vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED		4


/*
 * base addresses ok flash and sram memories
 */

#define FLASH_BASEADDR    			0x08000000U
#define SRAM1_BASEADDR				0x20000000U //112kb
#define SRAM2_BASEADDR				0x2001C000U //16kb
#define ROM							0x1FFF0000U
#define SRAM 						SRAM1_BASEADDR


/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASE					0x40000000U
#define APB1PERIPH_BASE				PERIPH_BASE
#define APB2PERIPH_BASE				0x40010000U
#define AHB1PERIPH_BASE				0x40020000U
#define AHB2PERIPH_BASE				0x50000000U


/*
 * Base addresses of peripherals which are hanging on AHB1 Bus
 */

#define GPIOA_BASEADDR				(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASE + 0x1C00)

//Clock base address
#define RCC_BASEADDR				(AHB1PERIPH_BASE + 0x3800)


/*
 * Base addresses of peripherals which are hanging on APB1 Bus
 */

#define I2C1_BASEADDR				(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASE + 0x5000)

/*
 * Base addresses of peripherals which are hanging on APB2 Bus
 */

#define EXTI_BASEADDR				(APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR				(APB2PERIPH_BASE + 0x3000)
#define SPI4_BASEADDR				(APB2PERIPH_BASE + 0x3400)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASE + 0x3800)
#define USART1_BASEADDR				(APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASE + 0x1400)

/*
 * EXTI macro definition
 */

#define EXTI						((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG						((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*************************Peripheral Register definition structure for GPIO***************************/

typedef struct
{
	_vo uint32_t MODER;					/* GPIO port mode register					Address offset: 0x00		*/
	_vo uint32_t OTYPER;				/* GPIO port output type register			Address offset: 0x04		*/
	_vo uint32_t OSPEEDER;				/* GPIO port output speed register			Address offset: 0x08		*/
	_vo uint32_t PUPDR;					/* GPIO port pull-up/pull-down register		Address offset: 0x0C		*/
	_vo uint32_t IDR;					/* GPIO port input data register			Address offset: 0x10		*/
	_vo uint32_t ODR;					/* GPIO port output data register			Address offset: 0x14		*/
	_vo uint32_t BSRR;					/* GPIO port bit set/reset register			Address offset: 0x18		*/
	_vo uint32_t LCKR;					/* GPIO port configuration lock register	Address offset: 0x1C		*/
	_vo uint32_t AFR[2];				/* AFR[0] : GPIO alternate function low register	Address offset: 0x20, AFR[1] : GPIO alternate function high register	Address offset: 0x24*/
}GPIO_RegDef_t;


/*************************Peripheral Register definition structure for GPIO***************************/

typedef struct
{
    _vo uint32_t CR;          // 0x00
    _vo uint32_t PLLCFGR;     // 0x04
    _vo uint32_t CFGR;        // 0x08
    _vo uint32_t CIR;         // 0x0C
    _vo uint32_t AHB1RSTR;    // 0x10
    _vo uint32_t AHB2RSTR;    // 0x14
    _vo uint32_t AHB3RSTR;    // 0x18
    uint32_t RESERVED0;       // 0x1C
    _vo uint32_t APB1RSTR;    // 0x20
    _vo uint32_t APB2RSTR;    // 0x24
    uint32_t RESERVED1[2];    // 0x28, 0x2C
    _vo uint32_t AHB1ENR;     // 0x30
    _vo uint32_t AHB2ENR;     // 0x34
    uint32_t RESERVED2;       // 0x38
    _vo uint32_t APB1ENR;     // 0x3C
    _vo uint32_t APB2ENR;     // 0x40
    uint32_t RESERVED3[2];    // 0x44, 0x48
    _vo uint32_t AHB1LPENR;   // 0x4C
    _vo uint32_t AHB2LPENR;   // 0x50
    _vo uint32_t AHB3LPENR;   // 0x54
    uint32_t RESERVED4;       // 0x58
    _vo uint32_t APB1LPENR;   // 0x5C
    _vo uint32_t APB2LPENR;   // 0x60
    uint32_t RESERVED5[2];    // 0x64, 0x68
    _vo uint32_t BDCR;        // 0x6C
    _vo uint32_t CSR;         // 0x70
    uint32_t RESERVED6[2];    // 0x74, 0x78
    _vo uint32_t SSCGR;       // 0x7C
    _vo uint32_t PLLI2SCFGR;  // 0x80
    _vo uint32_t PLLSAICFGR;  // 0x84
    _vo uint32_t DCKCFGR;     // 0x88
    _vo uint32_t CKGATENR;    // 0x8C
    _vo uint32_t DCKCFGR2;    // 0x90
} RCC_RegDef_t;


/*************************Peripheral Register definition structure for EXTI***************************/

typedef struct
{
	_vo uint32_t IMR;
	_vo uint32_t EMR;
	_vo uint32_t RTSR;
	_vo uint32_t FTSR;
	_vo uint32_t SWIER;
	_vo uint32_t PR;
}EXTI_RegDef_t;


/*************************Peripheral Register definition structure for SYSCFG***************************/

typedef struct
{
	_vo uint32_t MEMRMP;
	_vo uint32_t PMC;
	_vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	_vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
	_vo uint32_t CFGR;
}SYSCFG_RegDef_t;


/*
 * peripheral definitions   ( Peripheral base address typecasted to xxx_RegDef_t)
 */

#define GPIOA						((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB						((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC						((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD						((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE						((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF						((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG						((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH						((GPIO_RegDef_t*)GPIOH_BASEADDR)


#define RCC							((RCC_RegDef_t*)RCC_BASEADDR)


/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 0) )
#define GPIOB_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 1) )
#define GPIOC_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 2) )
#define GPIOD_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 3) )
#define GPIOE_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 4) )
#define GPIOF_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 5) )
#define GPIOG_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 6) )
#define GPIOH_PCLK_EN()				( RCC->AHB1ENR |= ( 1 << 7) )

/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 21) )
#define I2C2_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 22) )
#define I2C3_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 23) )


/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()				( RCC->APB2ENR |= ( 1 << 12) )
#define SPI2_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 14) )
#define SPI3_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 15) )
#define SPI4_PCLK_EN()				( RCC->APB2ENR |= ( 1 << 13) )


/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 4) )
#define USART2_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 17) )
#define USART3_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 18) )
#define UART4_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 19) )
#define UART5_PCLK_EN()				( RCC->APB1ENR |= ( 1 << 20) )
#define USART6_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 5) )

/*
 * Clock Enable Macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 14) )

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 0) )
#define GPIOB_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 1) )
#define GPIOC_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 2) )
#define GPIOD_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 3) )
#define GPIOE_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 4) )
#define GPIOF_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 5) )
#define GPIOG_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 6) )
#define GPIOH_PCLK_DI()				( RCC->AHB1ENR &= ~( 1 << 7) )

/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 21) )
#define I2C2_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 22) )
#define I2C3_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 23) )


/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_DI()				( RCC->APB2ENR &= ~( 1 << 12) )
#define SPI2_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 14) )
#define SPI3_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 15) )
#define SPI4_PCLK_DI()				( RCC->APB2ENR &= ~( 1 << 13) )


/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_DI()			( RCC->APB2ENR &= ~( 1 << 4) )
#define USART2_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 17) )
#define USART3_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 18) )
#define UART4_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 19) )
#define UART5_PCLK_DI()				( RCC->APB1ENR &= ~( 1 << 20) )
#define USART6_PCLK_DI()			( RCC->APB2ENR &= ~( 1 << 5) )

/*
 * Clock Enable Macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_DI()			( RCC->APB2ENR &= ~( 1 << 14) )


/********Geniric Macros**********/

#define ENABLE						1
#define DISABLE						0
#define SET							ENABLE
#define RESET						DISABLE
#define GPIO_PIN_SET				SET
#define GPIO_PIN_RESET				RESET


/*
 * MACROS TO RESET GPIOx PERIPHERALS
 */

#define GPIOA_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 0));	(RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 1));	(RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 2));	(RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 3));	(RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 4));	(RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 5));	(RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 6));	(RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 7));	(RCC->AHB1RSTR &= ~(1 << 7)); }while(0)


/*
 * returns port code
 */

#define GPIO_BASEADDR_TO_CODE(x)	( (x == GPIOA)?0:\
									  (x == GPIOB)?1:\
									  (x == GPIOC)?2:\
									  (x == GPIOD)?3:\
									  (x == GPIOE)?4:\
									  (x == GPIOF)?5:\
									  (x == GPIOG)?6:\
									  (x == GPIOH)?7:0)


/*
 * 	IRQ(Interrupt Request) Number of STM32F446x MCU
 */

#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40


#include "stm32f446_gpio_driver.h"

#endif /* INC_STM32F446_H_ */

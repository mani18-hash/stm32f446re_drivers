/*
 * 002Button_Interrupt.c
 *
 *  Created on: 12-Aug-2026
 *      Author: user
 */


#include "stm32f446.h"


#define HIGH				1
#define LOW					0
#define BTN_PRESSED_LOW

void EXTI15_10_IRQHandler(void)
	{
		GPIO_IRQHandling(GPIO_PIN_NO_13);
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
	}

int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);

	GPIO_Init(&GpioLed);

	GPIO_Handle_t GPIOBtn;

	//button gpio configuration
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOC, ENABLE);

	GPIO_Init(&GPIOBtn);

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);


	return 0;
}

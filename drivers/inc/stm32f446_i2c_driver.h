/*
 * stm32f446_i2c_driver.h
 *
 *  Created on: 10-Oct-2026
 *      Author: Manikanta Kore
 */

#ifndef INC_STM32F446_I2C_DRIVER_H_
#define INC_STM32F446_I2C_DRIVER_H_

#include "stm32f446.h"

/*
 *  Configuration structure for I2Cx Peripheral
 */

typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
}I2C_Config_t;

/*
 *  Handle structure for I2Cx Peripheral
 */

typedef struct
{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
}I2C_Handle_t;

/*
 * @I2C_SCLSpeed
 */

#define I2C_SCL_SPEED_STANDARD				100000
#define I2C_SCL_SPEED_FAST  				400000

/*
 *  @I2C_ACKControl
 */

#define I2C_ACK_ENABLE						1
#define I2C_ACK_DISABLE						0

/*
 * @I2C_FMDutyCycle
 */

#define I2C_FM_DUTY_2						0
#define I2C_FM_DUTY_16/9					1

/******************************************************************************************************************
 * 									APIs supported by this driver
 *****************************************************************************************************************/


/* Peripheral clock setup*/

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/* Initialize and De-innitialize*/

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/* Data send and Receive */


/* IRQ Configuration and ISR Handling */



/*
 * other peripheral APIs
 */

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


#endif /* INC_STM32F446_I2C_DRIVER_H_ */

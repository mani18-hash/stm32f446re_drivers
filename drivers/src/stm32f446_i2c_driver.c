/*
 * stm32f446_i2c_driver.c
 *
 *  Created on: 13-Oct-2026
 *      Author: Manikanta Kore
 */


#include "stm32f446.h"
#include "stm32f446_i2c_driver.h"

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pI2Cx==I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{

}
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= ( 1 << I2C_CR1_PE );
	}
	else
	{
		pI2Cx->CR1 &= ~( 1 << 0 );
	}
}




/*
 * LPM.c
 *
 *  Created on: May 17, 2023
 *      Author: shine
 */

#include "Types.h"
#include "Registers.h"
#include "Macros.h"
#include "LPM.h"

void LPM_Enable(void)
{
    SET_BIT(MCUCR, 7);
}

void LPM_Disable(void)
{
    CLR_BIT(MCUCR, 7);
}

void LowPower_Mode(LowPower_ModeType mode)
{
    switch (mode)
    {
    case IDLE:
        SET_BIT(MCUCR, 7);
        CLR_BIT(MCUCR, 4);
        CLR_BIT(MCUCR, 5);
        CLR_BIT(MCUCR, 6);
        break;

    case ADC_NOISE_REDUCTION:
        SET_BIT(MCUCR, 7);
        SET_BIT(MCUCR, 4);
        CLR_BIT(MCUCR, 5);
        CLR_BIT(MCUCR, 6);
        break;

    case POWER_DOWN:
        SET_BIT(MCUCR, 7);
        CLR_BIT(MCUCR, 4);
        SET_BIT(MCUCR, 5);
        CLR_BIT(MCUCR, 6);
        break;

    case POWER_SAVE:
        SET_BIT(MCUCR, 7);
        SET_BIT(MCUCR, 4);
        SET_BIT(MCUCR, 5);
        CLR_BIT(MCUCR, 6);
        break;

    case STANDBY:
        SET_BIT(MCUCR, 7);
        CLR_BIT(MCUCR, 4);
        SET_BIT(MCUCR, 5);
        SET_BIT(MCUCR, 6);
        break;

    case EXRENDED_STANDBY:
        SET_BIT(MCUCR, 7);
        SET_BIT(MCUCR, 4);
        SET_BIT(MCUCR, 5);
        SET_BIT(MCUCR, 6);
        break;

    default:
        break;
    }
}

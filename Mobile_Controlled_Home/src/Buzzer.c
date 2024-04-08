/*
 * Buzzer.c
 *
 *  Created on: May 17, 2023
 *      Author: shine
 */

#include "Types.h"
#include "Dio.h"
#include "Buzzer_Cfg.h"
#include "Buzzer.h"

void Buzzer_Init (Dio_PortType port, Dio_PinType pin)
{
    Dio_SetPinMode(port, pin, DIO_MODE_OUTPUT);
}

void Buzzer_On (Dio_PortType port, Dio_PinType pin)
{
    Dio_SetPinLevel(port, pin, DIO_LEVEL_HIGH);
}

void Buzzer_Off (Dio_PortType port, Dio_PinType pin)
{
    Dio_SetPinLevel(port, pin, DIO_LEVEL_LOW);
}
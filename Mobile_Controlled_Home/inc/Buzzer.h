/*
 * Buzzer.h
 *
 *  Created on: May 17, 2023
 *      Author: shine
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "Dio.h"
#include "Buzzer_Cfg.h"

void Buzzer_Init (Dio_PortType port, Dio_PinType pin);
void Buzzer_On (Dio_PortType port, Dio_PinType pin);
void Buzzer_Off (Dio_PortType port, Dio_PinType pin);

#endif /* INC_BUZZER_H_ */

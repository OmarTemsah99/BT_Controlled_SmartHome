/*
 * LPM.h
 *
 *  Created on: May 17, 2023
 *      Author: shine
 */

#ifndef INC_LPM_H_
#define INC_LPM_H_

#include "Types.h"

typedef enum
{
    IDLE,
    ADC_NOISE_REDUCTION,
    POWER_DOWN,
    POWER_SAVE,
    STANDBY,
    EXRENDED_STANDBY
} LowPower_ModeType;

void LPM_Enable     (void);
void LPM_Disable    (void);
void LowPower_Mode  (LowPower_ModeType mode);

#endif /* INC_LPM_H_ */

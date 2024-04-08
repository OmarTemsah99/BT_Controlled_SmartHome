/*
 * Functions.h
 *
 *  Created on: Apr 11, 2023
 *      Author: shine
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <string.h>
#include "Types.h"
#include "Dio.h"
#include "Wdt.h"

u8 CompareStrings(u8 arr1[10], u8 arr2[10]);

#define Reset_AVR() Wdt_SetTimeOut(WDT_TIMEOUT_32_5_MS); Wdt_Enable(); while(1) {}

#endif /* INC_FUNCTIONS_H_ */

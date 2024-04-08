/*
 * Functions.c
 *
 *  Created on: Apr 11, 2023
 *      Author: shine
 */

#include "Functions.h"

u8 CompareStrings(u8 arr1[10], u8 arr2[10])
{
	u8 value;
	u8 flag;
	value = strcmp(arr1, arr2);

	if (value == 0)
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}
	return flag;
}
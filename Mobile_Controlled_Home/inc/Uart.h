/*
 * Uart.h
 *
 *  Created on: Mar 10, 2023
 *      Author: ahmad
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "Types.h"

typedef enum {
    UART_INT_SOURCE_RX,
    UART_INT_SOURCE_TX,
    UART_INT_SOURCE_DATA_REG_EMPTY
} Uart_InterruptSourceType;

void Uart_Init                  (void);
void Uart_SetBaudRate           (u16 value);
void Uart_Transmit              (u8 data);
u8   Uart_Receive               (void);
u8   Uart_Receive_String        (u8 *str);
u16  Uart_Receive_NineBitFrame  (void);
void Uart_EnableNotification    (Uart_InterruptSourceType source);
void Uart_DisableNotification   (Uart_InterruptSourceType source);
void Uart_SetTransmitCallback   (void (*funcPtr) (void));
void Uart_SetDataEmptyCallback  (void (*funcPtr) (void));
void Uart_SetReceiveCallback    (void (*funcPtr) (u8));
void Uart_SendNumber            (s32 number);
void Uart_SendString            (const char *str);
void Uart_SendArray             (u8 arr[10]);
void Uart_Flush                 (void);

#endif /* INC_UART_H_ */

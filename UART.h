#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"

void UART0_Init(void);
uint8_t UART0_Receive(void);
void UART0_Send(uint8_t);
void UART0_DeInit(void);

void UART2_Init(void);
uint8_t UART2_Receive(void);
void UART2_Send(uint8_t);
void UART2_DeInit(void);

#endif // __UART_H__

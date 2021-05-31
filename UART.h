#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"

void UART0_Init(void);
uint8_t UART0_Receive(void);
void UART0_Send(uint8_t);

#endif // __UART_H__

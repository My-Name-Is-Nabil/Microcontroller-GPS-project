#pragma once
#include <stdint.h>

/*
 * Initaliza PORTF (PF1) for LED.
 */
void RGBLED_Init(void);

/*
 * Writing data on PF1, 1 for turning on LED, 0 for turning off LED.
 */
void RGBLED_Write(uint8_t data);

/*
 * Checking if the LED is ON or OFF (not sure if it is needed).
 */
uint8_t RGBLED_Read(void);
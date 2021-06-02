#pragma once

/*
 * Initaliza PORTF (PF1) for LED.
 */
void RGBLED_Init(void);

/*
 * Writing data on PF1, 1 for turning on LED, 0 for turning off LED.
 */
void RGBLED_Write(unsigned char data);

/*
 * Checking if the LED is ON or OFF (not sure if it is needed).
 */
unsigned char RGBLED_Read(void);
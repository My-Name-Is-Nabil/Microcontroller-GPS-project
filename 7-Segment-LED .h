#pragma once

// Segment patterns for the 10 decimal digits for a common cathode 7-seg LED.
#define NUM_0 0x3F
#define NUM_1 0x06
#define NUM_2 0x5B
#define NUM_3 0x4F
#define NUM_4 0x66
#define NUM_5 0x6D
#define NUM_6 0x7D
#define NUM_7 0x07
#define NUM_8 0x7F
#define NUM_9 0x6F

/*
 * Initialize PORTB to drive the segment.
 * Initialize PORTA (PA4,PA5,PA6,PA7) to select which 7-segments is used currently.
 */
void SEVENSEGMENT_Init(void);

/*
 * Write the required digit which will be displayed on one of the segments.
 */
void SEVENSEGMENT_Write_Units(int data);
void SEVENSEGMENT_Write_Tens(int data);
void SEVENSEGMENT_Write_Hundreds(int data);

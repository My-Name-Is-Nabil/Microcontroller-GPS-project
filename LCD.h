#include "stdint.h"

void LCD_Command(unsigned char command);
void LCD_Init(void);
void LCD_Data(unsigned char data);
void LCD_Write(uint32_t distance);
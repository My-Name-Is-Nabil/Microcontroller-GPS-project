/*
                           | Wire connections  |
                           | ================= |

    LCD D0 -> D7 =====> portB B0 -> B7
    LCD RS =====> portE E0
    LCD RW =====> portE E1
    LCD Enable =====> PortE E2
*/

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "LCD.h"
#include "systick.h"

void LCD_Command(unsigned char command){
    // set RS and RW to 0
    GPIO_PORTE_DATA_R = 0x00;          // 000000

    // Write command to LCD D0 -> D7
	GPIO_PORTB_DATA_R = command;
	
    // Set the enable hiegh for 230 MicroSeconds
    GPIO_PORTE_DATA_R |= 0X04;          // 000100
	systick_delay(1);                   // Delay 230 MicroSeconds
	GPIO_PORTE_DATA_R &= 0x3B;          // 111011
}

void LCD_Data(unsigned char data){
	// set RS  = 1, and RW = 0
    GPIO_PORTE_DATA_R &= 0x01;          // 000001

    // Write data to LCD D0 -> D7
	GPIO_PORTB_DATA_R = data;
	
    // Set the enable hiegh for 230 MicroSeconds
    GPIO_PORTE_DATA_R |= 0X04;          // 000100
	systick_delay(1);                   // Delay 230 MicroSeconds
	GPIO_PORTE_DATA_R &= 0x3B;          // 111011
}

void LCD_Init(void){
    // initialize portB  B0 -> B7  for LCD D0 -> D7
	SYSCTL_RCGCGPIO_R |= 0X02;          // 000010
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R = 0XFF;
	GPIO_PORTB_DIR_R = 0XFF;
	GPIO_PORTB_DEN_R = 0XFF;
    GPIO_PORTB_AFSEL_R = 0x0;
    GPIO_PORTB_PCTL_R = 0x0; 
	GPIO_PORTB_AMSEL_R = 0x00;

    // initailize portE E0 -> E2 for RS, RW, Enable
    SYSCTL_RCGCGPIO_R |= 0X10;          // 010000
    while ((SYSCTL_PRGPIO_R & 0x10) == 0);
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R = 0XFF;
	GPIO_PORTE_DIR_R = 0X07;            // 000111
	GPIO_PORTE_DEN_R = 0X07;            // 000111
    GPIO_PORTE_AFSEL_R = 0x0;
    GPIO_PORTE_PCTL_R = 0x0; 
	GPIO_PORTE_AMSEL_R = 0x00;
	
    // Wakeup LCD
    LCD_Command(0X30);
    systick_delay(1);       // Delay 40 MicroSeconds
    
    // Use the 8-bits
    LCD_Command(0X38);
    systick_delay(1);       // Delay 40 MicroSeconds
    
    // Clear screen
    LCD_Command(0X01);
    systick_delay(2);       //Delay 1.64 MelliSeconds
    
    // Display on
    LCD_Command(0X0F);
    systick_delay(1);       // Delay 40 MicroSeconds

    // Curser to the middle
    LCD_Command(0X87);
    systick_delay(1);       // Delay 40 MicroSeconds

    // Write 000.
    LCD_Data('0');
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds
    LCD_Data('0');
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds
    LCD_Data('0');
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds
} 

void LCD_Write(uint32_t distance){
	  int units, tens, hundreds;
    
    // Clear screen
    LCD_Command(0X01);
    systick_delay(2);       //Delay 1.64 MelliSeconds

    // Curser to the middle
    LCD_Command(0X87);
    systick_delay(1);       // Delay 40 MicroSeconds

    // Calculate hundreds, tens, units.
    hundreds = distance / 100;
    tens = (distance / 10) % 10;
    units = distance % 10;

    // Write hundreds.
    LCD_Data((char) (hundreds + 48));
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds

    // Write tens.
    LCD_Data((char) (tens + 48));
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds

    // Write units.
    LCD_Data((char) (units + 48));
    // Shift the cursor
    LCD_Command(0X6);
    systick_delay(1);       // Delay 40 MicroSeconds
}

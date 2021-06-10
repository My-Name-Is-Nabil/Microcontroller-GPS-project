#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
////*                SYSTICK TIMER       *////
void systick_Init (void)
{
    NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=0X00FFFFFF;
    NVIC_ST_CURRENT_R=0;
    NVIC_ST_CTRL_R=0X05; // Enbling the timer with the processor clock //
}
void _systick_delay (void)
{
    uint32_t counts;
	  counts=80000;
    //NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=counts-1;
    NVIC_ST_CURRENT_R=0;
    while ((NVIC_ST_CTRL_R&0x00010000)==0)
    {}
}
void systick_delay(uint32_t delay)
{
    uint32_t i;
    for (i=0;i<delay;i++)
    {
        //Enter delay in milli seconds)
        //1 ms delay
        _systick_delay();
        
    }
}
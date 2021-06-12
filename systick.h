#pragma once
void systick_Init (void);
void _systick_delay (void);
void systick_delay(uint32_t);
void systick_wait_micro(void);
void systick_delay_micro(uint32_t delay);

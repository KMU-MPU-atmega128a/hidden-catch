#ifndef __utils_c
#define __utils_c

#include <iom128v.h>
#include "my128.h"
#include "lcd.h"

void LED_correct(void);

void usart0_transmit(void);
void usart0_receive(void);
void Init_USART0(void);

void timer2_comp_isr(void);
void Init_Timer2(void);
int get_random(int max);

#endif

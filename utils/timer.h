#ifndef __timer_h
#define __timer_h

#include <iom128v.h>
#include "my128.h"
#include "lcd.h"

void Init_Timer2(void);
void timer2_comp_isr(void);
void second_counter(void);
Byte get_random(Byte max);

#endif

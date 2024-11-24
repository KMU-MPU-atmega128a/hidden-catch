#include "timer.h"

void Init_Timer2(void) {
    TCCR2 = (1 << WGM21) | (1 << CS22);   // CTC 모드, 분주비 256
    OCR2 = 249;
    TIMSK |= (1 << OCIE2);  // Output Compare Interrupt 사용
}

#pragma interrupt_handler timer2_comp_isr: iv_TIM2_COMP
unsigned long long tmp = 0;
unsigned long long n = 0;

void timer2_comp_isr(void) {
    tmp++;
} // tmp++ every 4ms

void second_counter(void) {
    if (tmp >= 250) {
        n++;
        tmp = 0;
    }
}

Byte get_random(Byte max) { return n % max; }

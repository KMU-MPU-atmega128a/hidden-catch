#include "led.h"

void LED_correct(void) {  // 정답 시 LED 전체 점등 함수
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}

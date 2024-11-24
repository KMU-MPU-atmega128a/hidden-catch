#include "led.h"

void LED_correct(void) {  // 정답 시 LED 전체 점등 함수
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}

Byte LED_score = 0xFF;  // LED 정답 표기 여부 저장용 변수

void LED_scoreboard(int n) {
    LED_score &= ~(1 << n - 1);     // n번 정답 시 LED_score 변수에 n번 bit만 clear된 변수 저장
    PORTB = LED_score;          // PORTB에 LED_score 변수 대입
}

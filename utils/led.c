#include "led.h"

void LED_correct(void) {  // ���� �� LED ��ü ���� �Լ�
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}

Byte LED_score = 0xFF;  // LED ���� ǥ�� ���� ����� ����

void LED_scoreboard(int n) {
    LED_score &= ~(1 << n - 1);     // n�� ���� �� LED_score ������ n�� bit�� clear�� ���� ����
    PORTB = LED_score;          // PORTB�� LED_score ���� ����
}

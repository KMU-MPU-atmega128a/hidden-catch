#include "led.h"

void LED_correct(void) {  // ���� �� LED ��ü ���� �Լ�
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}

#include "utils.h"

void LED_correct(void) {  // ���� �� LED ��ü ���� �Լ�
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}

Byte txdata = 0;    // ���� ���� �� 'B' ����
Byte rxdata = 0;    // 'A' ���� �� ���� ����

#pragma interrupt_handler usart0_transmit: iv_USART0_DRE
void usart0_transmit(void) { UDR0 = txdata; }

#pragma interrupt_handler usart0_receive: iv_USART0_RXC
void usart0_receive(void) { rxdata = UDR0; }

void Init_USART0(void) {
    UCSR0A &= ~(1 << U2X0); // 1��� ���

    UCSR0B = (1 << RXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0);
    // ��/���� �� ��/���� ���ͷ�Ʈ �㰡
    UCSR0C = (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00);
    // �񵿱�� ���, ¦�� �и�Ƽ, 1bit stop bit, 8bit data

    UBRR0H = 0x00;
    UBRR0L = 0x67; // baud rate 9,600bps

    SREG |= 0x80;  // allow all interrupts
}

void Init_Timer2(void) {
    TCCR2 = (1 << WGM21) | (1 << CS22) | (1 << CS21);   // CTC ���, ���ֺ� 256
    OCR2 = 250;
    TIMSK |= (1 << OCIE2);
    TCNT2 = 0;
}

#pragma interrupt_handler timer2_comp_isr: iv_TIM2_COMP
unsigned long long random_seed = 0;     // random seed (8 bytes)
unsigned long long n = 0;

void timer2_comp_isr(void) {
    random_seed++;
    if (random_seed > 500) n++;
} // random_seed++ every 4ms

int get_random(int max) { return n % max; }

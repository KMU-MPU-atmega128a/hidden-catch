#include "usart.h"

void Init_USART0(void) {
    UCSR0A &= ~(1 << U2X0); // 1배속 통신

    UCSR0B = (1 << RXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0);
    // 송/수신 및 송/수신 인터럽트 허가
    UCSR0C = (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00);
    // 비동기식 통신, 짝수 패리티, 1bit stop bit, 8bit data

    UBRR0H = 0x00;
    UBRR0L = 0x67; // baud rate 9,600bps

    SREG |= 0x80;  // allow all interrupts
}

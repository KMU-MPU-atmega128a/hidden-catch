#include "interrupt.h"

void Interrupt_init(void) {
    EIMSK |= 1 << INT0;          // INT0 ��ư ���ͷ�Ʈ ���
    EICRA |= 1 << ISC01 | 1 << ISC11 | 1 << ISC21 | 1 << ISC31;
    // INT0~INT3 falling edge trigger ����
    EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61 | 1 << ISC71;
    // INT4~INT7 falling edge trigger ����
    SREG |= 0x80;           // ���� ���ͷ�Ʈ �㰡
}

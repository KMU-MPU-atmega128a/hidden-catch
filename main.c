#include <iom128v.h>
#include <stdlib.h>
#include <time.h>
#include "my128.h"
#include "lcd.h"
#include "cgram.h"

unsigned int score = 0; // ���� ����

// flags: start / quiz 1~8 sequence �������̸� 1, ���� ���� ���̰ų� �Ϸ�Ǿ����� 0
int start_flag = 0;
int q1_flag = 0;
int q2_flag = 0;

/* time.h ��� ���� ��� ���, Ÿ�̸� ���������� ��������� ������
#pragma interrupt_handler timer2_comp_isr: iv_TIM2_COMP
unsigned int n = 0;

void timer2_comp_isr(void) {
    n++;
    OCR2 = 249;
    if (n > 60000) n = 0;
}

void Init_Timer2(void) {
    TCCR2 = ((1 << WGM21) | (1 << CS22));
    OCR2 = 249;
    TIMSK |= (1 << OCIE2);
}*/

void LED_correct(void) {  // ���� �� LED ��ü ���� �Լ�
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}
/*
void Interrupt_init(void) {
    EIMSK |= 1 << INT0;          // INT0 ��ư ���ͷ�Ʈ ���
    EICRA |= 1 << ISC01 | 1 << ISC11 | 1 << ISC21 | 1 << ISC31;
    // INT0~INT3 falling edge trigger ����
    EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61 | 1 << ISC71;
    // INT4~INT7 falling edge trigger ����
    SREG |= 0x80;           // ���� ���ͷ�Ʈ �㰡
}
*/
void LCD_game_start(void) {
    if (start_flag) {
        Cursor_Home();
        LCD_STR("Starting in...");
        LCD_pos(0,15);
        LCD_STR("3");
        delay_ms(1000);

        LCD_pos(0,15);
        LCD_STR("2");
        delay_ms(1000);

        LCD_pos(0,15);
        LCD_STR("1");
        delay_ms(1000);

        LCD_Clear();
        Cursor_Home();
        LCD_STR("GO!!!");
        delay_ms(800);

        LCD_Clear();
        start_flag = 0; // start sequence ����
        q1_flag = 1;    // quiz1 sequence ����
    }
}

void Quiz_1(void) {     // �� �� CLCD�� ���ڵ� �� �ٸ� ���� ���� 1�� ã��
    Cursor_Home();

    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A ���ڷ� 32ĭ �� ä��
    // srand((unsigned int)time(NULL));

    Byte answer_row = rand() % 2;      // 0, 1�� �� ���� �ϳ� ����
    Byte answer_col = rand() % 16;     // 0~15�� �� ���� �ϳ� ����

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // ������ ��,���� B ���� ���

    LCD_Comm(0x0E);
    Cursor_Home();

    Byte cursor_row = 0, cursor_col = 0;
    while (q1_flag == 1) {
        Byte D = PIND & 0xFF;
        switch (D) {
            case 0b11101111: if (cursor_row > 0) cursor_row--; break;   // PD4, move cursor up
            case 0b11011111: if (cursor_row < 1) cursor_row++; break;   // PD5, move cursor down
            case 0b10111111: if (cursor_col > 0) cursor_col--; break;   // PD6, move cursor left
            case 0b01111111: if (cursor_col < 15) cursor_col++; break;  // PD7, move cursor right
        }

        LCD_pos(cursor_row, cursor_col);

        if (D == 0b11111101) {  // ����ڰ� Ŀ�� �̵� �Ϸ� �� ���� ���� ��ư (PD1) ������ ��
            if (cursor_row == answer_row && cursor_col == answer_col) {
                // ���� ���� ��ġ�� Ŀ�� ��ġ ��ġ �� ����
                q1_flag = 0; score++;   // quiz1 flag ���� (q1 sequence ����), score ����
                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // ���� �޼��� ���
                LED_correct(); LCD_Clear(); // LED ����, ���� LCD clear, Ŀ�� ����
                break;
            }
            else {
            // �ƴϸ� ���� ó�� �� ���ο� ���� ����
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // ���� �޽��� ���
                delay_ms(1000); LCD_Clear(); Quiz_1();  // LCD clear �� �� ���� ����
            }
        }

        delay_ms(100); // ��ư �Է� �� ������ ���� ����
    }
    // ���� ���� ���� (A,B) ���̻� ������� �ʰ� ����


    LCD_Comm(0x0E);     // LCD Ŀ�� on
    Cursor_Home();      // lCD Ŀ�� Ȩ���� �̵�
}

void quiz_2(void) {
    Cursor_Home();
}

void main(void) {
    DDRB = 0xFF;        // PORTB ��� ��� (LED)
    PORTB = 0xFF;       // LED ��ü off

    DDRD = 0xFF;        // PORTD ��� ��� (��ư)
    PORTD = 0xFF;       // PORTD ���� Ǯ�� ���� ����ϱ� ���� Set
    SFIOR |= 0x04;      // PUD bit 1�� ����

    Interrupt_init();
    PortInit();
    LCD_Init();
    CGRAM_set_menu();

    Cursor_Home();
    LCD_menu();
    delay_ms(10);

    while (1) {
        if ((PIND & 0xFF) == 0b01111111) {  // PD7 ������ ���� ����
            start_flag = 1;
            LCD_game_start();
        }
        if (start_flag == 0 && q1_flag == 1)
            Quiz_1();
        if (start_flag == 0 && q2_flag == 1)
            Quiz_2();
    }

}

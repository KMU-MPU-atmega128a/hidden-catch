#include <iom128v.h>
#include "my128.h"
#include "interrupt.h"
#include "lcd.h"
#include "cgram.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "quiz.h"

Byte score = 0; // ���� ����

// flags[0]: start flag
// flags[1] ~ flags[8]: quiz 1~8 sequence �������̸� 1, ���� ���� ���̰ų� �Ϸ�Ǿ����� 0
Byte flags[8 + 1] = {0, };

// 4������ ���� button interrupts
Byte choice[4 + 1] = {0, };  // 4�� ���� ����� ���� �� �迭
Byte ans = 0;    // ���� ���� ����

/*
#pragma interrupt_handler ext_int0_isr: iv_EXT_INT0
#pragma interrupt_handler ext_int1_isr: iv_EXT_INT1
#pragma interrupt_handler ext_int2_isr: iv_EXT_INT2
#pragma interrupt_handler ext_int3_isr: iv_EXT_INT3

// PD0 ���� 1�� ���� ����
void ext_int0_isr(void) { choice[1] = 1; }
// PD1 ���� 2�� ���� ����
void ext_int1_isr(void) { choice[2] = 1; }
// PD2 ���� 3�� ���� ����
void ext_int2_isr(void) { choice[3] = 1; }
// PD3 ���� 4�� ���� ����
void ext_int3_isr(void) { choice[4] = 1; }
*/

// USART ��� ����
Byte txdata = 0;    // ���� ���� �� 'B' ����
Byte rxdata = 0;    // 'A' ���� �� ���� ����

#pragma interrupt_handler usart0_transmit: iv_USART0_DRE
void usart0_transmit(void) { UDR0 = txdata; }

#pragma interrupt_handler usart0_receive: iv_USART0_RXC
void usart0_receive(void) { rxdata = UDR0; }

// ���� ����
void LCD_game_start(void) {
    if (flags[0] == 1) {
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
        flags[0] = 0;   // start sequence ����
        flags[1] = 1;   // quiz1 sequence ����
    }
}


void Quiz_1(void) {     // �� �� CLCD�� ���ڵ� �� �ٸ� ���� ���� 1�� ã��
    Cursor_Home();
    PORTB = 0xFF;   // ���� ǥ��� LED �ʱ�ȭ

    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A ���ڷ� 32ĭ �� ä��

    Byte answer_row = (unsigned char)get_random(2);    // 0, 1�� �� ���� �ϳ� ����
    Byte answer_col = (unsigned char)get_random(16);   // 0~15�� �� ���� �ϳ� ����

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // ������ ��,���� B ���� ���

    LCD_Comm(0x0E);             // lCD Ŀ�� on (1�� ���� ���࿡ �ʿ�)
    Cursor_Home();

    Byte cursor_row = 0, cursor_col = 0;
    while (flags[1] == 1) {
        Byte D = PIND & 0xFF;
        switch (D) {
            case 0b11101111: if (cursor_row > 0) cursor_row--; break;   // PD4, move cursor up
            case 0b11011111: if (cursor_row < 1) cursor_row++; break;   // PD5, move cursor down
            case 0b10111111: if (cursor_col > 0) cursor_col--; break;   // PD6, move cursor left
            case 0b01111111: if (cursor_col < 15) cursor_col++; break;  // PD7, move cursor right
        }

        LCD_pos(cursor_row, cursor_col);

        if (D == 0b11111110) {  // ����ڰ� Ŀ�� �̵� �Ϸ� �� ���� ���� ��ư (PD0) ������ ��
            if (cursor_row == answer_row && cursor_col == answer_col) {
                // ���� ���� ��ġ�� Ŀ�� ��ġ ��ġ �� ����
                flags[1] = 0; score++;   // flag 1 ���� (q1 sequence ����), score ����

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // ���� �޼��� ���
                LED_correct(); LCD_Clear(); // LED ����, ���� LCD clear, Ŀ�� ����
                LED_scoreboard(1);          // 1�� ���� ���� ǥ��

                flags[2] = 1;   // 2�� ���� sequence �غ�
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

    LCD_Comm(0x0C);     // LCD Ŀ�� off
    Cursor_Home();      // lCD Ŀ�� Ȩ���� �̵�
}


void Quiz_2(void) {
    Cursor_Home();
    clear_choice(choice);     // ��ư ���� ��� �ʱ�ȭ (PD0~PD3���� ���� ����)
    // 2�� ���� ������ CGRAM�� �Է� ('��': 0x00, '��': 0x01, '��': 0x02)
    CGRAM_set_quiz2();
    choice_generator(2); // ���� ���� �Ϸ�

    ans = 3;            //* ���� 3�� (�ӽ�, ���� �ۼ� �� ����)
    while (flags[2] == 1) {     // 2�� sequence ���� ��
        Byte D = PIND & 0xFF;
        switch (D) {
            case 0b11101111: choice[1] = 1; break;  // PD4, 1�� ����
            case 0b11011111: choice[2] = 1; break;  // PD5, 1�� ����
            case 0b10111111: choice[3] = 1; break;  // PD6, 1�� ����
            case 0b01111111: choice[4] = 1; break;  // PD7, 1�� ����
        }
        if (D != 0xFF) {
            if (check_answer(choice, ans) == 1) { // ���� ���� ����, �ش� ��ư ������ ���
                flags[2] = 0; score++;  // flag 2 ���� (q2 sequence ����), score ����

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // ���� �޼��� ���
                LED_correct(); LCD_Clear(); // LED ����, ���� LCD clear, Ŀ�� ����
                LED_scoreboard(2);          // 2�� ���� ���� ǥ��

                flags[3] = 1;   // 2�� ���� sequence �غ�
                break;
            }
            else if (check_answer(choice, ans) == 0) { // �ٸ� ���� �����ؼ� Ʋ���� ���
                // ���� ó�� �� ���ο� ���� ����
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // ���� �޽��� ���
                clear_choice(choice); // ����� ���� �ʱ�ȭ
                delay_ms(1000); LCD_Clear(); Quiz_2();  // LCD clear �� �� ���� ����
            }
        }
    }

}

void Quiz_3(void) {
    Cursor_Home();
    clear_choice(choice);     // ��ư ���� ��� �ʱ�ȭ (PD0~PD3���� ���� ����)
    // 2�� ���� ������ CGRAM�� �Է� ('��': 0x00, '��': 0x01, '��': 0x02)
    CGRAM_set_quiz3();
    choice_generator(3); // ���� ���� �Ϸ�

    ans = 3;            //* ���� 3�� (�ӽ�, ���� �ۼ� �� ����)
    while (flags[3] == 1) {     // 2�� sequence ���� ��
        Byte D = PIND & 0xFF;
        switch (D) {
            case 0b11101111: choice[1] = 1; break;  // PD4, 1�� ����
            case 0b11011111: choice[2] = 1; break;  // PD5, 1�� ����
            case 0b10111111: choice[3] = 1; break;  // PD6, 1�� ����
            case 0b01111111: choice[4] = 1; break;  // PD7, 1�� ����
        }
        if (D != 0xFF) {
            if (check_answer(choice, ans) == 1) { // ���� ���� ����, �ش� ��ư ������ ���
                flags[3] = 0; score++;  // flag 3 ���� (q3 sequence ����), score ����

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // ���� �޼��� ���
                LED_correct(); LCD_Clear(); // LED ����, ���� LCD clear, Ŀ�� ����
                LED_scoreboard(3);          // 2�� ���� ���� ǥ��

                flags[3] = 1;   // 2�� ���� sequence �غ�
                break;
            }
            else if (check_answer(choice, ans) == 0) { // �ٸ� ���� �����ؼ� Ʋ���� ���
                // ���� ó�� �� ���ο� ���� ����
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // ���� �޽��� ���
                clear_choice(choice); // ����� ���� �ʱ�ȭ
                delay_ms(1000); LCD_Clear(); Quiz_3();  // LCD clear �� �� ���� ����
            }
        }
    }

}

void main(void) {
    DDRB = 0xFF;        // PORTB ��� ��� (LED)
    PORTB = 0xFF;       // LED ��ü off

    DDRD = 0xFF;        // PORTD ��� ��� (��ư)
    PORTD = 0xFF;       // PORTD ���� Ǯ�� ���� ����ϱ� ���� Set
    SFIOR |= 0x04;      // PUD bit 1�� ����

    Interrupt_init();
    Init_USART0();
    PortInit();
    LCD_Init();

    CGRAM_set_menu();
    Cursor_Home();
    LCD_menu();
    delay_ms(10);

    while (1) {
        second_counter();
        txdata = 'A';
        // if (rxdata == 'A') {
        if ((PIND & 0xFF) == 0b01111111) {  // PD7 ������ ���� ����
        // �׽�Ʈ�� ������ rxdata == 'A'�� ����

            flags[0] = 1;       // initial sequence ����
            LCD_game_start();
        }

        if (flags[0] == 0) {
            if (flags[1] == 1) Quiz_1();
            if (flags[2] == 1) Quiz_2();
            if (flags[3] == 1) Quiz_3();
        }

    }   // end of while loop

}   // end of main loop

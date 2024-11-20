#include <iom128v.h>
#include <stdlib.h> // rand() function usage
#include "my128.h"
#include "lcd.h"
#include "cgram.h"

unsigned int score = 0; // ���� �����ϴ� ����

int start_flag = 0;
int q1_flag = 0;



void Interrupt_init(void) {
    EIMSK |= 1 << INT0;          // INT0 ��ư ���ͷ�Ʈ ���
    EICRA |= 1 << ISC01 | 1 << ISC11 | 1 << ISC21 | 1 << ISC31;
    // INT0~INT3 falling edge trigger ����
    EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61 | 1 << ISC71;
    // INT4~INT7 falling edge trigger ����
    SREG |= 0x80;           // ���� ���ͷ�Ʈ �㰡
}

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
        start_flag = 0;
        q1_flag = 1;
    }
}


void Quiz_1(void) {     // �� �� CLCD�� ���ڵ� �� �ٸ� ���� ���� 1�� ã��
    Cursor_Home();


    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A ���ڷ� 32ĭ �� ä��

    Byte answer_row = rand() % 2;      // 0, 1�� �� ���� �ϳ� ����
    Byte answer_col = rand() % 16;     // 0~15�� �� ���� �ϳ� ����

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // ������ ��,���� B ���� ���

    LCD_Comm(0x0E);
    Cursor_Home();

    Byte cursor_row = 0, cursor_col = 0;
    while (q1_flag == 1) {
        Byte D = PIND & 0xF0;
        switch (D) {
            case 0b11100000: if (cursor_row > 0) cursor_row--; break;   // PD4, move cursor up
            case 0b11010000: if (cursor_row < 1) cursor_row++; break;   // PD5, move cursor down
            case 0b10110000: if (cursor_col > 0) cursor_col--; break;   // PD6, move cursor left
            case 0b01110000: if (cursor_col < 15) cursor_col++; break;  // PD7, move cursor right
        }

        LCD_pos(cursor_row, cursor_col);

        if (cursor_row == answer_row && cursor_col == answer_col) {
            q1_flag = 0;
            score++;
            LCD_Clear();
            Cursor_Home();
            LCD_STR("Correct!");
            delay_ms(1000);
            LCD_Clear();
            break;
        }

        delay_ms(100);
    }
    // ���� ���� ���� (A,B) ���̻� ������� �ʰ� ����


    LCD_Comm(0x0E);     // LCD Ŀ�� on
    Cursor_Home();      // lCD Ŀ�� Ȩ���� �̵�
    // ����ڰ� Ŀ�� �̵�, ���� ��ư ������ �� Ŀ�� ��ġ�� row, col�� �����ϴٸ� flag set
    // ��ư�� ������ �� q1_flag = 0�̸� Quiz_1 sequence �ݺ�, q1_flag = 1�̸� score+1, quiz 2�� �̵�
}

void main(void) {
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
    }

}

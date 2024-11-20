#include <iom128v.h>
#include <stdlib.h> // rand() function usage
#include "my128.h"
#include "lcd.h"
#include "cgram.h"

unsigned int score = 0; // 점수 저장하는 변수

int start_flag = 0;
int q1_flag = 0;



void Interrupt_init(void) {
    EIMSK |= 1 << INT0;          // INT0 버튼 인터럽트 허용
    EICRA |= 1 << ISC01 | 1 << ISC11 | 1 << ISC21 | 1 << ISC31;
    // INT0~INT3 falling edge trigger 설정
    EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61 | 1 << ISC71;
    // INT4~INT7 falling edge trigger 설정
    SREG |= 0x80;           // 전역 인터럽트 허가
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


void Quiz_1(void) {     // 꽉 찬 CLCD의 문자들 중 다른 영어 문자 1개 찾기
    Cursor_Home();


    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A 문자로 32칸 다 채움

    Byte answer_row = rand() % 2;      // 0, 1행 중 랜덤 하나 선택
    Byte answer_col = rand() % 16;     // 0~15열 중 랜덤 하나 선택

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // 랜덤한 행,열에 B 문자 출력

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
    // 문제 출제 종료 (A,B) 더이상 출력하지 않게 설정


    LCD_Comm(0x0E);     // LCD 커서 on
    Cursor_Home();      // lCD 커서 홈으로 이동
    // 사용자가 커서 이동, 만약 버튼 눌렀을 때 커서 위치가 row, col과 동일하다면 flag set
    // 버튼이 눌렸을 때 q1_flag = 0이면 Quiz_1 sequence 반복, q1_flag = 1이면 score+1, quiz 2로 이동
}

void main(void) {
    DDRD = 0xFF;        // PORTD 출력 모드 (버튼)
    PORTD = 0xFF;       // PORTD 내부 풀업 저항 사용하기 위해 Set
    SFIOR |= 0x04;      // PUD bit 1로 설정

    Interrupt_init();
    PortInit();
    LCD_Init();
    CGRAM_set_menu();

    Cursor_Home();
    LCD_menu();
    delay_ms(10);

    while (1) {
        if ((PIND & 0xFF) == 0b01111111) {  // PD7 눌러서 퀴즈 시작
            start_flag = 1;
            LCD_game_start();
        }
        if (start_flag == 0 && q1_flag == 1)
            Quiz_1();
    }

}

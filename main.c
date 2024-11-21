#include <iom128v.h>
#include <stdlib.h>
#include <time.h>
#include "my128.h"
#include "lcd.h"
#include "cgram.h"

unsigned int score = 0; // 점수 저장

// flags: start / quiz 1~8 sequence 진행중이면 1, 아직 진행 전이거나 완료되었으면 0
int start_flag = 0;
int q1_flag = 0;
int q2_flag = 0;

/* time.h 사용 못할 경우 대비, 타이머 생성했으나 사용할지는 미지수
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

void LED_correct(void) {  // 정답 시 LED 전체 점등 함수
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
    PORTB = 0x00; delay_ms(250);
    PORTB = 0xFF; delay_ms(250);
}
/*
void Interrupt_init(void) {
    EIMSK |= 1 << INT0;          // INT0 버튼 인터럽트 허용
    EICRA |= 1 << ISC01 | 1 << ISC11 | 1 << ISC21 | 1 << ISC31;
    // INT0~INT3 falling edge trigger 설정
    EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61 | 1 << ISC71;
    // INT4~INT7 falling edge trigger 설정
    SREG |= 0x80;           // 전역 인터럽트 허가
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
        start_flag = 0; // start sequence 종료
        q1_flag = 1;    // quiz1 sequence 시작
    }
}

void Quiz_1(void) {     // 꽉 찬 CLCD의 문자들 중 다른 영어 문자 1개 찾기
    Cursor_Home();

    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A 문자로 32칸 다 채움
    // srand((unsigned int)time(NULL));

    Byte answer_row = rand() % 2;      // 0, 1행 중 랜덤 하나 선택
    Byte answer_col = rand() % 16;     // 0~15열 중 랜덤 하나 선택

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // 랜덤한 행,열에 B 문자 출력

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

        if (D == 0b11111101) {  // 사용자가 커서 이동 완료 후 정답 선택 버튼 (PD1) 눌렀을 때
            if (cursor_row == answer_row && cursor_col == answer_col) {
                // 만약 정답 위치와 커서 위치 일치 시 정답
                q1_flag = 0; score++;   // quiz1 flag 내림 (q1 sequence 종료), score 증가
                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // 정답 메세지 출력
                LED_correct(); LCD_Clear(); // LED 점등, 이후 LCD clear, 커서 제거
                break;
            }
            else {
            // 아니면 오답 처리 후 새로운 문제 출제
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // 오답 메시지 출력
                delay_ms(1000); LCD_Clear(); Quiz_1();  // LCD clear 후 새 문제 출제
            }
        }

        delay_ms(100); // 버튼 입력 간 딜레이 조절 가능
    }
    // 문제 출제 종료 (A,B) 더이상 출력하지 않게 설정


    LCD_Comm(0x0E);     // LCD 커서 on
    Cursor_Home();      // lCD 커서 홈으로 이동
}

void quiz_2(void) {
    Cursor_Home();
}

void main(void) {
    DDRB = 0xFF;        // PORTB 출력 모드 (LED)
    PORTB = 0xFF;       // LED 전체 off

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
        if (start_flag == 0 && q2_flag == 1)
            Quiz_2();
    }

}

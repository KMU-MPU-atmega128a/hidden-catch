#include <iom128v.h>
#include "my128.h"
#include "interrupt.h"
#include "lcd.h"
#include "cgram.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "quiz.h"

Byte score = 0; // 점수 저장

// flags[0]: start flag
// flags[1] ~ flags[8]: quiz 1~8 sequence 진행중이면 1, 아직 진행 전이거나 완료되었으면 0
Byte flags[8 + 1] = {0, };

// 4지선다 선택 button interrupts
Byte choice[4 + 1] = {0, };  // 4개 선지 사용자 선택 비교 배열
Byte ans = 0;    // 정답 선지 선택

/*
#pragma interrupt_handler ext_int0_isr: iv_EXT_INT0
#pragma interrupt_handler ext_int1_isr: iv_EXT_INT1
#pragma interrupt_handler ext_int2_isr: iv_EXT_INT2
#pragma interrupt_handler ext_int3_isr: iv_EXT_INT3

// PD0 눌러 1번 선지 선택
void ext_int0_isr(void) { choice[1] = 1; }
// PD1 눌러 2번 선지 선택
void ext_int1_isr(void) { choice[2] = 1; }
// PD2 눌러 3번 선지 선택
void ext_int2_isr(void) { choice[3] = 1; }
// PD3 눌러 4번 선지 선택
void ext_int3_isr(void) { choice[4] = 1; }
*/

// USART 통신 변수
Byte txdata = 0;    // 게임 종료 시 'B' 전송
Byte rxdata = 0;    // 'A' 수신 시 게임 시작

#pragma interrupt_handler usart0_transmit: iv_USART0_DRE
void usart0_transmit(void) { UDR0 = txdata; }

#pragma interrupt_handler usart0_receive: iv_USART0_RXC
void usart0_receive(void) { rxdata = UDR0; }

// 게임 시작
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
        flags[0] = 0;   // start sequence 종료
        flags[1] = 1;   // quiz1 sequence 시작
    }
}


void Quiz_1(void) {     // 꽉 찬 CLCD의 문자들 중 다른 영어 문자 1개 찾기
    Cursor_Home();
    PORTB = 0xFF;   // 정답 표기용 LED 초기화

    LCD_STR("AAAAAAAAAAAAAAAA");
    LCD_pos(1,0);
    LCD_STR("AAAAAAAAAAAAAAAA");
    // A 문자로 32칸 다 채움

    Byte answer_row = (unsigned char)get_random(2);    // 0, 1행 중 랜덤 하나 선택
    Byte answer_col = (unsigned char)get_random(16);   // 0~15열 중 랜덤 하나 선택

    LCD_pos(answer_row, answer_col);
    LCD_STR("B");               // 랜덤한 행,열에 B 문자 출력

    LCD_Comm(0x0E);             // lCD 커서 on (1번 문제 진행에 필요)
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

        if (D == 0b11111110) {  // 사용자가 커서 이동 완료 후 정답 선택 버튼 (PD0) 눌렀을 때
            if (cursor_row == answer_row && cursor_col == answer_col) {
                // 만약 정답 위치와 커서 위치 일치 시 정답
                flags[1] = 0; score++;   // flag 1 내림 (q1 sequence 종료), score 증가

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // 정답 메세지 출력
                LED_correct(); LCD_Clear(); // LED 점등, 이후 LCD clear, 커서 제거
                LED_scoreboard(1);          // 1번 문제 정답 표기

                flags[2] = 1;   // 2번 문제 sequence 준비
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

    LCD_Comm(0x0C);     // LCD 커서 off
    Cursor_Home();      // lCD 커서 홈으로 이동
}

void choice_detector(Byte D) {  // 사용자 선택 (PD4~PD7) 확인 함수
    switch (D) {
        case 0b11101111: choice[1] = 1; break;  // PD4, 1번 선택
        case 0b11011111: choice[2] = 1; break;  // PD5, 1번 선택
        case 0b10111111: choice[3] = 1; break;  // PD6, 1번 선택
        case 0b01111111: choice[4] = 1; break;  // PD7, 1번 선택
    }
}

void Quiz_2(void) {
    Cursor_Home();
    clear_choice(choice);     // 버튼 누른 기록 초기화 (PD0~PD3으로 선지 선택)
    // 2번 문제 데이터 CGRAM에 입력 ('식': 0x00, '사': 0x01, '샤': 0x02)
    CGRAM_set_quiz2();
    choice_generator(2); // 문제 출제 완료

    ans = 3;            //* 정답 3번 (임시, 난수 작성 후 변경)
    while (flags[2] == 1) {     // 2번 sequence 진행 중
        Byte D = PIND & 0xFF;
        choice_detector(D);

        if (D != 0xFF) {
            if (check_answer(choice, ans) == 1) { // 정답 선지 선택, 해당 버튼 눌렀을 경우
                flags[2] = 0; score++;  // flag 2 내림 (q2 sequence 종료), score 증가

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // 정답 메세지 출력
                LED_correct(); LCD_Clear(); // LED 점등, 이후 LCD clear, 커서 제거
                LED_scoreboard(2);          // 2번 문제 정답 표기

                flags[3] = 1;   // 3번 문제 sequence 준비
                break;
            }
            else if (check_answer(choice, ans) == 0) { // 다른 선지 선택해서 틀렸을 경우
                // 오답 처리 후 새로운 문제 출제
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // 오답 메시지 출력
                clear_choice(choice); // 사용자 선택 초기화
                delay_ms(1000); LCD_Clear(); Quiz_2();  // LCD clear 후 새 문제 출제
            }
        }
    }
}

void Quiz_3(void) {
    Cursor_Home();
    clear_choice(choice);     // 버튼 누른 기록 초기화 (PD0~PD3으로 선지 선택)
    // 2번 문제 데이터 CGRAM에 입력 ('식': 0x00, '사': 0x01, '샤': 0x02)
    CGRAM_set_quiz3();
    choice_generator(3); // 문제 출제 완료

    ans = 3;            //* 정답 3번 (임시, 난수 작성 후 변경)
    while (flags[3] == 1) {     // 3번 sequence 진행 중
        Byte D = PIND & 0xFF;
        choice_detector(D);

        if (D != 0xFF) {
            if (check_answer(choice, ans) == 1) { // 정답 선지 선택, 해당 버튼 눌렀을 경우
                flags[3] = 0; score++;  // flag 3 내림 (q3 sequence 종료), score 증가

                LCD_Clear(); Cursor_Home(); LCD_STR("Correct!");    // 정답 메세지 출력
                LED_correct(); LCD_Clear(); // LED 점등, 이후 LCD clear, 커서 제거
                LED_scoreboard(3);          // 3번 문제 정답 표기

                flags[4] = 1;   // 4번 문제 sequence 준비
                break;
            }
            else if (check_answer(choice, ans) == 0) { // 다른 선지 선택해서 틀렸을 경우
                // 오답 처리 후 새로운 문제 출제
                LCD_Clear(); Cursor_Home(); LCD_STR("Wrong!");  // 오답 메시지 출력
                clear_choice(choice); // 사용자 선택 초기화
                delay_ms(1000); LCD_Clear(); Quiz_3();  // LCD clear 후 새 문제 출제
            }
        }
    }
}

void Quiz_4(void) {
    Cursor_Home();
    clear_choice(choice);

    CGRAM_set_quiz4();
}

void main(void) {
    DDRB = 0xFF;        // PORTB 출력 모드 (LED)
    PORTB = 0xFF;       // LED 전체 off

    DDRD = 0xFF;        // PORTD 출력 모드 (버튼)
    PORTD = 0xFF;       // PORTD 내부 풀업 저항 사용하기 위해 Set
    SFIOR |= 0x04;      // PUD bit 1로 설정

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
        if ((PIND & 0xFF) == 0b01111111) {  // PD7 눌러서 퀴즈 시작
        // 테스트할 때에는 rxdata == 'A'로 변경

            flags[0] = 1;       // initial sequence 시작
            LCD_game_start();
        }

        if (flags[0] == 0) {
            if (flags[1] == 1) Quiz_1();
            if (flags[2] == 1) Quiz_2();
            if (flags[3] == 1) Quiz_3();
            if (flags[4] == 1) Quiz_4();
        }

    }   // end of while loop

}   // end of main loop

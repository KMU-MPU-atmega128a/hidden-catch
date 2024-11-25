#include "quiz.h"

Byte check_answer(Byte choice[], Byte ans) {   // 선택한 보기가 정답인지 확인하는 함수
    if (choice[ans] == 1) return 1;
    else return 0;
}

void clear_choice(Byte choice[]) {   // 버튼 누른 내역 초기화
    for (int i = 1; i <= 4; i++)
        choice[i] = 0;
}

void choice_generator(Byte n) {   // 랜덤 적용해서 수정 필요 (n=한 선지 글자 수)
    // if n = 2, 선지 3개에 0x00 0x01    /   1개에 0x00 0x02 출력
    // if n = 3, 선지 3개에 0x00 0x01 0x03 / 1개에 0x00 0x02 0x03 출력uuㅕㄴ`uuㅕㄴ`u```

    // 1번 선지
    Cursor_Home();
    LCD_STR("1. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);

    // 2번 선지
    LCD_pos(0,8);
    LCD_STR("2. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);

    // 3번 선지
    LCD_pos(1,0);
    LCD_STR("3. ");
    LCD_Data(0x00);
    LCD_Data(0x02);
    if (n == 3) LCD_Data(0x03);

    // 4번 선지
    LCD_pos(1,8);
    LCD_STR("4. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);
}

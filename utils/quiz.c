#include "quiz.h"

int check_answer(int choice[], int ans) {
    if (choice[ans] == 1) return 1;
    else return 0;
}

void clear_choice(int choice[]) {
    for (int i = 1; i <= 4; i++)
        choice[i] = 0;
}



void choice_generator(void) {   // 랜덤 적용해서 수정 필요
    // 선지 3개에 0x00, 0x01 출력, 1개에 0x00, 0x02 출력

    // 1번 선지
    Cursor_Home();
    LCD_STR("1. ");
    LCD_Data(0x00);
    LCD_Data(0x01);

    // 2번 선지
    LCD_pos(0,8);
    LCD_STR("2. ");
    LCD_Data(0x00);
    LCD_Data(0x01);

    // 3번 선지
    LCD_pos(1,0);
    LCD_STR("3. ");
    LCD_Data(0x00);
    LCD_Data(0x02);

    // 4번 선지
    LCD_pos(1,8);
    LCD_STR("4. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
}

#include "quiz.h"

Byte check_answer(Byte choice[], Byte ans) {   // ������ ���Ⱑ �������� Ȯ���ϴ� �Լ�
    if (choice[ans] == 1) return 1;
    else return 0;
}

void clear_choice(Byte choice[]) {   // ��ư ���� ���� �ʱ�ȭ
    for (int i = 1; i <= 4; i++)
        choice[i] = 0;
}

void choice_generator(Byte n) {   // ���� �����ؼ� ���� �ʿ� (n=�� ���� ���� ��)
    // if n = 2, ���� 3���� 0x00 0x01    /   1���� 0x00 0x02 ���
    // if n = 3, ���� 3���� 0x00 0x01 0x03 / 1���� 0x00 0x02 0x03 ���uu�Ť�`uu�Ť�`u```

    // 1�� ����
    Cursor_Home();
    LCD_STR("1. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);

    // 2�� ����
    LCD_pos(0,8);
    LCD_STR("2. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);

    // 3�� ����
    LCD_pos(1,0);
    LCD_STR("3. ");
    LCD_Data(0x00);
    LCD_Data(0x02);
    if (n == 3) LCD_Data(0x03);

    // 4�� ����
    LCD_pos(1,8);
    LCD_STR("4. ");
    LCD_Data(0x00);
    LCD_Data(0x01);
    if (n == 3) LCD_Data(0x03);
}

#include "cgram.h"

void CGRAM_set_menu(void) { // �ʱ� ȭ�� �Լ� ("�ٸ�����ã��" ���)
    Byte menu1[] = {0x02, 0x1E, 0x12, 0x13, 0x12, 0x1E, 0x02, 0x02};
    Byte menu2[] = {0x0E, 0x02, 0x0E, 0x08, 0x0E, 0x1F, 0x08, 0x0E};
    Byte menu3[] = {0x0E, 0x0A, 0x0E, 0x00, 0x1F, 0x04, 0x08, 0x0E};
    Byte menu4[] = {0x02, 0x1E, 0x0A, 0x17, 0x16, 0x02, 0x02, 0x00};
    Byte menu5[] = {0x0A, 0x1E, 0x0B, 0x16, 0x02, 0x0E, 0x04, 0x0A};
    Byte menu6[] = {0x02, 0x1A, 0x0A, 0x0A, 0x0A, 0x0A, 0x02, 0x02};

    LCD_Comm(0x40); // CGRAM �ּ�: 0b01 000000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu1[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x48); // CGRAM �ּ�: 0b01 001000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu2[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x50); // CGRAM �ּ�: 0b01 010000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu3[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x58); // CGRAM �ּ�: 0b01 011000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu4[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x60); // CGRAM �ּ�: 0b01 100000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu5[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x68); // CGRAM �ּ�: 0b01 101000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu6[i]);
        LCD_delay(1);
    }
}

void LCD_menu(void) {   // �ʱ� ���� "�ٸ�����ã��" LCD�� ���
    for (Byte i = 0x00; i < 0x06; i++) {
        LCD_Data(i);
        LCD_delay(1);
    }
}
// 2��: '�Ļ�', '�Ļ�'
void CGRAM_set_quiz2(void) {
    Byte q2_1[] = {0x09, 0x09, 0x09, 0x15, 0x01, 0x0E, 0x02, 0x02}; // '��'
    Byte q2_2[] = {0x02, 0x0A, 0x0A, 0x0B, 0x16, 0x02, 0x02, 0x02}; // '��'
    Byte q2_3[] = {0x02, 0x0A, 0x0B, 0x16, 0x17, 0x02, 0x02, 0x02}; // '��'

    LCD_Comm(0x40);     // CGRAM �ּ�: 0b01 000000
    for (int i = 0; i < 8; i++) {
        LCD_Data(q2_1[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x48);     // CGRAM �ּ�: 0b01 001000
    for (int i = 0; i < 8; i++) {
        LCD_Data(q2_2[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x50);     // CGRAM �ּ�: 0b01 010000
    for (int i = 0; i < 8; i++) {
        LCD_Data(q2_3[i]);
        LCD_delay(1);
    }
}
// 3��: '������', '�ݱ��' (or '����', '�ݱ�')
void CGRAM_set_quiz3(void) {
    Byte q3_1[] = {0x0E, 0x02, 0x02, 0x1F, 0x00, 0x0E, 0x0A, 0x0E}; // '��'
    Byte q3_2[] = {0x01, 0x1D, 0x05, 0x05, 0x05, 0x05, 0x01, 0x01}; // '��'
    Byte q3_3[] = {0x01, 0x1D, 0x09, 0x09, 0x15, 0x01, 0x01, 0x01}; // '��'
    Byte q3_4[] = {0x01, 0x09, 0x15, 0x17, 0x15, 0x15, 0x09, 0x01}; // '��'

    LCD_Comm(0x40);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q3_1[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x48);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q3_2[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x50);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q3_3[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x58);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q3_4[i]);
        LCD_delay(1);
    }

}


// 4��: '������', '������'
void CGRAM_set_quiz4(void) {
    Byte q4_1[] = {0x04, 0x0A, 0x0A, 0x04, 0x04, 0x04, 0x1F, 0x00}; // '��'
    Byte q4_2[] = {0x02, 0x1A, 0x1B, 0x1A, 0x02, 0x08, 0x08, 0x0E}; // '��'
    Byte q4_3[] = {0x09, 0x15, 0x09, 0x1D, 0x0B, 0x09, 0x04, 0x07}; // '��'
    Byte q4_4[] = {0x09, 0x15, 0x09, 0x1D, 0x09, 0x09, 0x04, 0x07}; // '��'

    LCD_Comm(0x40);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q4_1[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x48);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q4_2[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x50);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q4_3[i]);
        LCD_delay(1);
    }
    LCD_Comm(0x58);
    for (int i = 0; i < 8; i++) {
        LCD_Data(q4_4[i]);
        LCD_delay(1);
    }
}


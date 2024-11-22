#include <iom128v.h>
#include "my128.h"
#include "lcd.h"

void CGRAM_set_menu(void) { // 초기 화면 함수 ("다른문자찾기" 출력)
    Byte menu1[] = {0x02, 0x1E, 0x12, 0x13, 0x12, 0x1E, 0x02, 0x02};
    Byte menu2[] = {0x0E, 0x02, 0x0E, 0x08, 0x0E, 0x1F, 0x08, 0x0E};
    Byte menu3[] = {0x0E, 0x0A, 0x0E, 0x00, 0x1F, 0x04, 0x08, 0x0E};
    Byte menu4[] = {0x02, 0x1E, 0x0A, 0x17, 0x16, 0x02, 0x02, 0x00};
    Byte menu5[] = {0x0A, 0x1E, 0x0B, 0x16, 0x02, 0x0E, 0x04, 0x0A};
    Byte menu6[] = {0x02, 0x1A, 0x0A, 0x0A, 0x0A, 0x0A, 0x02, 0x02};

    LCD_Comm(0x40); // CGRAM 주소: 0b01 000000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu1[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x48); // CGRAM 주소: 0b01 001000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu2[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x50); // CGRAM 주소: 0b01 010000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu3[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x58); // CGRAM 주소: 0b01 011000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu4[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x60); // CGRAM 주소: 0b01 100000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu5[i]);
        LCD_delay(1);
    }

    LCD_Comm(0x68); // CGRAM 주소: 0b01 101000
    LCD_delay(1);
    for (int i = 0; i < 8; i++) {
        LCD_Data(menu6[i]);
        LCD_delay(1);
    }
}

void LCD_menu(void) {   // 초기 문자 "다른문자찾기" LCD에 출력
    for (Byte i = 0x00; i < 0x06; i++) {
        LCD_Data(i);
        LCD_delay(1);
    }
}


void main(void) {
    PortInit();
    LCD_Init();
    CGRAM_set_menu();

    Cursor_Home();
    LCD_menu();
    delay_ms(10);


}

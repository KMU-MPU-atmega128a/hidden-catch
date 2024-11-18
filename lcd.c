#include "lcd.h"

void LCD_delay(Byte ms) { delay_ms(ms); }   // LCD time delay

void PortInit(void) {
    DDRA = 0xFF;    // PORTA to output mode
    DDRG = 0x0F;    // PORTG 0~3 to output mode
}

void LCD_Data(Byte ch) {
    LCD_CTRL |=  (1 << LCD_RS); // RS  = 1
    LCD_CTRL &= ~(1 << LCD_RW); // R/W = 0 -> Enter data write cycle
    LCD_CTRL |=  (1 << LCD_EN); // enable LCD
    delay_us(50);

    LCD_WDATA = ch;             // Write DATA
    delay_us(50);

    LCD_CTRL &= ~(1 << LCD_EN); // disable LCD
}   // Write Data to LCD Data Register (CGRAM, DDRAM)

void LCD_Comm(Byte ch) {
    LCD_CTRL &= ~(1 << LCD_RS); // RS  = 0
    LCD_CTRL &= ~(1 << LCD_RW); // R/W = 0 -> Enter instruction write cycle
    LCD_CTRL |=  (1 << LCD_EN); // enable LCD
    delay_us(50);

    LCD_WINST = ch;             // Write INSTruction
    delay_us(50);

    LCD_CTRL &= ~(1 << LCD_EN); // disable LCD
}   // Write Instruction to LCD Instruction Register (CGRAM, DDRAM)

void LCD_Shift(char p) { // *
    if (p == RIGHT) {
        LCD_Comm(0x1C);         // command: 0b00011100
        LCD_delay(1);
    }
    else if (p == LEFT) {
        LCD_Comm(0x18);         // command: 0b00011000
        LCD_delay(1);
    }
}

void LCD_CHAR(Byte c) {
    LCD_delay(1);
    LCD_Data(c);    // write char data C
}

void LCD_STR(Byte *str) {
    while (*str != 0) {
        LCD_CHAR(*str); // write string data 'str'
        str++;
    }
}

void LCD_pos(unsigned char row, unsigned char col) {
    LCD_Comm(0x80 | (row * 0x40 + col));
}

void LCD_Clear(void) {
    LCD_Comm(0x01);
    LCD_delay(2);
}

void LCD_Init(void) {
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x0e);
    LCD_delay(2);
    LCD_Comm(0x01);
    LCD_delay(30);
    LCD_Comm(0x06);
    LCD_delay(2);
}

void Cursor_Home(void) {
    LCD_Comm(0x02); // move LCD cursor to home
    LCD_delay(2);
}

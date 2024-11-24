#ifndef __lcd_h
#define __lcd_h

#include <iom128v.h>
#include "my128.h"

#define LCD_WDATA   PORTA           // LCD Data Bus definition (Write DATA)
#define LCD_WINST   PORTA           // LCD Data Bus definition (Write INSTruction)
#define LCD_RDATA   PINA            // LCD Data Bus definition (Read DATA)
#define LCD_CTRL    PORTG           // LCD Control Signal definition
#define LCD_EN      0               // Enable (Pin 6)                                   - PORTG.0
#define LCD_RW      1               // Read(1)/Write(0) (Pin 5)                         - PORTG.1
#define LCD_RS      2               // Data(1)/Instruction(0) Register Select (Pin 4)   - PORTG.2

#define On          1
#define Off         2

#define RIGHT       1
#define LEFT        0

#define sbi(x,y)    (x |=  (1 << y))   // Set BIt function declaration
#define cbi(x,y)    (x &= ~(1 << y))  // Clear BIt function declaration


// LCD function declaration
void LCD_delay(Byte ms);                            // LCD time delay
void PortInit(void);                                // PORT A initialization for LCD usage
void LCD_Data(Byte ch);                             // Data Write
void LCD_Comm(Byte ch);                             // Instruction Write
void LCD_Shift(char p);                             // Shift LCD (to left or right)
void LCD_CHAR(Byte c);                              // Print char
void LCD_STR(Byte *str);                            // Print string
void LCD_pos(unsigned char row, unsigned char col);  // Print location designation
void LCD_Clear(void);                               // LCD clearing
void LCD_Init(void);                                // LCD intialization
void Cursor_Home(void);                             // Move Cursor to (0,0)

#endif
#include "my128.h"

void delay_ms(unsigned int m) {
    unsigned int i, j;
    
    for (i = 0; i < m; i++)
        for (j = 0; j < 2130; j++)
            ;
}   // delay_ms definition

void delay_us(unsigned int m) {
    unsigned int i, j;

    for (i = 0; i < m; i++)
        for (j = 0; j < 2; j++)
            ;
}   // delay_us definition
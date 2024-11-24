#ifndef __quiz_h
#define __quiz_h

#include <iom128v.h>
#include "my128.h"
#include "lcd.h"

int check_answer(int choice[], int ans);
void clear_choice(int choice[]);

void choice_generator(void);

#endif

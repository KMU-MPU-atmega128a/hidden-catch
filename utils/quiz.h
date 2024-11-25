#ifndef __quiz_h
#define __quiz_h

#include <iom128v.h>
#include "my128.h"
#include "lcd.h"

Byte check_answer(Byte choice[], Byte ans);
void clear_choice(Byte choice[]);

void choice_generator(Byte n);

#endif

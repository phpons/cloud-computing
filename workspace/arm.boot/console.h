#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"

// Helper macros
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Characters
#define BACKSPACE 127

int run();
void screen_clear();

#endif /* CONSOLE_H_ */

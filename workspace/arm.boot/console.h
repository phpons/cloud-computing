#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"

// Helper macros
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Characters
#define BACKSPACE 127

int run();
void process_command(char *current_command);
void get_command_and_args(char *current_command);
void clear_buffer();

void echo(char *s);
void screen_clear();
void remove_character();

#endif /* CONSOLE_H_ */

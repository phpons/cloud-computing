#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"

// Helper macros
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


// Command line parameters
#define BUFFER_SIZE 128

// Characters
#define BACKSPACE 127

// Characters
#define SCROLL_UP -1
#define SCROLL_DOWN 1

int run();

void process_command(char *current_command);
void get_command_and_args(char *current_command);
void clear_buffer();

void echo(char *s);
void screen_clear();
void remove_character();

#endif /* CONSOLE_H_ */

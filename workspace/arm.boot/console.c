#include "console.h"

// Helper constants
const int true = 1, false = 0;

// Command line variables
int cursor_pos = 0;
char command[128];

int escape_sequence_index = 0; 
void process_char(char c) {
    int special_character = false;
    debugkprintf("Char %c = %d\n\r", c, c);
    debugkprintf("Current line %s | cursor pos = %d\n\r", command, cursor_pos);
    switch(c) {
        case BACKSPACE:
            cursor_pos = MAX(0, cursor_pos - 1);
            command[cursor_pos] = '/0';
            special_character = true;
            remove_character();
            break;
        case 27: // First character of escape sequence
            if (escape_sequence_index == 0) {
                escape_sequence_index++;
                special_character = true;
            }
            break;
        case 91: // Second character of escape sequence
            if (escape_sequence_index == 1) {
                escape_sequence_index++;
                special_character = true;
            }
            break;
        case 65: // Arrow up
            if (escape_sequence_index == 2) {
                special_character = true;
            }
            break;
        case 66: // Arrow down
            if (escape_sequence_index == 2) {
                special_character = true;
            }
            break;
        case 67: // Arrow right
            if (escape_sequence_index == 2) {
                special_character = true;
            }
            break;
        case 68: // Arrow left
            if (escape_sequence_index == 2) {
                special_character = true;
            }
            break;
    }
    if (!special_character) {
        escape_sequence_index = 0;

        // Place character and "move" cursor
        command[cursor_pos] = c;
        cursor_pos++;
        kputchar(c);
    }
}

int run() {
    screen_clear(); 
    while (1) {
        unsigned char c;
        while (uart_receive(UART0, &c) == false) {}
        if (c == '\r') {
            kprintf('\r\n');
        } else {
            process_char(c);
        }
    }
    return 1;
}

void remove_character() {
    kprintf("\b \b");
}

void screen_clear() {
    kprintf("\033[2J\033[1;1H");
}
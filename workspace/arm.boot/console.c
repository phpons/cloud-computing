#include "console.h"
#include "string.h"

// Helper constants
const int true = 1, false = 0;

// console line variables
int cursor_pos = 0;
char command_line[BUFFER_SIZE];

// used for command "extraction"
char detected_command[BUFFER_SIZE];
char detected_args[BUFFER_SIZE];

// character processing
int escape_sequence_index = 0; 

// command_history (implemented in a circular buffer fashion)
char command_history[20][BUFFER_SIZE];
int history_index = 0;
int scroll_index = 0;


void scroll_history(int dir) {
    int new_index = 0;
    new_index = (20 + scroll_index + dir) % 20;

    if (new_index != history_index) { // Logic can be adapted for down / up
        scroll_index = new_index;
        strcpy(command_history[scroll_index], command_line, BUFFER_SIZE);
        cursor_pos = strlen(command_line);

        // Reprint line with chosen history line
        kprintf("\33[2K\r");
        kprintf(command_line);
    }
    
}

void update_history(char *command_line) {
    strcpy(command_line, command_history[history_index], BUFFER_SIZE);
    history_index = (20 + history_index + 1) % 20;
    scroll_index = history_index;
}

int run() {
    screen_clear(); 
    while (1) {
        unsigned char c;
        while (uart_receive(UART0, &c) == false) {}
        if (c == '\r') {
            kprintf("\r\n");
            process_command(command_line);
            update_history(command_line);
            clear_buffer();
        } else {
            process_char(c);
        }
    }
    return 1;
}

void echo(char *s) {
    kprintf("%s\n\r", s);
}

void screen_clear() {
    kprintf("\033[2J\033[1;1H");
}

void remove_character() {
    kprintf("\b \b");
}

void clear_buffer() {
    cursor_pos = 0;
    int i = 0;
    for (i = 0; i < BUFFER_SIZE; i++) {
        command_line[i] = 0;
        detected_command[i] = 0;
        detected_args[i] = 0;
    }
}

void process_command(char *current_command) {
    get_command_and_args(current_command);
    if (strcmp(detected_command, "echo") == 0) {
        echo(detected_args);
    } else if (strcmp(detected_command, "reset") == 0) {
        screen_clear();
    } else {
        kprintf("Command not recognized.\r\n");
    }
}

void get_command_and_args(char *current_command) {
    int i = 0;
    while(current_command[i] != ' ' && current_command[i] != '\0'){
        detected_command[i] = current_command[i];
        i++;
    }
    detected_command[i + 1] = "\0";

    int j = 0;
    if (current_command[i] != "\0") {
        i += 1;
        while(current_command[i] != '\0'){
            detected_args[j] = current_command[i];
            i++;
            j++;
        }
    }
    detected_args[j + 1] = "\0";

    debugkprintf("Current line %s | cursor pos = %d\n\r", command_line, cursor_pos);
    debugkprintf(detected_command);
    debugkprintf("\r\n");
    debugkprintf(detected_args);
}

void process_char(char c) {
    int special_character = false;

    //debugkprintf("Char %c = %d\n\r", c, c);
    //debugkprintf("Current line %s | cursor pos = %d\n\r", command_line, cursor_pos);

    switch(c) {
        case BACKSPACE:
            cursor_pos = MAX(0, cursor_pos - 1);
            command_line[cursor_pos] = '/0';
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
                escape_sequence_index = 0;
                scroll_history(SCROLL_UP);
            }
            break;
        case 66: // Arrow down
            if (escape_sequence_index == 2) {
                special_character = true;
                escape_sequence_index = 0;
                scroll_history(SCROLL_DOWN);
            }
            break;
        case 67: // Arrow right
            if (escape_sequence_index == 2) {
                special_character = true;
                escape_sequence_index = 0;
                // Move right if "acceptable"
                if (cursor_pos + 1 < BUFFER_SIZE) {
                    kprintf("%c%c%c", 27, 91, 67);
                    cursor_pos++;
                }
                debugkprintf("Cursor position is %d\r\n", cursor_pos);
            }
            break;
        case 68: // Arrow left
            if (escape_sequence_index == 2) {
                special_character = true;
                escape_sequence_index = 0;
                kprintf("%c%c%c", 27, 91, 68);
                cursor_pos = MAX(0, cursor_pos - 1);
            }
            break;
    }
    if (!special_character) {
        escape_sequence_index = 0;

        // Place character and "move" cursor
        command_line[cursor_pos] = c;
        command_history[history_index][cursor_pos] = c;

        cursor_pos++;
        kputchar(c);
    }
}
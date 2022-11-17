#include "string.h"

// Source: https://stackoverflow.com/questions/34873209/implementation-of-strcmp
int strcmp (char *string_1, char *string_2) {
    while (*string_1 && (*string_1 == *string_2))
    {
        string_1++;
        string_2++;
    }
    return *(const unsigned char*)string_1 - *(const unsigned char*)string_2;
}

void strcpy(char *src, char *dest, int len) {
    for(int i = 0; i < len; i++){
        dest[i] = src[i];
    }
}

int strlen(char *s) {
    int i = 0;
    while(*s != '\0') {
        i++;
        s++;
    }
    return i;
}
#include "string.h"

// Source: https://stackoverflow.com/questions/34873209/implementation-of-strcmp
int str_cmp (char *string_1, char *string_2) {
    while (*string_1 && (*string_1 == *string_2))
    {
        string_1++;
        string_2++;
    }
    return *(const unsigned char*)string_1 - *(const unsigned char*)string_2;
}
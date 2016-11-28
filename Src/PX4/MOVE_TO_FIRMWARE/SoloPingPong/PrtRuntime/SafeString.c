#include "SafeString.h"


char  *strcpy_s(char *dest, int size, const char *src)
{
    char* result = dest;
    for (int i = 0; i < size; i++)
    {
        char ch = *src++;
        *dest = ch;
        if (ch == '\0')
        {
            break;
        }
        dest++;
    }
    *dest = '\0'; // null terminate at size limit.
    return result;
}

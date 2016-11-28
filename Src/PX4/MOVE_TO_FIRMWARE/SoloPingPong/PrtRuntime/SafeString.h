#ifndef _SAFESTRING_H
#define _SAFESTRING_H

#include <stddef.h>

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

EXTERN char  *strcpy_s(char *dest, int size, const char *src);


#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif

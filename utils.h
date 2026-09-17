#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sys/param.h>
#include <stdbool.h>
#include <stdint.h>

char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strscpy(char* dest, const char* src, size_t n);
char* util_strscpy_p(char* dest, const char* src, size_t n);
size_t util_strscpy_l(char* dest, const char* src, size_t n);

#endif // UTILS_H_INCLUDED

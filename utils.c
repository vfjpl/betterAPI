#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include "utils.h"
#include <string.h>


char* util_strcpy_p(char* dest, const char* src)
{
	return stpcpy(dest, src);//_GNU_SOURCE
}
size_t util_strcpy_l(char* dest, const char* src)
{
	return util_strcpy_p(dest, src) - dest;
}
void util_strscpy(char* dest, const char* src, size_t n)
{
	--n;
	strncpy(dest, src, n)[n] = '\0';
}
char* util_strscpy_p(char* dest, const char* src, size_t n)
{
	--n;
	char* end = stpncpy(dest, src, n);//_GNU_SOURCE
	dest[n] = '\0';
	return end;
}
size_t util_strscpy_l(char* dest, const char* src, size_t n)
{
	return util_strscpy_p(dest, src, n) - dest;
}

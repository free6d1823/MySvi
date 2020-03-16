#include <string.h>

int errno;

/**
 * strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;
}

#ifdef GENERIC_MEMCPY
void *memcpy(void *dest, const void *src, size_t size)
{
	void *tmp = dest;

	while (size) {
		*(char *)dest++ = *(char *)src++;
		size--;
	}
	return tmp;
}
#endif

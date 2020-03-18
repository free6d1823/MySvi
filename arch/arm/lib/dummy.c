#include <string.h>

size_t strlen(const char *p)
{
	int i = 0;
	while (! *p++)
		i++;

	return i;
}

void *memset(void *d, int v, size_t s)
{
	while (s--)
		*((char*)d++) = v;

	return d;
}

int strcmp(const char *s1, const char *s2)
{
	char c1, c2;

	if (!s1 || !s2)
		return -1;

	do {
		c1=(unsigned char)*s1++;
		c2=(unsigned char)*s2++;
		if(c1=='\0')
			return c1-c2;
	} while(c1 == c2);

	return c1-c2;
}

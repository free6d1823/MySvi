#include <stdio.h>
#include <target/spinlock.h>
#include <target/console.h>

static DEFINE_SPINLOCK(std_lock);

int vprintf(const char *fmt, va_list arg)
{
	int len;
	char buf[DEBUG_BUFFER_SIZE];

	len = vsnprintf(buf, sizeof(buf), fmt, arg);

	puts(buf);

	return len;
}

int printf(const char *fmt, ...)
{
	va_list arg;
	int len;

	va_start(arg, fmt);
	len = vprintf(fmt, arg);
	va_end(arg);

	return len;
}

int puts(const char *s)
{
	int len = 0;

	spin_lock(&std_lock);

	while (*s) {
		if (*s == '\n') {
			putchar('\r');
			len++;
		}
		putchar(*s++);
		len++;
	}

	spin_unlock(&std_lock);

	return len;
}

int fprintf(void *fp, const char *fmt, ...)
{
	va_list arg;
	int len;

	va_start(arg, fmt);
	len = vprintf(fmt, arg);
	va_end(arg);

	return len;
}

void *__stack_chk_guard = (void*)0x0AFF;
void __stack_chk_fail(void)
{
	printf("stack smashing detected.\n");
}
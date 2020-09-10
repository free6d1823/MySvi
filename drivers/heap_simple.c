#include <target/memory.h>
#include <target/heap.h>
#include <stdio.h>
#include <errno.h>
#include <target/cmdline.h>

uintptr_t gp_buf = HEAP_START;
uintptr_t gp_end = HEAP_END;


void *heap_aligned_alloc(size_t align, size_t size)
{
	uintptr_t cur;

	if (align & (align - 1)) {
		printf("heap_alloc wrong align!\n");
		return NULL;
	}

	cur = ALIGN_UP(gp_buf, (uintptr_t)align);

	if ((cur + size) > gp_end) {

		printf("heap_alloc out of memory!\n");
		return NULL;
	} else {
		gp_buf = cur + size;
		return (void *)cur;
	}
}

//when test usb, should change heap location
//(0x60040000 --0x70000000)
int heap_switch(int argc, char *argv[])
{

	if (argc < 3)
		return -EUSAGE;

	gp_buf = strtoull(argv[1], 0, 0);
	gp_end = strtoull(argv[2], 0, 0);

	printf("heap memory switched to 0x%llx-0x%llx\n", gp_buf, gp_end);
	return 0;
}

int heap_switch_direct(uintptr_t addr1, uintptr_t addr2)
{

	gp_buf = addr1;
	gp_end = addr2;
	return 0;
}

MK_CMD(heapswitch, heap_switch, "switch heap memory location to other address",
		"heapswitch <start address> <end address>\n"
);

void *heap_alloc(size_t size)
{
	return heap_aligned_alloc(16, size);
}


void heap_free(void *p)
{
	(void) p;
}

void *heap_save_current()
{
	return (void *)gp_buf;
}

void heap_restore(void *p)
{
	gp_buf = (uintptr_t)p;
}

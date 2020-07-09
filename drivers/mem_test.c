#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/timer.h>
#include <target/utils.h>
#include <errno.h>

#define SIZE_1M  0x100000
#define WATCHDOG_RESET() {}

static inline void unmap_sysmem(const void *vaddr)
{
}

static inline void *map_sysmem(phys_addr_t paddr, unsigned long len)
{
	return (void *)(uintptr_t)paddr;
}

static ulong mem_test_alt(vu_long *buf, ulong start_addr, ulong end_addr,
			  vu_long *dummy)
{
	vu_long *addr;
	ulong errs = 0;
	ulong val, readback;
	int j;
	vu_long offset;
	vu_long test_offset;
	vu_long pattern;
	vu_long temp;
	vu_long anti_pattern;
	vu_long num_words;
	static const ulong bitpattern[] = {
		0x00000001,	/* single bit */
		0x00000003,	/* two adjacent bits */
		0x00000007,	/* three adjacent bits */
		0x0000000F,	/* four adjacent bits */
		0x00000005,	/* two non-adjacent bits */
		0x00000015,	/* three non-adjacent bits */
		0x00000055,	/* four non-adjacent bits */
		0xaaaaaaaa,	/* alternating 1/0 */
	};

	num_words = (end_addr - start_addr) / sizeof(vu_long);

	/*
	 * Data line test: write a pattern to the first
	 * location, write the 1's complement to a 'parking'
	 * address (changes the state of the data bus so a
	 * floating bus doesn't give a false OK), and then
	 * read the value back. Note that we read it back
	 * into a variable because the next time we read it,
	 * it might be right (been there, tough to explain to
	 * the quality guys why it prints a failure when the
	 * "is" and "should be" are obviously the same in the
	 * error message).
	 *
	 * Rather than exhaustively testing, we test some
	 * patterns by shifting '1' bits through a field of
	 * '0's and '0' bits through a field of '1's (i.e.
	 * pattern and ~pattern).
	 */
	addr = buf;
	for (j = 0; j < sizeof(bitpattern) / sizeof(bitpattern[0]); j++) {
		val = bitpattern[j];
		for (; val != 0; val <<= 1) {
			*addr = val;
			*dummy	= ~val; /* clear the test data off the bus */
			readback = *addr;
			if (readback != val) {
				printf("FAILURE (data line): "
					"expected %08lx, actual %08lx\n",
						val, readback);
				errs++;
			}
			*addr  = ~val;
			*dummy	= val;
			readback = *addr;
			if (readback != ~val) {
				printf("FAILURE (data line): "
					"Is %08lx, should be %08lx\n",
						readback, ~val);
				errs++;
			}
		}
	}

	/*
	 * Based on code whose Original Author and Copyright
	 * information follows: Copyright (c) 1998 by Michael
	 * Barr. This software is placed into the public
	 * domain and may be used for any purpose. However,
	 * this notice must not be changed or removed and no
	 * warranty is either expressed or implied by its
	 * publication or distribution.
	 */

	/*
	* Address line test

	 * Description: Test the address bus wiring in a
	 *				memory region by performing a walking
	 *				1's test on the relevant bits of the
	 *				address and checking for aliasing.
	 *				This test will find single-bit
	 *				address failures such as stuck-high,
	 *				stuck-low, and shorted pins. The base
	 *				address and size of the region are
	 *				selected by the caller.

	 * Notes:	For best results, the selected base
	 *			address should have enough LSB 0's to
	 *			guarantee single address bit changes.
	 *			For example, to test a 64-Kbyte
	 *			region, select a base address on a
	 *			64-Kbyte boundary. Also, select the
	 *			region size as a power-of-two if at
	 *			all possible.
	 *
	 * Returns: 	0 if the test succeeds, 1 if the test fails.
	 */
	pattern = (vu_long) 0xaaaaaaaa;
	anti_pattern = (vu_long) 0x55555555;
	//debug("%s:%d: length = 0x%.8lx\n", __func__, __LINE__, num_words);
	/*
	 * Write the default pattern at each of the
	 * power-of-two offsets.
	 */
	for (offset = 1; offset < num_words; offset <<= 1){
		addr[offset] = pattern;
	}
	/*
	 * Check for address bits stuck high.
	 */
	test_offset = 0;
	addr[test_offset] = anti_pattern;
	for (offset = 1; offset < num_words; offset <<= 1) {
		temp = addr[offset];
		if (temp != pattern) {
			printf("\nFAILURE: Address bit stuck high @ 0x%.8lx:"
				" expected 0x%.8lx, actual 0x%.8lx\n",
				start_addr + offset*sizeof(vu_long),
				pattern, temp);
			errs++;
		}
	}
	addr[test_offset] = pattern;
	WATCHDOG_RESET();
	/*
	 * Check for addr bits stuck low or shorted.
	 */
	for (test_offset = 1; test_offset < num_words; test_offset <<= 1) {
		addr[test_offset] = anti_pattern;

		for (offset = 1; offset < num_words; offset <<= 1) {
			temp = addr[offset];
			if ((temp != pattern) && (offset != test_offset)) {
				printf("\nFAILURE: Address bit stuck low or"
					" shorted @ 0x%.8lx: expected 0x%.8lx,"
					" actual 0x%.8lx\n",
					start_addr + offset*sizeof(vu_long),
					pattern, temp);
				errs++;
			}
		}
		addr[test_offset] = pattern;
	}

	/*
	 * Description: Test the integrity of a physical
	 *		memory device by performing an
	 *		increment/decrement test over the
	 *		entire region. In the process every
	 *		storage bit in the device is tested
	 *		as a zero and a one. The base address
	 *		and the size of the region are
	 *		selected by the caller.
	 *
	 * Returns: 	0 if the test succeeds, 1 if the test fails.
	 */
	num_words++;
	/*
	 * Fill memory with a known pattern.
	 */
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		WATCHDOG_RESET();
		addr[offset] = pattern;
	}
	/*
	 * Check each location and invert it for the second pass.
	 */
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		WATCHDOG_RESET();
		temp = addr[offset];
		if (temp != pattern) {
			printf("\nFAILURE (read/write) @ 0x%.8lx:"
				" expected 0x%.8lx, actual 0x%.8lx)\n",
				start_addr + offset*sizeof(vu_long),
				pattern, temp);
			errs++;
		}
		anti_pattern = ~pattern;
		addr[offset] = anti_pattern;
	}
	/*
	 * Check each location for the inverted pattern and zero it.
	 */
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		WATCHDOG_RESET();
		anti_pattern = ~pattern;
		temp = addr[offset];
		if (temp != anti_pattern) {
			printf("\nFAILURE (read/write): @ 0x%.8lx:"
				" expected 0x%.8lx, actual 0x%.8lx)\n",
				start_addr + offset*sizeof(vu_long),
				anti_pattern, temp);
			errs++;
		}
		addr[offset] = 0;
	}
	return errs;
}

static int mem_rw_test(ulong star_addr, ulong end_addr, ulong length, ulong offset)
{
	vu_long *p;
	ulong i = 0;
	ulong temp_star,temp_end;
	ulong test_size = 0;
	ulong start_time, delta_time;

	test_size = length / SIZE_1M;
	p = (vu_long *)star_addr;
	temp_star = star_addr;
	temp_end = temp_star + length;
	printf("\nmemory read/write test begin \n");
	while(temp_star < end_addr) {
		i = 0;
		p = (vu_long *)temp_star;
		#if __WORDSIZE == 32
			printf("0x%08lx - 0x%08lx:\n", temp_star, temp_end);
		#elif __WORDSIZE == 64
			printf("0x%011llx - 0x%011llx:\n", temp_star, temp_end);
		#else
			printf(" __WORDSIZE not 32 or 64\n");
		#endif

		start_time = time_get_current_time();
		while ((ulong)p < temp_end) {
			*p++ = i++;
		}
		delta_time = time_get_current_time() - start_time;
		printf("write done -rate :%lld MB/s \n", (length / SIZE_1M) * 1000000 / delta_time);

		i = 0;
		p = (vu_long *)temp_star;
		start_time = time_get_current_time();
		while ((ulong)p < temp_end) {
			if (*p++ != i++) {
				printf("read failure %p(%d) on \n",p, i);
				return -1;
			}
		}
		delta_time = time_get_current_time() - start_time;
		printf("read done -rate : %lld MB/s \n", (length / SIZE_1M) * 1000000 / delta_time);
		printf("-------------------------------%d M test completed\n",test_size);
		temp_star += offset + length;
		temp_end =	temp_star + length;

		if(temp_end > end_addr)
			temp_end = end_addr;
		test_size += ((temp_end - temp_star)/SIZE_1M);
	}
	printf("===========memory read/write test complete ============\n");
	return 0;
}

static int do_mem_test(int argc, char * argv[])
{
	ulong start, end;
	vu_long *buf;
	vu_long dummy;
	int ret = 0;
	ulong errs = 0;
	uint64_t offset = 0;
	uint64_t length = SIZE_1M;
	uint64_t size = 0;

	if(argc < 2 ) {
		printf("The num of argument is not correct \n");
		return -EUSAGE;
	}

	if (!strcmp(argv[1],"sr")){
		if(argc < 3 || argc > 6) {
			printf("The num of argument is not correct \n");
			return -EUSAGE;
		}
		if(argc == 5){
			length = strtoul(argv[4], NULL, 0) * SIZE_1M;
		}
		if(argc == 6){
			offset = strtoul(argv[5], NULL, 0) * SIZE_1M;
		}
		start = strtoul(argv[2], NULL, 0);
		size = strtoul(argv[3], NULL, 0) * SIZE_1M;

		if((start% 0x1000 != 0)) {
			printf("ERROR:The star_addr is invalid, check if it over the max ddr size or not aline with 4K \n");
			return -1;
		}

		if(size < 0) {
			printf("ERROR:The size is invalid \n");
			return -1;
		}

		if(length > size){
			printf("ERROR:the length is bigger than the size you want to test.\n");
			return -1;
		}
		if(offset < 0) {
			printf("ERROR:the offset is invalid \n");
			return -1;
		}

		end = start + size;
		ret = mem_rw_test(start, end, length, offset);

	}else {
		start = strtoul(argv[1], NULL, 16);
		end = strtoul(argv[2], NULL, 16);

		if (end < start) {
			printf("Refusing to do empty test\n");
			return -1;
		}

		printf("Testing %08lx ... %08lx:\n", start, end);
		buf = map_sysmem(start, end - start);

		ret = mem_test_alt(buf, start, end, &dummy);
		/*
		 * Work-around for eldk-4.2 which gives this warning if we try to
		* case in the unmap_sysmem() call:
		 * warning: initialization discards qualifiers from pointer target type
		 */
		{
			void *vbuf = (void *)buf;
			void *vdummy = (void *)dummy;

			unmap_sysmem(vbuf);
			unmap_sysmem(vdummy);
		}
	}
	return ret;
}


MK_CMD(mt, do_mem_test, "test the memory",
	"mt start_addr end_addr \n"
	"	- test the memory at [start_addr, end_addr]\n"
	"mt sr {addr} {size(MB)} [length(MB)] [skip(MB)]\n"
	"	- test the speed rate at [addr, addr + size),\n"
	"	- test the length bytes and then skip size. \n"
);




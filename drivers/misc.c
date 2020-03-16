/*
 */
#include <stdint.h>
#include <target/bitops.h>

uint8_t hweight64(uint64_t w)
{
	uint64_t res;

	res = w - ((w >> 1) & 0x5555555555555555ul);
	res = (res & 0x3333333333333333ul) + ((res >> 2) & 0x3333333333333333ul);
	res = (res + (res >> 4)) & 0x0F0F0F0F0F0F0F0Ful;
	res = res + (res >> 8);
	res = res + (res >> 16);
	return (uint8_t)((res + (res >> 32)) & 0x00000000000000FFul);
}

uint32_t gcd32u(uint32_t n, uint32_t m)
{
	uint32_t t;

	while (m) {
		t = n % m;
		n = m;
		m = t;
	}
	return  n;
}

uint32_t __roundup32(uint32_t n)
{
	return (uint32_t)1 << (fls((uint32_t)(n - 1)) + 1);
}

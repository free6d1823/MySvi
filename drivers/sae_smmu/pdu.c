#include "elppdu.h"
/* Platform Specific I/O */
static int debug_on=0;

/* write a 32-bit word to a given address */
void pdu_io_write32 (void *addr, unsigned long val)
{
   if (addr == NULL) {
      debug_on ^= 1;
      return;
   }
   if (debug_on) {
      //ELPHW_PRINT("PDU: write %.8lx -> %p\n", val, addr);
   }
   //*((uint32_t *)addr) = val;
    *((unsigned int *)addr) = val;
}

/* read a 32-bit word from a given address */
unsigned int pdu_io_read32 (void *addr)
{
   unsigned int foo;
   //foo = *((uint32_t *)addr);
   foo = *((unsigned int*)addr);
   if (debug_on) {
      //ELPHW_PRINT("PDU: read  %.8lx <- %p\n", foo, addr);
   }
   return foo;
}

/* Platform specific DDT routines */

// initialize memory for DDT routines
int pdu_mem_init(void *device)
{
   return 0; // does nothing, here is where you could initialize your heap/etc
}

// cleanup memory used by DDT routines
void pdu_mem_deinit()
{
}


int pdu_ddt_init (pdu_ddt * ddt, unsigned long limit)
{
/*   limit &= 0x7FFFFFFF; // top bit is used for flags which is ignored here
   uint32_t calloc_buf[4];
   ddt->virt = (uint32_t*)calloc_buf;
   //ddt->virt = malloc(16);
   //ddt->virt  = calloc(8, limit + 1);
   ddt->phys = (PDU_DMA_ADDR_T)ddt->virt;
   ddt->idx = 0;
   ddt->len = 0;
   ddt->limit = limit;
   return ddt->virt == NULL ? -1 : 0;*/
   return 0;
}

int pdu_ddt_add (pdu_ddt * ddt, PDU_DMA_ADDR_T phys, unsigned long size)
{
   if (ddt->idx == ddt->limit) {
      return -1;
   }
   ddt->virt[ddt->idx * 2 + 0] = (uint32_t) phys;  /* write in address and size */
   ddt->virt[ddt->idx * 2 + 1] = size;
   ddt->virt[ddt->idx * 2 + 2] = 0;                /* ensure list is NULL terminated */
   ddt->virt[ddt->idx * 2 + 3] = 0;
   ddt->len += size;
   ++(ddt->idx);
   return 0;
}

int pdu_ddt_reset (pdu_ddt * ddt)
{
   ddt->idx = 0;
   ddt->len = 0;
   return 0;
}

int pdu_ddt_free (pdu_ddt * ddt)
{
   //free(ddt->virt);
   return 0;
}

/* Platform specific memory allocation */
void *pdu_malloc (unsigned long n)
{
   return malloc (n);
}

void pdu_free (void *p)
{
   free (p);
}

/* allocate coherent memory (currently just allocates heap memory) */
void *pdu_dma_alloc(size_t bytes, PDU_DMA_ADDR_T *phys)
{
   phys = pdu_malloc(bytes);
   return phys;
}

/* free coherent memory */
void* pdu_dma_free(size_t bytes, void *virt, PDU_DMA_ADDR_T phys)
{
   pdu_free(virt);
   return virt;
}


/* sync memory for the device to read, may be an empty function on cache coherent or cacheless designs */
void pdu_sync_single_for_device(uint32_t addr, uint32_t size)
{
}

/* sync memory for the CPU to read, may be an empty function on cache coherent or cacheless designs */
void pdu_sync_single_for_cpu(uint32_t addr, uint32_t size)
{
}




/**** PORTABLE PDU CODE ****/
void pdu_io_cached_write32 (void *addr, unsigned long val, uint32_t *cache)
{
   if (*cache == val) {
      return;
   }
   *cache = val;
   pdu_io_write32 (addr, val);
}

void pdu_to_dev32(void *addr, uint32_t *src, unsigned long nword)
{
   while (nword--) {
      pdu_io_write32(addr, *src++);
	  addr = (unsigned char*)((uint64_t)addr + 4);
   }
}

void pdu_from_dev32(uint32_t *dst, void *addr, unsigned long nword)
{
   while (nword--) {
      *dst++ = pdu_io_read32(addr);
	  //((unsigned char)addr) = ((unsigned char)addr) + 4;
	  addr = (unsigned char*)((uint64_t)addr + 4);
   }
}

void pdu_to_dev32_big(void *addr, const unsigned char *src, unsigned long nword)
{
   unsigned long v;

   while (nword--) {
     v = 0;
     v = (v << 8) | ((unsigned long)*src++);
     v = (v << 8) | ((unsigned long)*src++);
     v = (v << 8) | ((unsigned long)*src++);
     v = (v << 8) | ((unsigned long)*src++);
     pdu_io_write32(addr, v);
     //addr += 4;
	 addr = (unsigned char*)((uint64_t)addr + 4);
   }
}

void pdu_from_dev32_big(unsigned char *dst, void *addr, unsigned long nword)
{
   unsigned long v;
   while (nword--) {
      v = pdu_io_read32(addr);
      //addr += 4;
	  addr = (unsigned char*)((uint64_t)addr + 4);
      *dst++ = (v >> 24) & 0xFF; v <<= 8;
      *dst++ = (v >> 24) & 0xFF; v <<= 8;
      *dst++ = (v >> 24) & 0xFF; v <<= 8;
      *dst++ = (v >> 24) & 0xFF; v <<= 8;
   }
}

void pdu_to_dev32_little(void *addr, const unsigned char *src, unsigned long nword)
{
   unsigned long v;

   while (nword--) {
     v = 0;
     v = (v >> 8) | ((unsigned long)*src++ << 24UL);
     v = (v >> 8) | ((unsigned long)*src++ << 24UL);
     v = (v >> 8) | ((unsigned long)*src++ << 24UL);
     v = (v >> 8) | ((unsigned long)*src++ << 24UL);
     pdu_io_write32(addr, v);
     //addr += 4;
	 addr = (unsigned char*)((uint64_t)addr + 4);
   }
}

void pdu_from_dev32_little(unsigned char *dst, void *addr, unsigned long nword)
{
   unsigned long v;
   while (nword--) {
      v = pdu_io_read32(addr);
      //addr += 4;
	  addr = (unsigned char*)((uint64_t)addr + 4);
      *dst++ = v & 0xFF; v >>= 8;
      *dst++ = v & 0xFF; v >>= 8;
      *dst++ = v & 0xFF; v >>= 8;
      *dst++ = v & 0xFF; v >>= 8;
   }
}

void pdu_to_dev32_s(void *addr, const unsigned char *src, unsigned long nword, int endian)
{
   if (endian) {
      pdu_to_dev32_big(addr, src, nword);
   } else {
      pdu_to_dev32_little(addr, src, nword);
   }
}

void pdu_from_dev32_s(unsigned char *dst, void *addr, unsigned long nword, int endian)
{
   if (endian) {
      pdu_from_dev32_big(dst, addr, nword);
   } else {
      pdu_from_dev32_little(dst, addr, nword);
   }
}

/* Convert SDK error codes to corresponding kernel error codes. */
int pdu_error_code(int code)
{
   return code;
}


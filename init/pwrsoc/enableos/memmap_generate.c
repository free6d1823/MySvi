#include <string.h>
#include <stdint.h>
#include <target/launch.h>

#define ALIGN_UP(p, a) (((uint64_t)(p) + ((a) - 1)) & ~((a) - 1))

/*=============================================================================================================================
 *  EFI Memory attribute
 *===========================================================================================================================*/

/* Memory type */
enum _memory_type_name {
	mt_reserved = 0,
	mt_loadercode,
	mt_loaderdata,
	mt_bootcode,
	mt_bootdata,
	mt_runtimecode,
	mt_runtimedata,
	mt_coventionalmemory,
	mt_unusablememory,
	mt_acpireclaimmemory,
	mt_acpimemorynvs,
	mt_memorymappedio,
	mt_mmioportspace,
	mt_palcode,
	mt_persistentmemory
};

/* Attribute values: */
#define EFI_MEMORY_UC		((uint64_t)0x0000000000000001ULL)	/* uncached */
#define EFI_MEMORY_WC		((uint64_t)0x0000000000000002ULL)	/* write-coalescing */
#define EFI_MEMORY_WT		((uint64_t)0x0000000000000004ULL)	/* write-through */
#define EFI_MEMORY_WB		((uint64_t)0x0000000000000008ULL)	/* write-back */
#define EFI_MEMORY_UCE		((uint64_t)0x0000000000000010ULL)	/* uncached, exported */
#define EFI_MEMORY_WP		((uint64_t)0x0000000000001000ULL)	/* write-protect */
#define EFI_MEMORY_RP		((uint64_t)0x0000000000002000ULL)	/* read-protect */
#define EFI_MEMORY_XP		((uint64_t)0x0000000000004000ULL)	/* execute-protect */
#define EFI_MEMORY_NV		((uint64_t)0x0000000000008000ULL)	/* non-volatile */
#define EFI_MEMORY_MORE_RELIABLE \
				((uint64_t)0x0000000000010000ULL)	/* higher reliability */
#define EFI_MEMORY_RO		((uint64_t)0x0000000000020000ULL)	/* read-only */
#define EFI_MEMORY_RUNTIME	((uint64_t)0x8000000000000000ULL)	/* range requires runtime mapping */

#define CACHE_ATTR_NORM (EFI_MEMORY_UC|EFI_MEMORY_WC|EFI_MEMORY_WT|EFI_MEMORY_WB)

static char memory_type_name[][20] = {
	"Reserved",
	"Loader Code",
	"Loader Data",
	"Boot Code",
	"Boot Data",
	"Runtime Code",
	"Runtime Data",
	"Conventional Memory",
	"Unusable Memory",
	"ACPI Reclaim Memory",
	"ACPI Memory NVS",
	"Memory Mapped I/O",
	"MMIO Port Space",
	"PAL Code",
	"Persistent Memory",
};

typedef struct {
	uint32_t type;
	uint32_t pad;
	uint64_t phys_addr;
	uint64_t virt_addr;
	uint64_t num_pages;
	uint64_t attribute;
	uint64_t reserve;
} efi_memory_desc_t;

static efi_memory_desc_t memmap[]={
	{mt_runtimedata,       0x0, 0x200000,  0x200000,  32,      EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_coventionalmemory, 0x0, 0x820000,  0x000000,  0x2be0,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_coventionalmemory, 0x0, 0x3410000,  0x000000,  0xfcbf,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_acpimemorynvs, 0x0, 0x9010000, 0x000000, 0x70,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_coventionalmemory, 0x0, 0x10800000, 0x000000,  0x77f0,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_coventionalmemory, 0x0, 0x1c000000, 0x000000, 0x8000,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_coventionalmemory, 0x0, 0x1c810000, 0x000000, 0x0,  EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|CACHE_ATTR_NORM, 0},
	{mt_memorymappedio,    0X0, 0X00FF70030000, 0X0, 16, EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|EFI_MEMORY_UC, 0},
	{mt_memorymappedio,    0X0, 0X00FF70400000, 0X0, 16, EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|EFI_MEMORY_UC, 0},
	{mt_memorymappedio,    0X0, 0X00FF79000000, 0X0, 1024, EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|EFI_MEMORY_UC, 0},
	{mt_memorymappedio,    0X0, 0X00FF79420000, 0X0, 16, EFI_MEMORY_RUNTIME|EFI_MEMORY_XP|EFI_MEMORY_UC, 0},
};

void memmap_generate(uint64_t ddr_real_size)
{
    void * memmap_image = (void*)MEMMAP_IMAGE_START;
    void *dst = (void*)memmap_image;
    dst = (void*)ALIGN_UP(dst, 8);
    memmap[6].num_pages = (ddr_real_size*1024*1024 - 0x1c810000) / page_size;
    memcpy(dst, memmap, sizeof(memmap));
}

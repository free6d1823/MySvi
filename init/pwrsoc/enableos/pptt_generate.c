#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "pptt_generate.h"
#include <target/launch.h>
#include <asm/mach/cpus.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALbootHWIO.h>

#define ALIGN_UP(p, a) (((uint64_t)(p) + ((a) - 1)) & ~((a) - 1))

struct acpi_table_header pptt_tab_hdr = {
	.signature = {'P', 'P', 'T', 'T'},
	.length = 0,                     		/* Length of table in bytes, including this header */
	.revision = 1,                   		/* ACPI Specification minor version number */
	.checksum = 0,		                    /* To make sum of entire table == 0 */
	.oem_id = {'Q', 'C', 'O', 'M', ' ', ' '},	/* ASCII OEM identification */
	.oem_table_id = {'Q', 'D', 'F', '2', '4', '0', '0', ' '},	/* ASCII OEM table identification */
	.oem_revision = 3,	                        /* OEM revision number */
	.asl_compiler_id = {'I', 'N', 'T', 'L'},	/* ASCII ASL compiler vendor ID */
	.asl_compiler_revision = 0x20150515	        /* ASL compiler version */
};

struct acpi_pptt_cache Cache = {
	.header = {
		.type = ACPI_PPTT_TYPE_CACHE,
		.length = 0x18
	          },
	.reserved = 0x0000,         /* reserved - must be zero */
	.flags = ACPI_PPTT_SIZE_PROPERTY_VALID	|
			 ACPI_PPTT_CACHE_TYPE_VALID		|
			 ACPI_PPTT_WRITE_POLICY_VALID,
	.next_level_of_cache = 0x00000000,
	.size = 0x00000000,
	.number_of_sets = 0x00000000,
	.associativity = 0x00,
	.attributes = 0x00,
	.line_size = 0x0000,
};

struct acpi_pptt_id ProcessorId = {
	.header = {
		.type = ACPI_PPTT_TYPE_ID,
		.length = 0x1E
	          },
	.reserved = 0x0000,         /* reserved - must be zero */
	.vendor_id = SIGNATURE_32('Q', 'C', 'O', 'M'),
	.level1_id = 0,
	.level2_id = 0,
	.major_rev = 0,
	.minor_rev = 0,
	.spin_rev = 1,
};

struct acpi_pptt_processor Cluster = {
	.header = {
		.type = ACPI_PPTT_TYPE_PROCESSOR,
		.length = 0x1C
	          },
	.reserved = 0,
	.flags = 0x3,
	.parent = 0,
	.acpi_processor_id = 0x1000,
	.number_of_priv_resources = 0x2,
	.priv_resources1 = 0,
	.priv_resources2 = 0,
};

uint8_t pptt_tb_checksum(uint8_t *buffer, uint32_t length)
{
    uint8_t sum = 0;
    uint8_t *end = buffer + length;
    while (buffer < end)
        sum = (uint8_t)(sum + *(buffer++));
    return 256 - sum;
}

enum tab_order {
    PPTT = 0,
    CACHE,
    ID,
    CLUSTER,
};

static pptt_items_t image[] ={
    {"PPTT", 0, 0, 0},                           //Processor Properties Topology Table (PPTT)
    {"CACHE", (uint8_t*)&Cache, sizeof(Cache), 0},      //l1icache, l1dcache, l2cache, l3cache
    {"ID", (uint8_t*)&ProcessorId, sizeof(ProcessorId), 0},             //Processor ID
    {"CLUSTER", (uint8_t*)&Cluster, sizeof(Cluster), 0}  //Processor Hierarchy Node
};

static uint32_t L1iPpttOffset = 0;
static uint32_t L1dPpttOffset = 0;
static uint32_t L2PpttOffset = 0;
static uint32_t L3PpttOffset = 0;
static uint32_t ProcessoridPpttOffset = 0;
static uint32_t DiePpttOffset = 0;

int good_l3(uint64_t l3_partial_good)
{
    unsigned int count;
    for (count = 0; l3_partial_good != 0; l3_partial_good &= l3_partial_good - 1){
        count++;
    }
    return count;
}

void pptt_generate(uint64_t cpu_partial_good, uint64_t l3_partial_good)
{
    void * pptt_image = (void *)PPTT_IMAGE_START;
    CACHE_ATTRIBUTES_CONVERTER AttributesConverter;
    AttributesConverter.Attributes = 0;
    uint32_t cluster_id = 0;

    void *dst = (void*)pptt_image;
    dst = (void*)ALIGN_UP(dst, 8);
    pptt_items_t *pptt_items;
    struct acpi_table_pptt *pptt = NULL;

    pptt->header = pptt_tab_hdr;

    pptt_items = image + PPTT;
    pptt_items->data = (void*)pptt;
    pptt_items->len = sizeof(struct acpi_table_pptt);
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    L1iPpttOffset = sizeof(struct acpi_table_pptt);

    //generate the l1icache
    pptt_items = image + CACHE;
    Cache.size = 0x10000; //64kb
    AttributesConverter.BitsetAttr.CacheType = ATTRIBUTES_CACHE_INST;
    AttributesConverter.BitsetAttr.WritePolicy = ATTRIBUTES_WRITE_THRU;
    Cache.attributes = AttributesConverter.Attributes & 0x1F;
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    L1dPpttOffset = (uint32_t)(dst - pptt_image);

    //generate the l1dcache
    Cache.size = 0x8000; // 32kb
    AttributesConverter.BitsetAttr.CacheType = ATTRIBUTES_CACHE_DATA;
    AttributesConverter.BitsetAttr.WritePolicy = ATTRIBUTES_WRITE_THRU;
    Cache.attributes = AttributesConverter.Attributes & 0x1F;
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    L2PpttOffset = (uint32_t)(dst - pptt_image);

    //generate the l2cache
    Cache.size = 0x80000; // 512kb
    AttributesConverter.BitsetAttr.CacheType = ATTRIBUTES_CACHE_UNIF;
    AttributesConverter.BitsetAttr.WritePolicy = ATTRIBUTES_WRITE_BACK;
    Cache.attributes = AttributesConverter.Attributes & 0x1F;
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    L3PpttOffset = (uint32_t)(dst - pptt_image);

    //generate the l3cache
    Cache.size = good_l3(l3_partial_good) * L3_CACHE_SIZE_B;
    AttributesConverter.BitsetAttr.CacheType = ATTRIBUTES_CACHE_UNIF;
    AttributesConverter.BitsetAttr.WritePolicy = ATTRIBUTES_WRITE_BACK;
    Cache.attributes = AttributesConverter.Attributes & 0x1F;
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    ProcessoridPpttOffset = (uint32_t)(dst - pptt_image);

    //generate the Processor ID
    pptt_items = image + ID;
    ProcessorId.level1_id = HWIO_INF(TCSR_SOC_HW_VERSION, FAMILY_MEMBER);
    ProcessorId.level2_id = HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_MEMBER);
    ProcessorId.major_rev = HWIO_INF(TCSR_SOC_HW_VERSION, MAJOR_VERSION);
    ProcessorId.minor_rev = HWIO_INF(TCSR_SOC_HW_VERSION, MINOR_VERSION);
    memcpy(dst, pptt_items->data, pptt_items->len);

    dst += pptt_items->len;
    DiePpttOffset = (uint32_t)(dst - pptt_image);

    //generate all the Cluster
    pptt_items = image + CLUSTER;
    Cluster.priv_resources1 = L3PpttOffset;
    Cluster.priv_resources2 = ProcessoridPpttOffset;
    memcpy(dst, pptt_items->data, pptt_items->len);
    dst += pptt_items->len;

    for(cluster_id; cluster_id < MAX_CPU_CLUSTERS; cluster_id++) {
        if((cpu_partial_good >> (2*cluster_id)) & 0x3ULL) {
            uint32_t cpu_id = 0;
            uint32_t odd_cpu = 0;
            uint32_t cluster_mask = (cpu_partial_good >> (2*cluster_id))& 0x3ULL;
            Cluster.header.length = sizeof(struct acpi_pptt_processor) - 4;
            Cluster.flags = 0x2;
            Cluster.parent = DiePpttOffset;
            Cluster.acpi_processor_id = cluster_id + 0x10,
            Cluster.number_of_priv_resources = 0x1,
            Cluster.priv_resources1 = L2PpttOffset,
            memcpy(dst, pptt_items->data, Cluster.header.length);
            dst += Cluster.header.length;

            for(cpu_id; cpu_id < CPUS_PER_CLUSTER; cpu_id++){
                //only has odd_cpu
                if((cpu_id == 0) && (cluster_mask == 0x2)) {
                    odd_cpu = 1;
                    continue;
                }

                //only has even_cpu
                if((cpu_id == 1) && (cluster_mask == 0x1)) {
                    continue;
                }
            Cluster.header.length = sizeof(struct acpi_pptt_processor);
            Cluster.flags = 0x0;
            Cluster.parent = (uint32_t)(dst - pptt_image - Cluster.header.length + 4) - (uint32_t)((cpu_id - odd_cpu) * Cluster.header.length);
            Cluster.acpi_processor_id = CPUS_PER_CLUSTER * cluster_id + cpu_id;
            Cluster.number_of_priv_resources = 0x1,
            Cluster.priv_resources1 = L1iPpttOffset,
            Cluster.priv_resources2 = L1dPpttOffset,
            memcpy(dst, pptt_items->data, Cluster.header.length);
            dst += Cluster.header.length;
            }
        }
    }

    // modify the length of the whole PPTT table and the checksum
    pptt->header.length = (uint32_t)(dst - pptt_image);
    *(uint32_t*)((uint8_t *)pptt_image+0x4) = pptt->header.length;

    pptt->header.checksum = pptt_tb_checksum((uint8_t*)pptt_image, pptt->header.length);
    *((uint8_t*)pptt_image+0x9) = pptt->header.checksum;
}

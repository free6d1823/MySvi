#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "apic_generate.h"
#include <target/launch.h>
#include <asm/mach/cpus.h>

#define ALIGN_UP(p, a) (((uint64_t)(p) + ((a) - 1)) & ~((a) - 1))

struct acpi_table_header madt_tab_hdr = {
	.signature = {'A', 'P', 'I', 'C'},
	.length = 0,                     		/* Length of table in bytes, including this header */
	.revision = 4,                   		/* ACPI Specification minor version number */
	.checksum = 0,		                    /* To make sum of entire table == 0 */
	.oem_id = {'Q', 'C', 'O', 'M', ' ', ' '},	/* ASCII OEM identification */
	.oem_table_id = {'Q', 'D', 'F', '2', '4', '0', '0', ' '},	/* ASCII OEM table identification */
	.oem_revision = 1,	                        /* OEM revision number */
	.asl_compiler_id = {'I', 'N', 'T', 'L'},	/* ASCII ASL compiler vendor ID */
	.asl_compiler_revision = 0x20160422	        /* ASL compiler version */
};

struct acpi_madt_generic_distributor dist = {
        .header = {
		.type = 0x0c,
		.length = 0x18
	          },
        .reserved = 0x0000,         /* reserved - must be zero */
        .gic_id = 0x00000000,
        .base_address = 0x000000FF7EFC0000,
        .global_irq_base = 0x00000000,
        .version = 0x04,
        .reserved2 = {0x0, 0x0, 0x0}        /* reserved - must be zero */
};

struct acpi_madt_generic_msi_frame m = {
        .header = {
                .type = 0x0D,
                .length = 0x18
                  },
        .reserved = 0x0000,           /* reserved - must be zero */
        .msi_frame_id = 0x00000000,
        .base_address = 0x000000FF7EFD0000,
        .flags = 0x00000001,
        .spi_count = 0x001F,
        .spi_base = 0x0320,
};

struct acpi_madt_generic_translator its_entry = {
        .header = {
                .type = 0x0F,
                .length = 0x14
                 },
        .reserved = 0x0000,           /* reserved - must be zero */
        .translation_id = 0x00000000,
        .base_address = 0x000000FF7EFE0000,
        .reserved2 = 0x00000000,
};

struct acpi_madt_generic_interrupt gicc = {
        .header = {
                .type = 0x0B,
                .length = 0x50
                 },
        .reserved = 0x0000,           /* reserved - must be zero */
        .cpu_interface_number = 0x00000000,
        .uid = 0x00000000,
        .flags = 0x00000001,
        .parking_version = 0x00000000,
        .performance_interrupt = 0x00000017,
        .parked_address = 0x0000000000000000,
        .base_address = 0x0000000000000000,
        .gicv_base_address = 0x0000000000000000,
        .gich_base_address = 0x0000000000000000,
        .vgic_interrupt = 0x00000019,
        .gicr_base_address = 0x000000FF7F000000,
        .arm_mpidr = 0x0000000000000000,
        .efficiency_class = 0x00,
        .reserved2 = {0x0, 0x0, 0x0}
};

int good_core(uint64_t partial_good)
{
    unsigned int count;
    for (count = 0; partial_good != 0; partial_good &= partial_good - 1){
        count++;
    }
    return count;
}

uint8_t madt_tb_checksum(uint8_t *buffer, uint32_t length)
{
    uint8_t sum = 0;
    uint8_t *end = buffer + length;
    while (buffer < end)
        sum = (uint8_t)(sum + *(buffer++));
    return 256 - sum;
}

enum tab_order {
    MADT = 0,
    IDIST,
    MSIF,
    ITRANS,
    GIC,
};

static madt_items_t image[] ={
    {"MADT", 0, 0, 0},                           //Multiple APIC Description Table (MADT)
    {"IDIST", (uint8_t*)&dist, sizeof(dist), 0},      //Generic Interrupt Distributor
    {"MSIF", (uint8_t*)&m, sizeof(m), 0},             //Generic MSI Frame
    {"ITRANS", (uint8_t*)&its_entry, sizeof(its_entry), 0}, //Generic Interrupt Translator
    {"GIC", (uint8_t*)&gicc, sizeof(gicc), 0}    //Generic Interrupt Controller
};

void apic_generate(uint64_t partial_good)
{
    int i;
    int image_len = 0;

    void * apic_image = (void *)APIC_IMAGE_START;

    void *dst = (void*)apic_image;
    dst = (void*)ALIGN_UP(dst, 8);
    madt_items_t *madt_items;
    struct acpi_table_madt *madt = NULL;

    //generate the primary partial madt
    unsigned int good_core_cnt = good_core(partial_good);

    madt_tab_hdr.length = sizeof(struct acpi_table_madt) + dist.header.length + m.header.length + its_entry.header.length  + gicc.header.length * good_core_cnt;
    madt->header = madt_tab_hdr;
    madt->address = 0;
    madt->flags = 0;

    madt_items = image + MADT;
    madt_items->data = (void*)madt;
    madt_items->len = sizeof(struct acpi_table_madt);
    memcpy(dst, madt_items->data, madt_items->len);

    dst += madt_items->len;

    //generate the Generic Interrupt Distributor
    madt_items = image + IDIST;
    memcpy(dst, madt_items->data, madt_items->len);

    dst += madt_items->len;

    //generate the Generic MSI Frame
    madt_items = image + MSIF;
    memcpy(dst, madt_items->data, madt_items->len);

    dst += madt_items->len;

    //generate the Generic Interrupt Translator
    madt_items = image + ITRANS;
    memcpy(dst, madt_items->data, madt_items->len);

    dst += madt_items->len;

    //generate the Generic Interrupt Controller according to the partial good
    madt_items = image + GIC;
    i = 0;
    for (i=0; i < MAX_CPU_NUM/2; i++) {
        if ( partial_good & (0x1ULL<<(i*2))) {
            gicc.uid = i*2;
            gicc.gicr_base_address = 0x000000FF7F000000 + i * 0x80000;
            gicc.arm_mpidr = i * 0x100;
            memcpy(dst, madt_items->data, madt_items->len);
            dst += madt_items->len;
         }
    }

    for (i=0; i < MAX_CPU_NUM/2; i++) {
        if ( partial_good & (0x1ULL<<(i*2+1))) {
            gicc.uid = i*2+1;
            gicc.gicr_base_address = 0x000000FF7F040000 + i * 0x80000;
            gicc.arm_mpidr = i * 0x100 + 0x1;
            memcpy(dst, madt_items->data, madt_items->len);
            dst += madt_items->len;
        }
    }

    //modify the checksum value
    madt->header.checksum = madt_tb_checksum((uint8_t*)apic_image, madt_tab_hdr.length);
    *((uint8_t*)apic_image+0x9) = madt->header.checksum;
}

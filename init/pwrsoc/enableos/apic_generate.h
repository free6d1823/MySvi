#include <stdint.h>
#include <target/compiler.h>
#define ACPI_NAME_SIZE                  4
#define ACPI_OEM_ID_SIZE                6
#define ACPI_OEM_TABLE_ID_SIZE          8

/*******************************************************************************
 *
 * Master ACPI Table Header. This common header is used by all ACPI tables
 * except the RSDP and FACS.
 *
 ******************************************************************************/
struct acpi_table_header {
	char signature[ACPI_NAME_SIZE];	/* ASCII table signature */
	uint32_t length;		/* Length of table in bytes, including this header */
	uint8_t revision;		/* ACPI Specification minor version number */
	uint8_t checksum;		/* To make sum of entire table == 0 */
	char oem_id[ACPI_OEM_ID_SIZE];	/* ASCII OEM identification */
	char oem_table_id[ACPI_OEM_TABLE_ID_SIZE];	/* ASCII OEM table identification */
	uint32_t oem_revision;	/* OEM revision number */
	char asl_compiler_id[ACPI_NAME_SIZE];	/* ASCII ASL compiler vendor ID */
	uint32_t asl_compiler_revision;	/* ASL compiler version */
} __packed;

/*******************************************************************************
 *
 * MADT - Multiple APIC Description Table
 *        Version 3
 *
 ******************************************************************************/
struct acpi_table_madt {
	struct acpi_table_header header;	/* Common ACPI table header */
	uint32_t address;		/* Physical address of local APIC */
	uint32_t flags;
} __packed;

/* Generic subtable header (used in MADT, SRAT, etc.) */
struct acpi_subtable_header {
	uint8_t type;
	uint8_t length;
} __packed;

/* Generic Interrupt (ACPI 5.0 + ACPI 6.0 changes) */
struct acpi_madt_generic_interrupt {
	struct acpi_subtable_header header;
	uint16_t reserved;		/* reserved - must be zero */
	uint32_t cpu_interface_number;
	uint32_t uid;
	uint32_t flags;
	uint32_t parking_version;
	uint32_t performance_interrupt;
	uint64_t parked_address;
	uint64_t base_address;
	uint64_t gicv_base_address;
	uint64_t gich_base_address;
	uint32_t vgic_interrupt;
	uint64_t gicr_base_address;
	uint64_t arm_mpidr;
	uint8_t efficiency_class;
	uint8_t reserved2[3];
} __packed;

/* Generic Distributor (ACPI 5.0 + ACPI 6.0 changes) */
struct acpi_madt_generic_distributor {
	struct acpi_subtable_header header;
	uint16_t reserved;		/* reserved - must be zero */
	uint32_t gic_id;
	uint64_t base_address;
	uint32_t global_irq_base;
	uint8_t version;
	uint8_t reserved2[3];	/* reserved - must be zero */
} __packed;

/* Generic MSI Frame (ACPI 5.1) */
struct acpi_madt_generic_msi_frame {
	struct acpi_subtable_header header;
	uint16_t reserved;		/* reserved - must be zero */
	uint32_t msi_frame_id;
	uint64_t base_address;
	uint32_t flags;
	uint16_t spi_count;
	uint16_t spi_base;
} __packed;

/* Generic Translator (ACPI 6.0) */
struct acpi_madt_generic_translator {
	struct acpi_subtable_header header;
	uint16_t reserved;		/* reserved - must be zero */
	uint32_t translation_id;
	uint64_t base_address;
	uint32_t reserved2;
} __packed;

typedef struct {
    char *name;
    uint8_t *data;
    uint32_t  len;
    uint64_t  physical_address;
} madt_items_t;

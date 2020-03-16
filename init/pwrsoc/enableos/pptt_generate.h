#include <stdint.h>
#include "apic_generate.h"
#include <target/compiler.h>

/*******************************************************************************
 *
 * PPTT - Processor Properties Topology Table (ACPI 6.2)
 *        Version 1
 *
 ******************************************************************************/

struct acpi_table_pptt {
	struct acpi_table_header header;	/* Common ACPI table header */
}__packed;

/* Values for Type field above */

enum acpi_pptt_type {
	ACPI_PPTT_TYPE_PROCESSOR = 0,
	ACPI_PPTT_TYPE_CACHE = 1,
	ACPI_PPTT_TYPE_ID = 2,
	ACPI_PPTT_TYPE_RESERVED = 3
};

/* 0: Processor Hierarchy Node Structure */

struct acpi_pptt_processor {
	struct acpi_subtable_header header;
	uint16_t reserved;
	uint32_t flags;
	uint32_t parent;
	uint32_t acpi_processor_id;
	uint32_t number_of_priv_resources;
	uint32_t priv_resources1;
	uint32_t priv_resources2;
}__packed;

/* 1: Cache Type Structure */

struct acpi_pptt_cache {
	struct acpi_subtable_header header;
	uint16_t reserved;
	uint32_t flags;
	uint32_t next_level_of_cache;
	uint32_t size;
	uint32_t number_of_sets;
	uint8_t associativity;
	uint8_t attributes;
	uint16_t line_size;
}__packed;

/* 2: ID Structure */

struct acpi_pptt_id {
	struct acpi_subtable_header header;
	uint16_t reserved;
	uint32_t vendor_id;
	uint64_t level1_id;
	uint64_t level2_id;
	uint16_t major_rev;
	uint16_t minor_rev;
	uint16_t spin_rev;
}__packed;

/* Flags */

#define ACPI_PPTT_SIZE_PROPERTY_VALID       (1)	/* Physical property valid */
#define ACPI_PPTT_NUMBER_OF_SETS_VALID      (1<<1)	/* Number of sets valid */
#define ACPI_PPTT_ASSOCIATIVITY_VALID       (1<<2)	/* Associativity valid */
#define ACPI_PPTT_ALLOCATION_TYPE_VALID     (1<<3)	/* Allocation type valid */
#define ACPI_PPTT_CACHE_TYPE_VALID          (1<<4)	/* Cache type valid */
#define ACPI_PPTT_WRITE_POLICY_VALID        (1<<5)	/* Write policy valid */
#define ACPI_PPTT_LINE_SIZE_VALID           (1<<6)	/* Line size valid */

#define ATTRIBUTES_CACHE_DATA   0x0
#define ATTRIBUTES_CACHE_INST   0x1
#define ATTRIBUTES_CACHE_UNIF   0x2

#define ATTRIBUTES_WRITE_BACK   0x0
#define ATTRIBUTES_WRITE_THRU   0x1

#define L3_CACHE_SIZE_KB  0x0A00
#define L3_CACHE_SIZE_B  (L3_CACHE_SIZE_KB<<10)

/**
  Returns a 16-bit signature built from 2 ASCII characters.

  This macro returns a 16-bit value built from the two ASCII characters specified
  by A and B.

  @param  A    The first ASCII character.
  @param  B    The second ASCII character.

  @return A 16-bit value built from the two ASCII characters specified by A and B.

**/
#define SIGNATURE_16(A, B)        ((A) | (B << 8))

/**
  Returns a 32-bit signature built from 4 ASCII characters.

  This macro returns a 32-bit value built from the four ASCII characters specified
  by A, B, C, and D.

  @param  A    The first ASCII character.
  @param  B    The second ASCII character.
  @param  C    The third ASCII character.
  @param  D    The fourth ASCII character.

  @return A 32-bit value built from the two ASCII characters specified by A, B,
          C and D.

**/
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))

typedef struct {
    char *name;
    uint8_t *data;
    uint32_t  len;
    uint64_t  physical_address;
} pptt_items_t;

typedef struct {
  UINT8   AllocationType:2;
  UINT8   CacheType:2;
  UINT8   WritePolicy:1;
} CACHE_ATTRIBUTES;

typedef union CACHE_ATTRIBUTES_CONVERTER {
    CACHE_ATTRIBUTES BitsetAttr;
    UINT8 Attributes;
} CACHE_ATTRIBUTES_CONVERTER;


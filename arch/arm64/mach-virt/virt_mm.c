#include <asm/mmu.h>
#include <target/bitops.h>

const mmu_map_attr_t static_mmu_entry_list[] =
{
    /* virt_flash*/
    { 0x000000LL, 0x000000LL, 0x08000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, true, false,
      MMU_MAP_NAME_STATIC(boot-rom)
    },
    /*virt_cpuperiphs*/
    { 0x08000000LL, 0x08000000LL, 0x00020000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(cpu-periphs)
    },
    /*virt_gicdist*/
    { 0x08000000LL, 0x08000000LL, 0x00010000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, true, false,
      MMU_MAP_NAME_STATIC(gic-dis)
    },
    /*virt_giccpu*/
    { 0x08010000LL, 0x08010000LL, 0x00010000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gic-cpu)
    },

    /* virt_gicv2m */
    { 0x08020000LL, 0x08020000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gic-v2m)
    },

    /* virt_gichyp */
    { 0x08030000LL, 0x08030000LL, 0x00010000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gic-hyp)
    },
	/* virt_gicvcpu */
    { 0x08040000LL, 0x08040000LL,0x00010000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gic-vcpu)
    },
	/* The space in between here is reserved for GICv3 CPU/vCPU/HYP */
	/* virt_gicits */
    { 0x08080000LL, 0x08080000LL, 0x00020000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gic-its)
    },

    /* This redistributor space allows up to 2*64kB*123 CPUs */
	/* virt_gicredist */
    { 0x080A0000LL, 0x080A0000LL, 0x00F60000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, true, false,
      MMU_MAP_NAME_STATIC(gic-redist)
    },
    /* virt_uart */
    { 0x09000000LL, 0x09000000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(uart)
    },
    /* virt_rtc */
    { 0x09010000LL, 0x09010000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(rtc)
    },
	/* virt_fwcfg */
    { 0x09020000LL, 0x09020000LL, 0x00001000LL,
      PERM_R, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(fw-cfg)
    },

	/* virt_gpio */
    { 0x09030000LL, 0x09030000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(gpio)
    },
	/* virt_secureuart */
    { 0x09040000LL, 0x09040000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(secure-uart)
    },
	/* virt_smmu */
    { 0x09050000LL, 0x09050000LL, 0x00020000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(smmu)
    },

    /* virt_mmio */
    { 0x0a000000LL, 0x0a000000LL, 0x00001000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(mmio)
    },

    /* ...repeating for a total of NUM_VIRTIO_TRANSPORTS, each of that size */
    /* virt_platformbus */
    { 0x0c000000LL, 0x0c000000LL, 0x02000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(platform-bus)
    },

    /* virt_securemem */
    { 0x0e000000LL, 0x0e000000LL, 0x01000000LL,
      PERM_RW, 0x0, CACHE_OUTER_NC_INNER_NC, true, false,
      MMU_MAP_NAME_STATIC(secure-mem)
    },

    /* virt_pciemmio */
    { 0x10000000LL, 0x10000000LL, 0x2eff0000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(pcie-mmio)
    },

    /* virt_pciepio */
    { 0x3eff0000LL, 0x3eff0000LL, 0x00010000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(pcie-pio)
    },

    /* virt_ecam */
    { 0x3f000000LL, 0x3f000000LL, 0x01000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(ecam)
    },

    /* pci-host-0 config space */
    { 0x4010000000LL, 0x4010000000LL, 0x010000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(ecam)
    },

    /* Actual RAM size depends on initial RAM and device memory settings */
    /* virt_mem */
    { 0x40200000LL, 0x40200000LL, 0x3fe00000LL,
      PERM_RW, SHARE_INNER, CACHE_OUTER_WB_INNER_WB, false, false,
      MMU_MAP_NAME_STATIC(mem)
    },
};

UINT32 static_mmu_entry_list_len = ARRAY_SIZE(static_mmu_entry_list);


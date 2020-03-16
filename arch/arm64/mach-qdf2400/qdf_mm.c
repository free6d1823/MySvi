#include <asm/mmu.h>
#include <target/bitops.h>

/* imc_config.xml defined memory regions */
const mmu_map_attr_t static_mmu_entry_list[] =
{
    /* ddr */
    { 0x000000LL, 0x000000LL, 0xc000000000LL,
      PERM_RW, 0x0, CACHE_OUTER_NC_INNER_NC, false, false,
      MMU_MAP_NAME_STATIC(ddr-ncnc)
    },
    { 0xe000000000LL, 0x000000LL, 0x100000000LL,
      PERM_RW, 0x0, CACHE_OUTER_WB_INNER_WB, false, false,
      MMU_MAP_NAME_STATIC(ddr-wbwb)
    },
    { 0xe100000000LL, 0x000000LL, 0x100000000LL,
      PERM_RW, 0x0, CACHE_OUTER_NC_INNER_WB, false, false,
      MMU_MAP_NAME_STATIC(ddr-ncwb)
    },
    { 0xe200000000LL, 0x000000LL, 0x100000000LL,
      PERM_RW, 0x0, CACHE_OUTER_WB_INNER_NC, false, false,
      MMU_MAP_NAME_STATIC(ddr-wbnc)
    },

    /* IMC Non-MSA Window */
    { 0xfec0000000LL, 0xfec0000000LL, 0x40000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(non-msa)
    },

    /* System Fabric */
    /* Configuration Fabric */
    { 0xff00000000LL, 0xff00000000LL, 0x60000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(cfg-fab)
    },
    /* HS3/HS4/HS1/HS2/QDSS */
    { 0xff60000000LL, 0xff60000000LL, 0xf800000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(hs1234)
    },
    /* IMC Fabric: see below */
    /* Peripheral Fabric/HMSS/HS5 */
    { 0xff70500000LL, 0xff70500000LL, 0xfb00000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(hmss/hs5)
    },

    /* IMC Fabric */
    /* IMEM 4K NC*/
    { 0xff6f800000LL, 0xff6f800000LL, 0x1000LL,
      PERM_RW, 0x0, CACHE_OUTER_NC_INNER_NC, false, false,
      MMU_MAP_NAME_STATIC(imc-cfg)
    },
    /* APU/QGIC/QTIMER/GPIO/IMCCfg/Clock */
    { 0xff6fa00000LL, 0xff6fa00000LL, 0x300000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(imc-cfg)
    },
    /* RAM Cfg */
    { 0xff6fd00000LL, 0xff6fd00000LL, 0x200000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(ram-cfg)
    },
    /* Boot ROM */
    { 0xff6ff00000LL, 0xff6ff00000LL, 0x100000LL,
      PERM_R, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(boot-rom)
    },

    /* Peripheral Fabric */
    { 0xff78000000LL, 0xff78000000LL, 0x4000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(per-fab)
    },
    /* Monaco Cfg/SATA/DMA */
    { 0xff80000000LL, 0xff80000000LL, 0x20000000LL,
      PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
      MMU_MAP_NAME_STATIC(monaco)
    },
};

UINT32 static_mmu_entry_list_len = ARRAY_SIZE(static_mmu_entry_list);

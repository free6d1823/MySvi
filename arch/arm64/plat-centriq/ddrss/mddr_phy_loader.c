/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_phy_loader.c
*
* @par Description:
*    This module provides the functionality to load the DDR PHY firmware into
*    the corresponding DMEM and IMEM registers.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <target/ddr.h>

/******************************************************************************
* Global Variables
******************************************************************************/
phy_binary_hdr_t phy_binary_hdr[DDRPHY_NUM_IMAGES];


/******************************************************************************
* Function Prototypes
******************************************************************************/
void mddr_phy_getnload_fw(uint8_t ddr_chan, phy_binary_fwtype_t fwtype, phy_binary_fwid_t fwid);
unsigned int mddr_phy_get_image_info(phy_binary_fwid_t fwid, uint64_t* out_addr, uint32_t* size);


/*!****************************************************************************
*
* @par Description:
*    This function determines the firmware id based on the firware type and
*     invokes the DDR PHY get and load firmware function to load the PHY
*     binary images into the corresponding DDR PHY IMEM/DMEM register areas.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    fwtype    DDR PHY binary firmware type for each of the images.
*
* @return
*    None
*
* @author
*    lchavani
*
******************************************************************************/
void mddr_phy_load_fwtype(uint8_t ddr_chan, phy_binary_fwtype_t fwtype)
{
    if (fwtype == DDRPHY_FWTYPE_1DTRAINING)
    {
        if ((common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM) && (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4))
        {
            mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_1DTRAINING, DDR4_RDIMM_TRAIN_IMEM);
            mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_1DTRAINING, DDR4_RDIMM_TRAIN_DMEM);
        }
        else if ((common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM) && (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4))
        {
            mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_1DTRAINING, DDR4_LRDIMM_TRAIN_IMEM);
            mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_1DTRAINING, DDR4_LRDIMM_TRAIN_DMEM);
        }
    }
    else if (fwtype == DDRPHY_FWTYPE_2DTRAINING)
    {
        mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_2DTRAINING, DDR4_PMU_TRAIN2D_IMEM);
        mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_2DTRAINING, DDR4_PMU_TRAIN2D_DMEM);
    }
    else if (fwtype == DDRPHY_FWTYPE_DIAGS)
    {
        mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_DIAGS, DDR4_DIAG_IMEM);
        mddr_phy_getnload_fw(ddr_chan, DDRPHY_FWTYPE_DIAGS, DDR4_DIAG_DMEM);
    }

}


/*!****************************************************************************
*
* @par Description:
*    This function based on the firmware id, obtains the DDR PHY firmware binary
*     image info and loads the firmware into DDR PHY IMEM/DMEM register areas.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    fwtype    DDR PHY binary firmware type for each of the images.
*                                  @param
*    fwid      DDR PHY binary firmware id for each of the images.
*
* @return
*    None
*
* @author
*    lchavani
*
******************************************************************************/
void mddr_phy_getnload_fw(uint8_t ddr_chan, phy_binary_fwtype_t fwtype, phy_binary_fwid_t fwid)
{
    uint64_t mddr_base_addr;
    uint64_t bin_address;    // The start address of the PHY firmware binary image
    uint32_t bin_size;       // The size of the PHY firmware binary image
    unsigned status;
    uint32_t reg_val = 0x0;
    uint32_t offset = 0x0;
    uint32_t size = 0x0;
    uint8_t fwid_mask = 0x0;
    uint64_t ddrphy_uctl_base_addr;

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    // Micro controller csr requests ignored.
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICROCONTMUXSEL_OFFSET,
        "DDRPHY_APBONLY0_MICROCONTMUXSEL", 0x0);

    // Obtain the PHY firmware binary image info
    #ifdef __BAREMETAL__
    status = mddr_phy_get_image_info(fwid, &bin_address, &bin_size);
    #else
    status = (unsigned)monaco_get_ddr4_image_info(fwid, &bin_address, &bin_size);
    #endif

    if (status == COM_ERROR)
    {
        monaco_log(CRITICAL, "DDR PHY: Failed to obtain PHY binary FW!\n");
    }
    else    // status = COM_OK
    {
        // Load the PHY firmware binary image into the DDR PHY IMEM/DMEM register areas.
        fwid_mask = (uint8_t)fwid;

        // Bit[0] is used to distinguish between IMEM and DMEM
        if(fwid_mask & 0x1)
        {
            if (fwtype == DDRPHY_FWTYPE_DIAGS)
            {
                ddrphy_uctl_base_addr = (uint64_t)DDRPHY_UCTL_DMEM_3584_OFFSET;
            }
            else
            {
                ddrphy_uctl_base_addr = (uint64_t)DDRPHY_UCTL_DMEM_0_OFFSET;
            }
        }
        else
        {
            ddrphy_uctl_base_addr = (uint64_t)DDRPHY_UCTL_IMEM_0_OFFSET;
        }

        // Iterate thru the binary image to form the 16-bit register value to be written
        // into the destination registers.
        while(size < bin_size)
        {
            reg_val = read8(bin_address);
            bin_address++;
            reg_val |= read8(bin_address) << 8;

            write32(mddr_base_addr + ddrphy_uctl_base_addr + offset, reg_val);
            bin_address++;
            offset += 4;
            size += 2;
        }

        monaco_log(INFORMATIONAL, "DDR PHY: Completed loading PHY binary FW for firmware id = %d\n", fwid);

    }
}


#ifdef __BAREMETAL__
/*!****************************************************************************
*
* @par Description:
*    This function, based on the firmware id, obtains the required DDR PHY
*     firmware binary image info to be loaded into the corresponding
*     PHY IMEM and DMEM register areas.
*
*                                  @param
*    fwid      DDR PHY binary firmware id for each of the images.
*                                  @param
*    out_addr  Pointer to the PHY binary image start address.
*                                  @param
*    size      Pointer to the PHY binary image size.
*
* @return
*    The status indicating if the function is successful or not in getting the
*     firmware image info.
*
* @author
*    lchavani
*
******************************************************************************/
unsigned int mddr_phy_get_image_info(phy_binary_fwid_t fwid, uint64_t* out_addr, uint32_t* size)
{
    unsigned status = COM_OK;

    *out_addr = phy_binary_hdr[fwid].bin_start_addr;
    *size     = phy_binary_hdr[fwid].bin_size;

    if(*out_addr == 0x0 || *size == 0x0)
        return COM_ERROR;

    return status;
}
#endif



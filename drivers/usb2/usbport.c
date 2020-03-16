#include "usbport.h"
#include "usb.h"
#include "xhci.h"
#include "stdio.h"

#define _FV_MASK(name) \
	((name##_MASK) << (name##_OFFSET))

#define __raw_writel_nmask(v, n, a) \
	__raw_writel_mask(_SET_FV(n, v), _FV_MASK(n), a)

#define USB_PHY(n) (0xff7a400000 + 0x100000 * n)
#define USB_PHY_REVISION_ID3  0x000c

#define USB_PHY_UTMI_CTRL5    0x0074
#define POR                   _BV(1)

#define USB_PHY_CFG0          0x00c4
#define UTMI_PHY_CMN_CTRL_OVERRIDE_EN  _BV(2)

#define USB3(n) (0xff79800000 + 0x200000 * n)

#define USB3_GCTL             0xc110
#define CORESOFTRESET         _BV(11)

#define USB3_GENERAL_CFG      0xf8808
#define PIPE_UTMI_CLK_DIS     _BV(8)
#define PIPE_UTMI_CLK_SEL     _BV(0)
#define PIPE3_PHYSTATUS_SW    _BV(3)

#define USB3_GUSB2PHYCFG      0xc200
#define PHYSOFTRST            _BV(31)


#define USB3_GUCTL            0xc12c
#define REFCLKPER_MASK        0x3ff
#define REFCLKPER_OFFSET      22

#define USB3_GFLADJ           0xc630

#define USB3_DCTL             0xc704
#define CSFTRST               _BV(30)

#define USB3_GCTL             0xc110
#define U2EXIT_LFPS           _BV(2)
#define PRTCAPDIR_MASK        3
#define PRTCAPDIR_OFFSET      12

#define USB3_PORTSC_REGS_p_PORTSC 0x420
#define WCE                   _BV(25)

#define USB3_GRXTHRCFG           0xc10c
#define USBMaxRxBurstSize_MASK   0x1f
#define USBMaxRxBurstSize_OFFSET 19
#define USBRxPktCnt_MASK         0xf
#define USBRxPktCnt_OFFSET       24
#define USBRxPktCntSel           _BV(29)

int xhci_hcd_init(int index, struct xhci_hccr **hccr,
					struct xhci_hcor **hcor)
{
	int i;

	*hccr = (struct xhci_hccr *)USB3(index);
	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr
				+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	if (__raw_readl(USB_PHY(index) + USB_PHY_REVISION_ID3)) {
		__raw_setl(UTMI_PHY_CMN_CTRL_OVERRIDE_EN, USB_PHY(index) + USB_PHY_CFG0);
		__raw_setl(POR, USB_PHY(index) + USB_PHY_UTMI_CTRL5);
		mdelay(1);
		__raw_clearl(POR, USB_PHY(index) + USB_PHY_UTMI_CTRL5);
		__raw_clearl(UTMI_PHY_CMN_CTRL_OVERRIDE_EN, USB_PHY(index) + USB_PHY_CFG0);
	}

	__raw_setl(CORESOFTRESET, USB3(index) + USB3_GCTL);

	__raw_setl(PIPE_UTMI_CLK_DIS, USB3(index) + USB3_GENERAL_CFG);
	mdelay(1);
	__raw_setl(PIPE_UTMI_CLK_SEL, USB3(index) + USB3_GENERAL_CFG);
	mdelay(1);
	__raw_setl(PIPE3_PHYSTATUS_SW, USB3(index) + USB3_GENERAL_CFG);
	mdelay(1);
	__raw_clearl(PIPE_UTMI_CLK_DIS, USB3(index) + USB3_GENERAL_CFG);

	__raw_setl(PHYSOFTRST, USB3(index) + USB3_GUSB2PHYCFG);
	mdelay(1);
	__raw_clearl(PHYSOFTRST, USB3(index) + USB3_GUSB2PHYCFG);
	mdelay(10);

	__raw_clearl(CORESOFTRESET, USB3(index) + USB3_GCTL);

	/* 20mhz */
	__raw_writel_nmask(50, REFCLKPER, USB3(index) + USB3_GUCTL);

	__raw_writel(0, USB3(index) + USB3_GFLADJ);

	__raw_setl(CSFTRST, USB3(index) + USB3_DCTL);


	i = 100;
	while (i && __raw_testl(CSFTRST, USB3(index) + USB3_DCTL)) {
		mdelay(10);
		i--;
	}
	if (i == 0) printf("Timed out waiting for DCTL.CSFTRST=0\n");

	__raw_setl(U2EXIT_LFPS, USB3(index) + USB3_GCTL);
	__raw_writel_nmask(1, PRTCAPDIR, USB3(index) + USB3_GCTL);

	__raw_setl(WCE, USB3(index) + USB3_PORTSC_REGS_p_PORTSC);

	__raw_writel_nmask(3, USBMaxRxBurstSize, USB3(index) + USB3_GRXTHRCFG);
	__raw_writel_nmask(3, USBRxPktCnt, USB3(index) + USB3_GRXTHRCFG);
	__raw_setl(USBRxPktCntSel, USB3(index) + USB3_GRXTHRCFG);

	return 0;
}


void xhci_hcd_stop(int index)
{
	return;
}

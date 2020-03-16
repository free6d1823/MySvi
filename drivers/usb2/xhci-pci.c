#include "usbport.h"
#include "usb.h"
#include "xhci.h"
#include "stdio.h"
#include <target/pci.h>
#include <target/pci_ids.h>

int xhci_hcd_init(int index, struct xhci_hccr **hccr,
					struct xhci_hcor **hcor)
{
	pci_dev_t dev;

	if (index != 0)
		return -1;

	dev = pci_get_dev_by_class(0, PCI_CLASS_SERIAL_USB_XHCI);
	if (dev == -1) {
		printf("xhci device not found\n");
		return -1;
	}

	*hccr = (struct xhci_hccr *)pci_map_bar(0, dev, PCI_BASE_ADDRESS_0);

	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr +
			HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void xhci_hcd_stop(int index)
{
	return;
}

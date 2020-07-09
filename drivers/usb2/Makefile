obj-$(CONFIG_USB) += usb.o usb_hub.o
obj-$(CONFIG_USB) += usb_cmd.o

obj-$(CONFIG_USB_XHCI_HCD) += xhci.o xhci-mem.o xhci-ring.o
#obj-$(CONFIG_USB_XHCI_HCD) += usbport.o
obj-$(CONFIG_USB_XHCI_PCI) += xhci-pci.o

obj-$(CONFIG_USB_EHCI_HCD) += ehci-hcd.o
obj-$(CONFIG_USB_STORAGE) += usb_storage.o
# designware
obj-$(CONFIG_USB_DWC2) += dwc2.o
obj-$(CONFIG_USB_DWC3) += xhci-dwc3.o


obj-$(CONFIG_USB_DWC2_DEVICE) += ./gadget/
obj-$(CONFIG_USB_DWC3_GADGET) += ./gadget/

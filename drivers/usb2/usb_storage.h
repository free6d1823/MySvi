 #ifndef _USB_STORAGE_H
 #define _USB_STORAGE_H

#ifdef CONFIG_SYS_64BIT_LBA
typedef uint64_t lbaint_t;
#define LBAFlength "ll"
#else
typedef ulong lbaint_t;
#define LBAFlength "l"
#endif
#define LBAF "%" LBAFlength "x"
#define LBAFU "%" LBAFlength "u"

/* Interface types: */
enum if_type {
	IF_TYPE_UNKNOWN = 0,
	IF_TYPE_IDE,
	IF_TYPE_SCSI,
	IF_TYPE_ATAPI,
	IF_TYPE_USB,
	IF_TYPE_DOC,
	IF_TYPE_MMC,
	IF_TYPE_SD,
	IF_TYPE_SATA,
	IF_TYPE_HOST,
	IF_TYPE_NVME,
	IF_TYPE_EFI,
	IF_TYPE_VIRTIO,

	IF_TYPE_COUNT,			/* Number of interface types */
};

#define CONFIG_SYS_PCI_64BIT
#ifdef CONFIG_SYS_PCI_64BIT
typedef uint64_t pci_addr_t;
typedef uint64_t pci_size_t;
typedef uint64_t phys_addr_t;
typedef uint64_t phys_size_t;
#else
typedef uint32_t pci_addr_t;
typedef uint32_t pci_size_t;
typedef uint32_t phys_addr_t;
typedef uint32_t phys_size_t;
#endif

#define uswap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))
# define be32_to_cpu(x)		uswap_32(x)
#define LOG2(x) (((x & 0xaaaaaaaa) ? 1 : 0) + ((x & 0xcccccccc) ? 2 : 0) + \
		 ((x & 0xf0f0f0f0) ? 4 : 0) + ((x & 0xff00ff00) ? 8 : 0) + \
		 ((x & 0xffff0000) ? 16 : 0))

#define BLK_VEN_SIZE		40
#define BLK_PRD_SIZE		20
#define BLK_REV_SIZE		8
#define PART_TYPE_UNKNOWN	0x00
#define DEV_TYPE_UNKNOWN	0xff	/* not connected */
#define SCSI_SEND_DIAG	0x1D		/* Send Diagnostic (O) */
#define SCSI_REQ_SENSE	0x03		/* Request Sense (MANDATORY) */
#define SCSI_INQUIRY		0x12		/* Inquiry (MANDATORY) */
#define SCSI_TST_U_RDY	0x00		/* Test Unit Ready (MANDATORY) */
#define SCSI_RD_CAPAC	0x25		/* Read Capacity (MANDATORY) */
#define SCSI_READ10		0x28		/* Read 10-byte (MANDATORY) */
#define SCSI_WRITE10	0x2A		/* Write 10-Byte (MANDATORY) */
//#define ARCH_DMA_MINALIGN	128


typedef unsigned char		uchar;

/*
 * Identifies the partition table type (ie. MBR vs GPT GUID) signature
 */
enum sig_type {
	SIG_TYPE_NONE,
	SIG_TYPE_MBR,
	SIG_TYPE_GUID,

	SIG_TYPE_COUNT			/* Number of signature types */
};

typedef struct {
	u8 b[16];
} efi_guid_t __attribute__((aligned(8)));

#define dev_printk(dev, fmt, ...)				\
({								\
	printk(fmt, ##__VA_ARGS__);				\
})

struct scsi_cmd {
	unsigned char		cmd[16];					/* command				   */
	/* for request sense */
	unsigned char		sense_buf[64]
		__attribute__((aligned(ARCH_DMA_MINALIGN)));
	unsigned char		status;						/* SCSI Status			 */
	unsigned char		target;						/* Target ID				 */
	unsigned char		lun;							/* Target LUN        */
	unsigned char		cmdlen;						/* command len				*/
	unsigned long		datalen;					/* Total data length	*/
	unsigned char	*	pdata;						/* pointer to data		*/
	unsigned char		msgout[12];				/* Messge out buffer (NOT USED) */
	unsigned char		msgin[12];				/* Message in buffer	*/
	unsigned char		sensecmdlen;			/* Sense command len	*/
	unsigned long		sensedatalen;			/* Sense data len			*/
	unsigned char		sensecmd[6];			/* Sense command			*/
	unsigned long		contr_stat;				/* Controller Status	*/
	unsigned long		trans_bytes;			/* tranfered bytes		*/

	unsigned int		priv;
};

/*
 * With driver model (CONFIG_BLK) this is uclass platform data, accessible
 * with dev_get_uclass_platdata(dev)
 */
struct blk_desc {
	/*
	 * TODO: With driver model we should be able to use the parent
	 * device's uclass instead.
	 */
	enum if_type	if_type;	/* type of the interface */
	int		devnum;		/* device number */
	unsigned char	part_type;	/* partition type */
	unsigned char	target;		/* target SCSI ID */
	unsigned char	lun;		/* target LUN */
	unsigned char	hwpart;		/* HW partition, e.g. for eMMC */
	unsigned char	type;		/* device type */
	unsigned char	removable;	/* removable device */
#ifdef CONFIG_LBA48
	/* device can use 48bit addr (ATA/ATAPI v7) */
	unsigned char	lba48;
#endif
	lbaint_t	lba;		/* number of blocks */
	unsigned long	blksz;		/* block size */
	int		log2blksz;	/* for convenience: log2(blksz) */
	char		vendor[BLK_VEN_SIZE + 1]; /* device vendor string */
	char		product[BLK_PRD_SIZE + 1]; /* device product number */
	char		revision[BLK_REV_SIZE + 1]; /* firmware revision */
	enum sig_type	sig_type;	/* Partition table signature type */
	union {
		uint32_t mbr_sig;	/* MBR integer signature */
		efi_guid_t guid_sig;	/* GPT GUID Signature */
	};
#if CONFIG_IS_ENABLED(BLK)
	/*
	 * For now we have a few functions which take struct blk_desc as a
	 * parameter. This field allows them to look up the associated
	 * device. Once these functions are removed we can drop this field.
	 */
	struct udevice *bdev;
#else
	unsigned long	(*block_read)(struct blk_desc *block_dev,
				      lbaint_t start,
				      lbaint_t blkcnt,
				      void *buffer);
	unsigned long	(*block_write)(struct blk_desc *block_dev,
				       lbaint_t start,
				       lbaint_t blkcnt,
				       const void *buffer);
	unsigned long	(*block_erase)(struct blk_desc *block_dev,
				       lbaint_t start,
				       lbaint_t blkcnt);
	void		*priv;		/* driver private struct pointer */
#endif
};

/**
 * struct blk_driver - Driver for block interface types
 *
 * This provides access to the block devices for each interface type. One
 * driver should be provided using U_BOOT_LEGACY_BLK() for each interface
 * type that is to be supported.
 *
 * @if_typename:	Interface type name
 * @if_type:		Interface type
 * @max_devs:		Maximum number of devices supported
 * @desc:		Pointer to list of devices for this interface type,
 *			or NULL to use @get_dev() instead
 */
struct blk_driver {
	const char *if_typename;
	enum if_type if_type;
	int max_devs;
	struct blk_desc *desc;
	/**
	 * get_dev() - get a pointer to a block device given its number
	 *
	 * Each interface allocates its own devices and typically
	 * struct blk_desc is contained with the interface's data structure.
	 * There is no global numbering for block devices. This method allows
	 * the device for an interface type to be obtained when @desc is NULL.
	 *
	 * @devnum:	Device number (0 for first device on that interface,
	 *		1 for second, etc.
	 * @descp:	Returns pointer to the block device on success
	 * @return 0 if OK, -ve on error
	 */
	int (*get_dev)(int devnum, struct blk_desc **descp);

	/**
	 * select_hwpart() - Select a hardware partition
	 *
	 * Some devices (e.g. MMC) can support partitioning at the hardware
	 * level. This is quite separate from the normal idea of
	 * software-based partitions. MMC hardware partitions must be
	 * explicitly selected. Once selected only the region of the device
	 * covered by that partition is accessible.
	 *
	 * The MMC standard provides for two boot partitions (numbered 1 and 2),
	 * rpmb (3), and up to 4 addition general-purpose partitions (4-7).
	 * Partition 0 is the main user-data partition.
	 *
	 * @desc:	Block device descriptor
	 * @hwpart:	Hardware partition number to select. 0 means the main
	 *		user-data partition, 1 is the first partition, 2 is
	 *		the second, etc.
	 * @return 0 if OK, other value for an error
	 */
	int (*select_hwpart)(struct blk_desc *desc, int hwpart);
};

/*
 * Declare a new U-Boot legacy block driver. New drivers should use driver
 * model (UCLASS_BLK).
 */
#define U_BOOT_LEGACY_BLK(__name)					\
	ll_entry_declare(struct blk_driver, __name, blk_driver)

/**
 * ll_entry_declare() - Declare linker-generated array entry
 * @_type:	Data type of the entry
 * @_name:	Name of the entry
 * @_list:	name of the list. Should contain only characters allowed
 *		in a C variable name!
 *
 * This macro declares a variable that is placed into a linker-generated
 * array. This is a basic building block for more advanced use of linker-
 * generated arrays. The user is expected to build their own macro wrapper
 * around this one.
 *
 * A variable declared using this macro must be compile-time initialized.
 *
 * Special precaution must be made when using this macro:
 *
 * 1) The _type must not contain the "static" keyword, otherwise the
 *    entry is generated and can be iterated but is listed in the map
 *    file and cannot be retrieved by name.
 *
 * 2) In case a section is declared that contains some array elements AND
 *    a subsection of this section is declared and contains some elements,
 *    it is imperative that the elements are of the same type.
 *
 * 3) In case an outer section is declared that contains some array elements
 *    AND an inner subsection of this section is declared and contains some
 *    elements, then when traversing the outer section, even the elements of
 *    the inner sections are present in the array.
 *
 * Example:
 *
 * ::
 *
 *   ll_entry_declare(struct my_sub_cmd, my_sub_cmd, cmd_sub) = {
 *           .x = 3,
 *           .y = 4,
 *   };
 */
#define ll_entry_declare(_type, _name, _list)				\
	_type _u_boot_list_2_##_list##_2_##_name __aligned(4)		\
			__attribute__((unused,				\
			section(".u_boot_list_2_"#_list"_2_"#_name)))

extern ulong usb_blk_write_devnum(enum if_type if_type, int devnum, lbaint_t start,
		       lbaint_t blkcnt, const void *buffer);


extern ulong usb_blk_read_devnum(enum if_type if_type, int devnum, lbaint_t start,
				lbaint_t blkcnt, void *buffer);

int usb_print_info_num(unsigned int usb_num);

#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libfdt_env.h"
#include "fdt.h"
#include "libfdt.h"
#include "libfdt_internal.h"
#include "fdt_support.h"

/**
* fdt_path_offset_create - find & create a tree node by its full path,
* @fdt: pointer to the device tree blob
* @path: full path of the node to locate
*
* refer to fdt_path_offset and fdt_add_subnode_namelen
*/
int fdt_path_offset_create(void *fdt, const char *path)
{
	const char *end = path + strlen(path);
	const char *p = path;
	int offset = 0;
	int suboffset;
	int err;

	if ((err = fdt_check_header(fdt)) != 0)
			return err;

	/* see if we have an alias */
	if (*path != '/') {
		const char *q = strchr(path, '/');

		if (!q)
			q = end;

		p = fdt_get_alias_namelen(fdt, p, q - p);
		if (!p)
			return -FDT_ERR_BADPATH;
		offset = fdt_path_offset(fdt, p);

		p = q;
	}

	while (*p) {
		const char *q;

		while (*p == '/')
			p++;
		if (! *p)
			return offset;
		q = strchr(p, '/');
		if (! q)
			q = end;

		suboffset = fdt_subnode_offset_namelen(fdt, offset, p, q-p);
		if (suboffset < 0)
			suboffset = fdt_add_subnode_namelen(fdt, offset, p, q-p);

		if (suboffset < 0)
			return suboffset;
		else
			offset = suboffset;

		p = q;
	}

	return offset;
}

/**
 * fdt_find_and_setprop: Find a node and set it's property
 *
 * @fdt: ptr to device tree
 * @node: path of node
 * @prop: property name
 * @val: ptr to new value
 * @len: length of new property value
 * @create: flag to create the property if it doesn't exist
 *
 * Convenience function to directly set a property given the path to the node.
 */
int fdt_find_and_setprop(void *fdt, const char *node, const char *prop,
			 const void *val, int len, int create)
{
	int nodeoff = fdt_path_offset(fdt, node);

	if (nodeoff < 0)
		return nodeoff;

	if ((!create) && (fdt_get_property(fdt, nodeoff, prop, 0) == NULL))
		return 0; /* create flag not set; so exit quietly */

	return fdt_setprop(fdt, nodeoff, prop, val, len);
}

static inline int fdt_setprop_uxx(void *fdt, int nodeoffset, const char *name,
				  uint64_t val, int is_u64)
{
	if (is_u64)
		return fdt_setprop_u64(fdt, nodeoffset, name, val);
	else
		return fdt_setprop_u32(fdt, nodeoffset, name, (uint32_t)val);
}


int fdt_initrd(void *fdt, unsigned long initrd_start, unsigned long initrd_end)
{
	int   nodeoffset;
	int   err, j, total;
	int is_u64;
	uint64_t addr, size;

	/* just return if the size of initrd is zero */
	if (initrd_start == initrd_end)
		return 0;

	/* find or create "/chosen" node. */
	nodeoffset = fdt_path_offset (fdt, "/chosen");
	if (nodeoffset < 0)
		return nodeoffset;

	total = fdt_num_mem_rsv(fdt);

	/*
	 * Look for an existing entry and update it.  If we don't find
	 * the entry, we will j be the next available slot.
	 */
	for (j = 0; j < total; j++) {
		err = fdt_get_mem_rsv(fdt, j, &addr, &size);
		if (addr == initrd_start) {
			fdt_del_mem_rsv(fdt, j);
			break;
		}
	}

	err = fdt_add_mem_rsv(fdt, initrd_start, initrd_end - initrd_start);
	if (err < 0) {
		printf("fdt_initrd: %s\n", fdt_strerror(err));
		return err;
	}

	is_u64 = (fdt_address_cells(fdt, 0) == 2);

	err = fdt_setprop_uxx(fdt, nodeoffset, "linux,initrd-start",
				  (uint64_t)initrd_start, is_u64);

	if (err < 0) {
		printf("WARNING: could not set linux,initrd-start %s.\n",
			   fdt_strerror(err));
		return err;
	}

	err = fdt_setprop_uxx(fdt, nodeoffset, "linux,initrd-end",
				  (uint64_t)initrd_end, is_u64);

	if (err < 0) {
		printf("WARNING: could not set linux,initrd-end %s.\n",
			   fdt_strerror(err));

		return err;
	}

	return 0;

}

int fdt_chosen(void *fdt)
{
	int nodeoffset;
	int err;
	char *str;
	const char *path;

	err = fdt_check_header(fdt);
	if (err < 0) {
		printf("fdt_chosen: %s\n", fdt_strerror(err));
		return err;
	}

	/*
	 * Find the "chosen" node.
	 */
	nodeoffset = fdt_path_offset (fdt, "/chosen");

	/*
	 * If there is no "chosen" node in the blob, create it.
	 */
	if (nodeoffset < 0) {
		/*
		 * Create a new node "/chosen" (offset 0 is root level)
		 */
		nodeoffset = fdt_add_subnode(fdt, 0, "chosen");
		if (nodeoffset < 0) {
			printf("WARNING: could not create /chosen %s.\n",
				fdt_strerror(nodeoffset));
			return nodeoffset;
		}
	}
	return err;

}

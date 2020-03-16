#ifndef __FDT_SUPPORT_H
#define __FDT_SUPPORT_H


int fdt_path_offset_create(void *fdt, const char *path);
int fdt_find_and_setprop(void *fdt, const char *node, const char *prop,
			 const void *val, int len, int create);
int fdt_initrd(void *fdt, unsigned long initrd_start, unsigned long initrd_end);
int fdt_chosen(void *fdt);

#endif /* ifndef __FDT_SUPPORT_H */
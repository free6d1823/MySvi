#include <target/ddr.h>
#include <target/guid.h>

typedef GUID                      EFI_GUID;
//
// The Microsoft* C compiler can removed references to unreferenced data items
//  if the /OPT:REF linker option is used. We defined a macro as this is a
//  a non standard extension
//
#if defined(_MSC_EXTENSIONS) && !defined (MDE_CPU_EBC)
  ///
  /// Remove global variable from the linked image if there are no references to
  /// it after all compiler and linker optimizations have been performed.
  ///
  ///
  #define GLOBAL_REMOVE_IF_UNREFERENCED __declspec(selectany)
#else
  ///
  /// Remove the global variable from the linked image if there are no references
  ///  to it after all compiler and linker optimizations have been performed.
  ///
  ///
  #define GLOBAL_REMOVE_IF_UNREFERENCED
#endif

GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gSharedVariablesPartitionGuid = { 0x3E8954C9, 0xF738, 0x4ED6, { 0x8A, 0xD1, 0x22, 0x9E, 0x60, 0xE9, 0xB6, 0xC8 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gInternalSharedVariablesGuid = { 0x307b4686, 0x869a, 0x4b12, { 0xb6, 0x97, 0x2f, 0x42, 0x2a, 0x24, 0x2d, 0x09 } };

void sbl_read_ddrsi_table(char *note_name, unsigned long *ddrsi_base)
{
    unsigned int note_name_len = 0;
    unsigned int count = 0;
    unsigned char* ddrsi_addr = ddrsi_bin;
    note_name_len = strlen(note_name);

    for(count; count < ddrsi_bin_len;)
    {
        if(strncmp( (const char*)(ddrsi_addr + count), note_name, note_name_len) == 0)
            break;
        count += 8;
    }
    //The true ddr si data is offset 16
    *ddrsi_base = (unsigned long)(ddrsi_addr + count + 16);
}

int ddr_init()
{
    boot_init_boot_variables();
    ddr_initialize_common(get_cpu_mask(), get_llc_mask(), (uint64_t)ddrfw_bin, true);
    return 0;
}

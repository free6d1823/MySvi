#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <target/cmdline.h>

static unsigned int crc32_table[256];
#define CRC32_POLY_TABLE 0xedb88320L
static bool crc32_inited=false;

void init_crc_table(void)
{
    unsigned int c;
    unsigned int i, j;

    for (i = 0; i < 256; i++) {
        c = (unsigned int)i;
        for (j = 0; j < 8; j++) {
            if (c & 1)
                c =  CRC32_POLY_TABLE ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc32_table[i] = c;
    }
}

unsigned int cal_crc32(unsigned int crc, unsigned char *buffer, unsigned int size)
{
    unsigned int i;

    if(!crc32_inited) {
        crc32_inited = true;
        init_crc_table();
    }

    for (i = 0; i < size; i++) {
        crc = crc32_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
    }

    /*'not' is for compatible with linux tool crc32 cal result*/
    return ~crc;
}

/*
 * On line crc count web https://crccalc.com/
 * To verify the CRC32 value is correct or not
 */
int do_crc32(int argc, char * argv[])
{
    unsigned int crc;

    if (argc == 3) {
        uintptr_t buf_addr;
        unsigned int buf_size;

        if (!strcmp(argv[1],"selftest")) {
            unsigned char Verify_buf[] = {1};//ASCII code 0x31, hex code=1

            crc = cal_crc32(0xFFFFFFFF, Verify_buf, 1);
            if (crc != 0xA505DF1B) {
                printf("Test value %d, CRC32 value=0x%x, CRC32 self check \
                    doesn't pass, contact SW owner\n", Verify_buf[0], crc);
                return 1;
            } else {
                printf("Passed the self crc32 test 0x%X\n", crc);
            }

        Verify_buf[0] = strtoul(argv[2], NULL, 0);
        crc = cal_crc32(0xFFFFFFFF, Verify_buf, 1);
        printf("CRC32 value is 0x%X\n", crc);
        return 0;
    }

    buf_addr = strtoul(argv[1], NULL, 0);
    buf_size = strtoul(argv[2], NULL, 0);
    if (!buf_addr || !buf_size)
        return -1;

    crc = cal_crc32(0xFFFFFFFF, (unsigned char*)buf_addr, buf_size);
    printf("CRC32 value is 0x%X\n", crc);

    return 0;
    } else {
        return -EUSAGE;
    }
}
/*
 * demo code for CRC32 calculation based on file input
 */
#ifdef SHOW_CRC32_DEMO
#define CRC32_BUFSIZE     (1024*4)
int calc_img_crc_selftest(const char *in_file, unsigned int *img_crc)
{
    int fd;
    int nread;
    int ret;
    unsigned char buf[CRC32_BUFSIZE];
    unsigned int crc = 0xffffffff;
    init_crc_table();

    fd = open(in_file, O_RDONLY);
    if (fd < 0) {
        printf("%d:open failed.\n", __LINE__);
        return -1;
    }
    while ((nread = read(fd, buf, CRC32_BUFSIZE)) > 0) {
    if (0) {
            int i;
            for (i=0; i<nread; i++) {
                printf("%d, ", buf[i]);
                if ((i+1)%10 == 0)
                    printf("\n");
            }
        }
        crc = crc32(crc, buf, nread);
    }
    *img_crc = ~crc;

    close(fd);

    if (nread < 0) {
        printf("%d:read failed\n", __LINE__);
        return -1;
    }
    return 0;
}
#endif

MK_CMD(crc32, do_crc32, "Calclulate the crc32 value for given buffer",
        "crc32 <buffer ptr> <buffer size>\n"
        "   - Cal the crc32 value for given buffer\n"
        "crc32 selftest <value>\n"
        "   - Verified the pre_defined buffer 1, the crc32 value must\n"
        "       be 0xA505DF1B.\n"
        "   - Calculate the single byte value for verification\n");

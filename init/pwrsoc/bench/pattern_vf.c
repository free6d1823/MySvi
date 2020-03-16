#include <stdint.h>
#include <string.h>
#include <target/cpus.h>
#include <target/bench.h>

int pattern_sha256(void *);
int coremark_main(void *);
int dhrystone_main (void *);
int linpack_main (void *);

static pattern_vf_t vf_patterns[10];

int pattern_vf_name2id(char *p, int len)
{
    int i;

    if ( len < 0 )
        return -1;

    for ( i=0; i<sizeof(vf_patterns)/sizeof(pattern_vf_t); i++ ) {
        if ( strlen(vf_patterns[i].name) != len )
            continue;
        if ( !memcmp(vf_patterns[i].name, p, len) )
            return i;
    }

    return -1;
}

char* pattern_vf_id2name(int id)
{
    return vf_patterns[id].name;
}

ptn_entry_vf pattern_vf_get_entry(int id)
{
    return vf_patterns[id].entry;
}

int pattern_vf_get_timeout(int id)
{
    return vf_patterns[id].timeout;
}

void pattern_vf_register(char *name, ptn_entry_vf entry, uint32_t timeout)
{
    static int index = 0;

    vf_patterns[index].name = name;
    vf_patterns[index].entry = entry;
    vf_patterns[index++].timeout = timeout;
}

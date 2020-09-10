/**
*  vf bench create task list from the console input
*  example imput:   [r0-1,c17-19,d20] [sha256-10,coremark-20,linpack-]
*
*  input format: [apc arg] [pattern arg]
*
*  apc key:      c:cpu, d:duplex, r:rail, a:all
*  apc range:    0-48,0-24,0-7,
*  pattern:      name-loop
*/

#include <string.h>
#include <stdio.h>
#include <target/exception.h>
#include <target/cpus.h>
#include <target/memory.h>
#include <target/smp.h>
#include <target/bench.h>

#define INFINITE_LOOP (4096)
/*===========================================================================
                    task list definitions
===========================================================================*/
#define MAX_TASK_LIST (10)

#define BYPASS_SPACE(p) do { while (*p && *p == ' ') p++; } while (0)
#define APC_MSG_SIZE (16)

typedef enum {
    e_key = 0,
    e_left,
    e_right,
}e_parsing_apc;

typedef enum {
    e_ptn_name = 0,
    e_ptn_loop,
}e_parsing_pattern;

typedef enum _number_subfix{
    e_subfix_apc = 0,      /* " -,]" */
    e_subfix_pattern,     /* " ,]"  */
}e_number_subfix;

typedef struct _range{
    int start;
    int end;
}range;

/*===========================================================================
                    Global variables apc_ctx and task_ctx are cache_wt
===========================================================================*/
/* task list created from console input */
static apc_task_t apc_ctx[MAX_CPU_NUM];

/* task list created from console input */
static task_ctx_t task_ctx[MAX_TASK_LIST];

/*===========================================================================
                    LOCAL FUNCTION DEFINITIONS
===========================================================================*/

static uint64_t vf_mem = 0;

static task_list_t* task_alloc()
{
    return NULL;
}

static task_list_t* tasklist_append(int index, uint32_t p_id, uint32_t loop)
{
    task_list_t *t0, *t = task_alloc();

    t->task.p_id = p_id;
    t->task.loop = loop;
    t->next = (task_t*)0;

    if ( task_ctx[index].tl == 0 ){
        task_ctx[index].tl = t;
    } else {
        t0 = task_ctx[index].tl;
        while ( t0->next )
            t0 = (task_list_t*)t0->next;

        t0->next = (task_t*)t;
    }
    return t;
}

static uint64_t apcary;
static void mark_apc(char key, range *r)
{
    typedef struct _cpu_range{
        char key;
        int  count;
    }apc_range;

    apc_range ary[] = { {'a', MAX_CPU_NUM},
                        {'r', CPUS_PER_RAIL},
                        {'d', CPUS_PER_CLUSTER},
                        {'c', 1} };

    int i, start=0, end=0;

    if ( key != 'a' ) {
        for ( i=0 ; i<sizeof(ary)/sizeof(apc_range); i++) {
            if( key == ary[i].key ) {
                start = r->start * ary[i].count;
                end = (r->end+1) * ary[i].count;
                break;
            }
        }
    } else {
        start = 0;
        end = 48;
    }

    for( i=start; i<end; i++) {
        apcary = apcary |(1ULL << i);
    }
}

/**
* parse the first int
* return:
*         succeed: pointer to the first valid separator
*         failed:  (char*)0
*/
static char* parse_number(char *str, int *value, e_number_subfix subfix)
{
    char c, *p = str;
    *value = -1;

    //printf("    %s      %s", __FUNCTION__, str);
    BYPASS_SPACE(p);

    while ( (c = *p) ) {
        if ( c >= '0' && c <= '9' ) {
            if ( *value == -1 ) *value = 0;
            *value = *value * 10 + c - '0';
            p++;
        } else {
            if ( subfix == e_subfix_apc ) {
                if ( c == ' ' || c == '-' || c == ',' || c == ']' ) {
                    break;
                } else {
                    return (char*)0;
                }
            } else {
                if ( c == ' ' || c == ',' || c == ']' ) {
                    break;
                }else {
                    return (char*)0;
                }
            }
        }
    }

    return p;
}

static int check_apc_key(char c)
{
    int i;
    char keys[] = {'a','r','d','c'};

    for ( i=0; i<sizeof(keys)/sizeof(char); i++ ) {
        if( c == keys[i] )
            return 0;
    }
    return -1;
}

/**
*  parse apc keyword 'a,r,d,c'
*  return:
*         succeed: pointer to the first valid separator
*         failed:  (char*)0
*/
static char* parse_apc_key(char *str, char *key)
{
    char c, *p = str;
    //printf("    %s      %s", __FUNCTION__, str);
    BYPASS_SPACE(p);

    while ( (c = *p) ) {
        if ( !check_apc_key(c) ) {
            *key = c;
            c = *(++p);

            if ( *key == 'a' ) {
                if (  c == ' ' || c == ',' || c == ']' ) {
                    return p;
                } else {
                    return (char*)0;
                }
            } else {
                if ( c == ' ' || ( c >= '0' && c <= '9' ) ) {
                    return p;
                } else {
                    return (char *)0;
                }
            }
        } else {
            return (char *)0;
        }
    }

    return (char *)0;
}

/**
*  parse pattern name
*  return:
*         succeed: pointer to the first valid separator ' ' , ',' , '-' , ']'
*         failed:  (char*)0
*/
static char* parse_pattern_name(char *str, int *p_id)
{
    char c, *start, *p = str;

    //printf("    %s      %s", __FUNCTION__, str);
    BYPASS_SPACE(p);
    start = p;

    while ( (c = *p) ) {
        if ( c == ' ' || c == ',' || c == '-' || c == ']' ) {
            *p_id = pattern_vf_name2id(start, p-start);
            if ( *p_id < 0 )
                return (char*) 0;
            else
                return p;
        } else {
            p++;
        }
    }

    return (char*)0;
}

static int check_argv(char *argv)
{
    int len=strlen(argv);

    if(argv[0] != '[' || argv[len-1] != ']')
        return -1;

    return 0;
}

/**
*  parse apc string
*  return:
*         mark apc[] which is assigned in the string
*         failed:  (char*)0
*/
static int parse_arg_apc(char *argv)
{
    range r = {-1, -1};
    int value;

    char key, *p = argv;
    e_parsing_apc now_parsing = e_key;

    //printf("%s      %s\n", __FUNCTION__, argv);

    if( check_argv(p) ) return -1;
    p++;

    while( *p && (*p != ']') ){
        switch (now_parsing) {
            case e_key:
                p = parse_apc_key(p, &key);
                if ( !p ) return -1;
                //printf("    key=%c    %s\n", key, p);

                BYPASS_SPACE(p);
                if ( key == 'a' ) {
                    if( *p == ',' || *p == ']' ) {
                        mark_apc(key, &r);

                        if ( *p == ']' )
                            return 0;

                        p++;
                        now_parsing = e_key;
                    }else{
                        return -1;
                    }
                } else {
                    now_parsing = e_left;
                }
            break;

            case e_left:
                p = parse_number(p, &value, e_subfix_apc);
                if ( !p || (value == -1) ) return -1;

                r.start = value;
                //printf("    number=%d        %s\n", value, p);

                BYPASS_SPACE(p);

                if ( *p == '-' ) {
                    p++;
                    now_parsing = e_right;
                } else if ( *p == ',' ) {
                    r.end = r.start;
                    mark_apc(key, &r);

                    p++;
                    now_parsing = e_key;
                } else if( *p == ']' ) {
                    r.end = r.start;
                    mark_apc(key, &r);
                    return 0;
                }
            break;

            case e_right:
                p = parse_number(p, &value, e_subfix_apc);
                if ( !p || (value == -1) ) return -1;

                r.end = value;
                //printf("    number=%d    %s\n", value, p);

                BYPASS_SPACE(p);

                if ( *p == '-' ) {
                    return -1;
                } else if ( *p == ',' ) {
                    mark_apc(key, &r);

                    p++;
                    now_parsing = e_key;
                } else if( *p == ']' ) {
                    mark_apc(key, &r);
                    return 0;
                }
            break;
        }
    }

    return 0;
}

static int parse_arg_pattern(char *argv, int index)
{
    int ptn_id, loop;
    char *p = argv;

    e_parsing_pattern now_parsing = e_ptn_name;

    //printf("%s      %s\n", __FUNCTION__, argv);

    if( check_argv(p) ) return -1;
    p++;

    while( *p && *p != ']' ){
        switch (now_parsing) {
            case e_ptn_name:
                p = parse_pattern_name(p, &ptn_id);
                if ( !p ) return -1;
                //printf("    ptn_id=%d    %s\n", ptn_id, p);

                BYPASS_SPACE(p);

                if ( *p == '-' ){
                    p++;
                    now_parsing = e_ptn_loop;

                    if( *p == ']' ){
                        tasklist_append(index, ptn_id, INFINITE_LOOP);
                        return 0;
                    }
                } else if ( *p == ',' || *p == ']'){
                    loop = 1;
                    tasklist_append(index, ptn_id, loop);

                    if (*p == ']')
                        return 0;

                    p++;
                    now_parsing = e_ptn_name;
                }else{
                    return -1;
                }
            break;

            case e_ptn_loop:
                p = parse_number(p, &loop, e_subfix_pattern);
                if ( !p ) return -1;
                if ( loop == -1 )
                    loop = INFINITE_LOOP;
                //printf("    loop=%d        %s\n", loop, p);

                BYPASS_SPACE(p);

                if( *p == ','  || *p == ' ' ){
                    tasklist_append(index, ptn_id, loop);

                    p++;
                    now_parsing = e_ptn_name;
                 }else if( *p == ']' ){
                    tasklist_append(index, ptn_id, loop);

                    return 0;
                 }else{
                     return -1;
                 }
            break;
        }
    }

    return 0;
}

static void get_tasklist_duration(int64_t *min, int64_t *max)
{
    int i;
    uint64_t _min = task_ctx[0].timeout, _max;

    _max = _min;
    for ( i=1; i<MAX_TASK_LIST; i++ ) {
        if ( task_ctx[i].tl == 0)
            break;

        if ( _min > task_ctx[i].timeout )
            _min = task_ctx[i].timeout;

        if ( _max < task_ctx[i].timeout )
            _max = task_ctx[i].timeout;
    }

    *min = _min;
    *max = _max;
}

static char *expect_str[] = {
    "idle",
    "running",
    "passed",
    "failed"
};

static char* taskid_2_patternname(unsigned long cid, unsigned int taskid)
{
    int i;
    task_list_t *tl = (task_ctx + apc_ctx[cid].tasklist_id)->tl;
    for ( i=0; i<taskid; i++)
        tl = (task_list_t*)tl->next;
    return pattern_vf_id2name(tl->task.p_id);
}

/* apc_do_dump() is called by imc */
void apc_dump( unsigned long cid, int verbose )
{
    if ( verbose ) {
        printf( "C_%02d : pwr=%d  st=%s:%d:%d  %s  tlid=%p msg=%s \n",
                cid,
                apc_ctx[cid].pwr,
                expect_str[apc_ctx[cid].status],
                task_ctx[apc_ctx[cid].task_id].count,
                apc_ctx[cid].count,
                taskid_2_patternname(cid, apc_ctx[cid].task_id),
                apc_ctx[cid].tasklist_id,
                apc_ctx[cid].msg );
    } else {
         printf( "C_%02d : pwr=%d st=%s:%d:%d  %s msg=%s\n",
                cid,
                apc_ctx[cid].pwr,
                expect_str[apc_ctx[cid].status],
                task_ctx[apc_ctx[cid].task_id].count,
                apc_ctx[cid].count,
                taskid_2_patternname(cid, apc_ctx[cid].task_id),
                apc_ctx[cid].msg );
    }
}

static void report_pattern_result(e_vf_status st)
{
    int i;
    if ( st == vf_passed)
        printf( "\nReport: %s\n", "VF_passed" );
    else
        printf( "\nReport: %s\n", "VF_failed" );

    if ( st == vf_failed ) {
        for ( i=0; i<MAX_CPU_NUM; i++ ) {
            if ( apc_ctx[i].assigned == 1 ) {
                apc_dump(i, 1);
             }
        }
    }
}

void apcctx_dump()
{
    int i;
    task_list_t *tl;

    printf( "============apc context============\n" );
    for ( i=0; i<MAX_TASK_LIST; i++ ) {
        tl = task_ctx[i].tl;
        if ( tl == 0) break;

        printf( "TASKLIST[%d]:   timeout=%d   count=%d ", i, task_ctx[i].timeout, task_ctx[i].count );
        while (tl) {
            printf("[%s:%d]->", pattern_vf_id2name(tl->task.p_id), tl->task.loop);
            tl = (task_list_t *)tl->next;
        }

        printf("[NULL]\n");
    }

    for ( i=0; i<MAX_CPU_NUM; i++ ) {
        if ( apc_ctx[i].assigned == 1 ) {
            apc_dump( i, 1 );
        }
    }
    printf( "================ end ==============\n" );
}

int apc_check_pattern_vf(int argc, char * argv[])
{
    int i, verbose=0, cnt0=0, cnt1=0;

    if( argc > 1 && strcmp(argv[1], "verb") == 0){
        verbose = 1;
    }

    for ( i=0; i<MAX_CPU_NUM; i++ ){
        if ( apc_ctx[i].assigned == 1 ) {
            cnt0++;
            apc_dump(i, verbose);

            if ( apc_ctx[i].status == vf_passed ) {
                cnt1++;
            } else if ( apc_ctx[i].status == vf_failed ) {
                report_pattern_result(vf_failed);
                break;
            }
        }
    }

    if ( cnt0 == cnt1 ) {
        report_pattern_result(vf_passed);
        return 0;
    }

    return -1;
}

static void vf_ctx_init()
{
    int i;
    for ( i=0; i<MAX_TASK_LIST; i++ ) {
        task_ctx[i].tl = 0;
        task_ctx[i].timeout = 0;
        task_ctx[i].count = 0;
    }

    for ( i=0; i<MAX_CPU_NUM; i++ ) {
        apc_ctx[i].assigned = 0;
        apc_ctx[i].count = 0;
        apc_ctx[i].status = vf_idle;
        apc_ctx[i].task_id = 0;
        apc_ctx[i].tasklist_id = 0;
        memset( (void*)apc_ctx[i].msg, 0 ,APC_MSG_SIZE);
    }

    apcary = 0;
    vf_mem = 0;
}

int pattern_vf_dispatch( int cnt, char *argv[] )
{
    int i = 0;
    int j = 0;
    int ret = 0;
    task_list_t *tl;
    int64_t interval, min, max;
    uint64_t partial_good = get_cpu_mask();

    int cpus = 0, workers = 0;
    int stresscbf_cpus[MAX_CPU_NUM];
    char *p;

    vf_ctx_init();

    for ( i=0; i<cnt/2; i++ ) {
        ret = parse_arg_apc(argv[i*2]);
        if (ret) return -1;

        ret = parse_arg_pattern( argv[i*2+1], i );
        if (ret) return -1;

        tl = task_ctx[i].tl;
        while ( tl ) {
            task_ctx[i].timeout += pattern_vf_get_timeout( tl->task.p_id ) * tl->task.loop;
            task_ctx[i].count += tl->task.loop;
            tl = (task_list_t*)tl->next;
        }

        for ( j=0; j<MAX_CPU_NUM; j++ ) {
            if ( ( apcary & ( 0x1ULL<<j ) ) && ( partial_good & (0x1ULL<<j) ) ) {
                apc_ctx[j].assigned = 1;
                apc_ctx[j].task_id = 0;
                apc_ctx[j].tasklist_id = i;
            }
        }
        apcary = 0;
    }

    /* update stresscbf_cpus according apc_ctx[] */
    for(i =0; i<MAX_CPU_NUM; i++)
        stresscbf_cpus[i] = 0;

    for (i=0; i<MAX_CPU_NUM; i++) {
        if (apc_ctx[i].assigned == 0)
            continue;
        p = taskid_2_patternname (i, apc_ctx[i].task_id);
	workers++;
        if (!strcmp(p, "stresscbf")) {
            stresscbf_cpus[ cpus ] = i;
            cpus++;
        }
    }

    for (i=0; i<MAX_CPU_NUM; i++) {
        if (apc_ctx[i].assigned == 0)
            continue;
        apc_ctx[i].cpus = workers;
    }

    if ( cpus ) {
        void *p_total = (void *)( 0xFFF8000000 );
        int pages_per_cpu = ( STRESSCBF_BUFFER_SIZE >> 12)/cpus;
        uint64_t buffer_per_cpu = pages_per_cpu << 12;

        for ( i = 0; i < cpus; i++){
            int cpuid = stresscbf_cpus[i];
            apc_ctx[cpuid].para.cpuid = cpuid;
            apc_ctx[cpuid].para.p_src = (void *)( p_total + i * buffer_per_cpu );
            apc_ctx[cpuid].para.p_end = (void *)( apc_ctx[cpuid].para.p_src + (buffer_per_cpu >> 1));

            printf("cpuid %d, src=%p, end=%p\n", apc_ctx[cpuid].para.cpuid, apc_ctx[cpuid].para.p_src, apc_ctx[cpuid].para.p_end);

            if ( pages_per_cpu % 2 == 0) {
                apc_ctx[cpuid].para.p_dst = apc_ctx[cpuid].para.p_end;
            } else {
                apc_ctx[cpuid].para.p_dst = apc_ctx[cpuid].para.p_end + 4096;
            }
        }
    }

    get_tasklist_duration(&min, &max);
    min = (0x01312D00)*min;
    max = (0x01312D00)*max;
    interval = 30;

    apcctx_dump();

    for ( i=0; i<MAX_CPU_NUM; i++ ){
        if (apc_ctx[i].assigned == 1) {
            apc_ctx[i].status = vf_running;

            if (apc_ctx[i].pwr == pwr_off) {
                apc_ctx[i].pwr = pwr_on;
                falkor_configure_entry_point(CPU_POWER_ON_ENTRY_POINT);
                falkor_deassert_reset(i, false);
            }
        }
    }

#if 0
    tick0 = get_ticks();
    while ( max > 0 ) {
        duration = get_ticks() - tick0;
        if ( duration >= interval ) {
            apc_check_pattern_vf();
            tick0 = get_ticks();
            max -= duration;
        }
    }
#endif

    return 0;
}

void apc_exception_handler(const char *msg)
{
    char c;
    int len = 0;

    unsigned long cid = plat_my_core_pos();

    while ( ( c = *msg++) && ( len < APC_MSG_SIZE-1 ) ) {
        apc_ctx[cid].msg[len] = c;
        len++;
    }
}

void apc_do_pattern_vf( unsigned long cid )
{
    int i, ret;
    ptn_entry_vf entry;

    register_exception_handler( apc_exception_handler );

dispatch:

    while ( apc_ctx[cid].status != vf_running );

    task_list_t *tl = task_ctx[apc_ctx[cid].tasklist_id].tl;
    apc_ctx[cid].task_id = 0;
    apc_ctx[cid].count = 0;

    while ( tl ) {
        entry = pattern_vf_get_entry(tl->task.p_id);

        for ( i = 0; i<tl->task.loop; i++ ) {
            ret = entry( apc_ctx+cid );
            if ( ret ) {
                apc_ctx[cid].status = vf_failed;
                goto dispatch;
            } else {
                apc_ctx[cid].count++;
            }
        }

        tl = (task_list_t*)tl->next;
        if ( tl ) {
            apc_ctx[cid].task_id++;
        }
    }

    apc_ctx[cid].status = vf_passed;
    goto dispatch;
}

void bench_vf_init()
{
    int i;

    //clear apc_ctx + task_ctx
    for ( i=0; i<MAX_CPU_NUM; i++ ) {
        apc_ctx[i].assigned = 0;
        apc_ctx[i].pwr = pwr_off;
    }
}

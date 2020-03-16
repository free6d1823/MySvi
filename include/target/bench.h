#ifndef BENCH_INTERNAL_H
#define BENCH_INTERNAL_H

#include <stdint.h>
#include <stddef.h>
#include <target/cpus.h>
#include <asm/mach/cpus.h>

#define SET     1
#define RESET   0
#define ALL_CPU 0xFFFFFFFFFFFF
#define SUCCESS 0
#define ERROR   -1
#define C0   C(0)
#define C1   C(1)
#define C2   C(2)
#define C3   C(3)
#define C4   C(4)
#define C5   C(5)
#define C6   C(6)
#define C7   C(7)
#define C8   C(8)
#define C9   C(9)
#define C10  C(10)
#define C11  C(11)
#define C12  C(12)
#define C13  C(13)
#define C14  C(14)
#define C15  C(15)
#define C16  C(16)
#define C17  C(17)
#define C18  C(18)
#define C19  C(19)
#define C20  C(20)
#define C21  C(21)
#define C22  C(22)
#define C23  C(23)
#define C24  C(24)
#define C25  C(25)
#define C26  C(26)
#define C27  C(27)
#define C28  C(28)
#define C29  C(29)
#define C30  C(30)
#define C31  C(31)
#define C32  C(32)
#define C33  C(33)
#define C34  C(34)
#define C35  C(35)
#define C36  C(36)
#define C37  C(37)
#define C38  C(38)
#define C39  C(39)
#define C40  C(40)
#define C41  C(41)
#define C42  C(42)
#define C43  C(43)
#define C44  C(44)
#define C45  C(45)
#define C46  C(46)
#define C47  C(47)

typedef int (*ptn_entry_vf)(void *);
typedef int (*ptn_entry)(void);

typedef struct {
    char        *name;
    ptn_entry_vf   entry;
    uint32_t    timeout;             /* second */
}pattern_vf_t;

typedef struct pattern_case{
    char *name;
    char *dic;
    uint64_t work_cpu;
    void *ptr;

    ptn_entry cpu_mission_table[MAX_CPU_NUM];

    int flag_reset;
    int flag_power;
    int flag_assign;

    int (*creat_mission_table)(struct pattern_case *, uint64_t);

    struct pattern_case *next_pt;
    }pattern_case_t;

typedef int (*creat_table)(pattern_case_t *, uint64_t);

/*===========================================================================
                    imc and falkor sync region start
===========================================================================*/
#define GET_ASSIGN_ERROR    0


/*infinite repeat*/
#define I_REPEAT            0xFFFFFFFFFFFFFFFF


#define BUSY     1
#define NOT_BUSY 0

#define CORE_BENCH  1
#define POWER_BENCH 2
#define STRESSCBF_BUFFER_SIZE 0x1C00000

typedef struct {
    uint64_t imc_ready;
    uint64_t cpu_state[MAX_CPU_NUM];
    uint64_t cpu_ack[MAX_CPU_NUM];
    uint64_t cpu_active[MAX_CPU_NUM];
    uint64_t cpu_busy[MAX_CPU_NUM];
    uint64_t cpu_sync[MAX_CPU_NUM];
    uint64_t repeat_cnt;
    uint64_t stop_flag;
}clt_state_t;

/***************************************************************************************
 * vf bench definition
 **************************************************************************************/
typedef struct
{
    uint32_t p_id;          /* index in vf_patterns[] */
    uint32_t loop;
}task_t;

typedef struct
{
    task_t task;
    task_t *next;
}task_list_t;

typedef struct
{
    int timeout;           /* timeout of whole list */
    int count;
    task_list_t *tl;
}task_ctx_t;

typedef enum
{
    pwr_off = 0,
    pwr_on
}e_pwr_status;

typedef enum
{
    vf_idle = 0,
    vf_running,
    vf_passed,
    vf_failed,
}e_vf_status;

typedef struct _pv_struct{
    int cpuid;
    void *p_src;
    void *p_end;
    void *p_dst;
} pv_para;

typedef struct
{
    int            assigned;              /* current apc is assigned, running pattern */
    int            cpus;                  /* working cpus in current dispatch */
    e_pwr_status   pwr;
    volatile e_vf_status status;          /* running result */
    uint64_t       count;                 /* count of finished pattern */
    uint32_t       task_id;               /* index in the joblist */
    uint32_t       tasklist_id;           /* one or more lists are created according to input from console
                                             each wroking cpu run a joblist */
    char           msg[16];
    pv_para        para;
}apc_task_t;

/*API*/
int default_creat_mission_tabel(pattern_case_t *pattern, uint64_t cpu_status);

/* Simple bench */
void bench_init(void);
void apc_do_bench();
void apc_do_pattern(unsigned long cur_cpu_id );
int pattern_case_init(pattern_case_t * target_pattern);
int pattern_case_exec(pattern_case_t *pattern, uint64_t work_list);
pattern_case_t * get_pattern_case(char *target_name);
int pattern_internal_init(pattern_case_t * target_pattern,  uint64_t cpu_status);
int dispatch_pattern(char *name, uint64_t work_list, uint64_t repeat);
void dispatch(pattern_case_t *pattern);

void bench_vf_init(void);
int pattern_vf_dispatch( int cnt, char *argv[] );
void apc_do_pattern_vf( unsigned long cid );
char* pattern_vf_id2name(int id);
ptn_entry_vf pattern_vf_get_entry(int id);
int pattern_vf_name2id(char *p, int len);
int pattern_vf_get_timeout(int id);
void pattern_vf_register(char *name, ptn_entry_vf entry, uint32_t timeout);

int pattern_init(void);
void show_pattern();
/**************************************************
 * add pattern case init function declaration here
 *************************************************/
int pattern_demo_init(void);
int linpack_bench_init(void);
int sha256_init(void);
int coremark_init(void);
int dhrystone_init();
int maxpower_init(void);
int stresscbf_init(void);
int maxpower2_init(void);
int atomic_test_init();
int spinlock_test_init(void);
#endif


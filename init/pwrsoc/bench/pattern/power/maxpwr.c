#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <target/cpus.h>
#include <target/heap.h>
#include <target/bench.h>

void powervirus(int loop, void *_data, void *pb, void *pe);
void stress_cbf(void *start, void *end, void *dst, int loop);
void *memcpy(void *dest, const void *src, size_t size);
void aw_powervirus2(int loop, void *_data, void *pb, void *pe);

#ifdef CONFIG_TESTOS_EMU
#include <testos.h>
#include <target/percpu.h>
#include <target/smp.h>

DEFINE_PERCPU(uint16_t, phase);
#define maxpwr_phase  get_percpu(phase)

void notify(uint16_t msg)
{
    uint8_t cpu = smp_processor_id();
    if (cpu == 0){
        printf("set tlmm\n");
        tlmm_output_phase_flags(msg |
                                (cpu << TESTOS_GPIO_PHASE_CPU_SHIFT) |
                                (1UL << TESTOS_GPIO_PHASE_VALID_SHIFT));
    }
}

void maxpwr_indicate_phase(void)
{
	notify(maxpwr_phase++);
}
#endif

static inline unsigned int _cpu_id()
{
    uint64_t t;
    asm volatile
    (
        "mov %0, sp\n\t"
        : "=r" (t)
    );
    t = t - STACKS_START;
    return (unsigned int)(t >> 12);
}

uint32_t aw10_data[] __aligned(16) = { //41e460
    0x49249249, 0x3ff29249, 0x49249249, 0x3ff29249,
    0x92492492, 0x3ff24924, 0x92492492, 0x3ff24924,
    0x49249249, 0x3ff29249, 0x49249249, 0x3ff29249,
    0x92492492, 0x3ff24924, 0x92492492, 0x3ff24924,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
};

uint32_t aw10_mem[] __aligned(16) = {    //41e520
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
};

uint32_t aw10_stress_mem[] __aligned(16)  = {    //40a1a8
    0x55550000, 0x55550000, 0x55550000, 0x55550000,
    0x55550000, 0x55550000, 0x55550000, 0x55550000,
    0xaaaa0000, 0xaaaa0000, 0xaaaa0000, 0xaaaa0000,
    0xaaaa0000, 0xaaaa0000, 0xaaaa0000, 0xaaaa0000,
    0x0000aaaa, 0x0000aaaa, 0x0000aaaa, 0x0000aaaa,
    0x0000aaaa, 0x0000aaaa, 0x0000aaaa, 0x0000aaaa,
    0x00005555, 0x00005555, 0x00005555, 0x00005555,
    0x00005555, 0x00005555, 0x00005555, 0x00005555,
};

uint32_t aw20_data[] __aligned(16)  = {    //41e460
    0x49249249, 0x3ff29249, 0x49249249, 0x3ff29249,
    0x92492492, 0x3ff24924, 0x92492492, 0x3ff24924,
    0x49249249, 0x3ff29249, 0x49249249, 0x3ff29249,
    0x92492492, 0x3ff24924, 0x92492492, 0x3ff24924,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
    0xffffffff, 0x3fffffff, 0xffffffff, 0x3fffffff,
    0x00000000, 0x44000000, 0x00000000, 0x44000000,
};

uint32_t aw20_mem[] __aligned(16) ={     //41e420
    0xaaaaaaaa, 0x55555555, 0xaaaaaaaa, 0x55555555,
    0xaaaaaaaa, 0x55555555, 0xaaaaaaaa, 0x55555555,
    0x55555555, 0xaaaaaaaa, 0x55555555, 0xaaaaaaaa,
    0x55555555, 0xaaaaaaaa, 0x55555555, 0xaaaaaaaa,
};

void fill_data(void *start, void *end, void *data, uint32_t size)
{
    while( start < end - size ){
        memcpy( start, data, size );
        start += size;
    }
}

static int aw10_powervirus()
{
    uint64_t te;
    int i;
    int cnt = 0x800;
    int loop = sizeof(aw10_mem)/sizeof(uint32_t);
    printf("cpu id :%d run aw10_powervirus\n",_cpu_id());

    void *p = apc_my_tcmheap(); //malloc(0x3000);         // 4k aligned
    p = (void*)((uint64_t)p & 0xfffffffffffff000ULL);

    uint32_t *dst = (uint32_t*)(p + 0x1000);
    while (cnt > 0) {
        for (i = 0; i < loop; i++) {
            *dst++ = aw10_mem[i];
        }
        cnt -= loop;
    }

    /* runtime is 10s */
    te = time()+ 10;

    while(time() < te) {
        powervirus(100, aw10_data, p + 0x1000, p + 0x3000);
    }

    return 0;
}

static int aw10_stresscbf(void *ctx)
{
    if(ctx) {
        uint64_t tend;
#ifdef CONFIG_TESTOS_EMU
       /* maxpwr_phase flag is equal to 0 */
        maxpwr_indicate_phase();
#endif

        apc_task_t * c = (apc_task_t *)ctx;
        int size = c->para.p_end - c->para.p_src;

        /* fill the specific data */
        fill_data( c->para.p_src, c->para.p_end, aw10_stress_mem, 128);
        fill_data( c->para.p_dst, c->para.p_dst + size, aw10_stress_mem, 128);

#ifdef CONFIG_TESTOS_EMU
        /* maxpwr_phase flag is equal to 1 */
        maxpwr_indicate_phase();
        stress_cbf(c->para.p_src, c->para.p_end, c->para.p_dst, 100 );
        stress_cbf(c->para.p_dst, c->para.p_dst+size, c->para.p_src, 100 );
        maxpwr_indicate_phase();
#endif
       /* stresscbf run defautly 10 seconds */
        tend = time() + 10;
        while (time() < tend) {
            stress_cbf(c->para.p_src, c->para.p_end, c->para.p_dst, 100 );
            stress_cbf(c->para.p_dst, c->para.p_dst+size, c->para.p_src, 100 );
        }
    }

    return 0;
}

static int aw20_powervirus()
{
    uint64_t te;
    int i;
    int cnt = 0x10000;
    int loop = sizeof(aw20_mem)/sizeof(uint32_t);
    printf("cpu id :%d run aw20_powervirus\n",_cpu_id());

    /* need to malloc(0x50000) at least */
    void *p = apc_my_tcmheap();

    /* 64k aligned */
    p = (void*)((uint64_t)p & 0xffffffffffff0000ULL);

    uint32_t *dst = (uint32_t*)(p + 0x10000);
    while (cnt > 0) {
        for (i = 0; i < loop; i++) {
            *dst++ = aw20_mem[i];
        }
        cnt -= loop;
    }

    te = time() + 10;
    while(time() < te){
        aw_powervirus2(100, aw20_data, p + 0x10000, p + 0x50000);
    }

    return 0;
}

int maxpower_main()
{
    aw10_powervirus();
    return 0;
}

int stresscbf_main(void *ctx)
{
    aw10_stresscbf(ctx);
    return 0;
}

int maxpower2_main()
{
    aw20_powervirus();
    return 0;
}

static pattern_case_t maxpower = {
     .name = "maxpower",
     .dic = "maxpower",
     .ptr = (void*)maxpower_main,
     .work_cpu = (C3),
     .flag_assign = SET,
     .flag_reset = RESET,
     .flag_power = SET,
     .creat_mission_table = default_creat_mission_tabel,
 };

int maxpower_init()
{
    pattern_vf_register("stresscore", maxpower_main, 2);
    return pattern_case_init(&maxpower);
}

static pattern_case_t stresscbf = {
     .name = "stresscbf",
     .dic = "stresscbf",
     .ptr = (void*)stresscbf_main,
     .work_cpu = (C3),
     .flag_assign = SET,
     .flag_reset = RESET,
     .flag_power = SET,
     .creat_mission_table = default_creat_mission_tabel,
};

int stresscbf_init()
{
    pattern_vf_register("stresscbf", stresscbf_main, 2);
    return pattern_case_init(&stresscbf);
}

static pattern_case_t maxpower2 = {
     .name = "maxpower2",
     .dic = "maxpower2",
     .ptr = (void*)maxpower2_main,
     .work_cpu = (C3),
     .flag_assign = SET,
     .flag_reset = RESET,
     .flag_power = SET,
     .creat_mission_table = default_creat_mission_tabel,
 };

int maxpower2_init()
{
    pattern_vf_register("virus", maxpower2_main, 2);
    return pattern_case_init(&maxpower2);
}

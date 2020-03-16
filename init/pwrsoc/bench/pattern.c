#include <string.h>
#include <stdio.h>
#include <target/cpus.h>
#include <target/bench.h>

pattern_case_t *g_pattern_head = NULL;

int pattern_case_register(pattern_case_t *target_pattern)
{
    pattern_case_t *tmp_pattern = NULL;

    if(NULL == target_pattern)
        return ERROR;

    if (!g_pattern_head){
        g_pattern_head = target_pattern;
        target_pattern->next_pt = NULL;
    } else{
        tmp_pattern = g_pattern_head;
        while(tmp_pattern->next_pt)
        {
            tmp_pattern = tmp_pattern->next_pt;
        }
        tmp_pattern->next_pt = target_pattern;
        target_pattern->next_pt = NULL;
    }
    return SUCCESS;
}


/*Get the pattern from link by name*/
pattern_case_t * get_pattern_case(char *target_name)
{
    pattern_case_t * tmp_pattern = g_pattern_head;

    while(tmp_pattern)
    {
        if(strcmp(tmp_pattern->name, target_name) == 0){
            return tmp_pattern;
        }
        tmp_pattern = tmp_pattern->next_pt;
    }
    printf("find not pattern \n");
    return NULL;
}


void show_pattern()
{
    int num = 0;
    pattern_case_t *tmp_pattern = g_pattern_head;

    printf("============================================================================= \n");
    printf("                           Pattern  List                                  \n");
    printf("============================================================================= \n");

    while(tmp_pattern)
    {
        printf("| %02d | %s  -------  %s \n", num ++, tmp_pattern->name, tmp_pattern->dic);
        tmp_pattern = tmp_pattern->next_pt;
    }
    if(num == 0){
        printf("There is no pattern case yet. \n");
    }

    printf("----------------------------------------------------------------------------- \n");
}



/*Call the pattern's creat_mission_table function to creat the final mission_table.*/
int pattern_internal_init(pattern_case_t * target_pattern,  uint64_t cpu_status)
{
    int re = SUCCESS;

    re = target_pattern->creat_mission_table(target_pattern, cpu_status);

    return re;
}



/*Pattern case init and register the pattern*/
int pattern_case_init(pattern_case_t * target_pattern)
{
    uint64_t cpu_status = get_cpu_mask();

    if(NULL == target_pattern)
        return ERROR;


    /*If the pattern doesn't support the cpu assign, call the internal init here to creat the mission.
      Because these patterns's mission_table may not change when dispath.*/
    if(!(target_pattern->flag_assign)){
        if(pattern_internal_init(target_pattern, cpu_status))
            return ERROR;
    }
    /*Register the pattern to the list*/
    if(pattern_case_register(target_pattern))
        return ERROR;

    return SUCCESS;
}


int pattern_init()
{
   /* ********************************
     Add x_pattern init here as flow
    **********************************
    */
    int pattern_count = 0;

#ifdef CONFIG_PWRSOC_POWERVIRUS
    if(maxpower_init())
        return ERROR;

    if(stresscbf_init())
        return ERROR;

    if(maxpower2_init())
        return ERROR;

    pattern_count++;
#endif
#ifdef CONFIG_SPINLOCK_TEST
    spinlock_test_init();
    pattern_count++;
#endif

#ifdef CONFIG_PWRSOC_ATOMICTEST
    if(atomic_test_init())
        return ERROR;
    pattern_count++;
#endif

    if (0 == pattern_count){
        printf("There is no pattern init \n");
        printf("You need to choose one to init \n");
        return ERROR;
    } else {
        printf("There are %d Pattern init success \n", pattern_count);
        return SUCCESS;
    }
}



int default_creat_mission_tabel(pattern_case_t *pattern, uint64_t cpu_status)
{
    int i = 0;

    ptn_entry *mission_table = NULL;
    ptn_entry mission_fun = NULL;
    uint64_t work_cpu = 0;

    if((NULL == pattern) || (NULL == pattern->ptr))
        return ERROR;

    mission_table = pattern->cpu_mission_table;
    mission_fun = (ptn_entry)(pattern->ptr);
    work_cpu = pattern->work_cpu;

    /*All cpu will run the test ,if work_cpu is 0. Otherwise it the target cpu will run follow the instructions of work_cpu mask*/
    if(0 == work_cpu){
        work_cpu = ALL_CPU;
        for(i = 0; i < MAX_CPU_NUM; i++){
            if(((uint64_t)1<<i) & cpu_status)
                mission_table[i] = mission_fun;
        }
    } else {
        /*Creat the mission_table flow the pattern's work_cpu*/
        for(i = 0; i < MAX_CPU_NUM; i++){
            if( (((uint64_t)1 << i) & (work_cpu)) && (((uint64_t)1 << i) & cpu_status))
                mission_table[i] = mission_fun;
            else
                mission_table[i] = NULL;
        }
    }
     return SUCCESS;
}



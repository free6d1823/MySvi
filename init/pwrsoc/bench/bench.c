#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <target/exception.h>
#include <target/cpus.h>
#include <target/cmdline.h>
#include <target/smp.h>
#include <target/bench.h>

/*===========================================================================
            following data are in the non-cache region
===========================================================================*/

static int vf_flag;
static clt_state_t clt_state;
ptn_entry cpu_do[MAX_CPU_NUM];

/*===========================================================================
                            end
===========================================================================*/

void bench_init()
{
}


static void wait_until_set(uint64_t *flag)
{
    while(!(*flag));
}

static void wait_until_rset(uint64_t *flag)
{
    while(*flag);
}


static void cpu_scync(unsigned long cur_cpu_id )
{
    clt_state_t *state = &clt_state;
    int id = 0;
    uint64_t sync = state->cpu_sync[cur_cpu_id];  //get current cpu's sync count

    for(id = 0; id < MAX_CPU_NUM; id++) {
       if(state->cpu_active[id] == 1) {
            /*compare current cpu's sync with all other active cpus',continue running untill they are equal.*/
            while(sync != state->cpu_sync[id]);
       }
    }
}

void apc_do_pattern(unsigned long cur_cpu_id )
{
    unsigned long cpu_id = cur_cpu_id;
    clt_state_t *apc_clt_state = &clt_state;
    uint64_t repeat = 0;

    apc_clt_state->cpu_busy[cpu_id] = NOT_BUSY;

    while(1)
    {
        /*wait for imc_ready flag*/
        while(!(apc_clt_state->imc_ready));   //wait_until_set(&(apc_clt_state->imc_ready));

        apc_clt_state->cpu_sync[cpu_id] = RESET;

        repeat = apc_clt_state->repeat_cnt;
        if(0 == repeat)
            repeat = 1;

        apc_clt_state->cpu_busy[cpu_id] = SET;

        apc_clt_state->cpu_ack[cpu_id] = SET;

        /* wait for imc reset cpu's ack */
        while(apc_clt_state->cpu_ack[cpu_id]);

        if((repeat == I_REPEAT))
        {
            while(!(apc_clt_state->stop_flag))
            {
                (apc_clt_state->cpu_sync[cpu_id])++;
                /*wait for mult cpu sync */
                cpu_scync(cpu_id);

                 if(NULL != cpu_do[cpu_id])
                    cpu_do[cpu_id]();
            }
        } else{
             while((repeat) && (!apc_clt_state->stop_flag))
            {
                repeat --;
                (apc_clt_state->cpu_sync[cpu_id])++;
                /*wait for mult cpu sync */
                cpu_scync(cpu_id);
                if(NULL != cpu_do[cpu_id])
                    cpu_do[cpu_id]();
                cpu_scync(cpu_id);
            }
        }

        apc_clt_state->cpu_busy[cpu_id] = NOT_BUSY;
    }
}

void apc_do_bench()
{
    unsigned long cpu_id = plat_my_core_pos();
    register_exception_handler(0);

    if( vf_flag == 1 ) {
        apc_do_pattern_vf(cpu_id);
    }

    clt_state_t *state = &clt_state;

    apc_do_pattern(cpu_id);
}

extern void busywait(uint32_t pause_time_us);

void dispatch(pattern_case_t *pattern)
{
    int id = 0;
    clt_state_t *imc_clt_state = &clt_state;
    imc_clt_state->stop_flag = SET;

    for(id = 0; id < MAX_CPU_NUM; id++){
        if(imc_clt_state->cpu_active[id] == SET)
            /*wait all active cpu until not busy  0 */
            while(imc_clt_state->cpu_busy[id] == BUSY);
    }

    imc_clt_state->stop_flag = RESET;
    /*Clear the cpu_do function pointer,prepare for next dispath*/
    memset((void*)cpu_do, 0x01, MAX_CPU_NUM * sizeof(ptn_entry));

    /*Update the apc fun point base on the pattern.*/
    memcpy((void*)cpu_do, pattern->cpu_mission_table, MAX_CPU_NUM * sizeof(ptn_entry));

    if((SET == pattern->flag_power) || (SET == pattern->flag_reset)) {

        if(SET == pattern->flag_reset) {
            /*IMC_CLOSE_ALL_CPU*/
            for(id = 0; id < MAX_CPU_NUM; id ++) {
                imc_clt_state->cpu_busy[id] = RESET;
                falkor_power_off_core(id);
            }
            memset( imc_clt_state->cpu_active, RESET, sizeof(imc_clt_state->cpu_active));
            // TODO :WAIT INTO C5   read register

            for(id = 0; id < MAX_CPU_NUM; id++) {
                if(pattern->cpu_mission_table[id]) {
                    imc_clt_state->cpu_active[id] = SET;
                    /* power on the target core*/
                    falkor_configure_entry_point(CPU_POWER_ON_ENTRY_POINT);
                    falkor_deassert_reset(id, false);
                }
            }
        } else {
            /*Power off the no-working cpu */
            for(id = 0; id < MAX_CPU_NUM; id++) {
                if(NULL == pattern->cpu_mission_table[id]) {
                    if(imc_clt_state->cpu_active[id] == SET) {
                        imc_clt_state->cpu_active[id] = RESET;
                        imc_clt_state->cpu_busy[id] = RESET;
                        /*Power off the no work cpu*/
                        falkor_power_off_core(id);
                    }
                }
            }
        }
    }

    for(id = 0; id < MAX_CPU_NUM; id++) {
        if((pattern->cpu_mission_table[id]) && (RESET == imc_clt_state->cpu_active[id])) {
            //Power  on the target core;
            imc_clt_state->cpu_active[id] = SET;
            falkor_configure_entry_point(CPU_POWER_ON_ENTRY_POINT);
            falkor_deassert_reset(id, false);
        }
    }

    imc_clt_state->imc_ready = SET;

    /*wait for active apc's ack */
    for(id = 0; id < MAX_CPU_NUM; id++) {
        if(imc_clt_state->cpu_active[id]) {
            while(!imc_clt_state->cpu_ack[id]);
        }
    }

    imc_clt_state->imc_ready = RESET;

    /*clear the cpu_ack as the imc feedback, then when apc read its own ack become to 0 ,it may run */
    memset(imc_clt_state->cpu_ack, 0 ,sizeof(imc_clt_state->cpu_ack));
}


/*===========================================================================
**  Function :  dispatch_pattern
** ==========================================================================
* parm:
*   name:       the name of the pattern that you want to run.
*   work_list:  the cpu you want to assign.
*   repeat:     the repeat times you want, when it's 0 ,use the default time 1.
                I_REPEAT means  infinite repeat.
*/
int dispatch_pattern(char *name, uint64_t work_list, uint64_t repeat)
{
    int id = 0;
    pattern_case_t *pattern = NULL;
    clt_state_t *state = &clt_state;
    uint64_t cpu_status = get_cpu_mask();

    pattern = get_pattern_case(name);
    if(!pattern)
        return ERROR;
    if((!pattern->flag_assign) && (work_list)) {
        printf("--ERROR: The pattern dosen't support the cpu assign.Please try again \n");
        return ERROR;
     }
    if(pattern->flag_assign) {
        if(work_list)
            pattern->work_cpu = work_list;
        if(pattern_internal_init(pattern, cpu_status))
            return ERROR;
    }
    /*default repeat count is 1*/
    if(0 == repeat)
        state->repeat_cnt = 1;
    else
        state->repeat_cnt = repeat;

    dispatch(pattern);

    return SUCCESS;
}

int pattern_case_exec(pattern_case_t *pattern, uint64_t work_list)
{
    int id = 0;
    clt_state_t *state = &clt_state;
    uint64_t cpu_status = get_cpu_mask();

    if (!pattern)
        return ERROR;

    if((!pattern->flag_assign) && (work_list)) {
        printf("--ERROR: The pattern dosen't support the cpu assign.Please try again \n");
        return ERROR;
     }
    if(pattern->flag_assign) {
        if(work_list)
            pattern->work_cpu = work_list;
        if(pattern_internal_init(pattern, cpu_status))
            return ERROR;
    }
    /*default repeat count is 1*/
    state->repeat_cnt = 1;

    dispatch(pattern);

    return SUCCESS;
}

uint64_t cluster2mask(int x)
{
    return ((uint64_t)1 << (x << 1)) | ((uint64_t)1 << ((x << 1) + 1));
}

uint64_t rail2mask(int x)
{
    uint64_t num = 0;
    uint64_t i = 0;
    uint64_t work_cpu = 0;
    num = x * 6;

    for(i = 0; i < 6; i++) {
        work_cpu |= ((uint64_t)1 << (num + i));   //fix
    }
    return work_cpu;
}

uint64_t decode_assign_cmd(char * assign_str, int num)
{
    uint64_t work_cpu = 0;
    int x = 0;
    /* Num */
    if(('0' <= assign_str[0]) && ('9' >= assign_str[0])) {
        /*Guarantee two digit legality*/
        if(num == 2){
            if(('0' > assign_str[1]) || ('9' < assign_str[1]))
               return GET_ASSIGN_ERROR;
        }
        work_cpu |= ((uint64_t)1 << strtoul(assign_str, 0, 0));
        return work_cpu;
    } else if(assign_str[0] == 'c') {
        if(('0' <= assign_str[1]) && ('9' >= assign_str[1])) {
            x = strtoul((assign_str + 1 ), 0, 0);

            if( x < MAX_CPU_CLUSTERS)
                 return cluster2mask(x);
            else{
                printf("--ERROR: Over the max num of the cluster\n");
                return GET_ASSIGN_ERROR;
            }
        }
    } else if(assign_str[0] == 'r') {
        if(('0' <= assign_str[1]) && ('9' >= assign_str[1])) {
            x = strtoul((assign_str + 1 ), 0, 0);;
            if( x < MAX_CPU_RAILS)
                return rail2mask(x);
            else{
                printf("--ERROR: Over the max num of the rail\n");
                return GET_ASSIGN_ERROR;
            }
        }
    }
    return GET_ASSIGN_ERROR;
}

/*decdoe the work_cpu cmd str to find the assign cpu*/
/*param：
 *sub_str ：store the sub_cmd.i.g:|C20| "c20" is sub_cmd   */
uint64_t get_work_lisk(char *cmd_str)
{
    int i = 0;
    int j = 0;
    uint64_t work_cpu = 0;
    uint64_t temp_data = 0;
    char sub_str[3] = {0};
   /*start from 1 is because the item 0 is the "[" */
    for(i = 1; (cmd_str[i] != ']'); i++) {
        if(cmd_str[i] != '|') {
            sub_str[j] = cmd_str[i];
            j ++;
            if( j > 3)
                /*when go here means taht the cpu num is over the array scope, The max length of sub_cmd is 3 */
                return GET_ASSIGN_ERROR;
                /*the cmd_str : N / CX /RX */
            if((cmd_str[i + 1] == '|' ) || (cmd_str[i + 1] == ']' )) {
                temp_data = decode_assign_cmd(sub_str, (j-1));
                memset(sub_str, 0, sizeof(sub_str));
                if(temp_data == GET_ASSIGN_ERROR)
                    return GET_ASSIGN_ERROR;
                work_cpu |= temp_data;
                j = 0;
            }
        }
    }
    if(i == 1){
        printf("--ERROR: There is empty in the [] \n");
        return GET_ASSIGN_ERROR;
    }

    return work_cpu;
}



int do_core_bench(int argc, char * argv[])
{
    int id = 0;
    char *cmd = NULL;
    char *name = NULL;
    char *temp_str = NULL;
    pattern_case_t *pattern = NULL;
    uint64_t work_cpu = 0;
    uint64_t repeat = 0;
    clt_state_t *state = &clt_state;

    if((argc < 2) || (argc > 6)){
        printf("--ERROR: The parameters not compatible \n");
        return ERROR;
    }
    /*get the cmd*/
    cmd = argv[1];

    vf_flag = 0;
    if(strcmp(cmd, "vf") == 0){
        vf_flag = 1;
        pattern_vf_dispatch(argc-2, argv+2);
        return SUCCESS;
    }

    /*cbench show: show the registered pattern cases */
    if(strcmp(cmd, "show") == 0){
        show_pattern();
        return SUCCESS;
    }
    /*cbench stop: stop the last runninng pattern case */
    if(strcmp(cmd, "stop") == 0){
        state->stop_flag = SET;
        /*wait until all cpu exit busy state*/
        for(id = 0; id < MAX_CPU_NUM; id ++){
            wait_until_rset(&(state->cpu_busy[id]));
        }
        return SUCCESS;
    }

    /*cbench run test [1|1-3|34] -r N */
    if((strcmp(cmd, "run") == 0) && (argc >= 3)) {
        name = argv[2];
        pattern = get_pattern_case(name);
        if(NULL == pattern){
            printf("--ERROR: There is no pattern case named %s in pattern list \n",name);
            return ERROR;
        }

        /*find the cpu assign cmd form the cmd line */
        for(id = 3; id < argc; id ++){
            /*scan from the 4th parm to the last parm, find if there is a "[" exist */
            if(argv[id][0] == '['){
                temp_str = argv[id];
                /*find the "[...]" decode the cmd to creat the work_list*/
                work_cpu = get_work_lisk(temp_str);
                if(work_cpu == GET_ASSIGN_ERROR){
                    printf("--ERROR:The cpu's number inputed is invalid. \n");
                    return ERROR;
                }
            }
            /*find -r flag*/
            if(argv[id][0] == '-'){
                if((id + 1 > argc -1) ) {
                    printf("--ERROR: Please input the repeat num or I_REPEAT after the -r.\n");
                    return ERROR;
                }

                if(argv[id + 1][0] == '[') {
                    printf("--ERROR: Please input the repeat num or I_REPEAT after the -r.\n");
                    return ERROR;
                }

                temp_str = argv[id + 1];
                if(('0' <= temp_str[0]) && (temp_str[0] < '9'))
                    repeat = strtoul(temp_str, 0, 0);
                else if (strcmp(temp_str, "I_REPEAT") == 0) {
                    repeat = I_REPEAT;
                } else{
                     printf("--ERROR: Please input the correct repeat num or I_REPEAT after the -r.\n");
                     return ERROR;
                }
            }
        }

        dispatch_pattern(name, work_cpu, repeat);

    } else {
        /*cbench run cmd need at least */
        printf("--ERROR: The parameters not compatible \n");
        return ERROR;
    }
    return SUCCESS;
}

MK_CMD(cbench, do_core_bench, "print command description/usage",
    "cbench show\n"
    "    - show the registered pattern cases\n"
    "cbench run name [n|cx|rx] -r repeattimes\n"
    "    - run the pattern case\n"
    "    - [n|cx|rx] use for select the work cpu core \n"
    "    - -r times   control the pattern repeat running times \n"

);

MK_CMD(vfcheck, apc_check_pattern_vf, "dump apc status",
    " vfcheck \n"
);

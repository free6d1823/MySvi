/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/gpio.h>

void tlmm_config_port(uint32_t gpio, uint32_t cfg)
{
	if (gpio >= TLMM_NR_GPIOS)
		return;

	tlmm_write_config(gpio, TLMM_GPIO_CFG(cfg));

	/* If an output value was specified. */
	if (HAL_RMT_VAL(cfg) == HAL_TLMM_OUTPUT_LOW) {
		HWIO_OUTMI(TLMM_GPIO_IN_OUTn, gpio, \
			   HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, \
			   ~(1UL << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT));
	} else if (HAL_RMT_VAL(cfg) == HAL_TLMM_OUTPUT_HIGH) {
		HWIO_OUTMI(TLMM_GPIO_IN_OUTn, gpio, \
			   HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, \
			   (1UL << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT));
	}
}

void tlmm_output_phase_flags(uint32_t flags)
{
	tlmm_write_phase_flags(flags);
}

#define GPIO_PHASE_FLAGS_CFG(port, bit)				\
	GPIO_ENCODE_CONFIG(GPIO##port##_FUNC_PHASEFLAGS_##bit,	\
			   GPIO_DIR_OUTPUT, GPIO_PULL_DOWN,	\
			   GPIO_DRIVE_MA(2))

void tlmm_config_phase_flags(void)
{
	gpio_config_port(65, GPIO_PHASE_FLAGS_CFG(65, 0));
	gpio_config_port(66, GPIO_PHASE_FLAGS_CFG(66, 1));
	gpio_config_port(67, GPIO_PHASE_FLAGS_CFG(67, 2));
	gpio_config_port(68, GPIO_PHASE_FLAGS_CFG(68, 3));
	gpio_config_port(69, GPIO_PHASE_FLAGS_CFG(69, 4));
	gpio_config_port(70, GPIO_PHASE_FLAGS_CFG(70, 5));
	gpio_config_port(71, GPIO_PHASE_FLAGS_CFG(71, 6));
	gpio_config_port(72, GPIO_PHASE_FLAGS_CFG(72, 7));
	gpio_config_port(73, GPIO_PHASE_FLAGS_CFG(73, 8));
	gpio_config_port(74, GPIO_PHASE_FLAGS_CFG(74, 9));
	gpio_config_port(75, GPIO_PHASE_FLAGS_CFG(75, 10));
	gpio_config_port(76, GPIO_PHASE_FLAGS_CFG(76, 11));
	gpio_config_port(77, GPIO_PHASE_FLAGS_CFG(77, 12));
	gpio_config_port(78, GPIO_PHASE_FLAGS_CFG(78, 13));
	gpio_config_port(80, GPIO_PHASE_FLAGS_CFG(80, 14));
	gpio_config_port(81, GPIO_PHASE_FLAGS_CFG(81, 15));
	gpio_config_port(82, GPIO_PHASE_FLAGS_CFG(82, 16));
	gpio_config_port(83, GPIO_PHASE_FLAGS_CFG(83, 17));
	gpio_config_port(84, GPIO_PHASE_FLAGS_CFG(84, 18));
	gpio_config_port(85, GPIO_PHASE_FLAGS_CFG(85, 19));
	gpio_config_port(86, GPIO_PHASE_FLAGS_CFG(86, 20));
	gpio_config_port(87, GPIO_PHASE_FLAGS_CFG(87, 21));
	gpio_config_port(91, GPIO_PHASE_FLAGS_CFG(91, 22));
	gpio_config_port(92, GPIO_PHASE_FLAGS_CFG(92, 23));
	gpio_config_port(93, GPIO_PHASE_FLAGS_CFG(93, 24));
	gpio_config_port(94, GPIO_PHASE_FLAGS_CFG(94, 25));
	gpio_config_port(95, GPIO_PHASE_FLAGS_CFG(95, 26));
	gpio_config_port(96, GPIO_PHASE_FLAGS_CFG(96, 27));
	gpio_config_port(97, GPIO_PHASE_FLAGS_CFG(97, 28));
	gpio_config_port(98, GPIO_PHASE_FLAGS_CFG(98, 29));
	gpio_config_port(99, GPIO_PHASE_FLAGS_CFG(99, 30));
	gpio_config_port(100, GPIO_PHASE_FLAGS_CFG(100, 31));
}

uint32_t tlmmTriggerHighDirectConfig(uint32_t gpio, uint32_t proc, uint32_t direct_num)
{

	if (direct_num >= 16) {
		printf("Error tlmmTriggerHighDirectConfig 0\r\n");
		return 1;
	}

	if (proc == GPIO_PROC_IMC) {
		/*set gpio direct intr sel*/
		tlmm_intr_dir_sel_imc_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_imc_config(direct_num, 1);
	} else if (proc == GPIO_PROC_HMSS) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_hmss_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_hmss_config(direct_num, 1);
	} else {
		printf("Error tlmmTriggerHighDirectConfig 1\r\n");
		return 1;
	}

	return 0;
}

uint32_t tlmmTriggerLowDirectConfig(uint32_t gpio, uint32_t proc, uint32_t direct_num)
{

	if (direct_num >= 16) {
		printf("Error tlmmTriggerLowDirectConfig 0\r\n");
		return 1;
	}

	if (proc == GPIO_PROC_IMC) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_imc_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_imc_config(direct_num, 0);
	} else if (proc == GPIO_PROC_HMSS) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_hmss_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_hmss_config(direct_num, 0);
	} else {
		printf("Error tlmmTriggerLowDirectConfig 1\r\n");
		return 1;
	}

	return 0;
}

uint32_t tlmmTriggerRisingDirectConfig(uint32_t gpio, uint32_t proc, uint32_t direct_num)
{
	if (direct_num >= 16) {
		printf("Error tlmmTriggerRisingDirectConfig 0\r\n");
		return 1;
	}

	if (proc == GPIO_PROC_IMC) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_imc_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_imc_config(direct_num, 1);
	} else if (proc == GPIO_PROC_HMSS) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_hmss_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_hmss_config(direct_num, 1);
	} else {
		printf("Error tlmmTriggerRisingDirectConfig 1\r\n");
		return 1;
	}

	return 0;
}

uint32_t tlmmTriggerFallingDirectConfig(uint32_t gpio, uint32_t proc, uint32_t direct_num)
{

	if (direct_num >= 16) {
		printf("Error tlmmTriggerFallingDirectConfig 0\r\n");
		return 1;
	}

	if (proc == GPIO_PROC_IMC) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_imc_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_imc_config(direct_num, 0);
	} else if (proc == GPIO_PROC_HMSS) {
		/*set gpio direct intr*/
		tlmm_intr_dir_sel_hmss_config(direct_num, gpio);

		/*set gpio direct conn enable*/
		HWIO_OUTI(TLMM_GPIO_INTR_CFGn, gpio, 0x100);

		/*set gpio direct intr polarity*/
		tlmm_intr_dir_pol_hmss_config(direct_num, 0);
	} else {
		printf("Error tlmmTriggerFallingDirectConfig 1\r\n");
		return 1;
	}

	return 0;
}

uint32_t tlmmTriggerHighSummaryConfig(uint32_t gpio, uint32_t proc)
{

	if (proc >= 3) {
		printf("Error tlmmTriggerHighSummaryConfig\r\n");
		return 1;
	}

	/* set gpio intr cpu target*/
	tlmm_intr_proc(gpio, proc);

	/* enable gpio raw intr*/
	tlmm_intr_enable_raw(gpio);

	/* set gpio intr level dect*/
	tlmm_intr_dect_config(gpio, 0);

	/* set gpio intr polarity*/
	tlmm_intr_pol_config(gpio, 1);

	/* clear gpio intr*/
	tlmm_intr_clear(gpio);

	/* enable gpio intr*/
	tlmm_intr_enable(gpio);

	return 0;
}

uint32_t tlmmTriggerLowSummaryConfig(uint32_t gpio, uint32_t proc)
{

	if (proc >= 3) {
		printf("Error tlmmTriggerLowSummaryConfig\r\n");
		return 1;
	}

	/* set gpio intr cpu target*/
	tlmm_intr_proc(gpio, proc);

	/* enable gpio raw intr*/
	tlmm_intr_enable_raw(gpio);

	/* set gpio intr level dect*/
	tlmm_intr_dect_config(gpio, 0);

	/* set gpio intr polarity*/
	tlmm_intr_pol_config(gpio, 0);

	/* clear gpio intr*/
	tlmm_intr_clear(gpio);

	/* enable gpio intr*/
	tlmm_intr_enable(gpio);

	return 0;
}

uint32_t tlmmTriggerRisingSummaryConfig(uint32_t gpio, uint32_t proc)
{

	if (proc >= 3) {
		printf("Error tlmmTriggerRisingSummaryConfig\r\n");
		return 1;
	}

	/* set gpio intr cpu target*/
	tlmm_intr_proc(gpio, proc);

	/* enable gpio raw intr*/
	tlmm_intr_enable_raw(gpio);

	/* set gpio intr level dect*/
	tlmm_intr_dect_config(gpio, 1);

	/* set gpio intr polarity*/
	tlmm_intr_pol_config(gpio, 1);

	/* clear gpio intr*/
	tlmm_intr_clear(gpio);

	/* enable gpio intr*/
	tlmm_intr_enable(gpio);

	return 0;
}

uint32_t tlmmTriggerFallingSummaryConfig(uint32_t gpio, uint32_t proc)
{

	if (proc >= 3) {
		printf("Error tlmmTriggerFallingSummaryConfig\r\n");
		return 1;
	}

	/* set gpio intr cpu target*/
	tlmm_intr_proc(gpio, proc);

	/* enable gpio raw intr*/
	tlmm_intr_enable_raw(gpio);

	/* set gpio intr level dect*/
	tlmm_intr_dect_config(gpio, 2);

	/* set gpio intr polarity*/
	tlmm_intr_pol_config(gpio, 1);

	/* clear gpio intr*/
	tlmm_intr_clear(gpio);

	/* enable gpio intr*/
	tlmm_intr_enable(gpio);

	return 0;
}

uint32_t tlmmTriggerDualEdgeSummaryConfig(uint32_t gpio, uint32_t proc)
{

	if (proc >= 3) {
		printf("Error tlmmTriggerDualEdgeSummaryConfig\r\n");
		return 1;
	}

	/* set gpio intr cpu target*/
	tlmm_intr_proc(gpio, proc);

	/* enable gpio raw intr*/
	tlmm_intr_enable_raw(gpio);

	/* set gpio intr level dect*/
	tlmm_intr_dect_config(gpio, 3);

	/* set gpio intr polarity*/
	tlmm_intr_pol_config(gpio, 1);

	/* clear gpio intr*/
	tlmm_intr_clear(gpio);

	/* enable gpio intr*/
	tlmm_intr_enable(gpio);

	return 0;
}


uint32_t tlmmSetPullConfig(uint32_t gpio, uint32_t config)
{

	/* set gpio pull*/
	tlmm_config_pull(gpio, config);

	return 0;
}


uint32_t tlmmSetDriveStrengthConfig(uint32_t gpio, uint32_t config)
{

	/* set gpio drive strength*/
	tlmm_config_drive(gpio, config);

	return 0;
}


uint32_t tlmmSetFunctionConfig(uint32_t gpio, uint32_t config)
{

	/* set gpio function*/
	tlmm_config_func(gpio, config);

	return 0;
}

uint32_t tlmmSetDirectionConfig(uint32_t gpio, uint32_t config)
{

	/* set gpio direction*/
	tlmm_config_dir(gpio, config);

	return 0;
}


static int do_gpio(int argc, char * argv[])
{
    int pin_num;
	int proc;
	int direct_num;
	int config;

	if (argc < 3) {
		return -1;
	}

    pin_num = strtoul(argv[2], 0, 0);
    if ('c' == argv[1][0]) {
        if (argc < 4) {
            return -1;
        }
        if ('i' == argv[3][0]) {
            gpio_config_port(pin_num, GPIO_ENCODE_CONFIG(0, GPIO_DIR_INPUT,        \
                           GPIO_KEEPER,      \
                           GPIO_DRIVE_MA(2)));
        }else if ('o' == argv[3][0]){
            gpio_config_port(pin_num, GPIO_ENCODE_CONFIG(0, GPIO_DIR_OUTPUT,        \
                           GPIO_PULL_DOWN,      \
                           GPIO_DRIVE_MA(2)));
        }else {
            return -1;
        }
    } else if ('r' == argv[1][0]) {
        printf("gpio%d = 0x%x\n", pin_num, gpio_read_input(pin_num));
    } else if ('w' == argv[1][0]){
        if (argc < 4) {
            return -1;
        }
        int v = strtoul(argv[3], 0, 0);
        gpio_write_output(pin_num, v);
        printf("set gpio%d = 0x%x\n", pin_num, v);
	} else if (strcmp(argv[1], "summary") == 0) {
		if (argc < 5) {
			return -1;
		}
		proc = strtoul(argv[4], 0, 0);
		if (strcmp(argv[3], "high") == 0) {
			tlmmTriggerHighSummaryConfig(pin_num, proc);
		} else if (strcmp(argv[3], "low") == 0) {
			tlmmTriggerLowSummaryConfig(pin_num, proc);
		} else if (strcmp(argv[3], "rising") == 0) {
			tlmmTriggerRisingSummaryConfig(pin_num, proc);
		} else if (strcmp(argv[3], "falling") == 0) {
			tlmmTriggerFallingSummaryConfig(pin_num, proc);
		} else if (strcmp(argv[3], "edge") == 0) {
			tlmmTriggerDualEdgeSummaryConfig(pin_num, proc);
		} else {
			return -1;
		}
	} else if (strcmp(argv[1], "direct") == 0) {
		if (argc < 6) {
			return -1;
		}
		proc = strtoul(argv[4], 0, 0);
		direct_num = strtoul(argv[5], 0, 0);
		if (strcmp(argv[3], "high") == 0) {
			tlmmTriggerHighDirectConfig(pin_num, proc, direct_num);
		} else if (strcmp(argv[3], "low") == 0) {
			tlmmTriggerLowDirectConfig(pin_num, proc, direct_num);
		} else if (strcmp(argv[3], "rising") == 0) {
			tlmmTriggerRisingDirectConfig(pin_num, proc, direct_num);
		} else if (strcmp(argv[3], "falling") == 0) {
			tlmmTriggerFallingDirectConfig(pin_num, proc, direct_num);
		} else {
			return -1;
		}
	} else if (strcmp(argv[1], "setpull") == 0) {
		if (argc < 4) {
			return -1;
		}
		config = strtoul(argv[3], 0, 0);
		tlmmSetPullConfig(pin_num, config);
	} else if (strcmp(argv[1], "setdrive") == 0) {
		if (argc < 4) {
			return -1;
		}
		config = strtoul(argv[3], 0, 0);
		tlmmSetDriveStrengthConfig(pin_num, config);
	} else if (strcmp(argv[1], "setfunc") == 0) {
		if (argc < 4) {
			return -1;
		}
		config = strtoul(argv[3], 0, 0);
		tlmmSetFunctionConfig(pin_num, config);
	} else if (strcmp(argv[1], "setdir") == 0) {
		if (argc < 4) {
			return -1;
		}
		config = strtoul(argv[3], 0, 0);
		tlmmSetDirectionConfig(pin_num, config);
	} else {
		return -1;
	}
	return 0;
}

MK_CMD(gpio,
	   do_gpio,
	   "config/read/write/intr gpio register",
	   "first config gpio,then read or write!\n"
	   "gpio config in or out...\n"
	   "   - gpio {config | c} {GPIO_NUM} {in | out}\n"
	   "gpio read register data...\n"
	   "   - gpio {read | r} {GPIO_NUM}\n"
	   "gpio write data to register...\n"
	   "    - gpio {write | w} {GPIO_NUM} {VALUE}"
	   "gpio intr summary Config...\n"
	   "    - gpio {summary} {GPIO_NUM} {high|low|rising|falling|edge}"
	   "{0:imc|1:hmss|2:tz}"
	   "gpio intr direct config...\n"
	   "    - gpio {direct} {GPIO_NUM} {high|low|rising|falling} "
	   "{0:imc|1:hmss} {direct_num:0-15}"
	   "gpio set pull config...\n"
	   "   - gpio {setpull} {GPIO_NUM} {VALUE}\n"
	   "gpio set drive strength config...\n"
	   "   - gpio {setdrive} {GPIO_NUM} {VALUE}\n"
	   "gpio set set function config...\n"
	   "   - gpio {setfunc} {GPIO_NUM} {VALUE}\n"
	   "gpio set set direction config...\n"
	   "   - gpio {setdir} {GPIO_NUM} {VALUE}\n");

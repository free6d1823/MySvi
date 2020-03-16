/*
 */
#ifndef __TESTOS_GPIO_H_INCLUDE__
#define __TESTOS_GPIO_H_INCLUDE__

#include <asm/gpio.h>

#define NR_GPIOS	ARCH_NR_GPIOS

/* Architecture independent GPIO configurations */

#define GPIO_PULL_NONE	0
#define GPIO_PULL_DOWN	1
#define GPIO_KEEPER	2
#define GPIO_PULL_UP	3

#define GPIO_DIR_INPUT	0
#define GPIO_DIR_OUTPUT	1

#define GPIO_INT_SUMMARY 0
#define GPIO_INT_DIRECT 1

#define GPIO_PROC_IMC 0
#define GPIO_PROC_HMSS 1
#define GPIO_PROC_TZ 2

#define GPIO_DRIVE_MA(x)		(((x) >> 1) - 1)

#define GPIO_DIR_SHIFT		0
#define GPIO_DIR_MASK		0x01
#define GPIO_PULL_SHIFT		1
#define GPIO_PULL_MASK		0x03
#define GPIO_DRIVE_SHIFT	4
#define GPIO_DRIVE_MASK		0x0F
#define GPIO_FUNC_SHIFT		8
#define GPIO_FUNC_MASK		0x3FF

#define GPIO_DECODE_DIR(cfg)		\
	(((cfg) >> GPIO_DIR_SHIFT) & GPIO_DIR_MASK)
#define GPIO_DECODE_PULL(cfg)		\
	(((cfg) >> GPIO_PULL_SHIFT) & GPIO_PULL_MASK)
#define GPIO_DECODE_DRIVE(cfg)		\
	(((cfg) >> GPIO_DRIVE_SHIFT) & GPIO_DRIVE_MASK)
#define GPIO_DECODE_FUNC(cfg)		\
	(((cfg) >> GPIO_FUNC_SHIFT) & GPIO_FUNC_MASK)

#define GPIO_ENCODE_DIR(drive)		\
	((((uint32_t)(drive)) & GPIO_DIR_MASK) << GPIO_DIR_SHIFT)
#define GPIO_ENCODE_PULL(drive)		\
	((((uint32_t)(drive)) & GPIO_PULL_MASK) << GPIO_PULL_SHIFT)
#define GPIO_ENCODE_DRIVE(drive)	\
	((((uint32_t)(drive)) & GPIO_DRIVE_MASK) << GPIO_DRIVE_SHIFT)
#define GPIO_ENCODE_FUNC(drive)		\
	((((uint32_t)(drive)) & GPIO_FUNC_MASK) << GPIO_FUNC_SHIFT)

#define GPIO_ENCODE_CONFIG(func, dir, pull, drive)	\
	(GPIO_ENCODE_DIR(dir) |				\
	 GPIO_ENCODE_PULL(pull) |			\
	 GPIO_ENCODE_DRIVE(drive) |			\
	 GPIO_ENCODE_FUNC(func))

#define gpio_config_port(gpio, cfg)	arch_gpio_config_port(gpio, cfg)
#define gpio_read_input(gpio)		arch_gpio_read_input(gpio)
#define gpio_read_output(gpio)		arch_gpio_read_output(gpio)
#define gpio_write_output(gpio, val)	arch_gpio_write_output(gpio, val)

#endif /* __TESTOS_GPIO_H_INCLUDE__ */

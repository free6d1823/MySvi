#ifndef __TESTOS_CMDLINE_H_INCLUDE__
#define __TESTOS_CMDLINE_H_INCLUDE__

#include <errno.h>
#include <target/compiler.h>

/*
 * COMMAND opt1 [opt2] opt3 | opt4 opt5=param1{,param2}*
 * The options use '[ ]' for optional,
 * and '|' for exclusive alternatives,
 * '{ }' to bracket alternative sets.
 * '*' means repeat as required.
 */
#define MK_CMD(name, cmd, help, usage) \
    int cmd(int, char *[]); \
    static const cmd_tbl __cmd_array_##name \
    __attribute__((used,section(".cmd_array."#name))) \
    = {#name, cmd, help, usage}

typedef struct {
    const char *name;  /* command name */
    int (*cmd)(int argc, char *argv[]);
    const char *help;  /* short description */
    const char *usage; /* long description */
} cmd_tbl;

#ifdef CONFIG_CONSOLE_COMMAND
int cmd_help(char *cmd);
int cmd_loop(void);
int cmd_init(void);
#else
static inline int cmd_help(char *cmd)
{
	return -ENODEV;
}
static inline int cmd_loop(void)
{
	return -ENODEV;
}
static inline int cmd_init(void)
{
	return -ENODEV;
}
#endif

#endif /* __TESTOS_CMDLINE_H_INCLUDE__ */

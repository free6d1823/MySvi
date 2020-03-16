#define PATTERN_NAME		"linpack"
#ifdef CONFIG_TESTOS_LINPACK_TIMEOUT
#define PATTERN_TIMEOUT		CONFIG_TESTOS_LINPACK_TIMEOUT
#else
#define PATTERN_TIMEOUT		(1 * 1000 * 1000)
#endif

#include "../../init/testos/testos_pattern_template.c"

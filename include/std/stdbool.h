#ifndef __GNU_STDBOOL_H
#define __GNU_STDBOOL_H

#if defined(__GNUC__)
#ifndef __cplusplus

#define bool	_Bool
#define true	1
#define false	0

#else /* __cplusplus */

/* Supporting <stdbool.h> in C++ is a GCC extension.  */
#define _Bool	bool
#define bool	bool
#define false	false
#define true	true

#endif /* __cplusplus */
#endif

#define __bool_true_false_are_defined	1

#endif /* __GNU_STDBOOL_H */

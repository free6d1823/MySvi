#ifndef _TIME_H
#define _TIME_H

#include <target/timer.h>

/* Not seconds based, but microseconds based */
#define time(__t)	(time_get_current_time() / 1000000)
#define utime(_t)	time_get_current_time()

#endif /* _TIME_H */

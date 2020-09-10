//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#include "acamera_logger.h"

/* If the kernel is not used then simply define these strings to empty string.
 * This way we can have a single LUT definition */

#ifndef KERN_DEBUG
#define KERN_DEBUG ""
#endif

#ifndef KERN_INFO
#define KERN_INFO ""
#endif

#ifndef KERN_NOTICE
#define KERN_NOTICE ""
#endif

#ifndef KERN_WARNING
#define KERN_WARNING ""
#endif

#ifndef KERN_ERR
#define KERN_ERR ""
#endif

#ifndef KERN_CRIT
#define KERN_CRIT ""
#endif

#ifndef KERN_ALERT
#define KERN_ALERT ""
#endif

#ifndef KERN_EMERG
#define KERN_EMERG ""
#endif

/*Table of const pointers to const strings. */
static const char *const m_level_names[LOG_LEVEL_MAX] = {
    [LOG_LEVEL_DEBUG] = KERN_DEBUG LOG_COLOR_DEBUG "[DEBUG]" LOG_COLOR_DEFAULT "  ",
    [LOG_LEVEL_INFO] = KERN_INFO LOG_COLOR_INFO "[INFO]" LOG_COLOR_DEFAULT "   ",
    [LOG_LEVEL_NOTICE] = KERN_NOTICE LOG_COLOR_NOTICE "[NOTICE]" LOG_COLOR_DEFAULT " ",
    [LOG_LEVEL_WARNING] = KERN_WARNING LOG_COLOR_WARN "[WARN]" LOG_COLOR_DEFAULT "   ",
    [LOG_LEVEL_ERROR] = KERN_ERR LOG_COLOR_ERROR "[ERROR]" LOG_COLOR_DEFAULT "  ",
    [LOG_LEVEL_CRIT] = KERN_CRIT LOG_COLOR_CRIT "[!CRIT!]" LOG_COLOR_DEFAULT " ",
    [LOG_LEVEL_ALERT] = KERN_ALERT LOG_COLOR_CRIT "[!ALERT!]" LOG_COLOR_DEFAULT " ",
    [LOG_LEVEL_EMERG] = KERN_EMERG LOG_COLOR_CRIT "[!EMERG!]" LOG_COLOR_DEFAULT " ",
};


/** logger internal data structure*/
static struct {
    void *lock;               /**< Pointer to a lock object (optional). */
    alog_lock_fn log_lock_fn; /**< User provided locking function, NULL by default. */
    alog_level_t level;       /**< Current log level. */
    alog_mask_t mask;         /**< current log mask*/

} g_alog = {.lock = NULL,
            .log_lock_fn = NULL,
            .level = LOG_DEFAULT_VALUE,
            .mask = ( alog_mask_t )( ( 1u << LOG_LEVEL_MAX ) - 1u )};


void alog_lock( void )
{
    if ( g_alog.log_lock_fn )
        g_alog.log_lock_fn( true, g_alog.lock );
}

void alog_unlock( void )
{
    if ( g_alog.log_lock_fn )
        g_alog.log_lock_fn( false, g_alog.lock );
}


void alog_set_locking( alog_lock_fn fun, void *lock )
{
    g_alog.log_lock_fn = fun;
    g_alog.lock = lock;
}

void alog_set_level( const alog_level_t level )
{
    if ( level < LOG_LEVEL_MAX ) {
        alog_lock();
        g_alog.level = level;
        alog_unlock();
    }
}


alog_level_t alog_get_level( void ) { return g_alog.level; }


void alog_set_mask( const alog_mask_t mask )
{
    alog_lock();
    g_alog.mask = mask;
    alog_unlock();
}

alog_mask_t alog_get_mask( void ) { return g_alog.mask; }


bool alog_check_level( const alog_level_t level )
{
    if ( g_alog.level == LOG_LEVEL_NOTHING ) return false;
    if ( level < g_alog.level ) return false;
    if ( ( ( 1 << level ) & g_alog.mask ) == 0 ) return false;
    return true;
}

const char *alog_level_string( const alog_level_t level )
{
    return m_level_names[level % LOG_LEVEL_MAX];
}

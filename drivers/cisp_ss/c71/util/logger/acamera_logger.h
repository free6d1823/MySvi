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

#ifndef ACAMERA_LOGGER_H
#define ACAMERA_LOGGER_H

#include "system_log.h"            // Necessary for printf implementation.
#include "acamera_configuration.h" // Set file can define LOG setup.

/*============================================
=            Logger Configuration            =
============================================*/

#ifdef SYSTEM_LOG_USE_COLOR
#define LOG_USE_COLOR SYSTEM_LOG_USE_COLOR
#else
#define LOG_USE_COLOR 0
#endif

#ifndef SYSTEM_PRINTF
#warning SYSTEM_PRINTF undefined, using printf
#define SYSTEM_PRINTF printf
#endif

#ifdef SYSTEM_LOG_POST_FIX
#define LOG_POST_FIX SYSTEM_LOG_POST_FIX
#else
#define LOG_POST_FIX ""
#endif

#ifdef SYSTEM_LOG_DEFAULT_VALUE
#define LOG_DEFAULT_VALUE SYSTEM_LOG_DEFAULT_VALUE
#else
#define LOG_DEFAULT_VALUE LOG_LEVEL_NOTICE
#endif

/*=====  End of Logger Configuration  ======*/


#if LOG_USE_COLOR
#define LOG_COLOR_DEBUG "\e[0;37m"
#define LOG_COLOR_INFO "\e[32m"
#define LOG_COLOR_NOTICE "\e[36m"
#define LOG_COLOR_WARN "\e[33m"
#define LOG_COLOR_ERROR "\e[0;31m"
#define LOG_COLOR_CRIT "\e[1;31m"
#define LOG_COLOR_FILE "\e[1;30m"
#define LOG_COLOR_DEFAULT "\033[0m"
#else
#define LOG_COLOR_DEBUG ""
#define LOG_COLOR_INFO ""
#define LOG_COLOR_NOTICE ""
#define LOG_COLOR_WARN ""
#define LOG_COLOR_ERROR ""
#define LOG_COLOR_CRIT ""
#define LOG_COLOR_FILE ""
#define LOG_COLOR_DEFAULT ""
#endif

#ifndef __FILENAME__
#define __FILENAME__ ( __builtin_strrchr( __FILE__, '/' ) ? __builtin_strrchr( __FILE__, '/' ) + 1 : __FILE__ )
#endif

/** Locking function prototype.*/
typedef void ( *alog_lock_fn )( const bool lock, void *lock_ptr );

/** Type of the mask, currently 8 bits. */
typedef uint8_t alog_mask_t;


/** Log levels, ideally these should be in order of verbosity (nothing at top,
 * crit at bottom) but I kept the previous levels to maintain API consistency */
typedef enum {
    LOG_LEVEL_DEBUG,   /**< Debug statements. */
    LOG_LEVEL_INFO,    /**< Informational message e.g. startup information at driver initialization. */
    LOG_LEVEL_NOTICE,  /**< Nothing serious, but notably nevertheless. Often used to report security events. */
    LOG_LEVEL_WARNING, /**< A warning, meaning nothing serious by itself but might indicate problems. */
    LOG_LEVEL_ERROR,   /**< An error condition, often used by drivers to indicate difficulties with the hardware. */
    LOG_LEVEL_CRIT,    /**< A critical condition occurred like a serious hardware/software failure. */
    LOG_LEVEL_ALERT,   /**< Something bad happened and action must be taken immediately. */
    LOG_LEVEL_EMERG,   /**< Emergency message, the system is about to or may crash. */
    LOG_LEVEL_NOTHING, /**< Do not log anything to the ouput. Quiet mode. */
    /* Leave this at the bottom */
    LOG_LEVEL_MAX,
} alog_level_t;


/**
 * @brief      Provides a function callback for locking and a mutex which is
 *             used by it.
 *
 * @param      fun   The function callback
 * @param      lock  The lock dataq
 *
 * @details    By default the logger is not safe for multi thread, it requires a
 *             user lock implemenation to be provided.
 * @warning    If you plan on calling LOG from ISR then the lock needs to be
 *             adequate (spinlock). If you only use LOG from thread context you
 *             can use a sleeping lock (mutex).
 */
void alog_set_locking( alog_lock_fn fun, void *lock );


/**
 * @brief      Sets log level.
 *
 * @param[in]  level  The level
 *
 * @details    Only messages of the provided level or above will be displayed.
 */
void alog_set_level( const alog_level_t level );


/**
 * @brief      Returns debug level.
 *
 * @return     Debug level
 *
 * @details    Used by the system API.
 */
alog_level_t alog_get_level( void );


/**
 * @brief      Sets the log filter mask.
 *
 * @param[in]  mask  The mask
 *
 * @details    The user can specify a mask for which messages to display. For
 *             example, if log level is LOG_LEVEL_DEBUG (all messages) we can set
 *             a mask to only display notice and critical level:
 * @code
 *             alog_set_mask( ( 1 << LOG_LEVEL_NOTICE) | ( 1 << LOG_LEVEL_CRIT ) );
 * @endcode
 */
void alog_set_mask( const alog_mask_t mask );


/**
 * @brief      Returns the log mask.
 *
 * @return     Bitmask of allowed logs
 *
 */
alog_mask_t alog_get_mask( void );


/**
 * @brief      Locks the logger using locking set by #alog_set_locking.
 *
 * @details    This is a private function, but needs to be exposed here since the
 *             log statement is a macro implementation.
 */
void alog_lock( void );

/**
 * @brief      Unlocks the logger using locking set by #alog_set_locking.
 *
 * @details    This is a private function, but needs to be exposed here since the
 *             log statement is a macro implementation.
 */
void alog_unlock( void );


/**
 * @brief      Checks if requested level can log.
 *
 * @param[in]  level  The level
 *
 * @return     True if log is allowed, false otherwise.
 *
 */
bool alog_check_level( const alog_level_t level );


/**
 * @brief      Helper function to return the log level string.
 *
 * @param[in]  level  The level
 *
 * @return     Pointer to log level string from static table.
 *
 * @details    This will always return a valid string, but levels above
 *             LOG_LEVEL_MAX will return an incorrect log level.
 *             It is the users responsibility to provide correct log level.
 */
const char *alog_level_string( const alog_level_t level );


#if defined( SYSTEM_GET_TIME_STAMP ) && !( __KERNEL__ )
/**
 * @brief      Helper log macro.
 *
 * @param      level  The level
 * @param      fmt    The format
 * @param      ...    va args
 *
 * @details    Helper macro to avoid parameter duplication. This version
 *             includes time string for non kernel builds where the user has
 *             provided a time string implementation. Printf like usage:
 * @code
 * LOG( LOG_CRIT, "This is a cool little message with an integer value %d", some_value );
 * @endcode
 *
 * @note       If printk is used you do not need to use any locking since it is
 *             safe to call from anywhere in the kernel.
 */
#define LOG( level, fmt, ... )                                                                 \
    do {                                                                                       \
        if ( alog_check_level( level ) ) {                                                     \
            alog_lock();                                                                       \
            SYSTEM_PRINTF( "%s%s" LOG_COLOR_FILE "%s:%d: " LOG_COLOR_DEFAULT fmt LOG_POST_FIX, \
                           SYSTEM_GET_TIME_STAMP(),                                            \
                           alog_level_string( level ),                                         \
                           __FILENAME__,                                                       \
                           __LINE__,                                                           \
                           ##__VA_ARGS__ );                                                    \
            alog_unlock();                                                                     \
        }                                                                                      \
    } while ( 0 )


#else /* For kernel debug or if no time func has been provided. */

/**
 * @brief      Helper log macro.
 *
 * @param      level  The level
 * @param      fmt    The format
 * @param      ...    va args
 *
 * @return     { description_of_the_return_value }
 *
 * @details    Helper macro to avoid parameter duplication. Printf like usage:
 * @code
 * LOG( LOG_CRIT, "ISP irq = %d, flags = 0x%x %s id :%d!", (int)isp_irq->start, (int)isp_irq->flags, pdev->name, pdev->id );
 * @endcode
 *
 * @note       If printk is used you do not need to use any locking since it is
 *             safe to call from anywhere in the kernel.
 */
#define LOG( level, fmt, ... )                                                               \
    do {                                                                                     \
        if ( alog_check_level( level ) ) {                                                   \
            alog_lock();                                                                     \
            SYSTEM_PRINTF( "%s" LOG_COLOR_FILE "%s:%d: " LOG_COLOR_DEFAULT fmt LOG_POST_FIX, \
                           alog_level_string( level ),                                       \
                           __FILENAME__,                                                     \
                           __LINE__,                                                         \
                           ##__VA_ARGS__ );                                                  \
            alog_unlock();                                                                   \
        }                                                                                    \
    } while ( 0 )


#endif /* defined( SYSTEM_GET_TIME_STAMP ) && !( __KERNEL__ ) */


#define LOG_CONT( level, fmt, ... )              \
    do {                                         \
        if ( alog_check_level( level ) ) {       \
            alog_lock();                         \
            SYSTEM_PRINTF( fmt, ##__VA_ARGS__ ); \
            alog_unlock();                       \
        }                                        \
    } while ( 0 )


/* This is neccessary to maintain backwards compatibility, ideally each of this would be function call. Forexample LOG_DEBUG(...). */

#define LOG_DEBUG LOG_LEVEL_DEBUG
#define LOG_INFO LOG_LEVEL_INFO
#define LOG_NOTICE LOG_LEVEL_NOTICE
#define LOG_WARNING LOG_LEVEL_WARNING
#define LOG_ERR LOG_LEVEL_ERROR
#define LOG_CRIT LOG_LEVEL_CRIT
#define LOG_ALERT LOG_LEVEL_ALERT
#define LOG_EMERG LOG_LEVEL_EMERG


#endif // ACAMERA_LOGGER_H

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

#ifndef __SYSTEM_ASSERT_H__
#define __SYSTEM_ASSERT_H__

/** @file system_assert.h
    @addtogroup   platform Platform
    @{
*/

/**
 * @brief      Calls when assertion fails.
 *
 * @param      file        The file
 * @param[in]  line        The line
 * @param      expression  The expression
 *
 * @details    Not to be called by user.
 * @warning    This handler is fatal and will not return.
 */
void _assert_handler( char const *const file, const int line, char const *const expression ) __attribute__( ( noreturn ) );

#ifdef assert
#undef assert
#endif
/**
 * @brief      Assert macro
 *
 * @param      expression  Expression to check
 *
 * @details    Calls handler with current file and line if the assertion is
 *             false.
 */
#define assert( expression ) \
    if ( !( expression ) )   \
    _assert_handler( __FILE__, __LINE__, #expression )


/** @} */

#endif /*__SYSTEM_ASSERT_H__*/

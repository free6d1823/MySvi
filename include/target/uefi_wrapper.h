#ifndef UEFI_WRAPPER_H
#define UEFI_WRAPPER_H

/// Function return status for EFI API.
///
typedef unsigned long long             EFI_STATUS;

///
/// Unsigned value of native width.  (4 bytes on supported 32-bit processor instructions,
/// 8 bytes on supported 64-bit processor instructions)
///
typedef unsigned long long  UINTN;
typedef long long           INTN;
typedef unsigned int        UINT32;
typedef unsigned char       UINT8;
typedef unsigned char       BOOLEAN;

typedef UINTN RETURN_STATUS;

#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */
#ifndef NULL
#define NULL ((void *)0)
#endif

#define EFIAPI

///
/// Datum is read-only.
///
#define CONST     const

///
/// Datum is scoped to the current file or function.
///
#define STATIC    static

///
/// Datum is passed to the function.
///
#define IN

///
/// Datum is returned from the function.
///
#define OUT

typedef  BOOLEAN            boolean;     /* Boolean value type. */

///
/// A value of native width with the highest bit set.
///
#define MAX_BIT     0x8000000000000000ULL
#define ENCODE_ERROR(StatusCode)     ((RETURN_STATUS)(MAX_BIT | (StatusCode)))

///
/// Enumeration of EFI_STATUS.

#define EFI_SUCCESS               0
#define EFI_DEVICE_ERROR          ENCODE_ERROR (7)
#define EFI_UNSUPPORTED           ENCODE_ERROR (3)
#define EFI_NOT_READY             ENCODE_ERROR (6)
#define EFI_INVALID_PARAMETER     ENCODE_ERROR (2)


#define RETURN_ERROR(StatusCode)     (((INTN)(RETURN_STATUS)(StatusCode)) < 0)
#define EFI_ERROR(A)              RETURN_ERROR(A)
#endif

/** @file
  Provides string functions, linked list functions, math functions, synchronization
  functions, file path functions, and CPU architecture-specific functions.

Copyright (c) 2006 - 2016, Intel Corporation. All rights reserved.<BR>
Portions copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __BASE_LIB__
#define __BASE_LIB__

//
// Definitions for architecture-specific types
//


#if defined (MDE_CPU_ARM)

typedef struct {
  UINT32    R3;  ///< A copy of R13.
  UINT32    R4;
  UINT32    R5;
  UINT32    R6;
  UINT32    R7;
  UINT32    R8;
  UINT32    R9;
  UINT32    R10;
  UINT32    R11;
  UINT32    R12;
  UINT32    R14;
} BASE_LIBRARY_JUMP_BUFFER;

#define BASE_LIBRARY_JUMP_BUFFER_ALIGNMENT 4

#endif  // defined (MDE_CPU_ARM)

#if defined (MDE_CPU_AARCH64)
typedef struct {
  // GP regs
  UINT64    X19;
  UINT64    X20;
  UINT64    X21;
  UINT64    X22;
  UINT64    X23;
  UINT64    X24;
  UINT64    X25;
  UINT64    X26;
  UINT64    X27;
  UINT64    X28;
  UINT64    FP;
  UINT64    LR;
  UINT64    PADD_0;
  UINT64    IP0;

  // FP regs
  UINT64    D8;
  UINT64    D9;
  UINT64    D10;
  UINT64    D11;
  UINT64    D12;
  UINT64    D13;
  UINT64    D14;
  UINT64    D15;
} BASE_LIBRARY_JUMP_BUFFER;

#define BASE_LIBRARY_JUMP_BUFFER_ALIGNMENT 8

#endif  // defined (MDE_CPU_AARCH64)


//
// String Services
//


/**
  Returns the length of a Null-terminated Unicode string.

  This function is similar as strlen_s defined in C11.

  If String is not aligned on a 16-bit boundary, then ASSERT().

  @param  String   A pointer to a Null-terminated Unicode string.
  @param  MaxSize  The maximum number of Destination Unicode
                   char, including terminating null char.

  @retval 0        If String is NULL.
  @retval MaxSize  If there is no null character in the first MaxSize characters of String.
  @return The number of characters that percede the terminating null character.

**/
UINTN
EFIAPI
StrnLenS (
  IN CONST CHAR16              *String,
  IN UINTN                     MaxSize
  );

/**
  Copies the string pointed to by Source (including the terminating null char)
  to the array pointed to by Destination.

  This function is similar as strcpy_s defined in C11.

  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Unicode string.
  @param  DestMax                  The maximum number of Destination Unicode
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Unicode string.

  @retval RETURN_SUCCESS           String is copied.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
StrCpyS (
  OUT CHAR16       *Destination,
  IN  UINTN        DestMax,
  IN  CONST CHAR16 *Source
  );

/**
  Copies not more than Length successive char from the string pointed to by
  Source to the array pointed to by Destination. If no null char is copied from
  Source, then Destination[Length] is always set to null.

  This function is similar as strncpy_s defined in C11.

  If Length > 0 and Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Length > 0 and Source is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Unicode string.
  @param  DestMax                  The maximum number of Destination Unicode
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Unicode string.
  @param  Length                   The maximum number of Unicode characters to copy.

  @retval RETURN_SUCCESS           String is copied.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than
                                   MIN(StrLen(Source), Length).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
StrnCpyS (
  OUT CHAR16       *Destination,
  IN  UINTN        DestMax,
  IN  CONST CHAR16 *Source,
  IN  UINTN        Length
  );

/**
  Appends a copy of the string pointed to by Source (including the terminating
  null char) to the end of the string pointed to by Destination.

  This function is similar as strcat_s defined in C11.

  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Unicode string.
  @param  DestMax                  The maximum number of Destination Unicode
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Unicode string.

  @retval RETURN_SUCCESS           String is appended.
  @retval RETURN_BAD_BUFFER_SIZE   If DestMax is NOT greater than
                                   StrLen(Destination).
  @retval RETURN_BUFFER_TOO_SMALL  If (DestMax - StrLen(Destination)) is NOT
                                   greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
StrCatS (
  IN OUT CHAR16       *Destination,
  IN     UINTN        DestMax,
  IN     CONST CHAR16 *Source
  );

/**
  Appends not more than Length successive char from the string pointed to by
  Source to the end of the string pointed to by Destination. If no null char is
  copied from Source, then Destination[StrLen(Destination) + Length] is always
  set to null.

  This function is similar as strncat_s defined in C11.

  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Unicode string.
  @param  DestMax                  The maximum number of Destination Unicode
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Unicode string.
  @param  Length                   The maximum number of Unicode characters to copy.

  @retval RETURN_SUCCESS           String is appended.
  @retval RETURN_BAD_BUFFER_SIZE   If DestMax is NOT greater than
                                   StrLen(Destination).
  @retval RETURN_BUFFER_TOO_SMALL  If (DestMax - StrLen(Destination)) is NOT
                                   greater than MIN(StrLen(Source), Length).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
StrnCatS (
  IN OUT CHAR16       *Destination,
  IN     UINTN        DestMax,
  IN     CONST CHAR16 *Source,
  IN     UINTN        Length
  );

/**
  Returns the length of a Null-terminated Ascii string.

  This function is similar as strlen_s defined in C11.

  @param  String   A pointer to a Null-terminated Ascii string.
  @param  MaxSize  The maximum number of Destination Ascii
                   char, including terminating null char.

  @retval 0        If String is NULL.
  @retval MaxSize  If there is no null character in the first MaxSize characters of String.
  @return The number of characters that percede the terminating null character.

**/
UINTN
EFIAPI
AsciiStrnLenS (
  IN CONST CHAR8               *String,
  IN UINTN                     MaxSize
  );

/**
  Copies the string pointed to by Source (including the terminating null char)
  to the array pointed to by Destination.

  This function is similar as strcpy_s defined in C11.

  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Ascii string.
  @param  DestMax                  The maximum number of Destination Ascii
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Ascii string.

  @retval RETURN_SUCCESS           String is copied.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
AsciiStrCpyS (
  OUT CHAR8        *Destination,
  IN  UINTN        DestMax,
  IN  CONST CHAR8  *Source
  );

/**
  Copies not more than Length successive char from the string pointed to by
  Source to the array pointed to by Destination. If no null char is copied from
  Source, then Destination[Length] is always set to null.

  This function is similar as strncpy_s defined in C11.

  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Ascii string.
  @param  DestMax                  The maximum number of Destination Ascii
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Ascii string.
  @param  Length                   The maximum number of Ascii characters to copy.

  @retval RETURN_SUCCESS           String is copied.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than
                                   MIN(StrLen(Source), Length).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
AsciiStrnCpyS (
  OUT CHAR8        *Destination,
  IN  UINTN        DestMax,
  IN  CONST CHAR8  *Source,
  IN  UINTN        Length
  );

/**
  Appends a copy of the string pointed to by Source (including the terminating
  null char) to the end of the string pointed to by Destination.

  This function is similar as strcat_s defined in C11.

  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Ascii string.
  @param  DestMax                  The maximum number of Destination Ascii
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Ascii string.

  @retval RETURN_SUCCESS           String is appended.
  @retval RETURN_BAD_BUFFER_SIZE   If DestMax is NOT greater than
                                   StrLen(Destination).
  @retval RETURN_BUFFER_TOO_SMALL  If (DestMax - StrLen(Destination)) is NOT
                                   greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
AsciiStrCatS (
  IN OUT CHAR8        *Destination,
  IN     UINTN        DestMax,
  IN     CONST CHAR8  *Source
  );

/**
  Appends not more than Length successive char from the string pointed to by
  Source to the end of the string pointed to by Destination. If no null char is
  copied from Source, then Destination[StrLen(Destination) + Length] is always
  set to null.

  This function is similar as strncat_s defined in C11.

  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Destination              A pointer to a Null-terminated Ascii string.
  @param  DestMax                  The maximum number of Destination Ascii
                                   char, including terminating null char.
  @param  Source                   A pointer to a Null-terminated Ascii string.
  @param  Length                   The maximum number of Ascii characters to copy.

  @retval RETURN_SUCCESS           String is appended.
  @retval RETURN_BAD_BUFFER_SIZE   If DestMax is NOT greater than
                                   StrLen(Destination).
  @retval RETURN_BUFFER_TOO_SMALL  If (DestMax - StrLen(Destination)) is NOT
                                   greater than MIN(StrLen(Source), Length).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.
**/
RETURN_STATUS
EFIAPI
AsciiStrnCatS (
  IN OUT CHAR8        *Destination,
  IN     UINTN        DestMax,
  IN     CONST CHAR8  *Source,
  IN     UINTN        Length
  );


#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Copies one Null-terminated Unicode string to another Null-terminated Unicode
  string and returns the new Unicode string.

  This function copies the contents of the Unicode string Source to the Unicode
  string Destination, and returns Destination. If Source and Destination
  overlap, then the results are undefined.

  If Destination is NULL, then ASSERT().
  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Source contains more than
  PcdMaximumUnicodeStringLength Unicode characters not including the
  Null-terminator, then ASSERT().

  @param  Destination The pointer to a Null-terminated Unicode string.
  @param  Source      The pointer to a Null-terminated Unicode string.

  @return Destination.

**/
CHAR16 *
EFIAPI
StrCpy (
  OUT     CHAR16                    *Destination,
  IN      CONST CHAR16              *Source
  );


/**
  [ATTENTION] This function is deprecated for security reason.

  Copies up to a specified length from one Null-terminated Unicode string to
  another Null-terminated Unicode string and returns the new Unicode string.

  This function copies the contents of the Unicode string Source to the Unicode
  string Destination, and returns Destination. At most, Length Unicode
  characters are copied from Source to Destination. If Length is 0, then
  Destination is returned unmodified. If Length is greater that the number of
  Unicode characters in Source, then Destination is padded with Null Unicode
  characters. If Source and Destination overlap, then the results are
  undefined.

  If Length > 0 and Destination is NULL, then ASSERT().
  If Length > 0 and Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Length > 0 and Source is NULL, then ASSERT().
  If Length > 0 and Source is not aligned on a 16-bit boundary, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Length is greater than
  PcdMaximumUnicodeStringLength, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Source contains more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the Null-terminator,
  then ASSERT().

  @param  Destination The pointer to a Null-terminated Unicode string.
  @param  Source      The pointer to a Null-terminated Unicode string.
  @param  Length      The maximum number of Unicode characters to copy.

  @return Destination.

**/
CHAR16 *
EFIAPI
StrnCpy (
  OUT     CHAR16                    *Destination,
  IN      CONST CHAR16              *Source,
  IN      UINTN                     Length
  );
#endif

/**
  Returns the length of a Null-terminated Unicode string.

  This function returns the number of Unicode characters in the Null-terminated
  Unicode string specified by String.

  If String is NULL, then ASSERT().
  If String is not aligned on a 16-bit boundary, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and String contains more than
  PcdMaximumUnicodeStringLength Unicode characters not including the
  Null-terminator, then ASSERT().

  @param  String  Pointer to a Null-terminated Unicode string.

  @return The length of String.

**/
UINTN
EFIAPI
StrLen (
  IN      CONST CHAR16              *String
  );


/**
  Returns the size of a Null-terminated Unicode string in bytes, including the
  Null terminator.

  This function returns the size, in bytes, of the Null-terminated Unicode string
  specified by String.

  If String is NULL, then ASSERT().
  If String is not aligned on a 16-bit boundary, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and String contains more than
  PcdMaximumUnicodeStringLength Unicode characters not including the
  Null-terminator, then ASSERT().

  @param  String  The pointer to a Null-terminated Unicode string.

  @return The size of String.

**/
UINTN
EFIAPI
StrSize (
  IN      CONST CHAR16              *String
  );


/**
  Compares two Null-terminated Unicode strings, and returns the difference
  between the first mismatched Unicode characters.

  This function compares the Null-terminated Unicode string FirstString to the
  Null-terminated Unicode string SecondString. If FirstString is identical to
  SecondString, then 0 is returned. Otherwise, the value returned is the first
  mismatched Unicode character in SecondString subtracted from the first
  mismatched Unicode character in FirstString.

  If FirstString is NULL, then ASSERT().
  If FirstString is not aligned on a 16-bit boundary, then ASSERT().
  If SecondString is NULL, then ASSERT().
  If SecondString is not aligned on a 16-bit boundary, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and FirstString contains more
  than PcdMaximumUnicodeStringLength Unicode characters not including the
  Null-terminator, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and SecondString contains more
  than PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().

  @param  FirstString   The pointer to a Null-terminated Unicode string.
  @param  SecondString  The pointer to a Null-terminated Unicode string.

  @retval 0      FirstString is identical to SecondString.
  @return others FirstString is not identical to SecondString.

**/
INTN
EFIAPI
StrCmp (
  IN      CONST CHAR16              *FirstString,
  IN      CONST CHAR16              *SecondString
  );


/**
  Compares up to a specified length the contents of two Null-terminated Unicode strings,
  and returns the difference between the first mismatched Unicode characters.

  This function compares the Null-terminated Unicode string FirstString to the
  Null-terminated Unicode string SecondString. At most, Length Unicode
  characters will be compared. If Length is 0, then 0 is returned. If
  FirstString is identical to SecondString, then 0 is returned. Otherwise, the
  value returned is the first mismatched Unicode character in SecondString
  subtracted from the first mismatched Unicode character in FirstString.

  If Length > 0 and FirstString is NULL, then ASSERT().
  If Length > 0 and FirstString is not aligned on a 16-bit boundary, then ASSERT().
  If Length > 0 and SecondString is NULL, then ASSERT().
  If Length > 0 and SecondString is not aligned on a 16-bit boundary, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Length is greater than
  PcdMaximumUnicodeStringLength, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and FirstString contains more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the Null-terminator,
  then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and SecondString contains more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the Null-terminator,
  then ASSERT().

  @param  FirstString   The pointer to a Null-terminated Unicode string.
  @param  SecondString  The pointer to a Null-terminated Unicode string.
  @param  Length        The maximum number of Unicode characters to compare.

  @retval 0      FirstString is identical to SecondString.
  @return others FirstString is not identical to SecondString.

**/
INTN
EFIAPI
StrnCmp (
  IN      CONST CHAR16              *FirstString,
  IN      CONST CHAR16              *SecondString,
  IN      UINTN                     Length
  );


#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Concatenates one Null-terminated Unicode string to another Null-terminated
  Unicode string, and returns the concatenated Unicode string.

  This function concatenates two Null-terminated Unicode strings. The contents
  of Null-terminated Unicode string Source are concatenated to the end of
  Null-terminated Unicode string Destination. The Null-terminated concatenated
  Unicode String is returned. If Source and Destination overlap, then the
  results are undefined.

  If Destination is NULL, then ASSERT().
  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Destination contains more
  than PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Source contains more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and concatenating Destination
  and Source results in a Unicode string with more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().

  @param  Destination The pointer to a Null-terminated Unicode string.
  @param  Source      The pointer to a Null-terminated Unicode string.

  @return Destination.

**/
CHAR16 *
EFIAPI
StrCat (
  IN OUT  CHAR16                    *Destination,
  IN      CONST CHAR16              *Source
  );


/**
  [ATTENTION] This function is deprecated for security reason.

  Concatenates up to a specified length one Null-terminated Unicode to the end
  of another Null-terminated Unicode string, and returns the concatenated
  Unicode string.

  This function concatenates two Null-terminated Unicode strings. The contents
  of Null-terminated Unicode string Source are concatenated to the end of
  Null-terminated Unicode string Destination, and Destination is returned. At
  most, Length Unicode characters are concatenated from Source to the end of
  Destination, and Destination is always Null-terminated. If Length is 0, then
  Destination is returned unmodified. If Source and Destination overlap, then
  the results are undefined.

  If Destination is NULL, then ASSERT().
  If Length > 0 and Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Length > 0 and Source is NULL, then ASSERT().
  If Length > 0 and Source is not aligned on a 16-bit boundary, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Length is greater than
  PcdMaximumUnicodeStringLength, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Destination contains more
  than PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Source contains more than
  PcdMaximumUnicodeStringLength Unicode characters, not including the
  Null-terminator, then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and concatenating Destination
  and Source results in a Unicode string with more than PcdMaximumUnicodeStringLength
  Unicode characters, not including the Null-terminator, then ASSERT().

  @param  Destination The pointer to a Null-terminated Unicode string.
  @param  Source      The pointer to a Null-terminated Unicode string.
  @param  Length      The maximum number of Unicode characters to concatenate from
                      Source.

  @return Destination.

**/
CHAR16 *
EFIAPI
StrnCat (
  IN OUT  CHAR16                    *Destination,
  IN      CONST CHAR16              *Source,
  IN      UINTN                     Length
  );
#endif

/**
  Returns the first occurrence of a Null-terminated Unicode sub-string
  in a Null-terminated Unicode string.

  This function scans the contents of the Null-terminated Unicode string
  specified by String and returns the first occurrence of SearchString.
  If SearchString is not found in String, then NULL is returned.  If
  the length of SearchString is zero, then String is returned.

  If String is NULL, then ASSERT().
  If String is not aligned on a 16-bit boundary, then ASSERT().
  If SearchString is NULL, then ASSERT().
  If SearchString is not aligned on a 16-bit boundary, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and SearchString
  or String contains more than PcdMaximumUnicodeStringLength Unicode
  characters, not including the Null-terminator, then ASSERT().

  @param  String          The pointer to a Null-terminated Unicode string.
  @param  SearchString    The pointer to a Null-terminated Unicode string to search for.

  @retval NULL            If the SearchString does not appear in String.
  @return others          If there is a match.

**/
CHAR16 *
EFIAPI
StrStr (
  IN      CONST CHAR16              *String,
  IN      CONST CHAR16              *SearchString
  );

/**
  Convert a Null-terminated Unicode decimal string to a value of
  type UINTN.

  This function returns a value of type UINTN by interpreting the contents
  of the Unicode string specified by String as a decimal number. The format
  of the input Unicode string String is:

                  [spaces] [decimal digits].

  The valid decimal digit character is in the range [0-9]. The
  function will ignore the pad space, which includes spaces or
  tab characters, before [decimal digits]. The running zero in the
  beginning of [decimal digits] will be ignored. Then, the function
  stops at the first character that is a not a valid decimal character
  or a Null-terminator, whichever one comes first.

  If String is NULL, then ASSERT().
  If String is not aligned in a 16-bit boundary, then ASSERT().
  If String has only pad spaces, then 0 is returned.
  If String has no pad spaces or valid decimal digits,
  then 0 is returned.
  If the number represented by String overflows according
  to the range defined by UINTN, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and String contains
  more than PcdMaximumUnicodeStringLength Unicode characters not including
  the Null-terminator, then ASSERT().

  @param  String      The pointer to a Null-terminated Unicode string.

  @retval Value translated from String.

**/
UINTN
EFIAPI
StrDecimalToUintn (
  IN      CONST CHAR16              *String
  );

/**
  Convert a Null-terminated Unicode decimal string to a value of
  type UINT64.

  This function returns a value of type UINT64 by interpreting the contents
  of the Unicode string specified by String as a decimal number. The format
  of the input Unicode string String is:

                  [spaces] [decimal digits].

  The valid decimal digit character is in the range [0-9]. The
  function will ignore the pad space, which includes spaces or
  tab characters, before [decimal digits]. The running zero in the
  beginning of [decimal digits] will be ignored. Then, the function
  stops at the first character that is a not a valid decimal character
  or a Null-terminator, whichever one comes first.

  If String is NULL, then ASSERT().
  If String is not aligned in a 16-bit boundary, then ASSERT().
  If String has only pad spaces, then 0 is returned.
  If String has no pad spaces or valid decimal digits,
  then 0 is returned.
  If the number represented by String overflows according
  to the range defined by UINT64, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and String contains
  more than PcdMaximumUnicodeStringLength Unicode characters not including
  the Null-terminator, then ASSERT().

  @param  String          The pointer to a Null-terminated Unicode string.

  @retval Value translated from String.

**/
UINT64
EFIAPI
StrDecimalToUint64 (
  IN      CONST CHAR16              *String
  );


/**
  Convert a Null-terminated Unicode hexadecimal string to a value of type UINTN.

  This function returns a value of type UINTN by interpreting the contents
  of the Unicode string specified by String as a hexadecimal number.
  The format of the input Unicode string String is:

                  [spaces][zeros][x][hexadecimal digits].

  The valid hexadecimal digit character is in the range [0-9], [a-f] and [A-F].
  The prefix "0x" is optional. Both "x" and "X" is allowed in "0x" prefix.
  If "x" appears in the input string, it must be prefixed with at least one 0.
  The function will ignore the pad space, which includes spaces or tab characters,
  before [zeros], [x] or [hexadecimal digit]. The running zero before [x] or
  [hexadecimal digit] will be ignored. Then, the decoding starts after [x] or the
  first valid hexadecimal digit. Then, the function stops at the first character
  that is a not a valid hexadecimal character or NULL, whichever one comes first.

  If String is NULL, then ASSERT().
  If String is not aligned in a 16-bit boundary, then ASSERT().
  If String has only pad spaces, then zero is returned.
  If String has no leading pad spaces, leading zeros or valid hexadecimal digits,
  then zero is returned.
  If the number represented by String overflows according to the range defined by
  UINTN, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and String contains more than
  PcdMaximumUnicodeStringLength Unicode characters not including the Null-terminator,
  then ASSERT().

  @param  String          The pointer to a Null-terminated Unicode string.

  @retval Value translated from String.

**/
UINTN
EFIAPI
StrHexToUintn (
  IN      CONST CHAR16              *String
  );


/**
  Convert a Null-terminated Unicode hexadecimal string to a value of type UINT64.

  This function returns a value of type UINT64 by interpreting the contents
  of the Unicode string specified by String as a hexadecimal number.
  The format of the input Unicode string String is

                  [spaces][zeros][x][hexadecimal digits].

  The valid hexadecimal digit character is in the range [0-9], [a-f] and [A-F].
  The prefix "0x" is optional. Both "x" and "X" is allowed in "0x" prefix.
  If "x" appears in the input string, it must be prefixed with at least one 0.
  The function will ignore the pad space, which includes spaces or tab characters,
  before [zeros], [x] or [hexadecimal digit]. The running zero before [x] or
  [hexadecimal digit] will be ignored. Then, the decoding starts after [x] or the
  first valid hexadecimal digit. Then, the function stops at the first character that is
  a not a valid hexadecimal character or NULL, whichever one comes first.

  If String is NULL, then ASSERT().
  If String is not aligned in a 16-bit boundary, then ASSERT().
  If String has only pad spaces, then zero is returned.
  If String has no leading pad spaces, leading zeros or valid hexadecimal digits,
  then zero is returned.
  If the number represented by String overflows according to the range defined by
  UINT64, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and String contains more than
  PcdMaximumUnicodeStringLength Unicode characters not including the Null-terminator,
  then ASSERT().

  @param  String          The pointer to a Null-terminated Unicode string.

  @retval Value translated from String.

**/
UINT64
EFIAPI
StrHexToUint64 (
  IN      CONST CHAR16             *String
  );

#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Convert a Null-terminated Unicode string to a Null-terminated
  ASCII string and returns the ASCII string.

  This function converts the content of the Unicode string Source
  to the ASCII string Destination by copying the lower 8 bits of
  each Unicode character. It returns Destination.

  The caller is responsible to make sure Destination points to a buffer with size
  equal or greater than ((StrLen (Source) + 1) * sizeof (CHAR8)) in bytes.

  If any Unicode characters in Source contain non-zero value in
  the upper 8 bits, then ASSERT().

  If Destination is NULL, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If Source and Destination overlap, then ASSERT().

  If PcdMaximumUnicodeStringLength is not zero, and Source contains
  more than PcdMaximumUnicodeStringLength Unicode characters not including
  the Null-terminator, then ASSERT().

  If PcdMaximumAsciiStringLength is not zero, and Source contains more
  than PcdMaximumAsciiStringLength Unicode characters not including the
  Null-terminator, then ASSERT().

  @param  Source        The pointer to a Null-terminated Unicode string.
  @param  Destination   The pointer to a Null-terminated ASCII string.

  @return Destination.

**/
CHAR8 *
EFIAPI
UnicodeStrToAsciiStr (
  IN      CONST CHAR16              *Source,
  OUT     CHAR8                     *Destination
  );

#endif

/**
  Convert a Null-terminated Unicode string to a Null-terminated
  ASCII string.

  This function is similar to AsciiStrCpyS.

  This function converts the content of the Unicode string Source
  to the ASCII string Destination by copying the lower 8 bits of
  each Unicode character. The function terminates the ASCII string
  Destination by appending a Null-terminator character at the end.

  The caller is responsible to make sure Destination points to a buffer with size
  equal or greater than ((StrLen (Source) + 1) * sizeof (CHAR8)) in bytes.

  If any Unicode characters in Source contain non-zero value in
  the upper 8 bits, then ASSERT().

  If Source is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Source        The pointer to a Null-terminated Unicode string.
  @param  Destination   The pointer to a Null-terminated ASCII string.
  @param  DestMax       The maximum number of Destination Ascii
                        char, including terminating null char.

  @retval RETURN_SUCCESS           String is converted.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.

**/
RETURN_STATUS
EFIAPI
UnicodeStrToAsciiStrS (
  IN      CONST CHAR16              *Source,
  OUT     CHAR8                     *Destination,
  IN      UINTN                     DestMax
  );

#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Copies one Null-terminated ASCII string to another Null-terminated ASCII
  string and returns the new ASCII string.

  This function copies the contents of the ASCII string Source to the ASCII
  string Destination, and returns Destination. If Source and Destination
  overlap, then the results are undefined.

  If Destination is NULL, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().

  @param  Destination The pointer to a Null-terminated ASCII string.
  @param  Source      The pointer to a Null-terminated ASCII string.

  @return Destination

**/
CHAR8 *
EFIAPI
AsciiStrCpy (
  OUT     CHAR8                     *Destination,
  IN      CONST CHAR8               *Source
  );


/**
  [ATTENTION] This function is deprecated for security reason.

  Copies up to a specified length one Null-terminated ASCII string to another
  Null-terminated ASCII string and returns the new ASCII string.

  This function copies the contents of the ASCII string Source to the ASCII
  string Destination, and returns Destination. At most, Length ASCII characters
  are copied from Source to Destination. If Length is 0, then Destination is
  returned unmodified. If Length is greater that the number of ASCII characters
  in Source, then Destination is padded with Null ASCII characters. If Source
  and Destination overlap, then the results are undefined.

  If Destination is NULL, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Length is greater than
  PcdMaximumAsciiStringLength, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().

  @param  Destination The pointer to a Null-terminated ASCII string.
  @param  Source      The pointer to a Null-terminated ASCII string.
  @param  Length      The maximum number of ASCII characters to copy.

  @return Destination

**/
CHAR8 *
EFIAPI
AsciiStrnCpy (
  OUT     CHAR8                     *Destination,
  IN      CONST CHAR8               *Source,
  IN      UINTN                     Length
  );
#endif

/**
  Returns the length of a Null-terminated ASCII string.

  This function returns the number of ASCII characters in the Null-terminated
  ASCII string specified by String.

  If Length > 0 and Destination is NULL, then ASSERT().
  If Length > 0 and Source is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and String contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().

  @param  String  The pointer to a Null-terminated ASCII string.

  @return The length of String.

**/
UINTN
EFIAPI
AsciiStrLen (
  IN      CONST CHAR8               *String
  );


/**
  Returns the size of a Null-terminated ASCII string in bytes, including the
  Null terminator.

  This function returns the size, in bytes, of the Null-terminated ASCII string
  specified by String.

  If String is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and String contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().

  @param  String  The pointer to a Null-terminated ASCII string.

  @return The size of String.

**/
UINTN
EFIAPI
AsciiStrSize (
  IN      CONST CHAR8               *String
  );


/**
  Compares two Null-terminated ASCII strings, and returns the difference
  between the first mismatched ASCII characters.

  This function compares the Null-terminated ASCII string FirstString to the
  Null-terminated ASCII string SecondString. If FirstString is identical to
  SecondString, then 0 is returned. Otherwise, the value returned is the first
  mismatched ASCII character in SecondString subtracted from the first
  mismatched ASCII character in FirstString.

  If FirstString is NULL, then ASSERT().
  If SecondString is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and FirstString contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and SecondString contains more
  than PcdMaximumAsciiStringLength ASCII characters not including the
  Null-terminator, then ASSERT().

  @param  FirstString   The pointer to a Null-terminated ASCII string.
  @param  SecondString  The pointer to a Null-terminated ASCII string.

  @retval ==0      FirstString is identical to SecondString.
  @retval !=0      FirstString is not identical to SecondString.

**/
INTN
EFIAPI
AsciiStrCmp (
  IN      CONST CHAR8               *FirstString,
  IN      CONST CHAR8               *SecondString
  );


/**
  Performs a case insensitive comparison of two Null-terminated ASCII strings,
  and returns the difference between the first mismatched ASCII characters.

  This function performs a case insensitive comparison of the Null-terminated
  ASCII string FirstString to the Null-terminated ASCII string SecondString. If
  FirstString is identical to SecondString, then 0 is returned. Otherwise, the
  value returned is the first mismatched lower case ASCII character in
  SecondString subtracted from the first mismatched lower case ASCII character
  in FirstString.

  If FirstString is NULL, then ASSERT().
  If SecondString is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and FirstString contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and SecondString contains more
  than PcdMaximumAsciiStringLength ASCII characters not including the
  Null-terminator, then ASSERT().

  @param  FirstString   The pointer to a Null-terminated ASCII string.
  @param  SecondString  The pointer to a Null-terminated ASCII string.

  @retval ==0    FirstString is identical to SecondString using case insensitive
                 comparisons.
  @retval !=0    FirstString is not identical to SecondString using case
                 insensitive comparisons.

**/
INTN
EFIAPI
AsciiStriCmp (
  IN      CONST CHAR8               *FirstString,
  IN      CONST CHAR8               *SecondString
  );


/**
  Compares two Null-terminated ASCII strings with maximum lengths, and returns
  the difference between the first mismatched ASCII characters.

  This function compares the Null-terminated ASCII string FirstString to the
  Null-terminated ASCII  string SecondString. At most, Length ASCII characters
  will be compared. If Length is 0, then 0 is returned. If FirstString is
  identical to SecondString, then 0 is returned. Otherwise, the value returned
  is the first mismatched ASCII character in SecondString subtracted from the
  first mismatched ASCII character in FirstString.

  If Length > 0 and FirstString is NULL, then ASSERT().
  If Length > 0 and SecondString is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Length is greater than
  PcdMaximumAsciiStringLength, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and FirstString contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and SecondString contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().

  @param  FirstString   The pointer to a Null-terminated ASCII string.
  @param  SecondString  The pointer to a Null-terminated ASCII string.
  @param  Length        The maximum number of ASCII characters for compare.

  @retval ==0       FirstString is identical to SecondString.
  @retval !=0       FirstString is not identical to SecondString.

**/
INTN
EFIAPI
AsciiStrnCmp (
  IN      CONST CHAR8               *FirstString,
  IN      CONST CHAR8               *SecondString,
  IN      UINTN                     Length
  );


#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Concatenates one Null-terminated ASCII string to another Null-terminated
  ASCII string, and returns the concatenated ASCII string.

  This function concatenates two Null-terminated ASCII strings. The contents of
  Null-terminated ASCII string Source are concatenated to the end of Null-
  terminated ASCII string Destination. The Null-terminated concatenated ASCII
  String is returned.

  If Destination is NULL, then ASSERT().
  If Source is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and Destination contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and concatenating Destination and
  Source results in a ASCII string with more than PcdMaximumAsciiStringLength
  ASCII characters, then ASSERT().

  @param  Destination The pointer to a Null-terminated ASCII string.
  @param  Source      The pointer to a Null-terminated ASCII string.

  @return Destination

**/
CHAR8 *
EFIAPI
AsciiStrCat (
  IN OUT CHAR8    *Destination,
  IN CONST CHAR8  *Source
  );


/**
  [ATTENTION] This function is deprecated for security reason.

  Concatenates up to a specified length one Null-terminated ASCII string to
  the end of another Null-terminated ASCII string, and returns the
  concatenated ASCII string.

  This function concatenates two Null-terminated ASCII strings. The contents
  of Null-terminated ASCII string Source are concatenated to the end of Null-
  terminated ASCII string Destination, and Destination is returned. At most,
  Length ASCII characters are concatenated from Source to the end of
  Destination, and Destination is always Null-terminated. If Length is 0, then
  Destination is returned unmodified. If Source and Destination overlap, then
  the results are undefined.

  If Length > 0 and Destination is NULL, then ASSERT().
  If Length > 0 and Source is NULL, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Length is greater than
  PcdMaximumAsciiStringLength, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Destination contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and concatenating Destination and
  Source results in a ASCII string with more than PcdMaximumAsciiStringLength
  ASCII characters, not including the Null-terminator, then ASSERT().

  @param  Destination The pointer to a Null-terminated ASCII string.
  @param  Source      The pointer to a Null-terminated ASCII string.
  @param  Length      The maximum number of ASCII characters to concatenate from
                      Source.

  @return Destination

**/
CHAR8 *
EFIAPI
AsciiStrnCat (
  IN OUT  CHAR8                     *Destination,
  IN      CONST CHAR8               *Source,
  IN      UINTN                     Length
  );
#endif

/**
  Returns the first occurrence of a Null-terminated ASCII sub-string
  in a Null-terminated ASCII string.

  This function scans the contents of the ASCII string specified by String
  and returns the first occurrence of SearchString. If SearchString is not
  found in String, then NULL is returned. If the length of SearchString is zero,
  then String is returned.

  If String is NULL, then ASSERT().
  If SearchString is NULL, then ASSERT().

  If PcdMaximumAsciiStringLength is not zero, and SearchString or
  String contains more than PcdMaximumAsciiStringLength Unicode characters
  not including the Null-terminator, then ASSERT().

  @param  String          The pointer to a Null-terminated ASCII string.
  @param  SearchString    The pointer to a Null-terminated ASCII string to search for.

  @retval NULL            If the SearchString does not appear in String.
  @retval others          If there is a match return the first occurrence of SearchingString.
                          If the length of SearchString is zero,return String.

**/
CHAR8 *
EFIAPI
AsciiStrStr (
  IN      CONST CHAR8               *String,
  IN      CONST CHAR8               *SearchString
  );


/**
  Convert a Null-terminated ASCII decimal string to a value of type
  UINTN.

  This function returns a value of type UINTN by interpreting the contents
  of the ASCII string String as a decimal number. The format of the input
  ASCII string String is:

                    [spaces] [decimal digits].

  The valid decimal digit character is in the range [0-9]. The function will
  ignore the pad space, which includes spaces or tab characters, before the digits.
  The running zero in the beginning of [decimal digits] will be ignored. Then, the
  function stops at the first character that is a not a valid decimal character or
  Null-terminator, whichever on comes first.

  If String has only pad spaces, then 0 is returned.
  If String has no pad spaces or valid decimal digits, then 0 is returned.
  If the number represented by String overflows according to the range defined by
  UINTN, then ASSERT().
  If String is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and String contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().

  @param  String          The pointer to a Null-terminated ASCII string.

  @retval The value translated from String.

**/
UINTN
EFIAPI
AsciiStrDecimalToUintn (
  IN      CONST CHAR8               *String
  );


/**
  Convert a Null-terminated ASCII decimal string to a value of type
  UINT64.

  This function returns a value of type UINT64 by interpreting the contents
  of the ASCII string String as a decimal number. The format of the input
  ASCII string String is:

                    [spaces] [decimal digits].

  The valid decimal digit character is in the range [0-9]. The function will
  ignore the pad space, which includes spaces or tab characters, before the digits.
  The running zero in the beginning of [decimal digits] will be ignored. Then, the
  function stops at the first character that is a not a valid decimal character or
  Null-terminator, whichever on comes first.

  If String has only pad spaces, then 0 is returned.
  If String has no pad spaces or valid decimal digits, then 0 is returned.
  If the number represented by String overflows according to the range defined by
  UINT64, then ASSERT().
  If String is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and String contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().

  @param  String          The pointer to a Null-terminated ASCII string.

  @retval Value translated from String.

**/
UINT64
EFIAPI
AsciiStrDecimalToUint64 (
  IN      CONST CHAR8               *String
  );


/**
  Convert a Null-terminated ASCII hexadecimal string to a value of type UINTN.

  This function returns a value of type UINTN by interpreting the contents of
  the ASCII string String as a hexadecimal number. The format of the input ASCII
  string String is:

                  [spaces][zeros][x][hexadecimal digits].

  The valid hexadecimal digit character is in the range [0-9], [a-f] and [A-F].
  The prefix "0x" is optional. Both "x" and "X" is allowed in "0x" prefix. If "x"
  appears in the input string, it must be prefixed with at least one 0. The function
  will ignore the pad space, which includes spaces or tab characters, before [zeros],
  [x] or [hexadecimal digits]. The running zero before [x] or [hexadecimal digits]
  will be ignored. Then, the decoding starts after [x] or the first valid hexadecimal
  digit. Then, the function stops at the first character that is a not a valid
  hexadecimal character or Null-terminator, whichever on comes first.

  If String has only pad spaces, then 0 is returned.
  If String has no leading pad spaces, leading zeros or valid hexadecimal digits, then
  0 is returned.

  If the number represented by String overflows according to the range defined by UINTN,
  then ASSERT().
  If String is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero,
  and String contains more than PcdMaximumAsciiStringLength ASCII characters not including
  the Null-terminator, then ASSERT().

  @param  String          The pointer to a Null-terminated ASCII string.

  @retval Value translated from String.

**/
UINTN
EFIAPI
AsciiStrHexToUintn (
  IN      CONST CHAR8               *String
  );


/**
  Convert a Null-terminated ASCII hexadecimal string to a value of type UINT64.

  This function returns a value of type UINT64 by interpreting the contents of
  the ASCII string String as a hexadecimal number. The format of the input ASCII
  string String is:

                  [spaces][zeros][x][hexadecimal digits].

  The valid hexadecimal digit character is in the range [0-9], [a-f] and [A-F].
  The prefix "0x" is optional. Both "x" and "X" is allowed in "0x" prefix. If "x"
  appears in the input string, it must be prefixed with at least one 0. The function
  will ignore the pad space, which includes spaces or tab characters, before [zeros],
  [x] or [hexadecimal digits]. The running zero before [x] or [hexadecimal digits]
  will be ignored. Then, the decoding starts after [x] or the first valid hexadecimal
  digit. Then, the function stops at the first character that is a not a valid
  hexadecimal character or Null-terminator, whichever on comes first.

  If String has only pad spaces, then 0 is returned.
  If String has no leading pad spaces, leading zeros or valid hexadecimal digits, then
  0 is returned.

  If the number represented by String overflows according to the range defined by UINT64,
  then ASSERT().
  If String is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero,
  and String contains more than PcdMaximumAsciiStringLength ASCII characters not including
  the Null-terminator, then ASSERT().

  @param  String          The pointer to a Null-terminated ASCII string.

  @retval Value translated from String.

**/
UINT64
EFIAPI
AsciiStrHexToUint64 (
  IN      CONST CHAR8                *String
  );

#ifndef DISABLE_NEW_DEPRECATED_INTERFACES

/**
  [ATTENTION] This function is deprecated for security reason.

  Convert one Null-terminated ASCII string to a Null-terminated
  Unicode string and returns the Unicode string.

  This function converts the contents of the ASCII string Source to the Unicode
  string Destination, and returns Destination.  The function terminates the
  Unicode string Destination by appending a Null-terminator character at the end.
  The caller is responsible to make sure Destination points to a buffer with size
  equal or greater than ((AsciiStrLen (Source) + 1) * sizeof (CHAR16)) in bytes.

  If Destination is NULL, then ASSERT().
  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero, and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters not including the Null-terminator,
  then ASSERT().
  If PcdMaximumUnicodeStringLength is not zero, and Source contains more than
  PcdMaximumUnicodeStringLength ASCII characters not including the
  Null-terminator, then ASSERT().

  @param  Source        The pointer to a Null-terminated ASCII string.
  @param  Destination   The pointer to a Null-terminated Unicode string.

  @return Destination.

**/
CHAR16 *
EFIAPI
AsciiStrToUnicodeStr (
  IN      CONST CHAR8               *Source,
  OUT     CHAR16                    *Destination
  );

#endif

/**
  Convert one Null-terminated ASCII string to a Null-terminated
  Unicode string.

  This function is similar to StrCpyS.

  This function converts the contents of the ASCII string Source to the Unicode
  string Destination. The function terminates the Unicode string Destination by
  appending a Null-terminator character at the end.

  The caller is responsible to make sure Destination points to a buffer with size
  equal or greater than ((AsciiStrLen (Source) + 1) * sizeof (CHAR16)) in bytes.

  If Destination is not aligned on a 16-bit boundary, then ASSERT().
  If an error would be returned, then the function will also ASSERT().

  If an error is returned, then the Destination is unmodified.

  @param  Source        The pointer to a Null-terminated ASCII string.
  @param  Destination   The pointer to a Null-terminated Unicode string.
  @param  DestMax       The maximum number of Destination Unicode
                        char, including terminating null char.

  @retval RETURN_SUCCESS           String is converted.
  @retval RETURN_BUFFER_TOO_SMALL  If DestMax is NOT greater than StrLen(Source).
  @retval RETURN_INVALID_PARAMETER If Destination is NULL.
                                   If Source is NULL.
                                   If PcdMaximumUnicodeStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumUnicodeStringLength.
                                   If PcdMaximumAsciiStringLength is not zero,
                                    and DestMax is greater than
                                    PcdMaximumAsciiStringLength.
                                   If DestMax is 0.
  @retval RETURN_ACCESS_DENIED     If Source and Destination overlap.

**/
RETURN_STATUS
EFIAPI
AsciiStrToUnicodeStrS (
  IN      CONST CHAR8               *Source,
  OUT     CHAR16                    *Destination,
  IN      UINTN                     DestMax
  );

/**
  Converts an 8-bit value to an 8-bit BCD value.

  Converts the 8-bit value specified by Value to BCD. The BCD value is
  returned.

  If Value >= 100, then ASSERT().

  @param  Value The 8-bit value to convert to BCD. Range 0..99.

  @return The BCD value.

**/
UINT8
EFIAPI
DecimalToBcd8 (
  IN      UINT8                     Value
  );


/**
  Converts an 8-bit BCD value to an 8-bit value.

  Converts the 8-bit BCD value specified by Value to an 8-bit value. The 8-bit
  value is returned.

  If Value >= 0xA0, then ASSERT().
  If (Value & 0x0F) >= 0x0A, then ASSERT().

  @param  Value The 8-bit BCD value to convert to an 8-bit value.

  @return The 8-bit value is returned.

**/
UINT8
EFIAPI
BcdToDecimal8 (
  IN      UINT8                     Value
  );

//
//  File Path Manipulation Functions
//

/**
  Removes the last directory or file entry in a path.

  @param[in, out] Path    The pointer to the path to modify.

  @retval FALSE     Nothing was found to remove.
  @retval TRUE      A directory or file was removed.
**/
BOOLEAN
EFIAPI
PathRemoveLastItem(
  IN OUT CHAR16 *Path
  );

/**
  Function to clean up paths.
    - Single periods in the path are removed.
    - Double periods in the path are removed along with a single parent directory.
    - Forward slashes L'/' are converted to backward slashes L'\'.

  This will be done inline and the existing buffer may be larger than required
  upon completion.

  @param[in] Path       The pointer to the string containing the path.

  @return       Returns Path, otherwise returns NULL to indicate that an error has occurred.
**/
CHAR16*
EFIAPI
PathCleanUpDirectories(
  IN CHAR16 *Path
  );

//
// Linked List Functions and Macros
//

/**
  Initializes the head node of a doubly linked list that is declared as a
  global variable in a module.

  Initializes the forward and backward links of a new linked list. After
  initializing a linked list with this macro, the other linked list functions
  may be used to add and remove nodes from the linked list. This macro results
  in smaller executables by initializing the linked list in the data section,
  instead if calling the InitializeListHead() function to perform the
  equivalent operation.

  @param  ListHead  The head note of a list to initialize.

**/
#define INITIALIZE_LIST_HEAD_VARIABLE(ListHead)  {&(ListHead), &(ListHead)}


/**
  Initializes the head node of a doubly linked list, and returns the pointer to
  the head node of the doubly linked list.

  Initializes the forward and backward links of a new linked list. After
  initializing a linked list with this function, the other linked list
  functions may be used to add and remove nodes from the linked list. It is up
  to the caller of this function to allocate the memory for ListHead.

  If ListHead is NULL, then ASSERT().

  @param  ListHead  A pointer to the head node of a new doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
EFIAPI
InitializeListHead (
  IN OUT  LIST_ENTRY                *ListHead
  );


/**
  Adds a node to the beginning of a doubly linked list, and returns the pointer
  to the head node of the doubly linked list.

  Adds the node Entry at the beginning of the doubly linked list denoted by
  ListHead, and returns ListHead.

  If ListHead is NULL, then ASSERT().
  If Entry is NULL, then ASSERT().
  If ListHead was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and prior to insertion the number
  of nodes in ListHead, including the ListHead node, is greater than or
  equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.
  @param  Entry     A pointer to a node that is to be inserted at the beginning
                    of a doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
EFIAPI
InsertHeadList (
  IN OUT  LIST_ENTRY                *ListHead,
  IN OUT  LIST_ENTRY                *Entry
  );


/**
  Adds a node to the end of a doubly linked list, and returns the pointer to
  the head node of the doubly linked list.

  Adds the node Entry to the end of the doubly linked list denoted by ListHead,
  and returns ListHead.

  If ListHead is NULL, then ASSERT().
  If Entry is NULL, then ASSERT().
  If ListHead was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and prior to insertion the number
  of nodes in ListHead, including the ListHead node, is greater than or
  equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.
  @param  Entry     A pointer to a node that is to be added at the end of the
                    doubly linked list.

  @return ListHead

**/
LIST_ENTRY *
EFIAPI
InsertTailList (
  IN OUT  LIST_ENTRY                *ListHead,
  IN OUT  LIST_ENTRY                *Entry
  );


/**
  Retrieves the first node of a doubly linked list.

  Returns the first node of a doubly linked list.  List must have been
  initialized with INTIALIZE_LIST_HEAD_VARIABLE() or InitializeListHead().
  If List is empty, then List is returned.

  If List is NULL, then ASSERT().
  If List was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes
  in List, including the List node, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().

  @param  List  A pointer to the head node of a doubly linked list.

  @return The first node of a doubly linked list.
  @retval List  The list is empty.

**/
LIST_ENTRY *
EFIAPI
GetFirstNode (
  IN      CONST LIST_ENTRY          *List
  );


/**
  Retrieves the next node of a doubly linked list.

  Returns the node of a doubly linked list that follows Node.
  List must have been initialized with INTIALIZE_LIST_HEAD_VARIABLE()
  or InitializeListHead().  If List is empty, then List is returned.

  If List is NULL, then ASSERT().
  If Node is NULL, then ASSERT().
  If List was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and List contains more than
  PcdMaximumLinkedListLength nodes, then ASSERT().
  If PcdVerifyNodeInList is TRUE and Node is not a node in List, then ASSERT().

  @param  List  A pointer to the head node of a doubly linked list.
  @param  Node  A pointer to a node in the doubly linked list.

  @return The pointer to the next node if one exists. Otherwise List is returned.

**/
LIST_ENTRY *
EFIAPI
GetNextNode (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );


/**
  Retrieves the previous node of a doubly linked list.

  Returns the node of a doubly linked list that precedes Node.
  List must have been initialized with INTIALIZE_LIST_HEAD_VARIABLE()
  or InitializeListHead().  If List is empty, then List is returned.

  If List is NULL, then ASSERT().
  If Node is NULL, then ASSERT().
  If List was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and List contains more than
  PcdMaximumLinkedListLength nodes, then ASSERT().
  If PcdVerifyNodeInList is TRUE and Node is not a node in List, then ASSERT().

  @param  List  A pointer to the head node of a doubly linked list.
  @param  Node  A pointer to a node in the doubly linked list.

  @return The pointer to the previous node if one exists. Otherwise List is returned.

**/
LIST_ENTRY *
EFIAPI
GetPreviousNode (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );


/**
  Checks to see if a doubly linked list is empty or not.

  Checks to see if the doubly linked list is empty. If the linked list contains
  zero nodes, this function returns TRUE. Otherwise, it returns FALSE.

  If ListHead is NULL, then ASSERT().
  If ListHead was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes
  in List, including the List node, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().

  @param  ListHead  A pointer to the head node of a doubly linked list.

  @retval TRUE  The linked list is empty.
  @retval FALSE The linked list is not empty.

**/
BOOLEAN
EFIAPI
IsListEmpty (
  IN      CONST LIST_ENTRY          *ListHead
  );


/**
  Determines if a node in a doubly linked list is the head node of a the same
  doubly linked list.  This function is typically used to terminate a loop that
  traverses all the nodes in a doubly linked list starting with the head node.

  Returns TRUE if Node is equal to List.  Returns FALSE if Node is one of the
  nodes in the doubly linked list specified by List.  List must have been
  initialized with INTIALIZE_LIST_HEAD_VARIABLE() or InitializeListHead().

  If List is NULL, then ASSERT().
  If Node is NULL, then ASSERT().
  If List was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or InitializeListHead(),
  then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes
  in List, including the List node, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().
  If PcdVerifyNodeInList is TRUE and Node is not a node in List the and Node is not equal
  to List, then ASSERT().

  @param  List  A pointer to the head node of a doubly linked list.
  @param  Node  A pointer to a node in the doubly linked list.

  @retval TRUE  Node is the head of the doubly-linked list pointed by List.
  @retval FALSE Node is not the head of the doubly-linked list pointed by List.

**/
BOOLEAN
EFIAPI
IsNull (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );


/**
  Determines if a node the last node in a doubly linked list.

  Returns TRUE if Node is the last node in the doubly linked list specified by
  List. Otherwise, FALSE is returned. List must have been initialized with
  INTIALIZE_LIST_HEAD_VARIABLE() or InitializeListHead().

  If List is NULL, then ASSERT().
  If Node is NULL, then ASSERT().
  If List was not initialized with INTIALIZE_LIST_HEAD_VARIABLE() or
  InitializeListHead(), then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes
  in List, including the List node, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().
  If PcdVerifyNodeInList is TRUE and Node is not a node in List, then ASSERT().

  @param  List  A pointer to the head node of a doubly linked list.
  @param  Node  A pointer to a node in the doubly linked list.

  @retval TRUE  Node is the last node in the linked list.
  @retval FALSE Node is not the last node in the linked list.

**/
BOOLEAN
EFIAPI
IsNodeAtEnd (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );


/**
  Swaps the location of two nodes in a doubly linked list, and returns the
  first node after the swap.

  If FirstEntry is identical to SecondEntry, then SecondEntry is returned.
  Otherwise, the location of the FirstEntry node is swapped with the location
  of the SecondEntry node in a doubly linked list. SecondEntry must be in the
  same double linked list as FirstEntry and that double linked list must have
  been initialized with INTIALIZE_LIST_HEAD_VARIABLE() or InitializeListHead().
  SecondEntry is returned after the nodes are swapped.

  If FirstEntry is NULL, then ASSERT().
  If SecondEntry is NULL, then ASSERT().
  If PcdVerifyNodeInList is TRUE and SecondEntry and FirstEntry are not in the
  same linked list, then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes in the
  linked list containing the FirstEntry and SecondEntry nodes, including
  the FirstEntry and SecondEntry nodes, is greater than or equal to
  PcdMaximumLinkedListLength, then ASSERT().

  @param  FirstEntry  A pointer to a node in a linked list.
  @param  SecondEntry A pointer to another node in the same linked list.

  @return SecondEntry.

**/
LIST_ENTRY *
EFIAPI
SwapListEntries (
  IN OUT  LIST_ENTRY                *FirstEntry,
  IN OUT  LIST_ENTRY                *SecondEntry
  );


/**
  Removes a node from a doubly linked list, and returns the node that follows
  the removed node.

  Removes the node Entry from a doubly linked list. It is up to the caller of
  this function to release the memory used by this node if that is required. On
  exit, the node following Entry in the doubly linked list is returned. If
  Entry is the only node in the linked list, then the head node of the linked
  list is returned.

  If Entry is NULL, then ASSERT().
  If Entry is the head node of an empty list, then ASSERT().
  If PcdMaximumLinkedListLength is not zero, and the number of nodes in the
  linked list containing Entry, including the Entry node, is greater than
  or equal to PcdMaximumLinkedListLength, then ASSERT().

  @param  Entry A pointer to a node in a linked list.

  @return Entry.

**/
LIST_ENTRY *
EFIAPI
RemoveEntryList (
  IN      CONST LIST_ENTRY          *Entry
  );

//
// Math Services
//

/**
  Shifts a 64-bit integer left between 0 and 63 bits. The low bits are filled
  with zeros. The shifted value is returned.

  This function shifts the 64-bit value Operand to the left by Count bits. The
  low Count bits are set to zero. The shifted value is returned.

  If Count is greater than 63, then ASSERT().

  @param  Operand The 64-bit operand to shift left.
  @param  Count   The number of bits to shift left.

  @return Operand << Count.

**/
UINT64
EFIAPI
LShiftU64 (
  IN      UINT64                    Operand,
  IN      UINTN                     Count
  );


/**
  Shifts a 64-bit integer right between 0 and 63 bits. This high bits are
  filled with zeros. The shifted value is returned.

  This function shifts the 64-bit value Operand to the right by Count bits. The
  high Count bits are set to zero. The shifted value is returned.

  If Count is greater than 63, then ASSERT().

  @param  Operand The 64-bit operand to shift right.
  @param  Count   The number of bits to shift right.

  @return Operand >> Count

**/
UINT64
EFIAPI
RShiftU64 (
  IN      UINT64                    Operand,
  IN      UINTN                     Count
  );


/**
  Shifts a 64-bit integer right between 0 and 63 bits. The high bits are filled
  with original integer's bit 63. The shifted value is returned.

  This function shifts the 64-bit value Operand to the right by Count bits. The
  high Count bits are set to bit 63 of Operand.  The shifted value is returned.

  If Count is greater than 63, then ASSERT().

  @param  Operand The 64-bit operand to shift right.
  @param  Count   The number of bits to shift right.

  @return Operand >> Count

**/
UINT64
EFIAPI
ARShiftU64 (
  IN      UINT64                    Operand,
  IN      UINTN                     Count
  );


/**
  Rotates a 32-bit integer left between 0 and 31 bits, filling the low bits
  with the high bits that were rotated.

  This function rotates the 32-bit value Operand to the left by Count bits. The
  low Count bits are fill with the high Count bits of Operand. The rotated
  value is returned.

  If Count is greater than 31, then ASSERT().

  @param  Operand The 32-bit operand to rotate left.
  @param  Count   The number of bits to rotate left.

  @return Operand << Count

**/
UINT32
EFIAPI
LRotU32 (
  IN      UINT32                    Operand,
  IN      UINTN                     Count
  );


/**
  Rotates a 32-bit integer right between 0 and 31 bits, filling the high bits
  with the low bits that were rotated.

  This function rotates the 32-bit value Operand to the right by Count bits.
  The high Count bits are fill with the low Count bits of Operand. The rotated
  value is returned.

  If Count is greater than 31, then ASSERT().

  @param  Operand The 32-bit operand to rotate right.
  @param  Count   The number of bits to rotate right.

  @return Operand >> Count

**/
UINT32
EFIAPI
RRotU32 (
  IN      UINT32                    Operand,
  IN      UINTN                     Count
  );


/**
  Rotates a 64-bit integer left between 0 and 63 bits, filling the low bits
  with the high bits that were rotated.

  This function rotates the 64-bit value Operand to the left by Count bits. The
  low Count bits are fill with the high Count bits of Operand. The rotated
  value is returned.

  If Count is greater than 63, then ASSERT().

  @param  Operand The 64-bit operand to rotate left.
  @param  Count   The number of bits to rotate left.

  @return Operand << Count

**/
UINT64
EFIAPI
LRotU64 (
  IN      UINT64                    Operand,
  IN      UINTN                     Count
  );


/**
  Rotates a 64-bit integer right between 0 and 63 bits, filling the high bits
  with the high low bits that were rotated.

  This function rotates the 64-bit value Operand to the right by Count bits.
  The high Count bits are fill with the low Count bits of Operand. The rotated
  value is returned.

  If Count is greater than 63, then ASSERT().

  @param  Operand The 64-bit operand to rotate right.
  @param  Count   The number of bits to rotate right.

  @return Operand >> Count

**/
UINT64
EFIAPI
RRotU64 (
  IN      UINT64                    Operand,
  IN      UINTN                     Count
  );


/**
  Returns the bit position of the lowest bit set in a 32-bit value.

  This function computes the bit position of the lowest bit set in the 32-bit
  value specified by Operand. If Operand is zero, then -1 is returned.
  Otherwise, a value between 0 and 31 is returned.

  @param  Operand The 32-bit operand to evaluate.

  @retval 0..31  The lowest bit set in Operand was found.
  @retval -1    Operand is zero.

**/
INTN
EFIAPI
LowBitSet32 (
  IN      UINT32                    Operand
  );


/**
  Returns the bit position of the lowest bit set in a 64-bit value.

  This function computes the bit position of the lowest bit set in the 64-bit
  value specified by Operand. If Operand is zero, then -1 is returned.
  Otherwise, a value between 0 and 63 is returned.

  @param  Operand The 64-bit operand to evaluate.

  @retval 0..63  The lowest bit set in Operand was found.
  @retval -1    Operand is zero.


**/
INTN
EFIAPI
LowBitSet64 (
  IN      UINT64                    Operand
  );


/**
  Returns the bit position of the highest bit set in a 32-bit value. Equivalent
  to log2(x).

  This function computes the bit position of the highest bit set in the 32-bit
  value specified by Operand. If Operand is zero, then -1 is returned.
  Otherwise, a value between 0 and 31 is returned.

  @param  Operand The 32-bit operand to evaluate.

  @retval 0..31  Position of the highest bit set in Operand if found.
  @retval -1    Operand is zero.

**/
INTN
EFIAPI
HighBitSet32 (
  IN      UINT32                    Operand
  );


/**
  Returns the bit position of the highest bit set in a 64-bit value. Equivalent
  to log2(x).

  This function computes the bit position of the highest bit set in the 64-bit
  value specified by Operand. If Operand is zero, then -1 is returned.
  Otherwise, a value between 0 and 63 is returned.

  @param  Operand The 64-bit operand to evaluate.

  @retval 0..63   Position of the highest bit set in Operand if found.
  @retval -1     Operand is zero.

**/
INTN
EFIAPI
HighBitSet64 (
  IN      UINT64                    Operand
  );


/**
  Returns the value of the highest bit set in a 32-bit value. Equivalent to
  1 << log2(x).

  This function computes the value of the highest bit set in the 32-bit value
  specified by Operand. If Operand is zero, then zero is returned.

  @param  Operand The 32-bit operand to evaluate.

  @return 1 << HighBitSet32(Operand)
  @retval 0 Operand is zero.

**/
UINT32
EFIAPI
GetPowerOfTwo32 (
  IN      UINT32                    Operand
  );


/**
  Returns the value of the highest bit set in a 64-bit value. Equivalent to
  1 << log2(x).

  This function computes the value of the highest bit set in the 64-bit value
  specified by Operand. If Operand is zero, then zero is returned.

  @param  Operand The 64-bit operand to evaluate.

  @return 1 << HighBitSet64(Operand)
  @retval 0 Operand is zero.

**/
UINT64
EFIAPI
GetPowerOfTwo64 (
  IN      UINT64                    Operand
  );


/**
  Switches the endianness of a 16-bit integer.

  This function swaps the bytes in a 16-bit unsigned value to switch the value
  from little endian to big endian or vice versa. The byte swapped value is
  returned.

  @param  Value A 16-bit unsigned value.

  @return The byte swapped Value.

**/
UINT16
EFIAPI
SwapBytes16 (
  IN      UINT16                    Value
  );


/**
  Switches the endianness of a 32-bit integer.

  This function swaps the bytes in a 32-bit unsigned value to switch the value
  from little endian to big endian or vice versa. The byte swapped value is
  returned.

  @param  Value A 32-bit unsigned value.

  @return The byte swapped Value.

**/
UINT32
EFIAPI
SwapBytes32 (
  IN      UINT32                    Value
  );


/**
  Switches the endianness of a 64-bit integer.

  This function swaps the bytes in a 64-bit unsigned value to switch the value
  from little endian to big endian or vice versa. The byte swapped value is
  returned.

  @param  Value A 64-bit unsigned value.

  @return The byte swapped Value.

**/
UINT64
EFIAPI
SwapBytes64 (
  IN      UINT64                    Value
  );


/**
  Multiples a 64-bit unsigned integer by a 32-bit unsigned integer and
  generates a 64-bit unsigned result.

  This function multiples the 64-bit unsigned value Multiplicand by the 32-bit
  unsigned value Multiplier and generates a 64-bit unsigned result. This 64-
  bit unsigned result is returned.

  @param  Multiplicand  A 64-bit unsigned value.
  @param  Multiplier    A 32-bit unsigned value.

  @return Multiplicand * Multiplier

**/
UINT64
EFIAPI
MultU64x32 (
  IN      UINT64                    Multiplicand,
  IN      UINT32                    Multiplier
  );


/**
  Multiples a 64-bit unsigned integer by a 64-bit unsigned integer and
  generates a 64-bit unsigned result.

  This function multiples the 64-bit unsigned value Multiplicand by the 64-bit
  unsigned value Multiplier and generates a 64-bit unsigned result. This 64-
  bit unsigned result is returned.

  @param  Multiplicand  A 64-bit unsigned value.
  @param  Multiplier    A 64-bit unsigned value.

  @return Multiplicand * Multiplier.

**/
UINT64
EFIAPI
MultU64x64 (
  IN      UINT64                    Multiplicand,
  IN      UINT64                    Multiplier
  );


/**
  Multiples a 64-bit signed integer by a 64-bit signed integer and generates a
  64-bit signed result.

  This function multiples the 64-bit signed value Multiplicand by the 64-bit
  signed value Multiplier and generates a 64-bit signed result. This 64-bit
  signed result is returned.

  @param  Multiplicand  A 64-bit signed value.
  @param  Multiplier    A 64-bit signed value.

  @return Multiplicand * Multiplier

**/
INT64
EFIAPI
MultS64x64 (
  IN      INT64                     Multiplicand,
  IN      INT64                     Multiplier
  );


/**
  Divides a 64-bit unsigned integer by a 32-bit unsigned integer and generates
  a 64-bit unsigned result.

  This function divides the 64-bit unsigned value Dividend by the 32-bit
  unsigned value Divisor and generates a 64-bit unsigned quotient. This
  function returns the 64-bit unsigned quotient.

  If Divisor is 0, then ASSERT().

  @param  Dividend  A 64-bit unsigned value.
  @param  Divisor   A 32-bit unsigned value.

  @return Dividend / Divisor.

**/
UINT64
EFIAPI
DivU64x32 (
  IN      UINT64                    Dividend,
  IN      UINT32                    Divisor
  );


/**
  Divides a 64-bit unsigned integer by a 32-bit unsigned integer and generates
  a 32-bit unsigned remainder.

  This function divides the 64-bit unsigned value Dividend by the 32-bit
  unsigned value Divisor and generates a 32-bit remainder. This function
  returns the 32-bit unsigned remainder.

  If Divisor is 0, then ASSERT().

  @param  Dividend  A 64-bit unsigned value.
  @param  Divisor   A 32-bit unsigned value.

  @return Dividend % Divisor.

**/
UINT32
EFIAPI
ModU64x32 (
  IN      UINT64                    Dividend,
  IN      UINT32                    Divisor
  );


/**
  Divides a 64-bit unsigned integer by a 32-bit unsigned integer and generates
  a 64-bit unsigned result and an optional 32-bit unsigned remainder.

  This function divides the 64-bit unsigned value Dividend by the 32-bit
  unsigned value Divisor and generates a 64-bit unsigned quotient. If Remainder
  is not NULL, then the 32-bit unsigned remainder is returned in Remainder.
  This function returns the 64-bit unsigned quotient.

  If Divisor is 0, then ASSERT().

  @param  Dividend  A 64-bit unsigned value.
  @param  Divisor   A 32-bit unsigned value.
  @param  Remainder A pointer to a 32-bit unsigned value. This parameter is
                    optional and may be NULL.

  @return Dividend / Divisor.

**/
UINT64
EFIAPI
DivU64x32Remainder (
  IN      UINT64                    Dividend,
  IN      UINT32                    Divisor,
  OUT     UINT32                    *Remainder  OPTIONAL
  );


/**
  Divides a 64-bit unsigned integer by a 64-bit unsigned integer and generates
  a 64-bit unsigned result and an optional 64-bit unsigned remainder.

  This function divides the 64-bit unsigned value Dividend by the 64-bit
  unsigned value Divisor and generates a 64-bit unsigned quotient. If Remainder
  is not NULL, then the 64-bit unsigned remainder is returned in Remainder.
  This function returns the 64-bit unsigned quotient.

  If Divisor is 0, then ASSERT().

  @param  Dividend  A 64-bit unsigned value.
  @param  Divisor   A 64-bit unsigned value.
  @param  Remainder A pointer to a 64-bit unsigned value. This parameter is
                    optional and may be NULL.

  @return Dividend / Divisor.

**/
UINT64
EFIAPI
DivU64x64Remainder (
  IN      UINT64                    Dividend,
  IN      UINT64                    Divisor,
  OUT     UINT64                    *Remainder  OPTIONAL
  );


/**
  Divides a 64-bit signed integer by a 64-bit signed integer and generates a
  64-bit signed result and a optional 64-bit signed remainder.

  This function divides the 64-bit signed value Dividend by the 64-bit signed
  value Divisor and generates a 64-bit signed quotient. If Remainder is not
  NULL, then the 64-bit signed remainder is returned in Remainder. This
  function returns the 64-bit signed quotient.

  It is the caller's responsibility to not call this function with a Divisor of 0.
  If Divisor is 0, then the quotient and remainder should be assumed to be
  the largest negative integer.

  If Divisor is 0, then ASSERT().

  @param  Dividend  A 64-bit signed value.
  @param  Divisor   A 64-bit signed value.
  @param  Remainder A pointer to a 64-bit signed value. This parameter is
                    optional and may be NULL.

  @return Dividend / Divisor.

**/
INT64
EFIAPI
DivS64x64Remainder (
  IN      INT64                     Dividend,
  IN      INT64                     Divisor,
  OUT     INT64                     *Remainder  OPTIONAL
  );


/**
  Reads a 16-bit value from memory that may be unaligned.

  This function returns the 16-bit value pointed to by Buffer. The function
  guarantees that the read operation does not produce an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 16-bit value that may be unaligned.

  @return The 16-bit value read from Buffer.

**/
UINT16
EFIAPI
ReadUnaligned16 (
  IN CONST UINT16              *Buffer
  );


/**
  Writes a 16-bit value to memory that may be unaligned.

  This function writes the 16-bit value specified by Value to Buffer. Value is
  returned. The function guarantees that the write operation does not produce
  an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 16-bit value that may be unaligned.
  @param  Value   16-bit value to write to Buffer.

  @return The 16-bit value to write to Buffer.

**/
UINT16
EFIAPI
WriteUnaligned16 (
  OUT UINT16                    *Buffer,
  IN  UINT16                    Value
  );


/**
  Reads a 24-bit value from memory that may be unaligned.

  This function returns the 24-bit value pointed to by Buffer. The function
  guarantees that the read operation does not produce an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 24-bit value that may be unaligned.

  @return The 24-bit value read from Buffer.

**/
UINT32
EFIAPI
ReadUnaligned24 (
  IN CONST UINT32              *Buffer
  );


/**
  Writes a 24-bit value to memory that may be unaligned.

  This function writes the 24-bit value specified by Value to Buffer. Value is
  returned. The function guarantees that the write operation does not produce
  an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 24-bit value that may be unaligned.
  @param  Value   24-bit value to write to Buffer.

  @return The 24-bit value to write to Buffer.

**/
UINT32
EFIAPI
WriteUnaligned24 (
  OUT UINT32                    *Buffer,
  IN  UINT32                    Value
  );


/**
  Reads a 32-bit value from memory that may be unaligned.

  This function returns the 32-bit value pointed to by Buffer. The function
  guarantees that the read operation does not produce an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 32-bit value that may be unaligned.

  @return The 32-bit value read from Buffer.

**/
UINT32
EFIAPI
ReadUnaligned32 (
  IN CONST UINT32              *Buffer
  );


/**
  Writes a 32-bit value to memory that may be unaligned.

  This function writes the 32-bit value specified by Value to Buffer. Value is
  returned. The function guarantees that the write operation does not produce
  an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 32-bit value that may be unaligned.
  @param  Value   32-bit value to write to Buffer.

  @return The 32-bit value to write to Buffer.

**/
UINT32
EFIAPI
WriteUnaligned32 (
  OUT UINT32                    *Buffer,
  IN  UINT32                    Value
  );


/**
  Reads a 64-bit value from memory that may be unaligned.

  This function returns the 64-bit value pointed to by Buffer. The function
  guarantees that the read operation does not produce an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 64-bit value that may be unaligned.

  @return The 64-bit value read from Buffer.

**/
UINT64
EFIAPI
ReadUnaligned64 (
  IN CONST UINT64              *Buffer
  );


/**
  Writes a 64-bit value to memory that may be unaligned.

  This function writes the 64-bit value specified by Value to Buffer. Value is
  returned. The function guarantees that the write operation does not produce
  an alignment fault.

  If the Buffer is NULL, then ASSERT().

  @param  Buffer  The pointer to a 64-bit value that may be unaligned.
  @param  Value   64-bit value to write to Buffer.

  @return The 64-bit value to write to Buffer.

**/
UINT64
EFIAPI
WriteUnaligned64 (
  OUT UINT64                    *Buffer,
  IN  UINT64                    Value
  );


//
// Bit Field Functions
//

/**
  Returns a bit field from an 8-bit value.

  Returns the bitfield specified by the StartBit and the EndBit from Operand.

  If 8-bit operations are not supported, then ASSERT().
  If StartBit is greater than 7, then ASSERT().
  If EndBit is greater than 7, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..7.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..7.

  @return The bit field read.

**/
UINT8
EFIAPI
BitFieldRead8 (
  IN      UINT8                     Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit
  );


/**
  Writes a bit field to an 8-bit value, and returns the result.

  Writes Value to the bit field specified by the StartBit and the EndBit in
  Operand. All other bits in Operand are preserved. The new 8-bit value is
  returned.

  If 8-bit operations are not supported, then ASSERT().
  If StartBit is greater than 7, then ASSERT().
  If EndBit is greater than 7, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If Value is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..7.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..7.
  @param  Value     New value of the bit field.

  @return The new 8-bit value.

**/
UINT8
EFIAPI
BitFieldWrite8 (
  IN      UINT8                     Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT8                     Value
  );


/**
  Reads a bit field from an 8-bit value, performs a bitwise OR, and returns the
  result.

  Performs a bitwise OR between the bit field specified by StartBit
  and EndBit in Operand and the value specified by OrData. All other bits in
  Operand are preserved. The new 8-bit value is returned.

  If 8-bit operations are not supported, then ASSERT().
  If StartBit is greater than 7, then ASSERT().
  If EndBit is greater than 7, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..7.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..7.
  @param  OrData    The value to OR with the read value from the value

  @return The new 8-bit value.

**/
UINT8
EFIAPI
BitFieldOr8 (
  IN      UINT8                     Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT8                     OrData
  );


/**
  Reads a bit field from an 8-bit value, performs a bitwise AND, and returns
  the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData. All other bits in Operand are
  preserved. The new 8-bit value is returned.

  If 8-bit operations are not supported, then ASSERT().
  If StartBit is greater than 7, then ASSERT().
  If EndBit is greater than 7, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..7.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..7.
  @param  AndData   The value to AND with the read value from the value.

  @return The new 8-bit value.

**/
UINT8
EFIAPI
BitFieldAnd8 (
  IN      UINT8                     Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT8                     AndData
  );


/**
  Reads a bit field from an 8-bit value, performs a bitwise AND followed by a
  bitwise OR, and returns the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData, followed by a bitwise
  OR with value specified by OrData. All other bits in Operand are
  preserved. The new 8-bit value is returned.

  If 8-bit operations are not supported, then ASSERT().
  If StartBit is greater than 7, then ASSERT().
  If EndBit is greater than 7, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..7.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..7.
  @param  AndData   The value to AND with the read value from the value.
  @param  OrData    The value to OR with the result of the AND operation.

  @return The new 8-bit value.

**/
UINT8
EFIAPI
BitFieldAndThenOr8 (
  IN      UINT8                     Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT8                     AndData,
  IN      UINT8                     OrData
  );


/**
  Returns a bit field from a 16-bit value.

  Returns the bitfield specified by the StartBit and the EndBit from Operand.

  If 16-bit operations are not supported, then ASSERT().
  If StartBit is greater than 15, then ASSERT().
  If EndBit is greater than 15, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..15.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..15.

  @return The bit field read.

**/
UINT16
EFIAPI
BitFieldRead16 (
  IN      UINT16                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit
  );


/**
  Writes a bit field to a 16-bit value, and returns the result.

  Writes Value to the bit field specified by the StartBit and the EndBit in
  Operand. All other bits in Operand are preserved. The new 16-bit value is
  returned.

  If 16-bit operations are not supported, then ASSERT().
  If StartBit is greater than 15, then ASSERT().
  If EndBit is greater than 15, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If Value is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..15.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..15.
  @param  Value     New value of the bit field.

  @return The new 16-bit value.

**/
UINT16
EFIAPI
BitFieldWrite16 (
  IN      UINT16                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT16                    Value
  );


/**
  Reads a bit field from a 16-bit value, performs a bitwise OR, and returns the
  result.

  Performs a bitwise OR between the bit field specified by StartBit
  and EndBit in Operand and the value specified by OrData. All other bits in
  Operand are preserved. The new 16-bit value is returned.

  If 16-bit operations are not supported, then ASSERT().
  If StartBit is greater than 15, then ASSERT().
  If EndBit is greater than 15, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..15.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..15.
  @param  OrData    The value to OR with the read value from the value

  @return The new 16-bit value.

**/
UINT16
EFIAPI
BitFieldOr16 (
  IN      UINT16                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT16                    OrData
  );


/**
  Reads a bit field from a 16-bit value, performs a bitwise AND, and returns
  the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData. All other bits in Operand are
  preserved. The new 16-bit value is returned.

  If 16-bit operations are not supported, then ASSERT().
  If StartBit is greater than 15, then ASSERT().
  If EndBit is greater than 15, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..15.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..15.
  @param  AndData   The value to AND with the read value from the value

  @return The new 16-bit value.

**/
UINT16
EFIAPI
BitFieldAnd16 (
  IN      UINT16                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT16                    AndData
  );


/**
  Reads a bit field from a 16-bit value, performs a bitwise AND followed by a
  bitwise OR, and returns the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData, followed by a bitwise
  OR with value specified by OrData. All other bits in Operand are
  preserved. The new 16-bit value is returned.

  If 16-bit operations are not supported, then ASSERT().
  If StartBit is greater than 15, then ASSERT().
  If EndBit is greater than 15, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..15.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..15.
  @param  AndData   The value to AND with the read value from the value.
  @param  OrData    The value to OR with the result of the AND operation.

  @return The new 16-bit value.

**/
UINT16
EFIAPI
BitFieldAndThenOr16 (
  IN      UINT16                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT16                    AndData,
  IN      UINT16                    OrData
  );


/**
  Returns a bit field from a 32-bit value.

  Returns the bitfield specified by the StartBit and the EndBit from Operand.

  If 32-bit operations are not supported, then ASSERT().
  If StartBit is greater than 31, then ASSERT().
  If EndBit is greater than 31, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..31.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..31.

  @return The bit field read.

**/
UINT32
EFIAPI
BitFieldRead32 (
  IN      UINT32                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit
  );


/**
  Writes a bit field to a 32-bit value, and returns the result.

  Writes Value to the bit field specified by the StartBit and the EndBit in
  Operand. All other bits in Operand are preserved. The new 32-bit value is
  returned.

  If 32-bit operations are not supported, then ASSERT().
  If StartBit is greater than 31, then ASSERT().
  If EndBit is greater than 31, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If Value is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..31.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..31.
  @param  Value     New value of the bit field.

  @return The new 32-bit value.

**/
UINT32
EFIAPI
BitFieldWrite32 (
  IN      UINT32                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT32                    Value
  );


/**
  Reads a bit field from a 32-bit value, performs a bitwise OR, and returns the
  result.

  Performs a bitwise OR between the bit field specified by StartBit
  and EndBit in Operand and the value specified by OrData. All other bits in
  Operand are preserved. The new 32-bit value is returned.

  If 32-bit operations are not supported, then ASSERT().
  If StartBit is greater than 31, then ASSERT().
  If EndBit is greater than 31, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..31.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..31.
  @param  OrData    The value to OR with the read value from the value.

  @return The new 32-bit value.

**/
UINT32
EFIAPI
BitFieldOr32 (
  IN      UINT32                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT32                    OrData
  );


/**
  Reads a bit field from a 32-bit value, performs a bitwise AND, and returns
  the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData. All other bits in Operand are
  preserved. The new 32-bit value is returned.

  If 32-bit operations are not supported, then ASSERT().
  If StartBit is greater than 31, then ASSERT().
  If EndBit is greater than 31, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..31.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..31.
  @param  AndData   The value to AND with the read value from the value

  @return The new 32-bit value.

**/
UINT32
EFIAPI
BitFieldAnd32 (
  IN      UINT32                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT32                    AndData
  );


/**
  Reads a bit field from a 32-bit value, performs a bitwise AND followed by a
  bitwise OR, and returns the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData, followed by a bitwise
  OR with value specified by OrData. All other bits in Operand are
  preserved. The new 32-bit value is returned.

  If 32-bit operations are not supported, then ASSERT().
  If StartBit is greater than 31, then ASSERT().
  If EndBit is greater than 31, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..31.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..31.
  @param  AndData   The value to AND with the read value from the value.
  @param  OrData    The value to OR with the result of the AND operation.

  @return The new 32-bit value.

**/
UINT32
EFIAPI
BitFieldAndThenOr32 (
  IN      UINT32                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT32                    AndData,
  IN      UINT32                    OrData
  );


/**
  Returns a bit field from a 64-bit value.

  Returns the bitfield specified by the StartBit and the EndBit from Operand.

  If 64-bit operations are not supported, then ASSERT().
  If StartBit is greater than 63, then ASSERT().
  If EndBit is greater than 63, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..63.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..63.

  @return The bit field read.

**/
UINT64
EFIAPI
BitFieldRead64 (
  IN      UINT64                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit
  );


/**
  Writes a bit field to a 64-bit value, and returns the result.

  Writes Value to the bit field specified by the StartBit and the EndBit in
  Operand. All other bits in Operand are preserved. The new 64-bit value is
  returned.

  If 64-bit operations are not supported, then ASSERT().
  If StartBit is greater than 63, then ASSERT().
  If EndBit is greater than 63, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If Value is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..63.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..63.
  @param  Value     New value of the bit field.

  @return The new 64-bit value.

**/
UINT64
EFIAPI
BitFieldWrite64 (
  IN      UINT64                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT64                    Value
  );


/**
  Reads a bit field from a 64-bit value, performs a bitwise OR, and returns the
  result.

  Performs a bitwise OR between the bit field specified by StartBit
  and EndBit in Operand and the value specified by OrData. All other bits in
  Operand are preserved. The new 64-bit value is returned.

  If 64-bit operations are not supported, then ASSERT().
  If StartBit is greater than 63, then ASSERT().
  If EndBit is greater than 63, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..63.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..63.
  @param  OrData    The value to OR with the read value from the value

  @return The new 64-bit value.

**/
UINT64
EFIAPI
BitFieldOr64 (
  IN      UINT64                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT64                    OrData
  );


/**
  Reads a bit field from a 64-bit value, performs a bitwise AND, and returns
  the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData. All other bits in Operand are
  preserved. The new 64-bit value is returned.

  If 64-bit operations are not supported, then ASSERT().
  If StartBit is greater than 63, then ASSERT().
  If EndBit is greater than 63, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..63.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..63.
  @param  AndData   The value to AND with the read value from the value

  @return The new 64-bit value.

**/
UINT64
EFIAPI
BitFieldAnd64 (
  IN      UINT64                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT64                    AndData
  );


/**
  Reads a bit field from a 64-bit value, performs a bitwise AND followed by a
  bitwise OR, and returns the result.

  Performs a bitwise AND between the bit field specified by StartBit and EndBit
  in Operand and the value specified by AndData, followed by a bitwise
  OR with value specified by OrData. All other bits in Operand are
  preserved. The new 64-bit value is returned.

  If 64-bit operations are not supported, then ASSERT().
  If StartBit is greater than 63, then ASSERT().
  If EndBit is greater than 63, then ASSERT().
  If EndBit is less than StartBit, then ASSERT().
  If AndData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().
  If OrData is larger than the bitmask value range specified by StartBit and EndBit, then ASSERT().

  @param  Operand   Operand on which to perform the bitfield operation.
  @param  StartBit  The ordinal of the least significant bit in the bit field.
                    Range 0..63.
  @param  EndBit    The ordinal of the most significant bit in the bit field.
                    Range 0..63.
  @param  AndData   The value to AND with the read value from the value.
  @param  OrData    The value to OR with the result of the AND operation.

  @return The new 64-bit value.

**/
UINT64
EFIAPI
BitFieldAndThenOr64 (
  IN      UINT64                    Operand,
  IN      UINTN                     StartBit,
  IN      UINTN                     EndBit,
  IN      UINT64                    AndData,
  IN      UINT64                    OrData
  );

//
// Base Library Checksum Functions
//

/**
  Returns the sum of all elements in a buffer in unit of UINT8.
  During calculation, the carry bits are dropped.

  This function calculates the sum of all elements in a buffer
  in unit of UINT8. The carry bits in result of addition are dropped.
  The result is returned as UINT8. If Length is Zero, then Zero is
  returned.

  If Buffer is NULL, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the sum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Sum         The sum of Buffer with carry bits dropped during additions.

**/
UINT8
EFIAPI
CalculateSum8 (
  IN      CONST UINT8              *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the two's complement checksum of all elements in a buffer
  of 8-bit values.

  This function first calculates the sum of the 8-bit values in the
  buffer specified by Buffer and Length.  The carry bits in the result
  of addition are dropped. Then, the two's complement of the sum is
  returned.  If Length is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the checksum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Checksum    The two's complement checksum of Buffer.

**/
UINT8
EFIAPI
CalculateCheckSum8 (
  IN      CONST UINT8              *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the sum of all elements in a buffer of 16-bit values.  During
  calculation, the carry bits are dropped.

  This function calculates the sum of the 16-bit values in the buffer
  specified by Buffer and Length. The carry bits in result of addition are dropped.
  The 16-bit result is returned.  If Length is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 16-bit boundary, then ASSERT().
  If Length is not aligned on a 16-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the sum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Sum         The sum of Buffer with carry bits dropped during additions.

**/
UINT16
EFIAPI
CalculateSum16 (
  IN      CONST UINT16             *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the two's complement checksum of all elements in a buffer of
  16-bit values.

  This function first calculates the sum of the 16-bit values in the buffer
  specified by Buffer and Length.  The carry bits in the result of addition
  are dropped. Then, the two's complement of the sum is returned.  If Length
  is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 16-bit boundary, then ASSERT().
  If Length is not aligned on a 16-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the checksum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Checksum    The two's complement checksum of Buffer.

**/
UINT16
EFIAPI
CalculateCheckSum16 (
  IN      CONST UINT16             *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the sum of all elements in a buffer of 32-bit values. During
  calculation, the carry bits are dropped.

  This function calculates the sum of the 32-bit values in the buffer
  specified by Buffer and Length. The carry bits in result of addition are dropped.
  The 32-bit result is returned. If Length is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 32-bit boundary, then ASSERT().
  If Length is not aligned on a 32-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the sum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Sum         The sum of Buffer with carry bits dropped during additions.

**/
UINT32
EFIAPI
CalculateSum32 (
  IN      CONST UINT32             *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the two's complement checksum of all elements in a buffer of
  32-bit values.

  This function first calculates the sum of the 32-bit values in the buffer
  specified by Buffer and Length.  The carry bits in the result of addition
  are dropped. Then, the two's complement of the sum is returned.  If Length
  is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 32-bit boundary, then ASSERT().
  If Length is not aligned on a 32-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the checksum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Checksum    The two's complement checksum of Buffer.

**/
UINT32
EFIAPI
CalculateCheckSum32 (
  IN      CONST UINT32             *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the sum of all elements in a buffer of 64-bit values.  During
  calculation, the carry bits are dropped.

  This function calculates the sum of the 64-bit values in the buffer
  specified by Buffer and Length. The carry bits in result of addition are dropped.
  The 64-bit result is returned.  If Length is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 64-bit boundary, then ASSERT().
  If Length is not aligned on a 64-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the sum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Sum         The sum of Buffer with carry bits dropped during additions.

**/
UINT64
EFIAPI
CalculateSum64 (
  IN      CONST UINT64             *Buffer,
  IN      UINTN                     Length
  );


/**
  Returns the two's complement checksum of all elements in a buffer of
  64-bit values.

  This function first calculates the sum of the 64-bit values in the buffer
  specified by Buffer and Length.  The carry bits in the result of addition
  are dropped. Then, the two's complement of the sum is returned.  If Length
  is 0, then 0 is returned.

  If Buffer is NULL, then ASSERT().
  If Buffer is not aligned on a 64-bit boundary, then ASSERT().
  If Length is not aligned on a 64-bit boundary, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param  Buffer      The pointer to the buffer to carry out the checksum operation.
  @param  Length      The size, in bytes, of Buffer.

  @return Checksum    The two's complement checksum of Buffer.

**/
UINT64
EFIAPI
CalculateCheckSum64 (
  IN      CONST UINT64             *Buffer,
  IN      UINTN                     Length
  );


//
// Base Library CPU Functions
//

/**
  Function entry point used when a stack switch is requested with SwitchStack()

  @param  Context1        Context1 parameter passed into SwitchStack().
  @param  Context2        Context2 parameter passed into SwitchStack().

**/
typedef
VOID
(EFIAPI *SWITCH_STACK_ENTRY_POINT)(
  IN      VOID                      *Context1,  OPTIONAL
  IN      VOID                      *Context2   OPTIONAL
  );


/**
  Used to serialize load and store operations.

  All loads and stores that proceed calls to this function are guaranteed to be
  globally visible when this function returns.

**/
VOID
EFIAPI
MemoryFence (
  VOID
  );


/**
  Saves the current CPU context that can be restored with a call to LongJump()
  and returns 0.

  Saves the current CPU context in the buffer specified by JumpBuffer and
  returns 0. The initial call to SetJump() must always return 0. Subsequent
  calls to LongJump() cause a non-zero value to be returned by SetJump().

  If JumpBuffer is NULL, then ASSERT().
  For Itanium processors, if JumpBuffer is not aligned on a 16-byte boundary, then ASSERT().

  NOTE: The structure BASE_LIBRARY_JUMP_BUFFER is CPU architecture specific.
  The same structure must never be used for more than one CPU architecture context.
  For example, a BASE_LIBRARY_JUMP_BUFFER allocated by an IA-32 module must never be used from an x64 module.
  SetJump()/LongJump() is not currently supported for the EBC processor type.

  @param  JumpBuffer  A pointer to CPU context buffer.

  @retval 0 Indicates a return from SetJump().

**/
UINTN
EFIAPI
SetJump (
  OUT     BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer
  );


/**
  Restores the CPU context that was saved with SetJump().

  Restores the CPU context from the buffer specified by JumpBuffer. This
  function never returns to the caller. Instead is resumes execution based on
  the state of JumpBuffer.

  If JumpBuffer is NULL, then ASSERT().
  For Itanium processors, if JumpBuffer is not aligned on a 16-byte boundary, then ASSERT().
  If Value is 0, then ASSERT().

  @param  JumpBuffer  A pointer to CPU context buffer.
  @param  Value       The value to return when the SetJump() context is
                      restored and must be non-zero.

**/
VOID
EFIAPI
LongJump (
  IN      BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer,
  IN      UINTN                     Value
  );


/**
  Enables CPU interrupts.

**/
VOID
EFIAPI
EnableInterrupts (
  VOID
  );


/**
  Disables CPU interrupts.

**/
VOID
EFIAPI
DisableInterrupts (
  VOID
  );


/**
  Disables CPU interrupts and returns the interrupt state prior to the disable
  operation.

  @retval TRUE  CPU interrupts were enabled on entry to this call.
  @retval FALSE CPU interrupts were disabled on entry to this call.

**/
BOOLEAN
EFIAPI
SaveAndDisableInterrupts (
  VOID
  );


/**
  Enables CPU interrupts for the smallest window required to capture any
  pending interrupts.

**/
VOID
EFIAPI
EnableDisableInterrupts (
  VOID
  );


/**
  Retrieves the current CPU interrupt state.

  Returns TRUE if interrupts are currently enabled. Otherwise
  returns FALSE.

  @retval TRUE  CPU interrupts are enabled.
  @retval FALSE CPU interrupts are disabled.

**/
BOOLEAN
EFIAPI
GetInterruptState (
  VOID
  );


/**
  Set the current CPU interrupt state.

  Sets the current CPU interrupt state to the state specified by
  InterruptState. If InterruptState is TRUE, then interrupts are enabled. If
  InterruptState is FALSE, then interrupts are disabled. InterruptState is
  returned.

  @param  InterruptState  TRUE if interrupts should enabled. FALSE if
                          interrupts should be disabled.

  @return InterruptState

**/
BOOLEAN
EFIAPI
SetInterruptState (
  IN      BOOLEAN                   InterruptState
  );


/**
  Requests CPU to pause for a short period of time.

  Requests CPU to pause for a short period of time. Typically used in MP
  systems to prevent memory starvation while waiting for a spin lock.

**/
VOID
EFIAPI
CpuPause (
  VOID
  );


/**
  Transfers control to a function starting with a new stack.

  Transfers control to the function specified by EntryPoint using the
  new stack specified by NewStack and passing in the parameters specified
  by Context1 and Context2.  Context1 and Context2 are optional and may
  be NULL.  The function EntryPoint must never return.  This function
  supports a variable number of arguments following the NewStack parameter.
  These additional arguments are ignored on IA-32, x64, and EBC architectures.
  Itanium processors expect one additional parameter of type VOID * that specifies
  the new backing store pointer.

  If EntryPoint is NULL, then ASSERT().
  If NewStack is NULL, then ASSERT().

  @param  EntryPoint  A pointer to function to call with the new stack.
  @param  Context1    A pointer to the context to pass into the EntryPoint
                      function.
  @param  Context2    A pointer to the context to pass into the EntryPoint
                      function.
  @param  NewStack    A pointer to the new stack to use for the EntryPoint
                      function.
  @param  ...         This variable argument list is ignored for IA-32, x64, and
                      EBC architectures.  For Itanium processors, this variable
                      argument list is expected to contain a single parameter of
                      type VOID * that specifies the new backing store pointer.


**/
VOID
EFIAPI
SwitchStack (
  IN      SWITCH_STACK_ENTRY_POINT  EntryPoint,
  IN      VOID                      *Context1,  OPTIONAL
  IN      VOID                      *Context2,  OPTIONAL
  IN      VOID                      *NewStack,
  ...
  );


/**
  Generates a breakpoint on the CPU.

  Generates a breakpoint on the CPU. The breakpoint must be implemented such
  that code can resume normal execution after the breakpoint.

**/
VOID
EFIAPI
CpuBreakpoint (
  VOID
  );


/**
  Executes an infinite loop.

  Forces the CPU to execute an infinite loop. A debugger may be used to skip
  past the loop and the code that follows the loop must execute properly. This
  implies that the infinite loop must not cause the code that follow it to be
  optimized away.

**/
VOID
EFIAPI
CpuDeadLoop (
  VOID
  );


#endif



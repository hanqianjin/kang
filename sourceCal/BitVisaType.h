//==============================================================================
//
// Title:		BitDisaType.h
// Purpose:		Fundamental DISA data types and macro definitions 
//
// Created on:	2017/12/18 at 10:14:21 by Steve.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __BitVisaType_H__
#define __BitVisaType_H__   

#define _DI_FAR
#define _DI_FUNC
#define _DI_FUNCC
#define _DI_FUNCH
#define _DI_SIGNED          signed  

#define _DI_ERROR           (-2147483647L-1)  /* 0x80000000 */
#define _DI_PTR             _DI_FAR *

/*- Bit Types --------------------------------------------------------------*/ 
typedef unsigned   __int64  DiUInt64;
typedef _DI_SIGNED __int64  DiInt64;

typedef DiUInt64    _DI_PTR DiPUInt64;
typedef DiUInt64    _DI_PTR DiAUInt64;
typedef DiInt64     _DI_PTR DiPInt64;
typedef DiInt64     _DI_PTR DiAInt64;

typedef unsigned int        DiUInt32;
typedef _DI_SIGNED int      DiInt32;   

typedef DiUInt32    _DI_PTR DiPUInt32;
typedef DiUInt32    _DI_PTR DiAUInt32;
typedef DiInt32     _DI_PTR DiPInt32;
typedef DiInt32     _DI_PTR DiAInt32;

typedef unsigned short      DiUInt16;
typedef DiUInt16    _DI_PTR DiPUInt16;
typedef DiUInt16    _DI_PTR DiAUInt16;

typedef _DI_SIGNED short    DiInt16;
typedef DiInt16     _DI_PTR DiPInt16;
typedef DiInt16     _DI_PTR DiAInt16;

typedef unsigned char       DiUInt8;
typedef DiUInt8     _DI_PTR DiPUInt8;
typedef DiUInt8     _DI_PTR DiAUInt8;

typedef _DI_SIGNED char     DiInt8;
typedef DiInt8      _DI_PTR DiPInt8;
typedef DiInt8      _DI_PTR DiAInt8;

typedef char                DiChar;
typedef DiChar      _DI_PTR DiPChar;
typedef DiChar      _DI_PTR DiAChar;

typedef unsigned char       DiByte;
typedef DiByte      _DI_PTR DiPByte;
typedef DiByte      _DI_PTR DiAByte;

typedef void        _DI_PTR DiAddr;
typedef DiAddr      _DI_PTR DiPAddr;
typedef DiAddr      _DI_PTR DiAAddr;

typedef float               DiReal32;
typedef DiReal32    _DI_PTR DiPReal32;
typedef DiReal32    _DI_PTR DiAReal32;

typedef double              DiReal64;
typedef DiReal64    _DI_PTR DiPReal64;
typedef DiReal64    _DI_PTR DiAReal64;

typedef DiPByte             DiBuf;
typedef DiPByte             DiPBuf;
typedef DiPByte     _DI_PTR DiABuf;

typedef DiPChar             DiString;
typedef DiPChar             DiPString;
typedef DiPChar     _DI_PTR DiAString;

typedef DiString            DiRsrc;
typedef DiString            DiPRsrc;
typedef DiString    _DI_PTR DiARsrc;

typedef DiUInt16            DiBoolean;
typedef DiBoolean   _DI_PTR DiPBoolean;
typedef DiBoolean   _DI_PTR DiABoolean;

typedef DiInt32             DiStatus;
typedef DiStatus    _DI_PTR DiPStatus;
typedef DiStatus    _DI_PTR DiAStatus;

typedef DiUInt32            DiDersion;
typedef DiDersion   _DI_PTR DiPDersion;
typedef DiDersion   _DI_PTR DiADersion;

typedef DiUInt32            DiObject;
typedef DiObject    _DI_PTR DiPObject;
typedef DiObject    _DI_PTR DiAObject;

typedef DiObject            DiSession;
typedef DiSession   _DI_PTR DiPSession;
typedef DiSession   _DI_PTR DiASession;

typedef DiUInt32             DiAttr;

#ifndef _DI_CONST_STRING_DEFINED
typedef const DiChar * DiConstString;
#define _DI_CONST_STRING_DEFINED
#endif  

/*- Completion and Error Codes ----------------------------------------------*/

#define DI_SUCCESS          (0L)

/*- Other VISA Definitions --------------------------------------------------*/

#define DI_NULL             (0)

#define DI_TRUE             (1)
#define DI_FALSE            (0)

/*- Backward Compatibility Macros -------------------------------------------*/

#define DISAFN              _DI_FUNC
#define DiPtr               _DI_PTR

/*- Interface types Macros----------------------------------------------------------*/ 
typedef DiUInt32             DiBusAddress;
typedef DiUInt32             DiBusSize;
typedef DiUInt32             DiAttrState;


#endif  /* ndef __BitVisaType_H__ */

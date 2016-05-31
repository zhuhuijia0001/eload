#ifndef _TYPE_H_
#define _TYPE_H_

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char uint8, UINT8, BYTE;
typedef signed   char int8, INT8;
typedef unsigned short uint16, UINT16, WORD;
typedef signed   short int16, INT16;
typedef unsigned long uint32, UINT32, DWORD;
typedef signed   long int32, INT32;

typedef unsigned int bool;

#ifndef true
#define true       1
#endif

#ifndef false
#define false      0
#endif

#ifndef NULL
#define NULL       0
#endif

#endif

/*
** Blue Dust - Types.h
*/
#ifndef _BD_TYPES_H
#define _BD_TYPES_H

#include <ctype.h>

#ifndef NULL
#define NULL	0
#endif

typedef signed char		tCHAR;		/* Character */
typedef unsigned char	tUCHAR;		/* Character */
typedef signed short	tWORD;		/* 16 bits */
typedef unsigned short	tUWORD;		/* 16 bits */
typedef signed long		tLONG;		/* 32 bits */
typedef unsigned long	tULONG;		/* 32 bits */

#define FOURCC(a,b,c,d)		(((a)<<24)|((b)<<16)|((c)<<8)|((d)))

#ifndef WIN32
#define strnicmp strncasecmp
#define stricmp strcasecmp
#endif

#endif	// _BD_TYPES_H


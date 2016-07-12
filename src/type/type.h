/* bdgui - a kind of embedded gui system
　* Copyright (C) 2016  BDGUI Team
　*
　* This program is free software; you can redistribute it and/or
　* modify it under the terms of the GNU General Public License
　* as published by the Free Software Foundation; either version 2
　* of the License, or (at your option) any later version.

　* This program is distributed in the hope that it will be useful,
　* but WITHOUT ANY WARRANTY; without even the implied warranty of
　* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
　* GNU General Public License for more details.

　* You should have received a copy of the GNU General Public License
　* along with this program; if not, mail to <allu_yuan@163.com>
 *
*/


#ifndef BD_TYPE_H
#define BD_TYPE_H

#include <stdint.h>
#include <stddef.h>

#define BD_HANDLE   void*
#define BD_INT      int
#define BD_UINT     unsigned int
#define BD_DOUBLE   double
#define BD_FLOAT    float
#define BD_LONG     long
#define BD_ULONG	unsigned long
#define BD_STRING	const char*
#define BD_CHAR		char
#define BD_LONGINT	long int
#define BD_ULONGINT unsigned long int

#define BD_SIZE		size_t

#define BD_UINT8	uint8_t
#define BD_UINT16	uint16_t
#define BD_UINT32	uint32_t
#define BD_UINT64	uint64_t


#define BD_NULL     0

typedef enum bd_type {
	BD_TYPE_INVALID = -1,
	BD_TYPE_OBJECT = -1,
	BD_TYPE_APPLICATION,
	BD_TYPE_COMPONENT,
	BD_TYPE_EVENT,
	BD_TYPE_DEV
} bd_type;

typedef struct bd_color {
	BD_UINT r;
	BD_UINT g;
	BD_UINT b;
} bd_color;



#endif

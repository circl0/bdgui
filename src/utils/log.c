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


#include "utils/log.h"
#include "type/type.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void bd_log(BD_STRING tag, BD_STRING format, ...)
{
//#ifdef WITH_LOG
	BD_CHAR buf[1024];
	memset(buf, 0, sizeof(buf));
	strcat(buf, "[");
	strcat(buf, tag);
	strcat(buf, "] ");
	BD_UINT length = strlen(buf);
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(buf + length, format, arg_ptr);
	va_end(arg_ptr);
	printf("%s", buf);
// #endif
}

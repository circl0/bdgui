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

#include "system/system.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/poll.h>
#include <sys/time.h>

BD_HANDLE bd_malloc(BD_INT size)
{
	return malloc(size);
}

void bd_free(BD_HANDLE handle)
{
	free(handle);
}

BD_ULONG bd_get_tick_count()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_usec;
}

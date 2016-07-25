/* bdgui - a kind of embedded gui system
　* Copyright (C) 2016  Allen Yuan
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


#include "system/mutex.h"

//#ifdef WITH_LINUX

void bd_mutex_init(bd_mutex_t* mutex)
{
	pthread_mutex_init(mutex, NULL);
}

void bd_mutex_destroy(bd_mutex_t* mutex)
{
	pthread_mutex_destroy(mutex);
}

BD_INT bd_mutex_lock(bd_mutex_t* mutex)
{
	return pthread_mutex_lock(mutex);
}

BD_INT bd_mutex_unlock(bd_mutex_t* mutex)
{
	return pthread_mutex_unlock(mutex);
}


//#endif
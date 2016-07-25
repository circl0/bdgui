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


#include "system/cond.h"

//#ifdef WITH_LINUX

void bd_cond_init(bd_cond_t* cond)
{
	pthread_cond_init(cond, NULL);
}

void bd_cond_destroy(bd_cond_t* cond)
{
	pthread_cond_destroy(cond);
}

BD_INT bd_cond_wait(bd_cond_t* cond, bd_mutex_t* mutex)
{
	return pthread_cond_wait(cond, mutex);
}

BD_INT bd_cond_signal(bd_cond_t* cond)
{
	return pthread_cond_signal(cond);
}


//#endif
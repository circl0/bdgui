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


#include "system/linux/mutex.h"

bd_mutex_internal_t bd_mutex_internal_create()
{
	bd_mutex_internal_t mutex = bd_mutex_internal_new();
	mutex->constructor(mutex);
	return mutex;
}

void bd_mutex_internal_destroy(bd_mutex_internal_t mutex)
{
	bd_mutex_internal_delete(mutex);
}

void bd_linux_mutex_constructor(bd_mutex_internal_t mutex)
{
	pthread_mutex_init(&mutex->pm, NULL);
}

void bd_linux_mutex_destructor(bd_mutex_internal_t mutex)
{
	pthread_mutex_destroy(&mutex->pm);
}

BD_INT bd_linux_mutex_lock(bd_mutex_internal_t mutex)
{
	return pthread_mutex_lock(&mutex->pm);
}

BD_INT bd_linux_mutex_unlock(bd_mutex_internal_t mutex)
{
	return pthread_mutex_unlock(&mutex->pm);
}


BD_CLASS_CONSTRUCTOR_START(bd_mutex_internal)
BD_CLASS_METHOD(constructor, bd_linux_mutex_constructor)
BD_CLASS_METHOD(destructor, bd_linux_mutex_destructor)
BD_CLASS_METHOD(lock, bd_linux_mutex_lock)
BD_CLASS_METHOD(unlock, bd_linux_mutex_unlock)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_mutex_internal)
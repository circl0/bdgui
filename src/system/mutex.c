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

bd_mutex_t bd_mutex_create()
{
	bd_mutex_t mutex = bd_mutex_new();
	mutex->constructor(mutex);
	return mutex;
}

void bd_mutex_destroy(bd_mutex_t mutex)
{
	bd_mutex_delete(mutex);
}

void bd_mutex_constructor(bd_mutex_t mutex)
{
	mutex->mutex_internal = bd_mutex_internal_create();
}

void bd_mutex_destructor(bd_mutex_t mutex)
{
	bd_mutex_internal_destroy(mutex->mutex_internal);
}

BD_INT bd_mutex_lock(bd_mutex_t mutex)
{
	mutex->mutex_internal->lock(mutex->mutex_internal);
}

BD_INT bd_mutex_unlock(bd_mutex_t mutex)
{
	mutex->mutex_internal->unlock(mutex->mutex_internal);
}

BD_INT bd_mutex_try_lock(bd_mutex_t mutex)
{
	return 0;
}

BD_CLASS_CONSTRUCTOR_START(bd_mutex)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_mutex_constructor)
BD_CLASS_METHOD(destructor, bd_mutex_destructor)
BD_CLASS_METHOD(lock, bd_mutex_lock)
BD_CLASS_METHOD(unlock, bd_mutex_unlock)
BD_CLASS_METHOD(try_lock, bd_mutex_try_lock)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_mutex)
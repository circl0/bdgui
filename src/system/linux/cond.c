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

bd_cond_internal_t bd_cond_internal_create()
{
	bd_cond_internal_t cond = bd_cond_internal_new();
	cond->constructor(cond);
	return cond;
}

void bd_cond_internal_destroy(bd_cond_internal_t cond)
{
	bd_cond_internal_delete(cond);
}

void bd_linux_cond_constructor(bd_cond_internal_t cond)
{
	pthread_cond_init(&cond->pc, NULL);
}

void bd_linux_cond_destructor(bd_cond_internal_t cond)
{
	pthread_cond_destroy(&cond->pc);
}

BD_INT bd_linux_cond_wait(bd_cond_internal_t cond, bd_mutex_internal_t mutex)
{
	return pthread_cond_wait(&cond->pc, &mutex->pm);
}

BD_INT bd_linux_cond_signal(bd_cond_internal_t cond)
{
	return pthread_cond_signal(&cond->pc);
}

BD_CLASS_CONSTRUCTOR_START(bd_cond_internal)
BD_CLASS_METHOD(constructor, bd_linux_cond_constructor)
BD_CLASS_METHOD(destructor, bd_linux_cond_destructor)
BD_CLASS_METHOD(wait, bd_linux_cond_wait)
BD_CLASS_METHOD(signal, bd_linux_cond_signal)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cond_internal)
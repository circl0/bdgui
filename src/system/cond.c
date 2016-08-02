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

bd_cond_t bd_cond_create()
{
	bd_cond_t cond = bd_cond_new();
	cond->constructor(cond);
	return cond;
}

void bd_cond_destroy(bd_cond_t cond)
{
	bd_cond_delete(cond);
}

void bd_cond_constructor(bd_cond_t cond)
{
	cond->cond_internal = bd_cond_internal_create();
}

void bd_cond_destructor(bd_cond_t cond)
{
	bd_cond_internal_destroy(cond->cond_internal);
}

BD_INT bd_cond_wait(bd_cond_t cond, bd_mutex_t mutex)
{
	cond->cond_internal->wait(cond->cond_internal, mutex->mutex_internal);
}

BD_INT bd_cond_signal(bd_cond_t cond)
{
	cond->cond_internal->signal(cond->cond_internal);
}

BD_CLASS_CONSTRUCTOR_START(bd_cond)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_cond_constructor)
BD_CLASS_METHOD(destructor, bd_cond_destructor)
BD_CLASS_METHOD(wait, bd_cond_wait)
BD_CLASS_METHOD(signal, bd_cond_signal)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cond)
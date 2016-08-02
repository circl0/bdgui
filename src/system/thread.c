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


#include "system/thread.h"

bd_thread_t bd_thread_create(bd_runnable runnable)
{
	bd_thread_t thread = bd_thread_new();
	thread->constructor(thread, runnable);
	return thread;
}

void bd_thread_destroy(bd_thread_t thread)
{
	bd_thread_delete(thread);
}

void bd_thread_constructor(bd_thread_t thread, bd_runnable runnable)
{
	thread->thread_internal = bd_thread_internal_create();
	thread->runnable = runnable;
}

void bd_thread_destructor(bd_thread_t thread)
{

}

BD_INT bd_thread_join(bd_thread_t thread)
{
	thread->thread_internal->join(thread->thread_internal);
}

BD_INT bd_thread_detach(bd_thread_t thread)
{
	thread->thread_internal->detach(thread->thread_internal);
}

BD_INT bd_thread_start(bd_thread_t thread, BD_HANDLE data)
{
	thread->thread_internal->start(thread->thread_internal, thread->runnable, data);
}

BD_CLASS_CONSTRUCTOR_START(bd_thread)
BD_CLASS_METHOD(constructor, bd_thread_constructor)
BD_CLASS_METHOD(destructor, bd_thread_destructor)
BD_CLASS_METHOD(join, bd_thread_join)
BD_CLASS_METHOD(detach, bd_thread_detach)
BD_CLASS_METHOD(start, bd_thread_start)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_thread)
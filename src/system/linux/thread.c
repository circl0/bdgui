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


#include "system/thread.h"

//#ifdef WITH_LINUX

#include <pthread.h>

bd_thread_t bd_thread_create(BD_HANDLE (*run)(BD_HANDLE data), BD_HANDLE data)
{
	bd_thread_t thread = bd_thread_new();
	thread->constructor(thread, run);
	return thread;
}

void bd_thread_destroy(bd_thread_t thread)
{

}

void bd_linux_thread_constructor(bd_thread_t thread, BD_HANDLE (*run)(BD_HANDLE data))
{
	thread->run = run;
}

void bd_linux_thread_destructor(bd_thread_t thread)
{
	thread->detach(thread);
}

BD_INT bd_linux_thread_start(bd_thread_t thread, BD_HANDLE data)
{
	return pthread_create(&thread->id, BD_NULL, thread->run, data);
}

BD_INT bd_linux_thread_join(bd_thread_t thread)
{
	return pthread_join(thread->id, NULL);
}

BD_INT bd_linux_thread_detach(bd_thread_t thread)
{
	return pthread_detach(thread->id);
}

BD_CLASS_CONSTRUCTOR_START(bd_thread)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_linux_thread_constructor)
BD_CLASS_METHOD(destructor, bd_linux_thread_destructor)
BD_CLASS_METHOD(join, bd_linux_thread_join)
BD_CLASS_METHOD(detach, bd_linux_thread_detach)
BD_CLASS_CONSTRUCTOR_END

//#endif

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

bd_thread_internal_t bd_thread_internal_create()
{
	bd_thread_internal_t thread = bd_thread_internal_new();
	thread->constructor(thread);
	return thread;
}

void bd_thread_internal_destroy(bd_thread_internal_t thread)
{
	thread->detach(thread);
	bd_thread_internal_delete(thread);
}

void bd_linux_thread_constructor(bd_thread_internal_t thread)
{

}

void bd_linux_thread_destructor(bd_thread_internal_t thread)
{

}

BD_INT bd_linux_thread_start(bd_thread_internal_t thread, BD_HANDLE (*run)(BD_HANDLE data), BD_HANDLE data)
{
	return pthread_create(&(thread->pt), BD_NULL, run, data);
}

BD_INT bd_linux_thread_join(bd_thread_internal_t thread)
{
	return pthread_join(thread->pt, NULL);
}

BD_INT bd_linux_thread_detach(bd_thread_internal_t thread)
{
	return pthread_detach(thread->pt);
}

BD_CLASS_CONSTRUCTOR_START(bd_thread_internal)
BD_CLASS_METHOD(constructor, bd_linux_thread_constructor)
BD_CLASS_METHOD(destructor, bd_linux_thread_destructor)
BD_CLASS_METHOD(start, bd_linux_thread_start)
BD_CLASS_METHOD(join, bd_linux_thread_join)
BD_CLASS_METHOD(detach, bd_linux_thread_detach)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_thread_internal)
//#endif

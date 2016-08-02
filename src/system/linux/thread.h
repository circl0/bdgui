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

#ifndef INCLUDE_SYSTEM_LINUX_THREAD_H_
#define INCLUDE_SYSTEM_LINUX_THREAD_H_

#include "type/object.h"
#include <pthread.h>

BD_CLASS(bd_thread_internal) {

	pthread_t pt;

	void(*constructor)(bd_thread_internal_t thread);
	void(*destructor)(bd_thread_internal_t thread);

	BD_INT (*join)(bd_thread_internal_t thread);
	BD_INT (*detach)(bd_thread_internal_t thread);
	BD_INT (*start)(bd_thread_internal_t thread, BD_HANDLE (*run)(BD_HANDLE data), BD_HANDLE data);
};

bd_thread_internal_t bd_thread_internal_create();
void bd_thread_internal_destroy(bd_thread_internal_t thread);

#endif
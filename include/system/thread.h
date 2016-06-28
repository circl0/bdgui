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


#ifndef INCLUDE_SYSTEM_THREAD_H_
#define INCLUDE_SYSTEM_THREAD_H_

#include "type/type.h"

#ifdef WITH_LINUX
#include <pthread.h>
typedef pthread_t bd_thread_t;
#endif
//typedef struct bd_thread bd_thread, *bd_thread_t;

typedef BD_HANDLE(*bd_thread_run_func)(BD_HANDLE);

bd_thread_t bd_thread_create(bd_thread_run_func runnable, BD_HANDLE data);

void bd_thread_destroy(bd_thread_t thread);

void bd_thread_join(bd_thread_t thread);

void bd_thread_detach(bd_thread_t thread);

#endif /* INCLUDE_SYSTEM_THREAD_H_ */

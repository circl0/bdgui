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


//#ifdef WITH_LINUX

#include "system/linux/timer.h"
#include "system/system.h"
#include "system/thread.h"
#include "system/source.h"
#include "system/source_pool.h"
#include "system/linux/source_pool.h"
#include "system/linux/input.h"
#include "system/input.h"
#include "type/object.h"
#include "utils/log.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/poll.h>

static void bd_source_pool_poll_function(bd_source_pool_t pool, bd_application_t app)
{
	BD_UINT size = pool->get_size(pool);
	for (BD_UINT i = 0; i < size; ++i) {
		if (pool->has_event(pool, i)) {
			bd_source_t source = pool->get_source(pool, i);
			bd_event_t event = source->read_events(source);

			if (event != BD_NULL && app != BD_NULL) {
				app->send_event(app, event);
			}
		}
	}
}

static BD_HANDLE bd_main_loop_run_function(bd_application_t app)
{
	bd_source_pool_t pool = bd_source_pool_create(3);

	bd_source_t input1 = BD_SUP(bd_input_create("event0", BD_INPUT_KEYBOARD), bd_source);
	bd_source_t input2 = BD_SUP(bd_input_create("event1", BD_INPUT_MOUSE), bd_source);
	bd_source_t timer = BD_SUP(bd_timer_create(1, 30000), bd_source);

	input1->init(input1);
	input2->init(input2);
	timer->init(timer);

	pool->push(pool, input1);
	pool->push(pool, input2);
	pool->push(pool, timer);

	while (1) {
		pool->wait_for_events(pool, app, bd_source_pool_poll_function);
	}
	return BD_NULL;
}

BD_HANDLE bd_malloc(BD_INT size)
{
	return malloc(size);
}

void bd_free(BD_HANDLE handle)
{
	free(handle);
}

BD_ULONG bd_get_tick_count()
{
	return 0L;
}

void bd_lock()
{

}

void bd_unlock()
{

}

void bd_main_loop(bd_application_t app)
{
	bd_main_loop_run_function(app);
}



//#endif

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


#ifdef WITH_LINUX

#include "system/system.h"
#include "system/thread.h"
#include "system/source.h"
#include "system/input.h"
#include "utils/log.h"
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t mutex;

static void bd_source_pool_poll_function(bd_source_pool_t pool)
{
	BD_UINT size = bd_source_pool_size(pool);
	for (BD_UINT i = 0; i < size; ++i) {
		if (bd_source_pool_has_event(pool, i)) {
			bd_source_t source = bd_source_pool_get(pool, i);
			switch(source->type) {
			case BD_SOURCE_INPUT:
			{
				bd_input_dev_t input = (bd_input_dev_t) source;
				bd_event_t event = bd_input_dev_read_event(input);
				break;
			}
			default:
				break;
			}
		}
	}
}

static BD_HANDLE bd_main_loop_run_function(BD_HANDLE data)
{
	bd_source_pool_t pool = bd_source_pool_create(2);

	bd_input_dev_t input1 = bd_input_dev_create("event0", BD_INPUT_KEYBOARD);
	bd_input_dev_t input2 = bd_input_dev_create("event1", BD_INPUT_MOUSE);

	bd_input_dev_open(input1);
	bd_input_dev_open(input2);

	bd_source_pool_push(pool, (bd_source_t)input1);
	bd_source_pool_push(pool, (bd_source_t)input2);

	while (1) {
		bd_source_pool_wait_for_events(pool, bd_source_pool_poll_function);
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
	pthread_mutex_lock(&mutex);
}

void bd_unlock()
{
	pthread_mutex_unlock(&mutex);
}

void bd_main_loop()
{
	bd_main_loop_run_function(BD_NULL);
}



#endif

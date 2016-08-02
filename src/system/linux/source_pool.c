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

#include <string.h>
#include <sys/poll.h>
#include "system/source.h"
#include "system/system.h"
#include "system/timer.h"
#include "system/linux/timer.h"
#include "system/input.h"
#include "system/linux/input.h"
#include "system/linux/source_pool.h"
#include "system/source_pool.h"
#include "utils/log.h"

#define SOURCE_TAG "source"

bd_source_pool_internal_t bd_source_pool_internal_create(BD_INT size)
{
	bd_source_pool_internal_t pool = bd_source_pool_internal_new();
	pool->constructor(pool, size);
	return pool;
}

void bd_source_pool_internal_destroy(bd_source_pool_internal_t pool)
{
	bd_source_pool_internal_delete(pool);
}

void bd_linux_source_pool_constructor(bd_source_pool_internal_t pool, BD_INT size)
{
	pool->fds = bd_malloc(sizeof(struct pollfd) * size);
}

void bd_linux_source_pool_destructor(bd_source_pool_internal_t pool)
{
	for (BD_INT i = 0; i < pool->size; ++i) {
		bd_free(pool->fds + i);
	}
	bd_free(pool->fds);
}

void bd_linux_source_pool_push(bd_source_pool_internal_t pool, bd_source_t source)
{
	if (pool == BD_NULL) {
		return;
	}
	struct pollfd* fp = pool->fds + pool->size;
	switch(source->type) {
	case BD_SOURCE_INPUT:
		fp->fd = BD_SUB(source, bd_source, bd_input)->input_internal->fd;
		break;
	case BD_SOURCE_TIMER:
		fp->fd = BD_SUB2(source, bd_source, bd_timer, bd_linux_timer)->fd;
		break;
	default:
		break;
	}
	fp->events = POLLIN;
	pool->size++;
}

void bd_linux_source_pool_clear(bd_source_pool_internal_t pool)
{
	memset(pool->fds, 0, sizeof(struct pollfd) * pool->size);
	pool->size = 0;
}

void bd_linux_source_pool_wait_for_events(bd_source_pool_internal_t pool, BD_INT* index, BD_INT size)
{
	BD_INT result = poll(pool->fds, pool->size, -1);

	if ((result > 0) && index != BD_NULL) {
		for (BD_INT i = 0; i < pool->size; ++i) {
			if (pool->fds[i].revents & POLLIN) {
				index[i] = 1;
			}
		}
	}

	for (BD_INT i = 0; i < pool->size; ++i) {
		pool->fds[i].revents = 0;
	}
}

BD_CLASS_CONSTRUCTOR_START(bd_source_pool_internal)
BD_CLASS_METHOD(constructor, bd_linux_source_pool_constructor)
BD_CLASS_METHOD(destructor, bd_linux_source_pool_destructor)
BD_CLASS_METHOD(push, bd_linux_source_pool_push)
BD_CLASS_METHOD(clear, bd_linux_source_pool_clear)
BD_CLASS_METHOD(wait_for_events, bd_linux_source_pool_wait_for_events)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_source_pool_internal)

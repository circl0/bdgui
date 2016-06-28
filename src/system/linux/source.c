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


#include "system/source.h"
#include "system/system.h"
#include "utils/log.h"
#include <string.h>
#include <sys/poll.h>

#define SOURCE_TAG "source"

struct bd_source_pool {
	bd_source_t* sources;
	struct pollfd* fds;
	BD_UINT max_size;
	BD_UINT size;
	BD_UINT timeout;
};

bd_source_pool_t bd_source_pool_create(BD_UINT max_size)
{
	bd_source_pool_t pool = (bd_source_pool_t) bd_malloc(sizeof(bd_source_pool));
	if (pool == BD_NULL) {
		return BD_NULL;
	}
	pool->fds = bd_malloc(sizeof(struct pollfd) * max_size);
	pool->sources = bd_malloc(sizeof(bd_source_t) * max_size);
	pool->max_size = max_size;
	pool->size = 0;
	pool->timeout = -1;
	return pool;
}

void bd_source_pool_destroy(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return;
	}
	bd_free(pool);
}

void bd_source_pool_set_time_out(bd_source_pool_t pool, BD_INT timeout)
{
	if (pool == BD_NULL) {
		return;
	}
	pool->timeout = timeout;
}

void bd_source_pool_push(bd_source_pool_t pool, bd_source_t source)
{
	if (pool == BD_NULL || pool->max_size == pool->size) {
		return;
	}
	struct pollfd* fp = pool->fds + pool->size;
	fp->fd = source->fd;
	fp->events = POLLIN;
	*(pool->sources + pool->size) = source;
	pool->size++;
}

void bd_source_pool_clear(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return;
	}
	memset(pool->fds, 0, sizeof(struct pollfd) * pool->max_size);
	memset(pool->sources, 0, sizeof(bd_source_t) * pool->max_size);
	pool->size = 0;
}

void bd_source_pool_wait_for_events(bd_source_pool_t pool, bd_source_pool_events_func func)
{
	if (pool == BD_NULL) {
		return;
	}
	BD_INT result = poll(pool->fds, pool->size, pool->timeout);

	if ((result > 0) && func != BD_NULL) {
		func(pool);
	}

	for (BD_INT i = 0; i < pool->size; ++i) {
		pool->fds[i].revents = 0;
	}
}

BD_UINT bd_source_pool_size(bd_source_pool_t pool)
{
	return pool->size;
}

bd_source_t bd_source_pool_get(bd_source_pool_t pool, BD_UINT i)
{
	if (pool == BD_NULL || i >= pool->size) {
		return BD_NULL;
	}
	return pool->sources[i];
}

BD_INT bd_source_pool_has_event(bd_source_pool_t pool, BD_UINT i)
{
	if (pool == BD_NULL || i >= pool->size) {
		return 0;
	}
	if (!(pool->fds[i].revents)) {
		return 0;
	}
	return 1;
}

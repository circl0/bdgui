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

bd_source_pool_t bd_source_pool_create(BD_UINT size)
{
	bd_linux_source_pool_t pool = bd_linux_source_pool_new();
	pool->constructor(pool, size);
	return BD_SUP(pool, bd_source_pool);
}

void bd_source_pool_destory(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return;
	}
	bd_linux_source_pool_t linux_pool = BD_SUB(pool, bd_source_pool, bd_linux_source_pool);
	bd_linux_source_pool_delete(linux_pool);
}

void bd_linux_source_pool_constructor(bd_linux_source_pool_t linux_pool, BD_UINT size)
{
	if (linux_pool == BD_NULL) {
		return;
	}
	bd_source_pool_t pool = BD_SUP(linux_pool, bd_source_pool);
	pool->constructor(pool, size);

	linux_pool->fds = bd_malloc(sizeof(struct pollfd) * size);

}

void bd_linux_source_pool_destructor(bd_linux_source_pool_t linux_pool)
{
	if (linux_pool == BD_NULL) {
		return;
	}

	for (BD_INT i = 0; linux_pool->bd_source_pool.size; ++i) {
		bd_free(linux_pool->fds + i);
	}

	bd_free(linux_pool->fds);
	bd_source_pool_t pool = BD_SUP(linux_pool, bd_source_pool);
	pool->destructor(pool);
}

void bd_linux_source_pool_push(bd_source_pool_t pool, bd_source_t source)
{
	bd_linux_source_pool_t linux_pool = BD_SUB(pool, bd_source_pool, bd_linux_source_pool);
	if (linux_pool == BD_NULL || linux_pool->bd_source_pool.max_size == linux_pool->bd_source_pool.size) {
		return;
	}
	struct pollfd* fp = linux_pool->fds + linux_pool->bd_source_pool.size;
	switch(source->type) {
	case BD_SOURCE_INPUT:
		fp->fd = BD_SUB2(source, bd_source, bd_input, bd_linux_input)->fd;
		break;
	case BD_SOURCE_TIMER:
		fp->fd = BD_SUB2(source, bd_source, bd_timer, bd_linux_timer)->fd;
		break;
	default:
		break;
	}
	fp->events = POLLIN;
	*(linux_pool->bd_source_pool.sources + linux_pool->bd_source_pool.size) = source;
	linux_pool->bd_source_pool.size++;
}

void bd_linux_source_pool_clear(bd_source_pool_t pool)
{
	bd_linux_source_pool_t linux_pool = BD_SUB(pool, bd_source_pool, bd_linux_source_pool);
	if (linux_pool == BD_NULL) {
		return;
	}
	memset(linux_pool->fds, 0, sizeof(struct pollfd) * linux_pool->bd_source_pool.max_size);
	memset(linux_pool->bd_source_pool.sources, 0, sizeof(bd_source_t) * linux_pool->bd_source_pool.max_size);
	linux_pool->bd_source_pool.size = 0;
}

void bd_linux_source_pool_wait_for_events(bd_source_pool_t pool, bd_application_t app, void(*bd_source_pool_events_func)(bd_source_pool_t, bd_application_t))
{
	bd_linux_source_pool_t linux_pool = BD_SUB(pool, bd_source_pool, bd_linux_source_pool);
	if (linux_pool == BD_NULL) {
		return;
	}

	BD_INT result = poll(linux_pool->fds, linux_pool->bd_source_pool.size, -1);

	if ((result > 0) && bd_source_pool_events_func != BD_NULL) {
		bd_source_pool_events_func(pool, app);
	}

	for (BD_INT i = 0; i < linux_pool->bd_source_pool.size; ++i) {
		linux_pool->fds[i].revents = 0;
	}
}

BD_INT bd_linux_source_pool_has_event(bd_source_pool_t pool, BD_UINT i)
{
	bd_linux_source_pool_t linux_pool = BD_SUB(pool, bd_source_pool, bd_linux_source_pool);
	if (linux_pool == BD_NULL || i >= linux_pool->bd_source_pool.size) {
		return 0;
	}
	if (!(linux_pool->fds[i].revents)) {
		return 0;
	}
	return 1;
}

BD_CLASS_CONSTRUCTOR_START(bd_linux_source_pool)
BD_SUPER_CONSTRUCTOR(bd_source_pool)
BD_CLASS_METHOD(constructor, bd_linux_source_pool_constructor)
BD_CLASS_METHOD(bd_source_pool.push, bd_linux_source_pool_push)
BD_CLASS_METHOD(bd_source_pool.clear, bd_linux_source_pool_clear)
BD_CLASS_METHOD(bd_source_pool.wait_for_events, bd_linux_source_pool_wait_for_events)
BD_CLASS_METHOD(bd_source_pool.has_event, bd_linux_source_pool_has_event)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_linux_source_pool)

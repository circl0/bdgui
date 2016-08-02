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


#include "system/source_pool.h"
#include "system/system.h"

bd_source_pool_t bd_source_pool_create(BD_UINT size)
{
	bd_source_pool_t pool = bd_source_pool_new();
	pool->constructor(pool, size);
	return pool;
}

void bd_source_pool_destroy(bd_source_pool_t pool)
{
	bd_source_pool_delete(pool);
}

void bd_source_pool_constructor(bd_source_pool_t pool, BD_UINT size)
{
	pool->source_pool_internal = bd_source_pool_internal_create(size);
	pool->max_size = size;
	pool->size = 0;
	pool->sources = (bd_source_t*)bd_malloc(sizeof(bd_source_t) * size);
}

void bd_source_pool_destructor(bd_source_pool_t pool)
{
	for (BD_INT i = 0; i < pool->size; ++i) {
		bd_source_t source = pool->get_source(pool, i);
		bd_source_destroy(source);
	}
	bd_free(pool->sources);
	bd_source_pool_internal_destroy(pool->source_pool_internal);
}

BD_UINT bd_source_pool_get_size(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return -1;
	}
	return pool->size;
}

bd_source_t bd_source_pool_get_source(bd_source_pool_t pool, BD_UINT i)
{
	if (pool == BD_NULL || i >= pool->size) {
		return BD_NULL;
	}
	return pool->sources[i];
}

void bd_source_pool_push(bd_source_pool_t pool, bd_source_t source)
{
	if (pool->max_size == pool->size) {
		return;
	}

	pool->sources[pool->size] = source;
	pool->source_pool_internal->push(pool->source_pool_internal, source, pool->size);

	pool->size++;
}

void bd_source_pool_clear(bd_source_pool_t pool)
{
	memset(pool->sources, 0, sizeof(bd_source_t) * pool->max_size);
	pool->source_pool_internal->clear(pool->source_pool_internal, pool->max_size);
	pool->size = 0;
}

void bd_source_pool_wait_for_events(bd_source_pool_t pool, bd_source_pool_events_func function)
{
	BD_INT index[BD_SOURCE_POOL_MAX];
	memset(index, 0, sizeof(BD_INT) * BD_SOURCE_POOL_MAX);
	pool->source_pool_internal->wait_for_events(pool->source_pool_internal, index, BD_SOURCE_POOL_MAX);
	for (BD_INT i = 0; i < pool->size; ++i) {
		if (index[i]) {
			function(pool->sources[i]);
		}
	}
}


BD_CLASS_CONSTRUCTOR_START(bd_source_pool)
BD_CLASS_METHOD(constructor, bd_source_pool_constructor)
BD_CLASS_METHOD(destructor, bd_source_pool_destructor)
BD_CLASS_METHOD(get_size, bd_source_pool_get_size)
BD_CLASS_METHOD(get_source, bd_source_pool_get_source)
BD_CLASS_METHOD(push, bd_source_pool_push)
BD_CLASS_METHOD(clear, bd_source_pool_clear)
BD_CLASS_METHOD(wait_for_events, bd_source_pool_wait_for_events)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_source_pool)

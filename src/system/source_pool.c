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

void bd_source_pool_constructor(bd_source_pool_t pool, BD_UINT size)
{
	if (pool == BD_NULL) {
		return;
	}
	pool->max_size = size;
	pool->size = 0;
	pool->sources = (bd_source_t*)bd_malloc(sizeof(bd_source_t) * size);
}

void bd_source_pool_destructor(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return;
	}
	for (BD_INT i = 0; i < pool->size; ++i) {
		bd_source_t source = pool->get_source(pool, i);
		bd_source_destroy(source);
	}
	bd_free(pool->sources);
}

BD_UINT bd_source_pool_size(bd_source_pool_t pool)
{
	if (pool == BD_NULL) {
		return -1;
	}
	return pool->size;
}

bd_source_t bd_source_pool_get(bd_source_pool_t pool, BD_UINT i)
{
	if (pool == BD_NULL || i >= pool->size) {
		return BD_NULL;
	}
	return pool->sources[i];
}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_source_pool)
BD_CLASS_METHOD(constructor, bd_source_pool_constructor)
BD_CLASS_METHOD(destructor, bd_source_pool_destructor)
BD_CLASS_METHOD(get_size, bd_source_pool_size)
BD_CLASS_METHOD(get_source, bd_source_pool_get)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END

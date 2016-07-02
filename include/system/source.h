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


#ifndef INCLUDE_SYSTEM_LINUX_SOURCE_H_
#define INCLUDE_SYSTEM_LINUX_SOURCE_H_

#include "type/type.h"

typedef enum bd_source_type {
	BD_SOURCE_INPUT = 0,
	BD_SOURCE_TIMER = 1,
} bd_source_type;

typedef struct bd_source {
	bd_source_type type;
	BD_INT fd;
} bd_source, *bd_source_t;

typedef struct bd_source_pool bd_source_pool, *bd_source_pool_t;

typedef void(*bd_source_pool_events_func)(bd_source_pool_t pool);

bd_source_pool_t bd_source_pool_create(BD_UINT size);
void bd_source_pool_destroy(bd_source_pool_t pool);


void bd_source_pool_set_time_out(bd_source_pool_t pool, BD_INT timeout);
void bd_source_pool_push(bd_source_pool_t pool, bd_source_t source);
void bd_source_pool_clear(bd_source_pool_t pool);
void bd_source_pool_wait_for_events(bd_source_pool_t pool, bd_source_pool_events_func func);

BD_UINT bd_source_pool_size(bd_source_pool_t pool);
bd_source_t bd_source_pool_get(bd_source_pool_t pool, BD_UINT i);
BD_INT bd_source_pool_has_event(bd_source_pool_t pool, BD_UINT i);


#endif /* INCLUDE_SYSTEM_LINUX_SOURCE_H_ */

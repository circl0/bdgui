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

#ifndef INCLUDE_SYSTEM_LINUX_SOURCE_POOL_H_
#define INCLUDE_SYSTEM_LINUX_SOURCE_POOL_H_

#include "system/source.h"
#include "type/object.h"

BD_CLASS(bd_source_pool_internal) {

	struct pollfd* fds;
	BD_INT size;

	void(*constructor)(bd_source_pool_internal_t source_pool, BD_INT size);
	void(*destructor)(bd_source_pool_internal_t source_pool);

	void(*push)(bd_source_pool_internal_t pool, bd_source_t source, BD_INT num);
	void(*clear)(bd_source_pool_internal_t pool, BD_INT num);

	void(*wait_for_events)(bd_source_pool_internal_t pool, BD_INT* index, BD_INT size);
};

bd_source_pool_internal_t bd_source_pool_internal_create(BD_INT size);
void bd_source_pool_internal_destroy(bd_source_pool_internal_t pool);

#endif 

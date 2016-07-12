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

#ifndef INCLUDE_SYSTEM_SOURCE_POOL_H_
#define INCLUDE_SYSTEM_SOURCE_POOL_H_

#include "type/object.h"
#include "system/source.h"
#include "application/application.h"

BD_ABSTRACT_CLASS(bd_source_pool) {
	BD_EXTENDS(bd_object);

	BD_UINT size;
	BD_UINT max_size;
	bd_source_t* sources;

	void(*constructor)(bd_source_pool_t self, BD_UINT size);
	void(*destructor)(bd_source_pool_t self);

	void(*push)(bd_source_pool_t pool, bd_source_t source);
	void(*clear)(bd_source_pool_t pool);
	void(*wait_for_events)(bd_source_pool_t pool, bd_application_t app, void(*bd_source_pool_events_func)(bd_source_pool_t, bd_application_t));
	BD_INT (*has_event)(bd_source_pool_t pool, BD_UINT i);

	BD_UINT (*get_size)(bd_source_pool_t pool);
	bd_source_t (*get_source)(bd_source_pool_t pool, BD_UINT i);

};

bd_source_pool_t bd_source_pool_create(BD_UINT size);
void bd_source_pool_destory(bd_source_pool_t pool);

#endif 

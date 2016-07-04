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

#include "type/type.h"
#include "type/object.h"
#include "system/timer.h"


void bd_timer_constructor(bd_timer_t self, BD_INT id, BD_ULONG milliseconds)
{
	if (self == BD_NULL) {
		return;
	}
	bd_source_t source = BD_SUP(self, bd_source);
	source->constructor(source, BD_SOURCE_TIMER);
	self->timeout = milliseconds;
	self->id = id;
}

void bd_timer_destructor(bd_timer_t self)
{
	bd_source_t source = BD_SUP(self, bd_source);
	source->destructor(source);
}

BD_INT bd_timer_init(bd_source_t source)
{
	return BD_SUB(source, bd_source, bd_timer)->start(BD_SUB(source, bd_source, bd_timer));
}

BD_INT bd_timer_deinit(bd_source_t source)
{
	return BD_SUB(source, bd_source, bd_timer)->stop(BD_SUB(source, bd_source, bd_timer));
}

bd_event_t bd_timer_read_events(bd_source_t source)
{
	return BD_SUB(source, bd_source, bd_timer)->read(BD_SUB(source, bd_source, bd_timer));
}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_timer)
BD_SUPER_CONSTRUCTOR(bd_source)
BD_CLASS_METHOD(bd_source.init, bd_timer_init)
BD_CLASS_METHOD(bd_source.deinit, bd_timer_deinit)
BD_CLASS_METHOD(bd_source.read_events, bd_timer_read_events)
BD_CLASS_METHOD(constructor, bd_timer_constructor)
BD_CLASS_METHOD(destructor, bd_timer_destructor)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END

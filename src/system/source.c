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
#include "system/input.h"
#include "system/timer.h"
#include "type/object.h"

void bd_source_destroy(bd_source_t source)
{
	if (source == BD_NULL) {
		return;
	}
	switch(source->type) {
	case BD_SOURCE_INPUT:
		bd_input_destroy(BD_SUB(source, bd_source, bd_input));
		break;
	case BD_SOURCE_TIMER:
		bd_timer_destroy(BD_SUB(source, bd_source, bd_timer));
		break;
	default:
		break;
	}
}

void bd_source_constructor(bd_source_t self, bd_source_type type)
{
	if (self == BD_NULL) {
		return;
	}
	self->type = type;
}

void bd_source_destructor(bd_source_t self)
{
	if (self == BD_NULL) {
		return;
	}
}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_source)
SUPER_CTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_source_constructor)
BD_CLASS_METHOD(destructor, bd_source_destructor)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END

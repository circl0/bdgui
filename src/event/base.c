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

#include "type/type.h"
#include "system/system.h"
#include "event/base.h"
#include "event/map.h"
#include "type/list.h"
#include "type/object.h"


void bd_event_constructor(bd_event_t self, bd_event_id id)
{
	self->id = id;
	self->sender = BD_NULL;
}

void bd_event_destructor(bd_event_t self)
{

}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_event)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_event_constructor)
BD_CLASS_METHOD(destructor, bd_event_destructor)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END



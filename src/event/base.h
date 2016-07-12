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


#ifndef BD_EVENT_H
#define BD_EVENT_H

#include "component/base.h"
#include "type/object.h"
#include "type/type.h"

#define BD_EVENT_NUM_MAX	256

typedef enum bd_event_id {
    BD_EVENT_INVALID = -1,
	BD_EVENT_ON_TIMER,
	BD_EVENT_ON_PAINT,
	BD_EVENT_ON_MOUSE,
	BD_EVENT_ON_KEYBOARD,
	BD_EVENT_ON_TOUCH,
	BD_EVENT_MAX = BD_EVENT_NUM_MAX,
} bd_event_id;


BD_ABSTRACT_CLASS(bd_event) {
	BD_EXTENDS(bd_object);

    bd_event_id id;
    bd_object_t sender;

    void(*constructor)(bd_event_t self, bd_event_id id);
    void(*destructor)(bd_event_t self);
};

typedef void(*bd_event_handler_t)(bd_event_t);


#endif

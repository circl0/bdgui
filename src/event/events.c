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

#include "event/events.h"
#include "type/object.h"
#include "event/base.h"

#define BD_DECLARE_EVENT(class, id) \
	void bd_##class##_constructor(class##_t event)\
	{\
		bd_event_t abstract_event = BD_SUP(event, bd_event);\
		abstract_event->constructor(abstract_event, id);\
	}\
	void bd_##class##_destructor(class##_t event)\
	{\
		\
	}\
	BD_CLASS_CONSTRUCTOR_START(class)\
	BD_SUPER_CONSTRUCTOR(bd_event)\
	BD_CLASS_METHOD(constructor, bd_##class##_constructor)\
	BD_CLASS_METHOD(destructor, bd_##class##_destructor)\
	BD_CLASS_CONSTRUCTOR_END

BD_DECLARE_EVENT(bd_mouse_event, BD_EVENT_ON_MOUSE)
BD_DECLARE_EVENT(bd_keyboard_event, BD_EVENT_ON_KEYBOARD)
BD_DECLARE_EVENT(bd_touch_event, BD_EVENT_ON_TOUCH)
BD_DECLARE_EVENT(bd_timer_event, BD_EVENT_ON_TIMER)

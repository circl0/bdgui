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
	void class##_constructor(class##_t event)\
	{\
		bd_event_t abstract_event = BD_SUP(event, bd_event);\
		abstract_event->constructor(abstract_event, id);\
	}\
	void class##_destructor(class##_t event)\
	{\
		\
	}\
	bd_event_t class##_clone(bd_event_t self)\
	{\
		class##_t class_event = BD_SUB(self, bd_event, class);\
		class##_t clone_class_event = class##_new();\
		memcpy(clone_class_event, class_event, sizeof(class));\
		return clone_class_event;\
	}\
	BD_CLASS_CONSTRUCTOR_START(class)\
	BD_SUPER_CONSTRUCTOR(bd_event)\
	BD_CLASS_METHOD(constructor, class##_constructor)\
	BD_CLASS_METHOD(destructor, class##_destructor)\
	BD_CLASS_METHOD(bd_event.clone, class##_clone)\
	BD_CLASS_CONSTRUCTOR_END \
	BD_CLASS_DESTRUCTOR(class)

BD_DECLARE_EVENT(bd_mouse_button_event, BD_EVENT_ON_MOUSE_BUTTON)
BD_DECLARE_EVENT(bd_mouse_move_event, BD_EVENT_ON_MOUSE_MOVE)
BD_DECLARE_EVENT(bd_keyboard_event, BD_EVENT_ON_KEYBOARD)
BD_DECLARE_EVENT(bd_touch_event, BD_EVENT_ON_TOUCH)
BD_DECLARE_EVENT(bd_timer_event, BD_EVENT_ON_TIMER)
BD_DECLARE_EVENT(bd_window_manager_invalidate_event, BD_EVENT_ON_INVALIDATE)

BD_DECLARE_EVENT(bd_window_invalidate_event, BD_EVENT_WINDOW_INVALIDATE)
BD_DECLARE_EVENT(bd_window_move_event, BD_EVENT_WINDOW_MOVE)
BD_DECLARE_EVENT(bd_window_resize_event, BD_EVENT_WINDOW_RESIZE)
BD_DECLARE_EVENT(bd_window_update_finish_event, BD_EVENT_WINDOW_UPDATE_FINISH)




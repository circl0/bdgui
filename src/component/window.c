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

#include "component/window.h"
#include "utils/log.h"

void bd_window_constructor(bd_window_t window)
{

}

void bd_window_destructor(bd_window_t window)
{

}

void bd_window_render(bd_component_t window)
{
	bd_log("window", "render handle: %ld\n", window);
}

void bd_window_handle_event(bd_window_t window, bd_event_t event)
{
	bd_log("window", "handle_event handle: %ld event_id: %d\n", window, event->id);
}

BD_CLASS_CONSTRUCTOR_START(bd_window)
BD_SUPER_CONSTRUCTOR(bd_component)
BD_CLASS_METHOD(constructor, bd_window_constructor)
BD_CLASS_METHOD(destructor, bd_window_destructor)
BD_CLASS_METHOD(bd_component.render, bd_window_render)
BD_CLASS_METHOD(handle_event, bd_window_handle_event)
BD_CLASS_CONSTRUCTOR_END


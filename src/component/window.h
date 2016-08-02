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

#ifndef INCLUDE_COMPONENT_WINDOW_H_
#define INCLUDE_COMPONENT_WINDOW_H_

#include "component/component.h"
#include "event/event.h"
#include "event/queue.h"
#include "system/thread.h"
#include "render/region.h"
#include "type/list.h"

BD_CLASS(bd_window) {
	BD_EXTENDS(bd_component);

	bd_thread_t thread;
	bd_event_queue_t event_queue;

	bd_region_t clip_region;

	bd_list_t children;

	BD_BOOL is_selected;
	BD_INT selected_x;
	BD_INT selected_y;

	char* title;

	void(*handle_event)(bd_window_t window, bd_event_t event);
	void(*send_event)(bd_window_t window, bd_event_t event);

	void(*constructor)(bd_window_t window, BD_INT id);
	void(*destructor)(bd_window_t window);

	void (*set_title)(bd_window_t window, const char* title);
	void (*add_child)(bd_window_t window, bd_component_t component);

	void (*set_clip_region)(bd_window_t window, bd_region_t region);
};


#endif 

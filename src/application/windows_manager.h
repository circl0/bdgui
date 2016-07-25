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

#ifndef INCLUDE_APPLICATION_WINDOWS_MANAGER_H_
#define INCLUDE_APPLICATION_WINDOWS_MANAGER_H_

#include "type/object.h"
#include "type/list.h"
#include "component/window.h"
#include "event/queue.h"
#include "render/surface.h"
#include "application/cursor.h"

BD_CLASS(bd_windows_manager){
	BD_EXTENDS(bd_object);

	bd_list_t windows_list;
	
	bd_surface_t surface;

	bd_cursor_t cursor;

	bd_event_queue_t event_queue;
	bd_thread_t thread;

	void (*constructor)(bd_windows_manager_t manager, bd_surface_t surface);
	void (*destructor)(bd_windows_manager_t manager);

	void (*handle_event)(bd_windows_manager_t manager);
	void (*send_event)(bd_windows_manager_t manager, bd_event_t event);

	void (*add)(bd_windows_manager_t manager, bd_window_t window);
	void (*remove)(bd_windows_manager_t manager, bd_window_t window);

	void (*update_clip_region)(bd_windows_manager_t manager, bd_window_t window);
	void (*bring_to_first)(bd_windows_manager_t manager, bd_window_t window);

	bd_surface_t (*get_surface)(bd_windows_manager_t manager);
};

bd_windows_manager_t bd_windows_manager_create(bd_surface_t surface);
bd_windows_manager_t bd_windows_manager_get();
void bd_windows_manager_destroy(bd_windows_manager_t manager);


#endif 

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

#include "application/windows_manager.h"
#include "type/object.h"
#include "utils/log.h"

bd_windows_manager_t bd_windows_manager_create()
{
	bd_windows_manager_t manager = bd_windows_manager_new();
	manager->constructor(manager);
	return manager;
}

void bd_windows_manager_destroy(bd_windows_manager_t manager)
{
	manager->destructor(manager);
}

void bd_windows_manager_constructor(bd_windows_manager_t manager)
{
	manager->windows_list = bd_list_create();
}

void bd_windows_manager_destructor(bd_windows_manager_t manager)
{
	bd_list_destroy(manager->windows_list);
}

static BD_INT bd_windows_manager_render_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_window_t window = (const bd_window_t) e;
	if (window != BD_NULL) {
		BD_SUP(window, bd_component)->render(BD_SUP(window, bd_component));
	}
	return 1;
}

void bd_windows_manager_render(bd_windows_manager_t manager)
{
	if (manager == BD_NULL) {
		return;
	}
	bd_list_for_each(manager->windows_list, bd_windows_manager_render_function, BD_NULL);
}

static BD_INT bd_windows_manager_handle_event_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_window_t window = (const bd_window_t) e;
	bd_event_t event = (bd_event_t) data;

	if (window != BD_NULL && event != BD_NULL) {
		window->handle_event(window, event);
	}
	return 1;
}

void bd_windows_manager_handle_event(bd_windows_manager_t manager, bd_event_t event)
{
	if (manager == BD_NULL || event == BD_NULL) {
		return;
	}
	bd_list_for_each(manager->windows_list, bd_windows_manager_handle_event_function, event);
	if (event->id == BD_EVENT_ON_TIMER) {
		manager->render(manager);
	}
}

void bd_windows_manager_add_window(bd_windows_manager_t manager, bd_window_t window)
{
	if (manager == BD_NULL) {
		return;
	}
	bd_list_push(manager->windows_list, window);
}

static BD_INT bd_windows_manager_delete_function(const BD_HANDLE e, BD_HANDLE value) {
	if (e == value) {
		return 0;
	}
	return -1;
}

void bd_windows_manager_remove_window(bd_windows_manager_t manager, bd_window_t window)
{
	if (manager == BD_NULL) {
		return;
	}
	bd_list_remove(manager->windows_list, bd_windows_manager_delete_function, window);
}

BD_CLASS_CONSTRUCTOR_START(bd_windows_manager)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_windows_manager_constructor)
BD_CLASS_METHOD(destructor, bd_windows_manager_destructor)
BD_CLASS_METHOD(render, bd_windows_manager_render)
BD_CLASS_METHOD(handler_event, bd_windows_manager_handle_event)
BD_CLASS_METHOD(add, bd_windows_manager_add_window)
BD_CLASS_METHOD(remove, bd_windows_manager_remove_window)
BD_CLASS_CONSTRUCTOR_END

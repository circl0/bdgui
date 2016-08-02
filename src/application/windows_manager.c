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
#include "render/painter.h"
#include "render/cairo/cairo_surface.h"
#include "render/cairo/cairo_region.h"
#include "event/event.h"

static bd_windows_manager_t manager = BD_NULL;

static BD_INT bd_windows_manager_handle_event_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_window_t window = (const bd_window_t) e;
	bd_event_t event = (bd_event_t) data;

	if (window != BD_NULL && event != BD_NULL) {
		window->send_event(window, event);
	}

	return 1;
}

static BD_INT bd_windows_manager_delete_function(const BD_HANDLE e, BD_HANDLE value) 
{
	if (e == value) {
		return 0;
	}
	return -1;
}

static BD_HANDLE bd_windows_manager_thread_function(BD_HANDLE data) 
{
	bd_windows_manager_t manager = (bd_windows_manager_t) data;
	if (manager == BD_NULL) {
		return BD_NULL;
	}
	while(1) {
		manager->handle_event(manager);
	}
}


static BD_INT bd_windows_manager_clip_free_region_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_window_t window = (const bd_window_t) e;
	bd_region_t region = (bd_region_t) data;

	bd_rect bound;
	BD_SUP(window, bd_component)->get_bound(BD_SUP(window, bd_component), &bound);

	region->substract(region, &bound);

	return 1;
}

static void bd_windows_manager_clip_free_region(bd_windows_manager_t manager, bd_region_t region)
{
	bd_list_for_each(manager->windows_list, bd_windows_manager_clip_free_region_function, region);
}

static void bd_windows_render_free_region(bd_windows_manager_t mananger)
{
	bd_surface_t surface = mananger->get_surface(mananger);
	bd_rect screen = {0, 0, surface->get_width(surface), surface->get_height(surface)};
	bd_region_t screen_region = bd_region_create_by_rect(&screen);
	bd_windows_manager_clip_free_region(manager, screen_region);

	surface->lock(surface);
	bd_painter_t painter = surface->get_painter(surface);

	painter->reset_clip(painter);

	bd_color c = {0, 0, 0};
	painter->set_color(painter, c);

	for (BD_INT i = 0; i < screen_region->get_rectangle_num(screen_region); ++i) {
		bd_rect rect;
		screen_region->get_rectangle(screen_region, i, &rect);
		painter->draw_rect(painter, &rect);
		painter->fill(painter);
	}

	surface->unlock(surface);
}

static void bd_windows_handle_window_update_finish_event(bd_windows_manager_t manager, bd_event_t event)
{
	if (manager == BD_NULL || event == BD_NULL) {
		return;
	}

	bd_window_update_finish_event_t window_update_finish_event = BD_SUB(event, bd_event, bd_window_update_finish_event);
	bd_event_t target_event = window_update_finish_event->event;

	target_event->finished++;
	printf("target_event %d\n", target_event->finished);
	if (target_event->finished == bd_list_size(manager->windows_list)) {
		// printf("bd_windows_handle_window_update_finish_event\n");
		switch(target_event->id) {
			case BD_EVENT_WINDOW_INVALIDATE:
				printf("BD_EVENT_WINDOW_INVALIDATE finish\n");
				bd_window_invalidate_event_delete(BD_SUB(target_event, bd_event, bd_window_invalidate_event));
				bd_windows_render_free_region(manager);

				break;
			default:
				break;
		}
	}
	bd_window_update_finish_event_delete(window_update_finish_event);
}

static BD_INT bd_windows_manager_bring_to_first_function(const BD_HANDLE e, BD_HANDLE value)
{
	if (e == value) {
		return 0;
	}
	return 1;
}

bd_windows_manager_t bd_windows_manager_create(bd_surface_t surface)
{
	if (manager == BD_NULL) {
		manager = bd_windows_manager_new();
		manager->constructor(manager, surface);
	}
	return manager;
}

bd_windows_manager_t bd_windows_manager_get()
{
	return manager;
}

void bd_windows_manager_destroy(bd_windows_manager_t manager)
{
	bd_windows_manager_delete(manager);
}

void bd_windows_manager_constructor(bd_windows_manager_t manager, bd_surface_t surface)
{
	manager->surface = surface;
	manager->cursor = bd_cursor_create();
	manager->windows_list = bd_list_create();
	manager->event_queue = bd_event_queue_create();
	manager->windows_region = BD_NULL;
	manager->thread = bd_thread_create(bd_windows_manager_thread_function);
	manager->thread->start(manager->thread, manager);

	bd_window_manager_invalidate_event_t invalidate_event = bd_window_manager_invalidate_event_new();
	invalidate_event->constructor(invalidate_event);
	manager->send_event(manager, BD_SUP(invalidate_event, bd_event));
}

void bd_windows_manager_destructor(bd_windows_manager_t manager)
{
	bd_event_queue_destroy(manager->event_queue);
	bd_list_destroy(manager->windows_list);
	bd_surface_destroy(manager->surface);
	bd_cursor_destroy(manager->cursor);
}

void bd_windows_manager_send_event(bd_windows_manager_t manager, bd_event_t event)
{
	if (manager == BD_NULL || manager->event_queue == BD_NULL || event == BD_NULL) {
		return;
	}
	bd_event_queue_push(manager->event_queue, event);
}

void bd_windows_manager_handle_event(bd_windows_manager_t manager)
{
	if (manager == BD_NULL || manager->event_queue == BD_NULL) {
		return;
	}

	bd_event_t event = bd_event_queue_get(manager->event_queue);
	if (event == BD_NULL) {
		return;
	}

	switch(event->id) {
		case BD_EVENT_ON_MOUSE_BUTTON:
		{
			bd_surface_t surface = manager->get_surface(manager);
			bd_mouse_button_event_t mouse_button_event = BD_SUB(event, bd_event, bd_mouse_button_event);
			mouse_button_event->x = mouse_button_event->x * surface->get_width(surface) / 255;
			mouse_button_event->y = mouse_button_event->y * surface->get_height(surface) / 255;
			printf("BD_EVENT_ON_MOUSE_BUTTON %d, %d\n", mouse_button_event->x, mouse_button_event->y);
			break;
		}
		case BD_EVENT_ON_MOUSE_MOVE:
		{
			bd_surface_t surface = manager->get_surface(manager);
			bd_mouse_move_event_t mouse_move_event = BD_SUB(event, bd_event, bd_mouse_move_event);
			mouse_move_event->x = mouse_move_event->x * surface->get_width(surface) / 255;
			mouse_move_event->y = mouse_move_event->y * surface->get_height(surface) / 255;
			printf("BD_EVENT_ON_MOUSE_MOVE %d, %d\n", mouse_move_event->x, mouse_move_event->y);
			break;			
		}
		case BD_EVENT_WINDOW_UPDATE_FINISH:
		{
			bd_windows_handle_window_update_finish_event(manager, event);
			return;
		}
		case BD_EVENT_ON_INVALIDATE:
		{
			bd_window_manager_invalidate_event_delete(BD_SUB(event, bd_event, bd_window_manager_invalidate_event));
			
			manager->update_clip_region(manager);

			bd_window_invalidate_event_t window_invalidate_event = bd_window_invalidate_event_new();
			window_invalidate_event->constructor(window_invalidate_event);
			window_invalidate_event->object = BD_INVALIDATE_FROM_WINDOW_MANAGER;
			event = BD_SUP(window_invalidate_event, bd_event);

			bd_surface_t surface = manager->get_surface(manager);
			break;
		}
	}

	// 3. send event to all the windows
	bd_list_for_each(manager->windows_list, bd_windows_manager_handle_event_function, event);
}

void bd_windows_manager_add_window(bd_windows_manager_t manager, bd_window_t window)
{
	if (manager == BD_NULL) {
		return;
	}
	bd_list_push(manager->windows_list, window);
}

void bd_windows_manager_remove_window(bd_windows_manager_t manager, bd_window_t window)
{
	if (manager == BD_NULL) {
		return;
	}
	bd_list_remove(manager->windows_list, bd_windows_manager_delete_function, window);
}

bd_surface_t bd_windows_manager_get_surface(bd_windows_manager_t manager)
{
	if (manager == BD_NULL) {
		return;
	}
	return manager->surface;
}

static BD_INT bd_windows_manager_update_clip_region_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_window_t window = (const bd_window_t) e;
	bd_region_t region = (bd_window_t) data;
	printf("region %d\n", region->get_rectangle_num(region));
	bd_rect bound;
	BD_SUP(window, bd_component)->get_bound(BD_SUP(window, bd_component), &bound);

	bd_region_t clip_region = bd_region_create_by_rect(&bound);

	clip_region->substract_region(clip_region, region);
	printf("clip_region %d\n", clip_region->get_rectangle_num(clip_region));

	window->set_clip_region(window, clip_region);
	region->add(region, &bound);

	return 1;
}

void bd_windows_manager_update_clip_region(bd_windows_manager_t manager)
{
	if (manager->windows_region == BD_NULL) {
		manager->windows_region = bd_region_create();
	}
	bd_list_for_each(manager->windows_list, bd_windows_manager_update_clip_region_function, manager->windows_region);

	bd_region_destroy(manager->windows_region);
	manager->windows_region = BD_NULL;
}

void bd_windows_manager_bring_to_first(bd_windows_manager_t manager, bd_window_t window)
{
	bd_list_bring_to_first(manager->windows_list, bd_windows_manager_bring_to_first_function, window);
}

BD_CLASS_CONSTRUCTOR_START(bd_windows_manager)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_windows_manager_constructor)
BD_CLASS_METHOD(destructor, bd_windows_manager_destructor)
BD_CLASS_METHOD(handle_event, bd_windows_manager_handle_event)
BD_CLASS_METHOD(send_event, bd_windows_manager_send_event)
BD_CLASS_METHOD(add, bd_windows_manager_add_window)
BD_CLASS_METHOD(remove, bd_windows_manager_remove_window)
BD_CLASS_METHOD(get_surface, bd_windows_manager_get_surface)
BD_CLASS_METHOD(update_clip_region, bd_windows_manager_update_clip_region)
BD_CLASS_METHOD(bring_to_first, bd_windows_manager_bring_to_first)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_windows_manager)
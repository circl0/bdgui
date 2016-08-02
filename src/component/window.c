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
#include "render/painter.h"
#include "type/type.h"
#include "application/windows_manager.h"
#include "system/system.h"
#include "event/event.h"
#include "render/cairo/cairo_region.h"
#include "render/region.h"

static BD_HANDLE bd_window_thread_function(BD_HANDLE data)
{
	bd_window_t window = (bd_window_t) data;
	bd_event_queue_t event_queue = window->event_queue;
	while(1) {
		bd_event_t event = bd_event_queue_get(event_queue);
		if (event == BD_NULL) {
			continue;
		}
		window->handle_event(window, event);
	}
	return BD_NULL;
}

static BD_INT bd_windows_manager_render_children_function(const BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	const bd_component_t component = (const bd_component_t) e;
	bd_surface_t surface = (bd_surface_t) data;
	component->on_render(component, surface);
	return 1;
}

static void bd_windows_manager_render_children(bd_window_t window)
{
	bd_list_t children = window->children;
	bd_windows_manager_t manager = bd_windows_manager_get();
	bd_surface_t surface = manager->get_surface(manager);
	bd_list_for_each(children, bd_windows_manager_render_children_function, surface);
}

void bd_window_constructor(bd_window_t window, BD_INT id)
{
	BD_SUP(window, bd_component)->constructor(BD_SUP(window, bd_component), id);
	window->clip_region = BD_NULL;
	window->event_queue = bd_event_queue_create();
	window->thread = bd_thread_create(bd_window_thread_function);
	window->children = bd_list_create();
	window->is_selected = BD_FALSE;
	window->thread->start(window->thread, window);

}

void bd_window_destructor(bd_window_t window)
{

}

void bd_window_invalidate(bd_component_t component)
{
	bd_window_t window = BD_SUB(component, bd_component, bd_window);
	bd_window_invalidate_event_t invalidate_event = bd_window_invalidate_event_new();
	invalidate_event->constructor(invalidate_event);
	window->send_event(window, (BD_SUP(invalidate_event, bd_event)));
}

void bd_window_on_render(bd_component_t component, bd_surface_t surface)
{
	surface->lock(surface);

	printf("start render %ld us\n", bd_get_tick_count());
	bd_window_t window = BD_SUB(component, bd_component, bd_window);
	bd_painter_t painter = surface->get_painter(surface);

	painter->clip(painter, window->clip_region);

	bd_color c1 = {0xbf, 0xbf, 0xbf};
    painter->set_color(painter, c1);
    painter->set_line_width(painter, 1);
    bd_rect rect1 = { component->x, component->y, component->width, component->height };
    painter->draw_rect(painter, &rect1);
    painter->fill(painter);

	bd_color c2 = {0x00, 0x00, 0x80};
    painter->set_color(painter, c2);
    bd_rect rect2 = { component->x + 2, component->y + 2, component->width - 4, 20 };
    painter->draw_rect(painter, &rect2);
    painter->fill(painter);

    bd_color c3 = {255, 255, 255};
    painter->set_font(painter, "Songti");
    painter->set_color(painter, c3);
	painter->set_font_size(painter, 16);
	painter->draw_text(painter, component->x + 5, component->y + 16, "BDGUI");
    
    bd_color c5 = {0, 0, 0};
    painter->set_font(painter, "Songti");
    painter->set_color(painter, c5);
	painter->set_font_size(painter, 24);
	painter->draw_text(painter, component->x + 55, component->y + 66, "BDGUI");

    painter->set_line_width(painter, 1);
	bd_color c7 = {0xdf, 0xdf, 0xdf};
	painter->set_color(painter, c7);
	painter->draw_line(painter, component->x, component->y, component->x + component->width, component->y);
	painter->draw_line(painter, component->x, component->y, component->x, component->y + component->height);
	bd_color c8 = {0x5f, 0x5f, 0x5f};
	painter->set_color(painter, c8);
	painter->draw_line(painter, component->x + component->width, component->y + component->height, component->x + component->width, component->y + 1);
	painter->draw_line(painter, component->x + component->width, component->y + component->height, component->x + 1, component->y + component->height);
	bd_color c9 = {0, 0, 0};
	painter->set_color(painter, c9);
	painter->draw_line(painter, component->x + component->width + 1, component->y + component->height + 1, component->x + component->width + 1, component->y + 1);
	painter->draw_line(painter, component->x + component->width + 1, component->y + component->height + 1, component->x + 1, component->y + component->height + 1);

	bd_windows_manager_render_children(window);

    printf("end render %ld us\n", bd_get_tick_count());

	surface->flip(surface);
    surface->unlock(surface);
}

void bd_window_handle_event(bd_window_t window, bd_event_t event)
{
	switch(event->id) {
		case BD_EVENT_WINDOW_INVALIDATE:
		{
			bd_window_invalidate_event_t invalidate_event = BD_SUB(event, bd_event, bd_window_invalidate_event);
			bd_component_t component = BD_SUP(window, bd_component);
			bd_windows_manager_t manager = bd_windows_manager_get();
			bd_surface_t surface = manager->get_surface(manager);

			// render
			component->on_render(component, surface);

			// send render finish if from windows manager
			if (invalidate_event->object == BD_INVALIDATE_FROM_WINDOW_MANAGER) {
				bd_window_update_finish_event_t update_finish_event = bd_window_update_finish_event_new();
				update_finish_event->constructor(update_finish_event);
				update_finish_event->event = invalidate_event;
				manager->send_event(manager, BD_SUP(update_finish_event, bd_event));
			}

			break;
		}
		case BD_EVENT_WINDOW_MOVE:
		{
			bd_windows_manager_t manager = bd_windows_manager_get();
			// callback
			bd_window_manager_invalidate_event_t invalidate_event = bd_window_manager_invalidate_event_new();
			invalidate_event->constructor(invalidate_event);
			manager->send_event(manager, BD_SUP(invalidate_event, bd_event));
			break;
		}
		case BD_EVENT_WINDOW_RESIZE:
		{
			bd_windows_manager_t manager = bd_windows_manager_get();
			// callback
			bd_window_manager_invalidate_event_t invalidate_event = bd_window_manager_invalidate_event_new();
			invalidate_event->constructor(invalidate_event);
			manager->send_event(manager, BD_SUP(invalidate_event, bd_event));
			break;
		}
		case BD_EVENT_ON_MOUSE_BUTTON:
		{
			// callback
			bd_mouse_button_event_t mouse_button_event = BD_SUB(event, bd_event, bd_mouse_button_event);
			bd_windows_manager_t manager = bd_windows_manager_get();
			switch(mouse_button_event->button) {
				case BD_MOUSE_BUTTON_LEFT:
				{
					if (mouse_button_event->action == BD_MOUSE_BUTTON_DOWN) {
						if (window->clip_region->contains_point(window->clip_region, mouse_button_event->x, mouse_button_event->y)) {
							manager->bring_to_first(manager, window);

							window->is_selected = BD_TRUE;

							window->selected_x = mouse_button_event->x;
							window->selected_y = mouse_button_event->y;	

							bd_window_manager_invalidate_event_t invalidate_event = bd_window_manager_invalidate_event_new();
							invalidate_event->constructor(invalidate_event);
							manager->send_event(manager, BD_SUP(invalidate_event, bd_event));
						}
					}
					else if (mouse_button_event->action == BD_MOUSE_BUTTON_UP) {
						window->is_selected = BD_FALSE;
					}
					break;
				}
				case BD_MOUSE_BUTTON_WHEEL:
					break;
				case BD_MOUSE_BUTTON_RIGHT:
					break;
			}
			break;
		}
		case BD_EVENT_ON_MOUSE_MOVE:
		{
			bd_mouse_move_event_t mouse_move_event = BD_SUB(event, bd_event, bd_mouse_move_event);
			if (window->is_selected) {
				bd_component_t c = BD_SUP(window, bd_component);

				c->move(c, mouse_move_event->x - window->selected_x, mouse_move_event->y -  window->selected_y);
				window->selected_x = mouse_move_event->x;
				window->selected_y = mouse_move_event->y;

				bd_windows_manager_t manager = bd_windows_manager_get();
				bd_window_manager_invalidate_event_t invalidate_event = bd_window_manager_invalidate_event_new();
				invalidate_event->constructor(invalidate_event);
				manager->send_event(manager, BD_SUP(invalidate_event, bd_event));
			}
			break;
		}
		default:
			break;
	}
}

void bd_window_send_event(bd_window_t window, bd_event_t event)
{
	if (window == BD_NULL || window->event_queue == BD_NULL) {
		return;
	}
	bd_event_queue_t event_queue = window->event_queue;
	bd_event_queue_push(event_queue, event);
}

void bd_window_set_title(bd_window_t window, const char* title)
{
	window->set_title(window, title);
}

void bd_window_get_bound(bd_component_t c, bd_rect_t rect)
{
	rect->x = c->get_x(c);
	rect->y = c->get_y(c);
	rect->width = c->get_width(c);
	rect->height = c->get_height(c);
}

void bd_window_resize(bd_component_t component, BD_INT width, BD_INT height)
{
	bd_window_t window = BD_SUB(component, bd_component, bd_window);
	component->width = width;
	component->height = height;
	bd_window_resize_event_t window_resize_event = bd_window_resize_event_new();
	window_resize_event->constructor(window_resize_event);
	window_resize_event->width = width;
	window_resize_event->height = height;
	window->send_event(window, BD_SUP(window_resize_event, bd_event));
}

void bd_window_add_child(bd_window_t window, bd_component_t component)
{
	bd_list_push(window->children, component);
}

void bd_window_set_clip_region(bd_window_t window, bd_region_t region)
{
	window->clip_region = region;
}

BD_CLASS_CONSTRUCTOR_START(bd_window)
BD_SUPER_CONSTRUCTOR(bd_component)
BD_CLASS_METHOD(bd_component.on_render, bd_window_on_render)
BD_CLASS_METHOD(bd_component.invalidate, bd_window_invalidate)
BD_CLASS_METHOD(bd_component.get_bound, bd_window_get_bound)
BD_CLASS_METHOD(bd_component.resize, bd_window_resize)
BD_CLASS_METHOD(constructor, bd_window_constructor)
BD_CLASS_METHOD(destructor, bd_window_destructor)
BD_CLASS_METHOD(send_event, bd_window_send_event)
BD_CLASS_METHOD(handle_event, bd_window_handle_event)
BD_CLASS_METHOD(add_child, bd_window_add_child)
BD_CLASS_METHOD(set_title, bd_window_set_title)
BD_CLASS_METHOD(set_clip_region, bd_window_set_clip_region)

BD_CLASS_CONSTRUCTOR_END


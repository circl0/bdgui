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


#ifndef BDGUI_EVENTS_H
#define BDGUI_EVENTS_H

#include "event/base.h"
#include "system/timer.h"
#include "component/window.h"

typedef enum bd_mouse_button {
	BD_MOUSE_BUTTON_LEFT = 0,
	BD_MOUSE_BUTTON_WHEEL,
	BD_MOUSE_BUTTON_RIGHT
} bd_mouse_button;

typedef enum bd_mouse_button_action {
	BD_MOUSE_BUTTON_UP = 0,
	BD_MOUSE_BUTTON_DOWN
} bd_mouse_button_action;

typedef enum bd_render_status {
	BD_RENDER_MOUSE_START = 0,
	BD_RENDER_MOUSE_FINISH
} bd_render_status;

typedef enum bd_window_invalidate_from_object {
	BD_INVALIDATE_FROM_WINDOW = 0,
	BD_INVALIDATE_FROM_WINDOW_MANAGER,
} bd_window_invalidate_from_object;

typedef enum bd_mouse_move_direction {
	BD_MOUSE_MOVE_DIRECTION_X = 0,
	BD_MOUSE_MOVE_DIRECTION_Y
} bd_mouse_move_direction;

BD_CLASS(bd_touch_event) {
	BD_EXTENDS(bd_event);
	BD_INT x;
	BD_INT y;
    void(*constructor)(bd_touch_event_t self);
    void(*destructor)(bd_touch_event_t self);
};

BD_CLASS(bd_keyboard_event) {
	BD_EXTENDS(bd_event);
	bd_event base;
	BD_INT code;
    void(*constructor)(bd_keyboard_event_t self);
    void(*destructor)(bd_keyboard_event_t self);
};

BD_CLASS(bd_timer_event) {
	BD_EXTENDS(bd_event);
	bd_timer_t timer;
    void(*constructor)(bd_timer_event_t self);
    void(*destructor)(bd_timer_event_t self);
};

BD_CLASS(bd_window_invalidate_event) {
	BD_EXTENDS(bd_event);
	bd_window_invalidate_from_object object;
    void(*constructor)(bd_window_invalidate_event_t self);
    void(*destructor)(bd_window_invalidate_event_t self);
};

BD_CLASS(bd_window_manager_invalidate_event) {
	BD_EXTENDS(bd_event);
	bd_window_invalidate_from_object object;
    void(*constructor)(bd_window_invalidate_event_t self);
    void(*destructor)(bd_window_invalidate_event_t self);
};

BD_CLASS(bd_window_update_finish_event) {
	BD_EXTENDS(bd_event);
	bd_event_t event;
    void(*constructor)(bd_window_update_finish_event_t self);
    void(*destructor)(bd_window_update_finish_event_t self);
};

BD_CLASS(bd_window_move_event) {
	BD_EXTENDS(bd_event);
	BD_INT x;
	BD_INT y;
	void(*constructor)(bd_window_move_event_t self);
    void(*destructor)(bd_window_move_event_t self);
};

BD_CLASS(bd_window_resize_event) {
	BD_EXTENDS(bd_event);
	BD_INT width;
	BD_INT height;
	void(*constructor)(bd_window_resize_event_t self);
    void(*destructor)(bd_window_resize_event_t self);
};

BD_CLASS(bd_mouse_move_event) {
	BD_EXTENDS(bd_event);
	BD_INT x;
	BD_INT y;
	bd_mouse_move_direction direction;
	void(*constructor)(bd_window_move_event_t self);
    void(*destructor)(bd_window_move_event_t self);
};

BD_CLASS(bd_mouse_button_event) {
	BD_EXTENDS(bd_event);
	bd_mouse_button_action action;
	bd_mouse_button button;
	BD_INT x;
	BD_INT y;
	void(*constructor)(bd_window_move_event_t self);
    void(*destructor)(bd_window_move_event_t self);
};

#endif //BDGUI_EVENTS_H

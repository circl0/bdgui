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

#include "type/object.h"
#include "type/type.h"
//#include "system/timer.h"

#define BD_EVENT_NUM_MAX	256

// event id
typedef enum bd_event_id {
    BD_EVENT_INVALID = -1,
	BD_EVENT_ON_TIMER,
	BD_EVENT_ON_MOUSE_BUTTON,
	BD_EVENT_ON_MOUSE_MOVE,
	BD_EVENT_ON_MOUSE_DRAG,
	BD_EVENT_ON_KEYBOARD,
	BD_EVENT_ON_TOUCH,
	BD_EVENT_ON_INVALIDATE,

	BD_EVENT_WINDOW_INVALIDATE,
	BD_EVENT_WINDOW_UPDATE_FINISH,
	BD_EVENT_WINDOW_MOVE,
	BD_EVENT_WINDOW_RESIZE,
	BD_EVENT_MAX = BD_EVENT_NUM_MAX,
} bd_event_id;

// event base
BD_ABSTRACT_CLASS(bd_event) {
	BD_EXTENDS(bd_object);

    bd_event_id id;
    bd_object_t sender;
    BD_INT finished;

    void(*constructor)(bd_event_t self, bd_event_id id);
    void(*destructor)(bd_event_t self);
    bd_event_t (*clone)(bd_event_t self);
};

// event arg
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

// events
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
	BD_INT id;
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
    void(*constructor)(bd_window_manager_invalidate_event_t self);
    void(*destructor)(bd_window_manager_invalidate_event_t self);
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
	void(*constructor)(bd_mouse_move_event_t self);
    void(*destructor)(bd_mouse_move_event_t self);
};

BD_CLASS(bd_mouse_button_event) {
	BD_EXTENDS(bd_event);
	bd_mouse_button_action action;
	bd_mouse_button button;
	BD_INT x;
	BD_INT y;
	void(*constructor)(bd_mouse_button_event_t self);
    void(*destructor)(bd_mouse_button_event_t self);
};

BD_CLASS(bd_mouse_drag_event) {
	BD_EXTENDS(bd_event);
	bd_mouse_button button;
	BD_INT start_x;
	BD_INT start_y;
	BD_INT current_x;
	BD_INT current_y;
	void(*constructor)(bd_window_move_event_t self);
    void(*destructor)(bd_window_move_event_t self);
};


#endif

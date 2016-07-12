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

typedef enum bd_mouse_button_type {
	BD_INPUT_MOUSE_NONE = 0,
	BD_INPUT_MOUSE_LEFT,
	BD_INPUT_MOUSE_MIDDLE,
	BD_INPUT_MOUSE_RIGHT
} bd_mouse_button_type;

BD_CLASS(bd_mouse_event) {
	EXTENDS(bd_event);
	BD_INT x;
	BD_INT y;
	bd_mouse_button_type which;
    void(*constructor)(bd_mouse_event_t self);
    void(*destructor)(bd_mouse_event_t self);
};

BD_CLASS(bd_touch_event) {
	EXTENDS(bd_event);
	BD_INT x;
	BD_INT y;
    void(*constructor)(bd_touch_event_t self);
    void(*destructor)(bd_touch_event_t self);
};

BD_CLASS(bd_keyboard_event) {
	EXTENDS(bd_event);
	bd_event base;
	BD_INT code;
    void(*constructor)(bd_keyboard_event_t self);
    void(*destructor)(bd_keyboard_event_t self);
};

BD_CLASS(bd_timer_event) {
	EXTENDS(bd_event);
	bd_timer_t timer;
    void(*constructor)(bd_timer_event_t self);
    void(*destructor)(bd_timer_event_t self);
};

#endif //BDGUI_EVENTS_H

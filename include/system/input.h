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


#ifndef INCLUDE_SYSTEM_LINUX_INPUT_H_
#define INCLUDE_SYSTEM_LINUX_INPUT_H_

#include "type/type.h"
#include "event/base.h"
#include "system/source.h"

typedef enum bd_input_type {
	BD_INPUT_INVALID = -1,
	BD_INPUT_MOUSE,
	BD_INPUT_TOUCH,
	BD_INPUT_KEYBOARD
} bd_input_type;

typedef enum bd_mouse_button_type {
	BD_INPUT_MOUSE_NONE = 0,
	BD_INPUT_MOUSE_LEFT,
	BD_INPUT_MOUSE_MIDDLE,
	BD_INPUT_MOUSE_RIGHT
} bd_mouse_button_type;

typedef struct bd_mouse_event {
	bd_event base;
	BD_INT x;
	BD_INT y;
	bd_mouse_button_type which;
} bd_mouse_event, *bd_mouse_event_t;

typedef struct bd_touch_event {
	bd_event base;
	BD_INT x;
	BD_INT y;
	BD_INT which;
} bd_touch_event, *bd_touch_event_t;

typedef struct bd_keyboard_event {
	bd_event base;
	BD_INT code;
} bd_keyboard_event, *bd_keyboard_event_t;

struct bd_input_dev;
typedef struct bd_input_dev bd_input_dev, *bd_input_dev_t;

bd_input_dev_t bd_input_dev_create(const char* name, bd_input_type type);
BD_INT bd_input_dev_open(bd_input_dev_t dev);
BD_INT bd_input_dev_close(bd_input_dev_t dev, BD_UINT size);

bd_event_t bd_input_dev_read_event(bd_input_dev_t dev);

#endif /* INCLUDE_SYSTEM_LINUX_INPUT_H_ */

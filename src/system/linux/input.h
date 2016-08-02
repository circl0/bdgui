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

#include "system/linux/source_pool.h"
#include "event/event.h"

typedef struct bd_linux_mouse_status {
	BD_INT x;
	BD_INT y;
	BD_INT button;
	BD_INT start_point[3][2];
} bd_linux_mouse_status;

typedef struct bd_linux_keyboard_status {

} bd_linux_keyboard_status;

typedef struct bd_linux_touch_status {

} bd_linux_touch_status;

typedef union bd_linux_input_status {
	bd_linux_mouse_status mouse_status;
	bd_linux_keyboard_status keyboard_status;
	bd_linux_touch_status touch_status;
} bd_linux_input_status;

BD_CLASS(bd_input_internal) {

	BD_INT fd;
	bd_linux_input_status input_status;

	void(*constructor)(bd_input_internal_t input);
	void(*destructor)(bd_input_internal_t input);

	BD_INT(*open)(bd_input_internal_t input, const char* name);
	BD_INT(*close)(bd_input_internal_t input);
	bd_event_t(*read)(bd_input_internal_t input, bd_input_type type);

};

bd_input_internal_t bd_input_internal_create();
void bd_input_internal_destroy(bd_input_internal_t input);

#endif 

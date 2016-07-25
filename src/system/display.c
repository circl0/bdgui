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

#include "system/display.h"
#include "type/type.h"

void bd_display_constructor(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	display->screen_width = 0;
	display->screen_height = 0;
	display->color_type = BD_COLOR_RGB565;
	bd_mutex_init(&display->mutex);
}

void bd_display_destructor(bd_display_t display)
{

}

BD_UINT bd_display_get_screen_width(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->screen_width;
}

BD_UINT bd_display_get_screen_height(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->screen_height;
}

bd_color_type bd_display_get_color_type(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->color_type;
}

void bd_display_lock(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	bd_mutex_lock(&display->mutex);
}

void bd_display_unlock(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	bd_mutex_unlock(&display->mutex);
}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_display)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_display_constructor)
BD_CLASS_METHOD(destructor, bd_display_destructor)
BD_CLASS_METHOD(lock, bd_display_lock)
BD_CLASS_METHOD(unlock, bd_display_unlock)
BD_CLASS_METHOD(get_screen_width, bd_display_get_screen_width)
BD_CLASS_METHOD(get_screen_height, bd_display_get_screen_height)
BD_CLASS_METHOD(get_color_type, bd_display_get_color_type)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END
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

bd_display_t bd_display_create()
{
	bd_display_t display = bd_display_new();
	display->constructor(display);
	return display;
}

void bd_display_destroy(bd_display_t display)
{
	bd_display_delete(display);
}

void bd_display_constructor(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	display->mutex = bd_mutex_create();
	display->display_internal = bd_display_internal_create();
}

void bd_display_destructor(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	bd_display_internal_destroy(display->display_internal);
	bd_mutex_destroy(display->mutex);
}

BD_UINT bd_display_get_screen_width(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->display_internal->get_width(display->display_internal);
}

BD_UINT bd_display_get_screen_height(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->display_internal->get_height(display->display_internal);
}

bd_color_type bd_display_get_color_type(bd_display_t display)
{
	if (display == BD_NULL) {
		return 0;
	}
	return display->display_internal->get_color_type(display->display_internal);
}

BD_INT bd_display_open(bd_display_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	return display->display_internal->open(display->display_internal);
}

BD_INT bd_display_close(bd_display_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	return display->display_internal->close(display->display_internal);
}

void bd_display_flip(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	display->display_internal->flip(display->display_internal);
}

BD_HANDLE bd_display_get_buffer(bd_display_t display)
{
	if (display == BD_NULL) {
		return BD_NULL;
	}
	return (BD_HANDLE)(display->display_internal->get_buffer(display->display_internal));
}

void bd_display_lock(bd_display_t display)
{
	display->mutex->lock(display->mutex);
}

void bd_display_unlock(bd_display_t display)
{
	display->mutex->unlock(display->mutex);
}

BD_CLASS_CONSTRUCTOR_START(bd_display)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_display_constructor)
BD_CLASS_METHOD(destructor, bd_display_destructor)
BD_CLASS_METHOD(get_screen_width, bd_display_get_screen_width)
BD_CLASS_METHOD(get_screen_height, bd_display_get_screen_height)
BD_CLASS_METHOD(get_color_type, bd_display_get_color_type)
BD_CLASS_METHOD(get_buffer, bd_display_get_buffer)
BD_CLASS_METHOD(open, bd_display_open)
BD_CLASS_METHOD(close, bd_display_close)
BD_CLASS_METHOD(flip, bd_display_flip)
BD_CLASS_METHOD(lock, bd_display_lock)
BD_CLASS_METHOD(unlock, bd_display_unlock)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_display)
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

#include "system/display.h"
#include "system/linux/display.h"
#include "system/linux/framebuffer.h"
#include "utils/log.h"

bd_display_internal_t bd_display_internal_create()
{
	bd_display_internal_t display = bd_display_internal_new();
	display->constructor(display);
	return display;
}

void bd_display_internal_destroy(bd_display_internal_t display)
{
	bd_display_internal_delete(display);
}

void bd_linux_display_constructor(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return;
	}

	display->fb = bd_fb_dev_create();
}

void bd_linux_display_destructor(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return;
	}
	
	bd_fb_dev_destroy(display->fb);

	display->destructor(display);	
}

BD_INT bd_linux_display_open(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	BD_INT result = bd_fb_dev_open(display->fb);
	if (result < 0) {
		return -1;
	}
	return 0;
}

BD_INT bd_linux_display_close(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	return bd_fb_dev_close(display->fb);
}

void bd_linux_display_flip(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return;
	}
	bd_fb_dev_flip(display->fb);
}

BD_HANDLE bd_linux_display_get_buffer(bd_display_internal_t display)
{
	if (display == BD_NULL) {
		return BD_NULL;
	}
	return display->fb->back_buffer;
}

BD_UINT bd_linux_display_get_width(bd_display_internal_t display)
{
	return display->fb->width;
}

BD_UINT bd_linux_display_get_height(bd_display_internal_t display)
{
	return display->fb->height;
}

bd_color_type bd_linux_display_get_color_type(bd_display_internal_t display)
{
	return BD_COLOR_RGB565;
}

BD_CLASS_CONSTRUCTOR_START(bd_display_internal)
BD_CLASS_METHOD(constructor, bd_linux_display_constructor)
BD_CLASS_METHOD(destructor, bd_linux_display_destructor)
BD_CLASS_METHOD(open, bd_linux_display_open)
BD_CLASS_METHOD(close, bd_linux_display_close)
BD_CLASS_METHOD(flip, bd_linux_display_flip)
BD_CLASS_METHOD(get_buffer, bd_linux_display_get_buffer)
BD_CLASS_METHOD(get_width, bd_linux_display_get_width)
BD_CLASS_METHOD(get_height, bd_linux_display_get_height)
BD_CLASS_METHOD(get_color_type, bd_linux_display_get_color_type)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_display_internal)

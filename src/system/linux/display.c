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

bd_display_t bd_display_create()
{
	bd_linux_display_t linux_display = bd_linux_display_new();
	linux_display->constructor(linux_display);
	return BD_SUP(linux_display, bd_display);
}

void bd_display_destroy(bd_display_t display)
{
	bd_linux_display_t linux_display = BD_SUB(display, bd_display, bd_linux_display);
	bd_linux_display_delete(linux_display);
}

void bd_linux_display_constructor(bd_linux_display_t linux_display)
{
	if (linux_display == BD_NULL) {
		return;
	}
	bd_display_t display = BD_SUP(linux_display, bd_display);
	display->constructor(display);

	linux_display->fb = bd_fb_dev_create();
}

void bd_linux_display_destructor(bd_linux_display_t linux_display)
{
	if (linux_display == BD_NULL) {
		return;
	}
	
	bd_fb_dev_destroy(linux_display->fb);

	bd_display_t display = BD_SUP(linux_display, bd_display);
	display->destructor(display);	
}

BD_INT bd_linux_display_open(bd_display_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	bd_linux_display_t linux_display = BD_SUB(display, bd_display, bd_linux_display);
	BD_INT result = bd_fb_dev_open(linux_display->fb);
	if (result < 0) {
		return -1;
	}
	display->screen_width = linux_display->fb->width;
	display->screen_height = linux_display->fb->height;
	display->color_type = BD_COLOR_RGB565;
}

BD_INT bd_linux_display_close(bd_display_t display)
{
	if (display == BD_NULL) {
		return -1;
	}
	bd_linux_display_t linux_display = BD_SUB(display, bd_display, bd_linux_display);
	return bd_fb_dev_close(linux_display->fb);
}

void bd_linux_display_flip(bd_display_t display)
{
	if (display == BD_NULL) {
		return;
	}
	bd_linux_display_t linux_display = BD_SUB(display, bd_display, bd_linux_display);
	bd_fb_dev_flip(linux_display->fb);
}

BD_HANDLE bd_linux_display_get_buffer(bd_display_t display)
{
	if (display == BD_NULL) {
		return BD_NULL;
	}
	bd_linux_display_t linux_display = BD_SUB(display, bd_display, bd_linux_display);
	return linux_display->fb->back_buffer;
}

BD_CLASS_CONSTRUCTOR_START(bd_linux_display)
BD_SUPER_CONSTRUCTOR(bd_display)
BD_CLASS_METHOD(constructor, bd_linux_display_constructor)
BD_CLASS_METHOD(destructor, bd_linux_display_destructor)
BD_CLASS_METHOD(bd_display.open, bd_linux_display_open)
BD_CLASS_METHOD(bd_display.close, bd_linux_display_close)
BD_CLASS_METHOD(bd_display.flip, bd_linux_display_flip)
BD_CLASS_METHOD(bd_display.get_buffer, bd_linux_display_get_buffer)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_linux_display)

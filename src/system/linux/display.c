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
#include "system/linux/framebuffer.h"

static bd_fb_dev_t fb = BD_NULL;

BD_INT bd_open_display()
{
	if (fb == BD_NULL) {
		fb = bd_fb_dev_create();
	}

	if (fb == BD_NULL) {
		return -1;
	}

	return bd_fb_dev_open(fb);
}

BD_INT bd_close_display()
{
	if (fb == BD_NULL) {
		return -1;
	}

	return bd_fb_dev_close(fb);
}

BD_UINT bd_get_screen_width()
{
	if (fb == BD_NULL) {
		return -1;
	}
	return fb->width;
}

BD_UINT bd_get_screen_height()
{
	if (fb == BD_NULL) {
		return -1;
	}
	return fb->height;
}

void bd_paint_pixel(BD_UINT x, BD_UINT y,
		bd_color c)
{
	if (fb == BD_NULL) {
		return;
	}
	bd_fb_dev_paint_pixel(fb, x, y, c.r, c.g, c.b);
}

void bd_paint_start()
{
	if (fb == BD_NULL) {
		return;
	}
}

void bd_paint_finish()
{
	if (fb == BD_NULL) {
		return;
	}
	bd_fb_dev_flip(fb);
}

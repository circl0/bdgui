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


#include "render/painter.h"
#include "system/system.h"
#include "system/display.h"
#include <string.h>

bd_painter_t bd_painter_create_from_surface(bd_surface_t surface)
{
	bd_painter_t p = (bd_painter_t) bd_malloc(sizeof(bd_painter));
	if (p == BD_NULL) {
		return BD_NULL;
	}
	memset(p, 0, sizeof(bd_painter));
	p->surface = surface;
	return p;
}

void bd_painter_destroy(bd_painter_t p)
{
	if (p == BD_NULL) {
		return;
	}
	bd_free(p);
}

void bd_painter_draw_line(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2)
{
	if (p == BD_NULL) {
		return;
	}
	bd_paint_pixel(x1, y1, p->line_color);
}

void bd_painter_set_line_color(bd_painter_t p, bd_color c)
{
	if (p == BD_NULL) {
		return;
	}
	p->line_color = c;
}

void bd_painter_set_line_width(bd_painter_t p, BD_UINT w)
{
	if (p == BD_NULL) {
		return;
	}
	p->line_width = w;
}

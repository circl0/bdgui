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


#include "render/painter.h"
#include "system/system.h"
#include "system/display.h"

bd_painter_t bd_painter_create()
{
	bd_painter_t painter = bd_painter_new();
	painter->constructor(painter);
	return painter;
}

void bd_painter_destroy(bd_painter_t p)
{
	p->destructor(p);
	bd_painter_delete(p);
}

void bd_painter_constructor(bd_painter_t p)
{
	if (p == BD_NULL) {
		return;
	}
}

void bd_painter_destructor(bd_painter_t p)
{
	if (p == BD_NULL) {
		return;
	}
}

void bd_painter_draw_line(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2)
{
	if (p == BD_NULL) {
		return;
	}
}

bd_color bd_painter_get_line_color(bd_painter_t p)
{
	bd_color c;
	if (p == BD_NULL) {
		return c;
	}
	return p->line_color;
}

void bd_painter_set_line_color(bd_painter_t p, bd_color c)
{
	if (p == BD_NULL) {
		return;
	}
	p->line_color = c;
}

BD_UINT bd_painter_get_line_width(bd_painter_t p)
{
	if (p == BD_NULL) {
		return 0;
	}
	return p->line_width;
}

void bd_painter_set_line_width(bd_painter_t p, BD_UINT w)
{
	if (p == BD_NULL) {
		return;
	}
	p->line_width = w;
}

bd_color bd_painter_get_font_color(bd_painter_t p)
{
	bd_color c;
	if (p == BD_NULL) {
		return c;
	}
	return p->font_color;
}

void bd_painter_set_font_color(bd_painter_t p, bd_color c)
{
	if (p == BD_NULL) {
		return;
	}
	p->font_color = c;
}

BD_CLASS_CONSTRUCTOR_START(bd_painter)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_painter_constructor)
BD_CLASS_METHOD(destructor, bd_painter_destructor)
BD_CLASS_METHOD(draw_line, bd_painter_draw_line)
BD_CLASS_METHOD(get_line_color, bd_painter_get_line_color)
BD_CLASS_METHOD(set_line_color, bd_painter_set_line_color)
BD_CLASS_METHOD(get_line_width, bd_painter_get_line_width)
BD_CLASS_METHOD(set_line_width, bd_painter_set_line_width)
BD_CLASS_METHOD(get_font_color, bd_painter_get_font_color)
BD_CLASS_METHOD(set_font_color, bd_painter_set_font_color)
BD_CLASS_CONSTRUCTOR_END

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
#include "render/cairo/cairo_painter.h"
#include <math.h>

bd_cairo_painter_t bd_cairo_painter_create(cairo_t* cr)
{
	bd_cairo_painter_t cp = bd_cairo_painter_new();
	cp->constructor(cp, cr);
	return cp;
}

void bd_cairo_painter_destroy(bd_cairo_painter_t cp)
{
	bd_cairo_painter_delete(cp);
}

void bd_cairo_painter_constructor(bd_cairo_painter_t cp, cairo_t* cr)
{
	if (cp == BD_NULL) return;
	cp->cr = cr;
}

void bd_cairo_painter_destructor(bd_cairo_painter_t cp)
{
	if (cp == BD_NULL) return;
	cairo_destroy(cp->cr);
}

void bd_cairo_painter_draw_line(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_new_path(cp->cr);
	cairo_move_to(cp->cr, x1, y1);
	cairo_line_to(cp->cr, x2, y2);
	cairo_stroke(cp->cr); 
}

void bd_cairo_painter_draw_text(bd_painter_t p, BD_INT x, BD_INT y, const char* text)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_new_path(cp->cr);
	cairo_move_to(cp->cr, x, y);
	cairo_show_text(cp->cr, text);
}

void bd_cairo_painter_draw_rect(bd_painter_t p, bd_rect* rect)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_new_path(cp->cr);
	cairo_rectangle(cp->cr, rect->x, rect->y, rect->width, rect->height);
	cairo_stroke_preserve(cp->cr);
}

void bd_cairo_painter_fill(bd_painter_t p)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_fill(cp->cr);
}


void bd_cairo_painter_draw_circle(bd_painter_t p, BD_INT x, BD_INT y, BD_INT r)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_new_path(cp->cr);
	cairo_new_sub_path(cp->cr);
	cairo_arc(cp->cr, x, y, r, 0, 2 * M_PI);
	cairo_stroke_preserve(cp->cr);
}

void bd_cairo_painter_set_line_width(bd_painter_t p, BD_UINT w)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_set_line_width(cp->cr, w);
}

void bd_cairo_painter_set_color(bd_painter_t p, bd_color c)
{
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_set_source_rgba(cp->cr, (BD_DOUBLE)c.r/ 255 ,(BD_DOUBLE)c.g/ 255 ,(BD_DOUBLE)c.b/ 255, 1);
}

void bd_cairo_painter_set_font(bd_painter_t p, const char* name)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_select_font_face (cp->cr, name, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
}

void bd_cairo_painter_set_font_size(bd_painter_t p, BD_INT size)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_set_font_size(cp->cr, size);
}

void bd_cairo_painter_save(bd_painter_t p)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_save(cp->cr);
}

void bd_cairo_painter_restore(bd_painter_t p)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_restore(cp->cr);
}

void bd_cairo_painter_clip(bd_painter_t p, bd_region_t region)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);

	BD_INT num = region->get_rectangle_num(region);
	bd_rect rect;
	for (BD_INT i = 0; i < num; ++i) {
		region->get_rectangle(region, i, &rect);
		cairo_rectangle(cp->cr, rect.x, rect.y, rect.width, rect.height);
	}

	cairo_reset_clip(cp->cr);
	cairo_clip(cp->cr);
}

void bd_cairo_painter_reset_clip(bd_painter_t p)
{
	if (p == BD_NULL) return;
	bd_cairo_painter_t cp = BD_SUB(p, bd_painter, bd_cairo_painter);
	cairo_reset_clip(cp->cr);
}

BD_CLASS_CONSTRUCTOR_START(bd_cairo_painter)
BD_CLASS_METHOD(constructor, bd_cairo_painter_constructor)
BD_CLASS_METHOD(destructor, bd_cairo_painter_destructor)
BD_CLASS_METHOD(bd_painter.draw_line, bd_cairo_painter_draw_line)
BD_CLASS_METHOD(bd_painter.draw_text, bd_cairo_painter_draw_text)
BD_CLASS_METHOD(bd_painter.draw_rect, bd_cairo_painter_draw_rect)
BD_CLASS_METHOD(bd_painter.fill, bd_cairo_painter_fill)
BD_CLASS_METHOD(bd_painter.save, bd_cairo_painter_save)
BD_CLASS_METHOD(bd_painter.restore, bd_cairo_painter_restore)
BD_CLASS_METHOD(bd_painter.draw_circle, bd_cairo_painter_draw_circle)
BD_CLASS_METHOD(bd_painter.set_line_width, bd_cairo_painter_set_line_width)
BD_CLASS_METHOD(bd_painter.set_color, bd_cairo_painter_set_color)
BD_CLASS_METHOD(bd_painter.set_font, bd_cairo_painter_set_font)
BD_CLASS_METHOD(bd_painter.set_font_size, bd_cairo_painter_set_font_size)
BD_CLASS_METHOD(bd_painter.clip, bd_cairo_painter_clip)
BD_CLASS_METHOD(bd_painter.reset_clip, bd_cairo_painter_reset_clip)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cairo_painter)
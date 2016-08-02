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

bd_painter_internal_t bd_painter_internal_create(bd_surface_internal_t surface)
{
	bd_painter_internal_t p = bd_painter_internal_new();
	p->constructor(p);
	p->cr = cairo_create(surface->cs);
	return p;
}

void bd_painter_internal_destroy(bd_painter_internal_t p)
{
	bd_painter_internal_delete(p);
}

void bd_cairo_painter_constructor(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
}

void bd_cairo_painter_destructor(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
	cairo_destroy(p->cr);
}

void bd_cairo_painter_draw_line(bd_painter_internal_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2)
{
	if (p == BD_NULL) return;
	cairo_new_path(p->cr);
	cairo_move_to(p->cr, x1, y1);
	cairo_line_to(p->cr, x2, y2);
	cairo_stroke(p->cr); 
}

void bd_cairo_painter_draw_text(bd_painter_internal_t p, BD_INT x, BD_INT y, const char* text)
{
	if (p == BD_NULL) return;
	cairo_new_path(p->cr);
	cairo_move_to(p->cr, x, y);
	cairo_show_text(p->cr, text);
}

void bd_cairo_painter_draw_rect(bd_painter_internal_t p, bd_rect* rect)
{
	if (p == BD_NULL) return;
	cairo_new_path(p->cr);
	cairo_rectangle(p->cr, rect->x, rect->y, rect->width, rect->height);
	cairo_stroke_preserve(p->cr);
}

void bd_cairo_painter_fill(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
	cairo_fill(p->cr);
}


void bd_cairo_painter_draw_circle(bd_painter_internal_t p, BD_INT x, BD_INT y, BD_INT r)
{
	if (p == BD_NULL) return;
	cairo_new_path(p->cr);
	cairo_new_sub_path(p->cr);
	cairo_arc(p->cr, x, y, r, 0, 2 * M_PI);
	cairo_stroke_preserve(p->cr);
}

void bd_cairo_painter_set_line_width(bd_painter_internal_t p, BD_UINT w)
{
	if (p == BD_NULL) return;
	cairo_set_line_width(p->cr, w);
}

void bd_cairo_painter_set_color(bd_painter_internal_t p, bd_color c)
{
	if (p == BD_NULL) return;
	cairo_set_source_rgba(p->cr, (BD_DOUBLE)c.r/ 255 ,(BD_DOUBLE)c.g/ 255 ,(BD_DOUBLE)c.b/ 255, 1);
}

void bd_cairo_painter_set_font(bd_painter_internal_t p, const char* name)
{
	if (p == BD_NULL) return;
	cairo_select_font_face (p->cr, name, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
}

void bd_cairo_painter_set_font_size(bd_painter_internal_t p, BD_INT size)
{
	if (p == BD_NULL) return;
	cairo_set_font_size(p->cr, size);
}

void bd_cairo_painter_save(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
	cairo_save(p->cr);
}

void bd_cairo_painter_restore(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
	cairo_restore(p->cr);
}

void bd_cairo_painter_clip(bd_painter_internal_t p, bd_region_internal_t region)
{
	if (p == BD_NULL) return;

	BD_INT num = region->get_rectangle_num(region);
	bd_rect rect;
	for (BD_INT i = 0; i < num; ++i) {
		region->get_rectangle(region, i, &rect);
		cairo_rectangle(p->cr, rect.x, rect.y, rect.width, rect.height);
	}

	cairo_reset_clip(p->cr);
	cairo_clip(p->cr);
}

void bd_cairo_painter_reset_clip(bd_painter_internal_t p)
{
	if (p == BD_NULL) return;
	cairo_reset_clip(p->cr);
}

BD_CLASS_CONSTRUCTOR_START(bd_painter_internal)
BD_CLASS_METHOD(constructor, bd_cairo_painter_constructor)
BD_CLASS_METHOD(destructor, bd_cairo_painter_destructor)
BD_CLASS_METHOD(draw_line, bd_cairo_painter_draw_line)
BD_CLASS_METHOD(draw_text, bd_cairo_painter_draw_text)
BD_CLASS_METHOD(draw_rect, bd_cairo_painter_draw_rect)
BD_CLASS_METHOD(fill, bd_cairo_painter_fill)
BD_CLASS_METHOD(save, bd_cairo_painter_save)
BD_CLASS_METHOD(restore, bd_cairo_painter_restore)
BD_CLASS_METHOD(draw_circle, bd_cairo_painter_draw_circle)
BD_CLASS_METHOD(set_line_width, bd_cairo_painter_set_line_width)
BD_CLASS_METHOD(set_color, bd_cairo_painter_set_color)
BD_CLASS_METHOD(set_font, bd_cairo_painter_set_font)
BD_CLASS_METHOD(set_font_size, bd_cairo_painter_set_font_size)
BD_CLASS_METHOD(clip, bd_cairo_painter_clip)
BD_CLASS_METHOD(reset_clip, bd_cairo_painter_reset_clip)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_painter_internal)
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

bd_painter_t bd_painter_create()
{
	bd_painter_t painter = bd_painter_new();
	painter->constructor(painter);
	return painter;
}

void bd_painter_destroy(bd_painter_t painter)
{
	bd_painter_delete(painter);
}

void bd_painter_constructor(bd_painter_t p)
{

}

void bd_painter_destructor(bd_painter_t p)
{

}

void bd_painter_draw_line(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2)
{
	p->painter_internal->draw_line(p->painter_internal, x1, y1, x2, y2);
}

void bd_painter_draw_text(bd_painter_t p, BD_INT x1, BD_INT y1, const char* text)
{
	p->painter_internal->draw_text(p->painter_internal, x1, y1, text);
}

void bd_painter_draw_rect(bd_painter_t p, bd_rect_t rect)
{
	p->painter_internal->draw_rect(p->painter_internal, rect);
}

void bd_painter_draw_circle(bd_painter_t p, BD_INT x, BD_INT y, BD_INT r)
{
	p->painter_internal->draw_circle(p->painter_internal, x, y, r);
}

void bd_painter_fill(bd_painter_t p)
{
	p->painter_internal->fill(p->painter_internal);
}

void bd_painter_save(bd_painter_t p)
{
	p->painter_internal->save(p->painter_internal);
}

void bd_painter_restore(bd_painter_t p)
{
	p->painter_internal->restore(p->painter_internal);
}

void bd_painter_set_line_width(bd_painter_t p, BD_UINT w)
{
	p->painter_internal->set_line_width(p->painter_internal, w);
}

void bd_painter_set_color(bd_painter_t p, bd_color c)
{
	p->painter_internal->set_color(p->painter_internal, c);
}

void bd_painter_set_font(bd_painter_t p, const char* name)
{
	p->painter_internal->set_font(p->painter_internal, name);
}

void bd_painter_set_font_size(bd_painter_t p, BD_INT size)
{
	p->painter_internal->set_font_size(p->painter_internal, size);
}

void bd_painter_clip(bd_painter_t p, bd_region_t region)
{
	p->painter_internal->clip(p->painter_internal, region->region_internal);
}

void bd_painter_reset_clip(bd_painter_t p)
{
	p->painter_internal->reset_clip(p->painter_internal);
}


BD_CLASS_CONSTRUCTOR_START(bd_painter)
BD_CLASS_METHOD(constructor, bd_painter_constructor)
BD_CLASS_METHOD(destructor, bd_painter_destructor)
BD_CLASS_METHOD(draw_line, bd_painter_draw_line)
BD_CLASS_METHOD(draw_text, bd_painter_draw_text)
BD_CLASS_METHOD(draw_rect, bd_painter_draw_rect)
BD_CLASS_METHOD(fill, bd_painter_fill)
BD_CLASS_METHOD(save, bd_painter_save)
BD_CLASS_METHOD(restore, bd_painter_restore)
BD_CLASS_METHOD(draw_circle, bd_painter_draw_circle)
BD_CLASS_METHOD(set_line_width, bd_painter_set_line_width)
BD_CLASS_METHOD(set_color, bd_painter_set_color)
BD_CLASS_METHOD(set_font, bd_painter_set_font)
BD_CLASS_METHOD(set_font_size, bd_painter_set_font_size)
BD_CLASS_METHOD(clip, bd_painter_clip)
BD_CLASS_METHOD(reset_clip, bd_painter_reset_clip)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_painter)
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

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "font/freetype/freetype_glyph.h"
#include "font/freetype/freetype_font.h"
#include "font/glyph.h"
#include "system/display.h"

bd_glyph_t bd_glyph_create()
{
	bd_freetype_glyph_t  freetype_glyph = bd_freetype_glyph_new();
	freetype_glyph->constructor(freetype_glyph);
	return BD_SUP(freetype_glyph, bd_glyph);
}

void bd_glyph_destroy(bd_glyph_t glyph)
{

}

void bd_freetype_glyph_constructor(bd_freetype_glyph_t glyph)
{
	if (glyph == BD_NULL) {
		return;
	}
	glyph->pen_x = 0;
	glyph->pen_y = 0;
	glyph->advance_x = 0;
	glyph->advance_y = 0;
}

void bd_freetype_glyph_destructor(bd_freetype_glyph_t glyph)
{

}

void bd_freetype_glyph_set_pen(bd_glyph_t glyph, BD_INT x, BD_INT y)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	ft_glyph->pen_x = x;
	ft_glyph->pen_y = y;
}

void bd_freetype_glyph_get_pen(bd_glyph_t glyph, BD_INT* x, BD_INT* y)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	*x = ft_glyph->pen_x;
	*y = ft_glyph->pen_y;
}

void bd_freetype_glyph_get_advance(bd_glyph_t glyph, BD_INT* x, BD_INT* y)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	*x = ft_glyph->advance_x;
	*y = ft_glyph->advance_y;
}

void bd_freetype_glyph_set_advance(bd_glyph_t glyph, BD_INT x, BD_INT y)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	ft_glyph->advance_x = x;
	ft_glyph->advance_y = y;
}

void bd_freetype_glyph_get_bbox(bd_glyph_t glyph, bd_glyph_bbox_t bbox)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);

	FT_BBox ft_bbox;
	FT_Glyph_Get_CBox(ft_glyph->glyph, 0, &ft_bbox);
	bbox->set_min(bbox, ft_bbox.xMin >> 6, ft_bbox.yMin >> 6);
	bbox->set_max(bbox, ft_bbox.xMax >> 6, ft_bbox.yMax >> 6);
}

void bd_freetype_glyph_move(bd_glyph_t glyph, BD_INT x, BD_INT y)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	FT_Vector v = {x ,y};
	FT_Glyph_Transform(ft_glyph->glyph, 0, &v);
}

void bd_freetype_glyph_render(bd_glyph_t glyph, BD_INT x, BD_INT y, bd_color c)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	FT_BitmapGlyph bitmap = (FT_BitmapGlyph) ft_glyph->glyph;
	for (BD_INT row = 0; row < bitmap->bitmap.rows; ++row) {
		for (BD_INT col = 0; col < bitmap->bitmap.width; ++col) {
			BD_INT gray = bitmap->bitmap.buffer[row * bitmap->bitmap.width + col];
			bd_color color = {gray, gray, gray};
			bd_paint_pixel(x + bitmap->left + col, y - bitmap->top + row + 30, color);
		}
	}
}

void bd_freetype_create_image(bd_glyph_t glyph)
{
	if (glyph == BD_NULL) {
		return;
	}
	bd_freetype_glyph_t ft_glyph = BD_SUB(glyph, bd_glyph, bd_freetype_glyph);
	FT_Glyph_To_Bitmap(&ft_glyph->glyph, FT_RENDER_MODE_NORMAL, 0, 1);
}

BD_CLASS_CONSTRUCTOR_START(bd_freetype_glyph)
BD_CLASS_METHOD(constructor, bd_freetype_glyph_constructor)
BD_CLASS_METHOD(destructor, bd_freetype_glyph_destructor)
BD_CLASS_METHOD(bd_glyph.get_pen, bd_freetype_glyph_get_pen)
BD_CLASS_METHOD(bd_glyph.set_pen, bd_freetype_glyph_set_pen)
BD_CLASS_METHOD(bd_glyph.get_advance, bd_freetype_glyph_get_advance)
BD_CLASS_METHOD(bd_glyph.set_advance, bd_freetype_glyph_set_advance)
BD_CLASS_METHOD(bd_glyph.get_bbox, bd_freetype_glyph_get_bbox)
BD_CLASS_METHOD(bd_glyph.move, bd_freetype_glyph_move)
BD_CLASS_METHOD(bd_glyph.create_image, bd_freetype_create_image)
BD_CLASS_METHOD(bd_glyph.render, bd_freetype_glyph_render)
BD_CLASS_CONSTRUCTOR_END

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
#include FT_IMAGE_H

#include "font/freetype/freetype_bbox.h"

bd_glyph_bbox_t bd_glyph_bbox_create()
{
	bd_freetype_glyph_bbox_t freetype_bbox = bd_freetype_glyph_bbox_new();
	freetype_bbox->constructor(freetype_bbox);
	return BD_SUP(freetype_bbox, bd_glyph_bbox);
}

void bd_glyph_bbox_destroy(bd_glyph_bbox_t bbox)
{

}

void bd_freetype_glyph_bbox_constructor(bd_freetype_glyph_bbox_t bbox)
{
	bbox->bbox.xMin = 0;
	bbox->bbox.yMin = 0;
	bbox->bbox.xMax = 0;
	bbox->bbox.yMax = 0;
}

void bd_freetype_glyph_bbox_destructor(bd_freetype_glyph_bbox_t bbox)
{

}

void bd_freetype_glyph_get_min(bd_glyph_bbox_t bbox, BD_INT* x, BD_INT* y)
{
	if (bbox == BD_NULL) {
		return;
	}
	bd_freetype_glyph_bbox_t freetype_bbox = BD_SUB(bbox, bd_glyph_bbox, bd_freetype_glyph_bbox);
	*x = freetype_bbox->bbox.xMin;
	*y = freetype_bbox->bbox.yMin;
}

void bd_freetype_glyph_get_max(bd_glyph_bbox_t bbox, BD_INT* x, BD_INT* y)
{
	if (bbox == BD_NULL) {
		return;
	}
	bd_freetype_glyph_bbox_t freetype_bbox = BD_SUB(bbox, bd_glyph_bbox, bd_freetype_glyph_bbox);
	*x = freetype_bbox->bbox.xMax;
	*y = freetype_bbox->bbox.yMax;
}

void bd_freetype_glyph_bbox_set_min(bd_glyph_bbox_t bbox, BD_INT x, BD_INT y)
{
	if (bbox == BD_NULL) {
		return;
	}
	bd_freetype_glyph_bbox_t freetype_bbox = BD_SUB(bbox, bd_glyph_bbox, bd_freetype_glyph_bbox);
	freetype_bbox->bbox.xMin = x;
	freetype_bbox->bbox.yMin = y;
}

void bd_freetype_glyph_bbox_set_max(bd_glyph_bbox_t bbox, BD_INT x, BD_INT y)
{
	if (bbox == BD_NULL) {
		return;
	}
	bd_freetype_glyph_bbox_t freetype_bbox = BD_SUB(bbox, bd_glyph_bbox, bd_freetype_glyph_bbox);
	freetype_bbox->bbox.xMax = x;
	freetype_bbox->bbox.yMax = y;
}

void bd_freetype_glyph_bbox_expand(bd_glyph_bbox_t self, bd_glyph_bbox_t other)
{
	if (self == BD_NULL || other == BD_NULL) {
		return;
	}
	BD_INT xMin = 0, yMin = 0, xMax = 0, yMax = 0;
	other->get_min(other, &xMin, &yMin);
	other->get_max(other, &xMax, &yMax);
	bd_freetype_glyph_bbox_t freetype_bbox = BD_SUB(self, bd_glyph_bbox, bd_freetype_glyph_bbox);
	if (xMin < freetype_bbox->bbox.xMin) {
		freetype_bbox->bbox.xMin = xMin;
	}
	if (yMin < freetype_bbox->bbox.yMin) {
		freetype_bbox->bbox.yMin = yMin;
	}
	if (xMax > freetype_bbox->bbox.xMax) {
		freetype_bbox->bbox.xMax = xMax;
	}
	if (yMax < freetype_bbox->bbox.yMax) {
		freetype_bbox->bbox.yMax = yMax;
	}

}

BD_CLASS_CONSTRUCTOR_START(bd_freetype_glyph_bbox)
BD_CLASS_METHOD(constructor, bd_freetype_glyph_bbox_constructor)
BD_CLASS_METHOD(destructor, bd_freetype_glyph_bbox_destructor)
BD_CLASS_METHOD(bd_glyph_bbox.get_min, bd_freetype_glyph_get_min)
BD_CLASS_METHOD(bd_glyph_bbox.get_max, bd_freetype_glyph_get_max)
BD_CLASS_METHOD(bd_glyph_bbox.set_min, bd_freetype_glyph_bbox_set_min)
BD_CLASS_METHOD(bd_glyph_bbox.set_max, bd_freetype_glyph_bbox_set_max)
BD_CLASS_METHOD(bd_glyph_bbox.expand, bd_freetype_glyph_bbox_expand)
BD_CLASS_CONSTRUCTOR_END

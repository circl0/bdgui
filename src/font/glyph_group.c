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


#include "font/glyph_group.h"
#include <string.h>


bd_glyph_group_t bd_glyph_group_create(BD_INT size)
{
	bd_glyph_group_t group = bd_glyph_group_new();
	group->constructor(group, size);
	return group;
}

void bd_glyph_group_destroy(bd_glyph_group_t group)
{

}

void bd_glyph_group_constructor(bd_glyph_group_t group, BD_INT size)
{
	if (group == BD_NULL) {
		return;
	}
	BD_INT pen_x = 0, pen_y = 0;
	BD_INT advance_x = 0, advance_y = 0;
	group->glyphs = bd_malloc(sizeof(bd_glyph_t) * size);
	group->size = 0;
	group->max_size = size;
	group->current_pen_x = 0;
	group->current_pen_y = 0;
}

void bd_glyph_group_destructor(bd_glyph_group_t group)
{

}

void bd_glyph_group_get_bbox(bd_glyph_group_t group, bd_glyph_bbox_t bbox)
{
	bd_log("bbox", "start\n");
	if (group == BD_NULL || group->size == 0) {
		return;
	}
	bd_glyph_t glyph = BD_NULL;
	bd_glyph_bbox_t temp = bd_glyph_bbox_create();
	BD_INT a = 0, b = 0;
	for (BD_INT i = 0; i < group->size; ++i) {
		glyph = group->glyphs[i];
		glyph->get_bbox(glyph, temp);
		temp->get_min(temp, &a, &b);
		bd_log("bbox", "%d, %d\n", a, b);
		bbox->expand(bbox, temp);
	}
	bd_glyph_bbox_destroy(temp);
	bbox->get_min(temp, &a, &b);
	bd_log("bbox", "%d, %d end\n", a, b);
}

void bd_glyph_group_add(bd_glyph_group_t group, bd_glyph_t glyph)
{
	if (group == BD_NULL || group->size == group->max_size) {
		return;
	}
	BD_INT advance_x = 0, advance_y = 0;
	*(group->glyphs + group->size) = glyph;
	group->size++;
	glyph->move(glyph, group->current_pen_x << 6, group->current_pen_y << 6);
	glyph->get_advance(glyph, &advance_x, &advance_y);
	group->current_pen_x += (advance_x >> 6);
	group->current_pen_y += (advance_y >> 6);
}

void bd_glyph_group_render(bd_glyph_group_t group, BD_INT x, BD_INT y, bd_color c)
{
	bd_glyph_t glyph = BD_NULL;
	for (BD_INT i = 0; i < group->size; ++i) {
		glyph = group->glyphs[i];
		glyph->create_image(glyph);
		glyph->render(glyph, x, y, c);
	}
}

BD_CLASS_CONSTRUCTOR_START(bd_glyph_group)
BD_CLASS_METHOD(constructor, bd_glyph_group_constructor)
BD_CLASS_METHOD(destructor, bd_glyph_group_destructor)
BD_CLASS_METHOD(get_bbox, bd_glyph_group_get_bbox)
BD_CLASS_METHOD(render, bd_glyph_group_render)
BD_CLASS_METHOD(add, bd_glyph_group_add)
BD_CLASS_CONSTRUCTOR_END

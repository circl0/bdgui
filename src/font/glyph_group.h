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

#ifndef INCLUDE_FONT_GLYPH_GROUP_H_
#define INCLUDE_FONT_GLYPH_GROUP_H_

#include "type/object.h"
#include "font/glyph.h"
#include "font/bbox.h"

BD_CLASS(bd_glyph_group) {
	BD_EXTENDS(bd_object);

	bd_glyph_t* glyphs;
	BD_INT size;
	BD_INT max_size;

	BD_INT current_pen_x;
	BD_INT current_pen_y;

	void (*constructor)(bd_glyph_group_t group, BD_INT size);
	void (*destructor)(bd_glyph_group_t group);

	void (*get_bbox)(bd_glyph_group_t group, bd_glyph_bbox_t bbox);
	void (*render)(bd_glyph_group_t group, BD_INT x, BD_INT y, bd_color c);
	void (*add)(bd_glyph_group_t group, bd_glyph_t glyph);
};

bd_glyph_group_t bd_glyph_group_create(BD_INT size);
void bd_glyph_group_destroy(bd_glyph_group_t group);


#endif 

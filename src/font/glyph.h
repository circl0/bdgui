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

#ifndef INCLUDE_FONT_GLYPH_H_
#define INCLUDE_FONT_GLYPH_H_

#include "type/object.h"
#include "font/bbox.h"

BD_INTERFACE(bd_glyph) {

	void (*get_advance)(bd_glyph_t glyph, BD_INT* x, BD_INT* y);
	void (*set_advance)(bd_glyph_t glyph, BD_INT x, BD_INT y);
	void (*get_pen)(bd_glyph_t glyph, BD_INT* x, BD_INT* y);
	void (*set_pen)(bd_glyph_t glyph, BD_INT x, BD_INT y);
	void (*get_bbox)(bd_glyph_t glyph, bd_glyph_bbox_t bbox);
	void (*move)(bd_glyph_t glyph, BD_INT x, BD_INT y);
	void (*render)(bd_glyph_t glyph, BD_INT x, BD_INT y, bd_color c);
	void (*create_image)(bd_glyph_t glyph);
};

bd_glyph_t bd_glyph_create();
void bd_glyph_destroy(bd_glyph_t glyph);


#endif 

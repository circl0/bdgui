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

#ifndef INCLUDE_RENDER_FONT_H_
#define INCLUDE_RENDER_FONT_H_

#include "type/object.h"
#include "font/glyph_group.h"
#include "font/glyph.h"

BD_INTERFACE(bd_font) {

	BD_INT (*get_size)(bd_font_t font);
	void (*set_size)(bd_font_t font, BD_INT size);
	bd_glyph_t (*create_glyph)(bd_font_t font, const char ch);
	bd_glyph_group_t (*create_glyph_group)(bd_font_t font, const char* str);


};

#endif 

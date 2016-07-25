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


#ifndef INCLUDE_FONT_CAIRO_FREETYPE_CAIRO_FONT_H_
#define INCLUDE_FONT_CAIRO_FREETYPE_CAIRO_FONT_H_

BD_CLASS(bd_cairo_font) {
	BD_IMPLEMENTS(bd_font);

	cairo_font_face_t* cairo_font_face;

	void (*constructor)(bd_cairo_font_t font, FT_Face face);
	void (*destructor)(bd_cairo_font_t font);
};

#endif
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

#include "utils/log.h"
#include "font/freetype/freetype_font.h"
#include "font/freetype/freetype_glyph.h"

void bd_freetype_font_constructor(bd_freetype_font_t font, const char* name, FT_Library library)
{
	if (font == BD_NULL || library == BD_NULL) {
		return;
	}
	BD_INT error = FT_New_Face(library, name, 0, &(font->face));
	if (error < 0) {
		bd_log("glyph_group", "error new face\n");
	}
}

void bd_freetype_font_destructor(bd_freetype_font_t font)
{

}

BD_INT bd_freetype_font_get_size(bd_font_t font)
{
	if (font == BD_NULL) {
		return -1;
	}
	return 0;
}

void bd_freetype_font_set_size(bd_font_t font, BD_INT size)
{
	if (font == BD_NULL) {
		return;
	}
	bd_freetype_font_t ft_font = BD_SUB(font, bd_font, bd_freetype_font);
	FT_Set_Pixel_Sizes(ft_font->face, 0, size);
}

bd_glyph_t bd_freetype_font_create_glyph(bd_font_t font, const char ch)
{
	if (font == BD_NULL) {
		return BD_NULL;
	}
	bd_freetype_font_t ft_font = BD_SUB(font, bd_font, bd_freetype_font);
	BD_UINT glyph_index = FT_Get_Char_Index(ft_font->face, ch);
	BD_INT error = FT_Load_Glyph(ft_font->face, glyph_index, FT_LOAD_DEFAULT);
	if (error < 0) {
		return BD_NULL;
	}
	bd_freetype_glyph_t glyph = bd_freetype_glyph_new();
	error = FT_Get_Glyph(ft_font->face->glyph, &(glyph->glyph));
	if (error < 0) {
		return BD_NULL;
	}
	glyph->advance_x = ft_font->face->glyph->advance.x;
	glyph->advance_y = ft_font->face->glyph->advance.y;
	return BD_SUP(glyph, bd_glyph);
}

bd_glyph_group_t bd_freetype_font_create_glyph_group(bd_font_t font, const char* str)
{
	BD_INT size = strlen(str);
	bd_glyph_group_t group = bd_glyph_group_create(size);
	bd_glyph_t glyph = BD_NULL;
	for (BD_INT i = 0; i < size; ++i) {
		glyph = font->create_glyph(font, str[i]);
		group->add(group, glyph);
	}
	return group;
}

BD_CLASS_CONSTRUCTOR_START(bd_freetype_font)
BD_CLASS_METHOD(constructor, bd_freetype_font_constructor)
BD_CLASS_METHOD(destructor, bd_freetype_font_destructor)
BD_CLASS_METHOD(bd_font.get_size, bd_freetype_font_get_size)
BD_CLASS_METHOD(bd_font.set_size, bd_freetype_font_set_size)
BD_CLASS_METHOD(bd_font.create_glyph, bd_freetype_font_create_glyph)
BD_CLASS_METHOD(bd_font.create_glyph_group, bd_freetype_font_create_glyph_group)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_freetype_font)

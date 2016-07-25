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

#include "type/type.h"
#include "font/freetype/freetype_font.h"

static FT_Library library = BD_NULL;

void bd_font_module_init()
{
	if (library == BD_NULL) {
		FT_Init_FreeType(&library);
	}
}

bd_font_t bd_font_module_load(const char* name)
{
	bd_freetype_font_t freetype_font = bd_freetype_font_new();
	freetype_font->constructor(freetype_font, name, library);
	return BD_SUP(freetype_font, bd_font);
}

void bd_font_module_unload(bd_font_t font)
{
	bd_freetype_font_t freetype_font = BD_SUB(font, bd_font, bd_freetype_font);
	freetype_font->destructor(freetype_font);
	bd_freetype_font_delete(freetype_font);
}

void bd_font_module_deinit()
{
	if (library == BD_NULL) {
		FT_Done_FreeType(library);
	}
}

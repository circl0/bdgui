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

#ifndef INCLUDE_RENDER_FREETYPE_GLYPH_H_
#define INCLUDE_RENDER_FREETYPE_GLYPH_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "type/object.h"
#include "font/glyph.h"

BD_CLASS(bd_freetype_glyph) {
  BD_IMPLEMENTS(bd_glyph);
  
  FT_Glyph glyph;
  BD_INT pen_x;
  BD_INT pen_y;
  BD_INT advance_x;
  BD_INT advance_y;

  void (*constructor)(bd_freetype_glyph_t glyph);
  void (*destructor)(bd_freetype_glyph_t glyph);

};




#endif 

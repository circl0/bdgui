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

#ifndef INCLUDE_FONT_FREETYPE_BBOX_H_
#define INCLUDE_FONT_FREETYPE_BBOX_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_IMAGE_H

#include "font/bbox.h"


BD_CLASS(bd_freetype_glyph_bbox) {
  BD_IMPLEMENTS(bd_glyph_bbox);

  FT_BBox bbox;

  void (*constructor)(bd_freetype_glyph_bbox_t bbox);
  void (*destructor)(bd_freetype_glyph_bbox_t bbox);

};

#endif 

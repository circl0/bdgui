/* bdgui - a kind of embedded gui system
　* Copyright (C) 2016  BDGUI Team
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


#ifndef INCLUDE_RENDER_PAINTER_H_
#define INCLUDE_RENDER_PAINTER_H_

#include "type/type.h"
#include "type/object.h"
#include "font/font.h"
#include "type/type.h"
#include "render/region.h"
 
BD_INTERFACE(bd_painter) {
	
	// drawing method
	void (*draw_line)(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2);
	void (*draw_text)(bd_painter_t p, BD_INT x1, BD_INT y1, const char* text);
	void (*draw_rect)(bd_painter_t p, bd_rect_t rect);
	void (*draw_circle)(bd_painter_t p, BD_INT x, BD_INT y, BD_INT r);

	void (*fill)(bd_painter_t p);

	void (*save)(bd_painter_t p);
	void (*restore)(bd_painter_t p);

	// getter/setter
	void (*set_line_width)(bd_painter_t p, BD_UINT w);
	void (*set_color)(bd_painter_t p, bd_color c);
	void (*set_font)(bd_painter_t p, const char* name);
	void (*set_font_size)(bd_painter_t p, BD_INT size);

	void (*clip)(bd_painter_t p, bd_region_t region);
	void (*reset_clip)(bd_painter_t p);
};


#endif /* INCLUDE_RENDER_RENDERER_H_ */

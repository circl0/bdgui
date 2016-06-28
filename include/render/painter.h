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


#ifndef INCLUDE_RENDER_PAINTER_H_
#define INCLUDE_RENDER_PAINTER_H_

#include "render/surface.h"
#include "type/type.h"

typedef struct bd_painter {
	//surface
	bd_surface_t surface;
	//context
	bd_color line_color;
	BD_UINT line_width;
	bd_color fill_color;

} bd_painter;

typedef bd_painter* bd_painter_t;

bd_painter_t bd_painter_create_from_surface(bd_surface_t surface);
void bd_painter_destroy(bd_painter_t p);
//pixel
void bd_painter_draw_pixel(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2);
//line
void bd_painter_draw_line(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2);
void bd_painter_set_line_color(bd_painter_t p, bd_color c);
void bd_painter_set_line_width(bd_painter_t p, BD_UINT w);


#endif /* INCLUDE_RENDER_RENDERER_H_ */

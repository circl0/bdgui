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


#ifndef INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_SURFACE_H_
#define INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_SURFACE_H_

#include "type/type.h"
#include "type/object.h"
#include "render/cairo/cairo_painter.h"
#include "system/display.h"
#include <cairo.h>

BD_CLASS(bd_surface_internal) {
	// cairo surface
	cairo_surface_t* cs;

	bd_color_type color_type;

	// con/des
    void (*constructor)(bd_surface_internal_t surface, bd_display_t display);
    void (*destructor)(bd_surface_internal_t surface);

};

bd_surface_internal_t bd_surface_internal_create(bd_display_t display);
void bd_surface_internal_destroy(bd_surface_internal_t surface);

#endif /* INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_SURFACE_H_ */
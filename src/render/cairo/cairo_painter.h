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


#ifndef INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_PAINTER_H_
#define INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_PAINTER_H_

#include "type/type.h"
#include "type/object.h"
#include "font/font.h"
#include <cairo.h>

BD_CLASS(bd_cairo_painter) {
	BD_IMPLEMENTS(bd_painter);
	// cairo context
	cairo_t* cr;
	// con/des
    void (*constructor)(bd_cairo_painter_t p, cairo_t* c);
    void (*destructor)(bd_cairo_painter_t p);

};

bd_cairo_painter_t bd_cairo_painter_create(cairo_t* cr);
void bd_cairo_painter_destroy(bd_cairo_painter_t cp);

#endif /* INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_PAINTER_H_ */

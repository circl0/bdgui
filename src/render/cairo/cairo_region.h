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


#ifndef INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_REGION_H_
#define INCLUDE_RENDER_PAINTER_INTERNAL_CAIRO_REGION_H_

#include "render/region.h"
#include "type/object.h"
#include <cairo.h>

BD_CLASS(bd_cairo_region) {
	BD_IMPLEMENTS(bd_region);
	
	cairo_region_t* cr;

	// con/des
    void (*constructor)(bd_cairo_region_t cr, bd_rect_t rect);
    void (*destructor)(bd_cairo_region_t cr);

};

bd_cairo_region_t bd_cairo_region_create(bd_rect_t rect);
void bd_cairo_region_destroy(bd_cairo_region_t cairo_region);

#endif
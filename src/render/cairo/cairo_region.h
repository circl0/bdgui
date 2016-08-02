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

#include "type/object.h"
#include <cairo.h>

BD_CLASS(bd_region_internal) {
	
	cairo_region_t* cr;

	// con/des
    void (*constructor)(bd_region_internal_t region);
    void (*constructor2)(bd_region_internal_t region, bd_rect_t rect);
    void (*destructor)(bd_region_internal_t region);

   	BD_INT (*get_rectangle_num)(bd_region_internal_t region);
	void (*get_rectangle)(bd_region_internal_t region, BD_INT num, bd_rect_t rect);
	void (*substract)(bd_region_internal_t region, bd_rect_t rect);
	void (*add)(bd_region_internal_t region, bd_rect_t rect);
	void (*substract_region)(bd_region_internal_t region, bd_region_internal_t other);
	BD_INT (*equal)(bd_region_internal_t region, bd_region_internal_t other);
	BD_INT (*contains)(bd_region_internal_t region, bd_rect_t rect);
	BD_INT (*contains_point)(bd_region_internal_t region, BD_INT x, BD_INT y);

};

bd_region_internal_t bd_region_internal_create_by_rect(bd_rect_t rect);
bd_region_internal_t bd_region_internal_create();
void bd_region_internal_destroy(bd_region_internal_t region);

#endif
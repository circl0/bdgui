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


#ifndef BDGUI_REGION_H
#define BDGUI_REGION_H

#include "type/type.h"
#include "type/object.h"
#include "render/cairo/cairo_region.h"
 
BD_CLASS(bd_region) {

	bd_region_internal_t region_internal;

	void (*constructor)(bd_region_t region);
	void (*constructor2)(bd_region_t region, bd_rect_t rect);
	void (*destructor)(bd_region_t region);

	BD_INT (*get_rectangle_num)(bd_region_t region);
	void (*get_rectangle)(bd_region_t region, BD_INT num, bd_rect_t rect);
	void (*substract)(bd_region_t region, bd_rect_t rect);
	void (*add)(bd_region_t region, bd_rect_t rect);
	void (*substract_region)(bd_region_t region, bd_region_t other);
	BD_INT (*equal)(bd_region_t region, bd_region_t other);
	BD_INT (*contains)(bd_region_t region, bd_rect_t rect);
	BD_INT (*contains_point)(bd_region_t region, BD_INT x, BD_INT y);
};

bd_region_t bd_region_create();
bd_region_t bd_region_create_by_rect(bd_rect_t rect);
void bd_region_destroy(bd_region_t region);

#endif //BDGUI_REGION_H
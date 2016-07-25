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


#ifndef BD_COMPONENT_H
#define BD_COMPONENT_H

#include "type/object.h"
#include "render/surface.h"

BD_ABSTRACT_CLASS(bd_component) {
	BD_EXTENDS(bd_object);

	void (*constructor)(bd_component_t component);
	void (*destructor)(bd_component_t component);

	BD_INT x;
	BD_INT y;
	BD_INT width;
	BD_INT height;

	void (*set_x)(bd_component_t component, BD_INT x);
	void (*set_y)(bd_component_t component, BD_INT y);
	void (*set_width)(bd_component_t component, BD_INT width);
	void (*set_height)(bd_component_t component, BD_INT height);
	
	void (*move)(bd_component_t component, BD_INT x, BD_INT y);
	void (*resize)(bd_component_t component, BD_INT width, BD_INT height);

	BD_INT (*get_x)(bd_component_t component);
	BD_INT (*get_y)(bd_component_t component);
	BD_INT (*get_width)(bd_component_t component);
	BD_INT (*get_height)(bd_component_t component);

	void (*get_bound)(bd_component_t component, bd_rect_t rect);

	void (*on_render)(bd_component_t, bd_surface_t);
	void (*invalidate)(bd_component_t);
};

#endif //BD_COMPONENT_H

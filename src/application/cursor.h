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

#ifndef INCLUDE_APPLICATION_CURSOR_H_
#define INCLUDE_APPLICATION_CURSOR_H_

#include "type/object.h"
#include "component/component.h"
#include "render/surface.h"
#include "type/type.h"

BD_CLASS(bd_cursor) {
	BD_EXTENDS(bd_object);

	BD_INT x;
	BD_INT y;

	void (*set_x)(bd_cursor_t cursor, BD_INT x);
	void (*set_y)(bd_cursor_t cursor, BD_INT y);
	BD_INT (*get_x)(bd_cursor_t cursor);
	BD_INT (*get_y)(bd_cursor_t cursor);

	void (*render)(bd_cursor_t cursor, bd_surface_t surface);
	void (*get_bound)(bd_cursor_t cursor, bd_rect_t rect);

	void (*constructor)(bd_cursor_t cursor);
	void (*destructor)(bd_cursor_t cursor);
};	

bd_cursor_t bd_cursor_create();
void bd_cursor_destroy(bd_cursor_t cursor);

#endif
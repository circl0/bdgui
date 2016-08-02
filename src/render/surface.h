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


#ifndef BDGUI_SURFACE_H
#define BDGUI_SURFACE_H

#include "type/type.h"
#include "type/object.h"
#include "render/painter.h"
#include "render/cairo/cairo_surface.h"
#include "system/display.h"

BD_CLASS(bd_surface) {
	BD_EXTENDS(bd_object);

	bd_surface_internal_t surface_internal;
	bd_painter_t painter;
	bd_display_t display;

	BD_INT width;
	BD_INT height;
	bd_color_type color_type;


	void (*constructor)(bd_surface_t surface, bd_display_t display);
	void (*destructor)(bd_surface_t surface);

    bd_painter_t (*get_painter)(bd_surface_t surface);
    BD_UINT (*get_width)(bd_surface_t surface);
    BD_UINT (*get_height)(bd_surface_t surface);

    void (*lock)(bd_surface_t surface);
    void (*unlock)(bd_surface_t surface);
    void (*flip)(bd_surface_t surface);

};

bd_surface_t bd_surface_create(bd_display_t display);
void bd_surface_destroy(bd_surface_t surface);

#endif //BDGUI_SURFACE_H

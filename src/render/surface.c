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


#include "render/surface.h"
#include "render/painter.h"
#include "system/system.h"
#include "system/display.h"

bd_surface_t bd_surface_create()
{
	bd_surface_t surface = bd_surface_new();
	surface->constructor(surface);
	return surface;
}

void bd_surface_destroy(bd_surface_t surface)
{
	surface->destructor(surface);
	bd_surface_delete(surface);
}

void bd_surface_constructor(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return;
    }
    surface->painter = bd_painter_create(surface);
    surface->height = bd_get_screen_height();
    surface->width = bd_get_screen_width();
}

void bd_surface_destructor(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return;
    }
	bd_painter_delete(surface->painter);
}

bd_painter_t bd_surface_get_painter(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return BD_NULL;
    }
    return surface->painter;
}

BD_UINT bd_surface_get_width(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return 0;
    }
    return surface->width;
}

BD_UINT bd_surface_get_height(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return 0;
    }
    return surface->height;
}

BD_CLASS_CONSTRUCTOR_START(bd_surface)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_surface_constructor)
BD_CLASS_METHOD(destructor, bd_surface_destructor)
BD_CLASS_METHOD(get_painter, bd_surface_get_painter)
BD_CLASS_METHOD(get_width, bd_surface_get_width)
BD_CLASS_METHOD(get_height, bd_surface_get_height)
BD_CLASS_CONSTRUCTOR_END

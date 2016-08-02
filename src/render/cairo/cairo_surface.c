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
#include "render/cairo/cairo_painter.h"
#include "render/cairo/cairo_surface.h"

bd_surface_internal_t bd_surface_internal_create(bd_display_t display)
{
    if (display == BD_NULL) {
        return BD_NULL;
    }
    bd_surface_internal_t surface = bd_surface_internal_new();
    surface->constructor(surface, display);
    return surface;
}

void bd_surface_internal_destroy(bd_surface_internal_t surface)
{
    bd_surface_internal_delete(surface);
}

void bd_cairo_surface_constructor(bd_surface_internal_t surface, bd_display_t display)
{
    if (surface == BD_NULL) return;
    void* buffer = display->get_buffer(display);
    bd_color_type color_type = display->get_color_type(display);

    BD_INT width = display->get_screen_width(display);
    BD_INT height = display->get_screen_height(display);

    surface->cs = cairo_image_surface_create_for_data((BD_UCHAR*)buffer,
                                                CAIRO_FORMAT_RGB16_565,
                                                width,
                                                height,
                                                cairo_format_stride_for_width(CAIRO_FORMAT_RGB16_565, width));
    cairo_t* cr = cairo_create(surface->cs);
}

void bd_cairo_surface_destructor(bd_surface_internal_t surface)
{
    if (surface == BD_NULL) return;
    cairo_surface_destroy(surface->cs);
}

BD_CLASS_CONSTRUCTOR_START(bd_surface_internal)
BD_CLASS_METHOD(constructor, bd_cairo_surface_constructor)
BD_CLASS_METHOD(destructor, bd_cairo_surface_destructor)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_surface_internal)
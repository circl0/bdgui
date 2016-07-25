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

bd_cairo_surface_t bd_cairo_surface_create(bd_display_t display)
{
    if (display == BD_NULL) {
        return BD_NULL;
    }
    bd_cairo_surface_t cs = bd_cairo_surface_new();
    cs->constructor(cs, display);
    return cs;
}

void bd_cairo_surface_destroy(bd_cairo_surface_t surface)
{
    bd_cairo_surface_delete(surface);
}

void bd_cairo_surface_constructor(bd_cairo_surface_t cs, bd_display_t display)
{
    if (cs == BD_NULL) return;
    cs->display = display;
    cs->buffer = display->get_buffer(display);
    cs->color_type = display->get_color_type(display);
    cs->width = display->get_screen_width(display);
    cs->height = display->get_screen_height(display);

    cs->cs = cairo_image_surface_create_for_data((BD_UCHAR*)cs->buffer,
                                                CAIRO_FORMAT_RGB16_565,
                                                cs->width,
                                                cs->height,
                                                cairo_format_stride_for_width(CAIRO_FORMAT_RGB16_565, cs->width));
    cairo_t* cr = cairo_create(cs->cs);

    cs->painter = bd_cairo_painter_create(cr);
}

void bd_cairo_surface_destructor(bd_cairo_surface_t cs)
{
    if (cs == BD_NULL) return;
    bd_cairo_painter_destroy(cs->painter);
    cairo_surface_destroy(cs->cs);
}

bd_painter_t bd_cairo_surface_get_painter(bd_surface_t s)
{
    if (s == BD_NULL) return BD_NULL;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    return BD_SUP(cs->painter, bd_painter);
}

BD_UINT bd_cairo_surface_get_width(bd_surface_t s)
{
    if (s == BD_NULL) return 0;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    return cs->width;
}

BD_UINT bd_cairo_surface_get_height(bd_surface_t s)
{
    if (s == BD_NULL) return 0;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    return cs->height;
}

void bd_cairo_surface_lock(bd_surface_t s)
{
    if (s == BD_NULL) return;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    cs->display->lock(cs->display);
}

void bd_cairo_surface_unlock(bd_surface_t s)
{
    if (s == BD_NULL) return;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    cs->display->unlock(cs->display);
}

void bd_cairo_surface_flip(bd_surface_t s)
{
    if (s == BD_NULL) return;
    bd_cairo_surface_t cs = BD_SUB(s, bd_surface, bd_cairo_surface);
    cs->display->flip(cs->display);
}

BD_CLASS_CONSTRUCTOR_START(bd_cairo_surface)
BD_CLASS_METHOD(constructor, bd_cairo_surface_constructor)
BD_CLASS_METHOD(destructor, bd_cairo_surface_destructor)
BD_CLASS_METHOD(bd_surface.get_painter, bd_cairo_surface_get_painter)
BD_CLASS_METHOD(bd_surface.get_width, bd_cairo_surface_get_width)
BD_CLASS_METHOD(bd_surface.get_height, bd_cairo_surface_get_height)
BD_CLASS_METHOD(bd_surface.lock, bd_cairo_surface_lock)
BD_CLASS_METHOD(bd_surface.unlock, bd_cairo_surface_unlock)
BD_CLASS_METHOD(bd_surface.flip, bd_cairo_surface_flip)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cairo_surface)
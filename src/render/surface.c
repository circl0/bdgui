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
#include "system/system.h"
#include "system/display.h"

bd_surface_t bd_surface_create()
{
    bd_surface_t surface = (bd_surface_t)bd_malloc(sizeof(bd_surface));
    if (surface == BD_NULL) {
        return BD_NULL;
    }
    surface->height = bd_get_screen_height();
    surface->width = bd_get_screen_width();
    surface->buffer = bd_malloc(surface->height * surface->width * sizeof(BD_UINT));
    return surface;
}

void bd_surface_destroy(bd_surface_t surface)
{
    if (surface == BD_NULL) {
        return;
    }
    if (surface->buffer != BD_NULL) {
        bd_free(surface->buffer);
    }
    bd_free(surface);
}

void bd_surface_output(bd_surface_t surface)
{

}

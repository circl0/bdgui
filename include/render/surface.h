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


#ifndef BDGUI_SURFACE_H
#define BDGUI_SURFACE_H

#include "type/type.h"

typedef struct bd_surface {
    BD_UINT width;
    BD_UINT height;
    BD_HANDLE buffer;
} bd_surface;

typedef bd_surface* bd_surface_t;

bd_surface_t bd_surface_create();

void bd_surface_destroy(bd_surface_t surface);

void bd_surface_draw_line(bd_surface_t surface, BD_UINT x1, BD_UINT y1, BD_UINT x2, BD_UINT y2);

void bd_surface_output(bd_surface_t surface);

#endif //BDGUI_SURFACE_H

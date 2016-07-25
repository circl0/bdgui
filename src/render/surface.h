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

BD_INTERFACE(bd_surface) {

    bd_painter_t (*get_painter)(bd_surface_t surface);
    BD_UINT (*get_width)(bd_surface_t surface);
    BD_UINT (*get_height)(bd_surface_t surface);

    void (*lock)(bd_surface_t surface);
    void (*unlock)(bd_surface_t surface);
    void (*flip)(bd_surface_t surface);

};

#endif //BDGUI_SURFACE_H

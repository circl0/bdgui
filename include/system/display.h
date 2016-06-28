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


#ifndef INCLUDE_SYSTEM_DISPLAY_H_
#define INCLUDE_SYSTEM_DISPLAY_H_

#include "type/type.h"

BD_INT bd_open_display();
BD_INT bd_close_display();
BD_UINT bd_get_screen_width();
BD_UINT bd_get_screen_height();

void bd_paint_start();
void bd_paint_finish();
void bd_paint_pixel(BD_UINT x, BD_UINT y,
		bd_color c);

#endif /* INCLUDE_SYSTEM_DISPLAY_H_ */

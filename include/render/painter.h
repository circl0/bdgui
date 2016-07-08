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


#ifndef INCLUDE_RENDER_PAINTER_H_
#define INCLUDE_RENDER_PAINTER_H_

#include "type/type.h"
#include "type/object.h"

BD_CLASS(bd_painter) {
	BD_EXTENDS(bd_object);
	//surface
	//context
	bd_color line_color;
	BD_UINT line_width;
	bd_color fill_color;
	bd_color font_color;
	// con/des
    void (*constructor)(bd_painter_t p);
    void (*destructor)(bd_painter_t p);
	// drawing method
	void (*draw_line)(bd_painter_t p, BD_INT x1, BD_INT y1, BD_INT x2, BD_INT y2);
	// getter/setter
	void (*set_line_width)(bd_painter_t p, BD_UINT w);
	BD_UINT (*get_line_width)(bd_painter_t p);

	void (*set_line_color)(bd_painter_t p, bd_color c);
	bd_color (*get_line_color)(bd_painter_t p);

	void (*set_font_color)(bd_painter_t p, bd_color c);
	bd_color (*get_font_color)(bd_painter_t p);

};

bd_painter_t bd_painter_create();
void bd_painter_destroy(bd_painter_t p);


#endif /* INCLUDE_RENDER_RENDERER_H_ */

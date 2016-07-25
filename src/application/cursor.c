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

#include "application/cursor.h"
#include "type/type.h"

bd_cursor_t bd_cursor_create()
{
	bd_cursor_t cursor = bd_cursor_new();
	cursor->constructor(cursor);
	return cursor;
}

void bd_cursor_destroy(bd_cursor_t cursor)
{
	bd_cursor_delete(cursor);
}

void bd_cursor_constructor(bd_cursor_t cursor)
{
	cursor->x = 0;
	cursor->y = 0;
}

void bd_cursor_destructor(bd_cursor_t cursor)
{

}

void bd_cursor_set_x(bd_cursor_t cursor, BD_INT x)
{
	cursor->x = x;
}

void bd_cursor_set_y(bd_cursor_t cursor, BD_INT y)
{
	cursor->y = y;
}

BD_INT bd_cursor_get_x(bd_cursor_t cursor)
{
	return cursor->x;
}

BD_INT bd_cursor_get_y(bd_cursor_t cursor)
{
	return cursor->y;
}

void bd_cursor_render(bd_cursor_t cursor, bd_surface_t surface)
{
	bd_painter_t painter = surface->get_painter(surface);
	surface->lock(surface);
	bd_color c = {255, 0, 0};
	bd_rect rect = {cursor->x, cursor->y, 16, 16};
	painter->reset_clip(painter);
	painter->set_color(painter, c);
	painter->draw_rect(painter, &rect);
	painter->fill(painter);
	surface->flip(surface);
	surface->unlock(surface);
}

void bd_cursor_get_bound(bd_cursor_t cursor, bd_rect_t rect)
{
	rect->x = cursor->x;
	rect->y = cursor->y;
	rect->width = 16;
	rect->height = 16;
}

BD_CLASS_CONSTRUCTOR_START(bd_cursor)
BD_CLASS_METHOD(constructor, bd_cursor_constructor)
BD_CLASS_METHOD(destructor, bd_cursor_destructor)
BD_CLASS_METHOD(get_x, bd_cursor_get_x)
BD_CLASS_METHOD(get_y, bd_cursor_get_y)
BD_CLASS_METHOD(set_x, bd_cursor_set_x)
BD_CLASS_METHOD(set_y, bd_cursor_set_y)
BD_CLASS_METHOD(render, bd_cursor_render)
BD_CLASS_METHOD(get_bound, bd_cursor_get_bound)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cursor)
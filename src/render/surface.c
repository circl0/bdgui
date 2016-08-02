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

bd_surface_t bd_surface_create(bd_display_t display)
{
	bd_surface_t surface = bd_surface_new();
	surface->constructor(surface, display);
	return surface;
}

void bd_surface_destroy(bd_surface_t surface)
{
	bd_surface_delete(surface);
}

void bd_surface_constructor(bd_surface_t surface, bd_display_t display)
{
	surface->display = display;
	surface->surface_internal = bd_surface_internal_create(display);
	surface->width = display->get_screen_width(display);
	surface->height = display->get_screen_height(display);
	surface->color_type = display->get_color_type(display);
	
	surface->painter = bd_painter_new();
	surface->painter->constructor(surface->painter);
	surface->painter->painter_internal = bd_painter_internal_create(surface->surface_internal);
}

void bd_surface_destructor(bd_surface_t surface)
{
	bd_surface_internal_destroy(surface->surface_internal);
}

bd_painter_t bd_surface_get_painter(bd_surface_t surface)
{
	return surface->painter;
}

BD_UINT bd_surface_get_width(bd_surface_t surface)
{
	return surface->width;
}

BD_UINT bd_surface_get_height(bd_surface_t surface)
{
	return surface->height;
}

void bd_surface_lock(bd_surface_t surface)
{
	surface->display->lock(surface->display);
}

void bd_surface_unlock(bd_surface_t surface)
{
	surface->display->unlock(surface->display);
}

void bd_surface_flip(bd_surface_t surface)
{
	surface->display->flip(surface->display);
}

BD_CLASS_CONSTRUCTOR_START(bd_surface)
BD_CLASS_METHOD(constructor, bd_surface_constructor)
BD_CLASS_METHOD(destructor, bd_surface_destructor)
BD_CLASS_METHOD(get_painter, bd_surface_get_painter)
BD_CLASS_METHOD(get_width, bd_surface_get_width)
BD_CLASS_METHOD(get_height, bd_surface_get_height)
BD_CLASS_METHOD(lock, bd_surface_lock)
BD_CLASS_METHOD(unlock, bd_surface_unlock)
BD_CLASS_METHOD(flip, bd_surface_flip)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_surface)
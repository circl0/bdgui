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

#include "component/component.h"

void bd_component_constructor(bd_component_t component, BD_INT id)
{
	component->id = id;
}

void bd_component_destructor(bd_component_t component)
{

}

void bd_component_set_x(bd_component_t component, BD_INT x)
{
	component->x = x;
}

void bd_component_set_y(bd_component_t component, BD_INT y)
{
	component->y = y;
}

void bd_component_set_width(bd_component_t component, BD_INT width)
{
	component->width = width;
}

void bd_component_set_height(bd_component_t component, BD_INT height)
{
	component->height = height;
}

void bd_component_set_background(bd_component_t component, bd_color background)
{
	component->background = background;
}

BD_INT bd_component_get_x(bd_component_t component)
{
	return component->x;
}

BD_INT bd_component_get_y(bd_component_t component)
{
	return component->y;
}

BD_INT bd_component_get_width(bd_component_t component)
{
	return component->width;
}

BD_INT bd_component_get_height(bd_component_t component)
{
	return component->height;
}

void bd_component_move(bd_component_t component, BD_INT x, BD_INT y)
{
	component->x += x;
	component->y += y;
}

void bd_component_set_on_mouse_button(bd_component_t component, void(*bd_mouse_button_listener_t)(bd_mouse_button_event_t event, bd_component_t component))
{
	component->bd_mouse_button_listener_t = bd_mouse_button_listener_t;
}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_component)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_component_constructor)
BD_CLASS_METHOD(destructor, bd_component_destructor)
BD_CLASS_METHOD(set_x, bd_component_set_x)
BD_CLASS_METHOD(set_y, bd_component_set_y)
BD_CLASS_METHOD(set_width, bd_component_set_width)
BD_CLASS_METHOD(set_height, bd_component_set_height)
BD_CLASS_METHOD(set_background, bd_component_set_background)
BD_CLASS_METHOD(get_x, bd_component_get_x)
BD_CLASS_METHOD(get_y, bd_component_get_y)
BD_CLASS_METHOD(get_width, bd_component_get_width)
BD_CLASS_METHOD(get_height, bd_component_get_height)
BD_CLASS_METHOD(move, bd_component_move)
BD_CLASS_METHOD(set_on_mouse_button, bd_component_set_on_mouse_button)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END

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

#include "component/button.h"
#include "type/type.h"
#include <string.h>

void bd_button_constructor(bd_button_t button, BD_INT id)
{
	BD_SUP(button, bd_component)->constructor(BD_SUP(button, bd_component), id);
	button->text = BD_NULL;
	button->text_size = 10;
	memset(&(button->text_color), 0, sizeof(bd_color));
}

void bd_button_destructor(bd_button_t button)
{

}

void bd_button_on_render(bd_component_t component, bd_surface_t surface)
{
	// surface->lock(surface);
	bd_painter_t painter = surface->get_painter(surface);
	bd_button_t button = BD_SUB(component, bd_component, bd_button);
	painter->set_color(painter, component->background);
	bd_rect rect = {component->x, component->y, component->width, component->height};
	painter->draw_rect(painter, &rect);
	painter->fill(painter);
	painter->set_color(painter, button->text_color);
	painter->set_font_size(painter, button->text_size);
	painter->set_font(painter, "Songti");
	painter->draw_text(painter, component->x + button->text_size / 2, component->y + 10, button->text);
	// surface->lock(surface);
}

void bd_button_on_mouse_button(bd_component_t component, bd_mouse_button_event_t mouse_button_event)
{

}

void bd_button_set_text(bd_button_t button, const BD_CHAR* text)
{
	if (button->text != BD_NULL) {
		bd_free(text);
		button->text = BD_NULL;
	}
	button->text = bd_malloc(strlen(text) + 1);
	strcpy(button->text, text);
}

void bd_button_set_text_size(bd_button_t button, BD_INT size)
{
	button->text_size = size;
}

void bd_button_set_text_color(bd_button_t button, bd_color c)
{
	button->text_color = c;
}


BD_CLASS_CONSTRUCTOR_START(bd_button)
BD_SUPER_CONSTRUCTOR(bd_component)
BD_CLASS_METHOD(constructor, bd_button_constructor)
BD_CLASS_METHOD(destructor, bd_button_constructor)
BD_CLASS_METHOD(bd_component.on_mouse_button, bd_button_on_mouse_button)
BD_CLASS_METHOD(bd_component.on_render, bd_button_on_render)
BD_CLASS_METHOD(set_text, bd_button_set_text)
BD_CLASS_METHOD(set_text_size, bd_button_set_text_size)
BD_CLASS_METHOD(set_text_color, bd_button_set_text_color)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_button)
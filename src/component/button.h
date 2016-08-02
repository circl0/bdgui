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


#ifndef BD_BUTTON_H
#define BD_BUTTON_H

#include "component/component.h"
#include "event/event.h"
#include "type/type.h"

BD_CLASS(bd_button) {
	BD_EXTENDS(bd_component);

	BD_CHAR* text;
	BD_INT text_size;
	bd_color text_color;
	
	void (*constructor)(bd_button_t button, BD_INT id);
	void (*destructor)(bd_button_t button);
	void (*set_text)(bd_button_t button, const BD_CHAR* text);
	void (*set_text_size)(bd_button_t button, BD_INT size);
	void (*set_text_color)(bd_button_t button, bd_color c);
	
};


#endif
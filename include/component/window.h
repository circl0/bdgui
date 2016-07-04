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

#ifndef INCLUDE_COMPONENT_WINDOW_H_
#define INCLUDE_COMPONENT_WINDOW_H_

#include "component/base.h"
#include "event/base.h"

typedef struct bd_window bd_window, *bd_window_t;

BD_CLASS(bd_window) {
	BD_EXTENDS(bd_component);
	void(*render)(bd_window_t window);
	void(*handle_event)(bd_window_t window, bd_event_t event);
};





#endif 

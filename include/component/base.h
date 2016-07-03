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


#ifndef BD_COMPONENT_H
#define BD_COMPONENT_H

#include "type/object.h"

typedef struct bd_component bd_component, *bd_component_t;

BD_ABSTRACT_CLASS(bd_component) {
	BD_EXTENDS(bd_object);

	void (*render)(bd_component_t);
};

#endif //BD_COMPONENT_H

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

#include "component/base.h"

void bd_component_constructor(bd_component_t component)
{

}

void bd_component_destructor(bd_component_t component)
{

}

BD_ABSTRACT_CLASS_CONSTRUCTOR_START(bd_component)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_component_constructor)
BD_CLASS_METHOD(destructor, bd_component_destructor)
BD_ABSTRACT_CLASS_CONSTRUCTOR_END

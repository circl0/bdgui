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


#ifndef INCLUDE_SYSTEM_SOURCE_H
#define INCLUDE_SYSTEM_SOURCE_H

#include "type/type.h"
#include "type/object.h"
#include "event/base.h"

typedef enum bd_source_type {
	BD_SOURCE_INPUT = 0,
	BD_SOURCE_TIMER,
} bd_source_type;

BD_ABSTRACT_CLASS(bd_source) {
	BD_EXTENDS(bd_object);
	bd_source_type type;

	void(*constructor)(bd_source_t self, bd_source_type type);
	void(*destructor)(bd_source_t self);
	BD_INT (*init)(bd_source_t source);
	BD_INT (*deinit)(bd_source_t source);
	bd_event_t (*read_events)(bd_source_t source);
};

void bd_source_destroy(bd_source_t source);

#endif /* INCLUDE_SYSTEM_LINUX_SOURCE_H_ */

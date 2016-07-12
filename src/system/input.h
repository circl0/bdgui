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


#ifndef INCLUDE_SYSTEM_INPUT_H_
#define INCLUDE_SYSTEM_INPUT_H_

#include "type/type.h"
#include "event/base.h"
#include "system/source.h"
#include "type/object.h"

typedef enum bd_input_type {
	BD_INPUT_INVALID = -1,
	BD_INPUT_MOUSE,
	BD_INPUT_TOUCH,
	BD_INPUT_KEYBOARD
} bd_input_type;

#define BD_INPUT_NAME_MAX 255

BD_ABSTRACT_CLASS(bd_input) {
	EXTENDS(bd_source);
	char name[BD_INPUT_NAME_MAX];
	bd_input_type type;

	void(*constructor)(bd_input_t input, bd_input_type type);
	void(*destructor)(bd_input_t input);

	BD_INT(*open)(bd_input_t input);
	BD_INT(*close)(bd_input_t input);
	bd_event_t(*read)(bd_input_t input);
};

bd_input_t bd_input_create(const char* name, bd_input_type type);
void bd_input_destroy(bd_input_t input);

#endif /* INCLUDE_SYSTEM_LINUX_INPUT_H_ */

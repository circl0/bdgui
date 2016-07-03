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

#ifndef INCLUDE_SYSTEM_LINUX_INPUT_H_
#define INCLUDE_SYSTEM_LINUX_INPUT_H_

#include "system/linux/source_pool.h"
#include "system/input.h"

BD_CLASS(bd_linux_input) {
	BD_EXTENDS(bd_input);
	BD_INT fd;

	void(*constructor)(bd_linux_input_t input, const char* name, bd_input_type type);
	void(*destructor)(bd_linux_input_t input);

};

#endif 

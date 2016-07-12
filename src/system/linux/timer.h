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

#ifndef INCLUDE_SYSTEM_LINUX_TIMER_H_
#define INCLUDE_SYSTEM_LINUX_TIMER_H_

#include "type/object.h"
#include "system/timer.h"

BD_CLASS(bd_linux_timer) {
	BD_EXTENDS(bd_timer);
	BD_INT fd;

	void(*constructor)(bd_linux_timer_t self, BD_INT id, BD_ULONG milliseconds);
	void(*destructor)(bd_linux_timer_t timer);

};


#endif 

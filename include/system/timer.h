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

#ifndef BDGUI_TIMER_H
#define BDGUI_TIMER_H

#include "type/type.h"
#include "type/object.h"
#include "system/source.h"

BD_ABSTRACT_CLASS(bd_timer) {
	EXTENDS(bd_source);

	BD_INT id;
	BD_ULONG timeout;

	void(*constructor)(bd_timer_t self, BD_INT id, BD_ULONG milliseconds);
	void(*destructor)(bd_timer_t self);

	BD_INT(*start)(bd_timer_t input);
	BD_INT(*stop)(bd_timer_t input);
	bd_event_t(*read)(bd_timer_t input);

};

bd_timer_t bd_timer_create(BD_INT id, BD_ULONG timeout);
void bd_timer_destroy(bd_timer_t timer);

#endif

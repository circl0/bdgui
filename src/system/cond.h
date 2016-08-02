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

#ifndef INCLUDE_SYSTEM_COND_H_
#define INCLUDE_SYSTEM_COND_H_

#include "type/object.h"
#include "system/mutex.h"
#include "system/linux/cond.h"

BD_CLASS(bd_cond) {
	BD_EXTENDS(bd_object);

	bd_cond_internal_t cond_internal;

	void (*constructor)(bd_cond_t cond);
	void (*destructor)(bd_cond_t cond);

	BD_INT (*wait)(bd_cond_t cond, bd_mutex_t mutex);
	BD_INT (*signal)(bd_cond_t cond);

};

bd_cond_t bd_cond_create();
void bd_cond_destroy(bd_cond_t cond);

#endif 

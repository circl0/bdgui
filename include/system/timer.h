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

#include "type/type.h"

struct bd_timer;
typedef struct bd_timer bd_timer, *bd_timer_t;

typedef void(*bd_timer_func)(BD_HANDLE);

bd_timer_t bd_timer_create(BD_UINT milliseconds);
void bd_timer_destroy(bd_timer_t timer);
void bd_timer_set_timeout(bd_timer_t timer, BD_UINT milliseconds);

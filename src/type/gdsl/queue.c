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


#ifdef WITH_GDSL

#include "type/queue.h"
#include "system/system.h"

bd_queue_t bd_queue_create()
{
	return gdsl_queue_alloc("", bd_malloc, bd_free);
}

void bd_queue_destroy(bd_queue_t queue)
{
	gdsl_queue_free(queue);
}

void bd_queue_push(bd_queue_t queue, BD_HANDLE data)
{
	gdsl_queue_insert(queue, data);
}

BD_HANDLE bd_queue_get(bd_queue_t queue)
{
	return gdsl_queue_remove(queue);
}

#endif

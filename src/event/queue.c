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

#include "event/queue.h"
#include "type/queue.h"
#include "type/type.h"
#include "system/system.h"

bd_event_queue_t bd_event_queue_create()
{
	bd_event_queue_t event_queue = (bd_event_queue_t) bd_malloc(sizeof(bd_event_queue));
	if (event_queue == BD_NULL) {
		return BD_NULL;
	}
	event_queue->mutex = bd_mutex_create();
	event_queue->queue = bd_queue_create();
	return event_queue;
}

void bd_event_queue_destroy(bd_event_queue_t event_queue)
{
	if (event_queue == BD_NULL) {
		return;
	}
	bd_queue_destroy(event_queue->queue);
	bd_mutex_destroy(event_queue->mutex);
}

void bd_event_queue_push(bd_event_queue_t event_queue, bd_event_t event)
{
	bd_mutex_lock(event_queue->mutex);
	bd_queue_push(event_queue->queue, event);
	bd_mutex_unlock(event_queue->mutex);
}

bd_event_t bd_event_queue_get(bd_event_queue_t event_queue)
{
	bd_event_t result = BD_NULL;
	bd_mutex_lock(event_queue->mutex);
	result = (bd_event_t) bd_queue_get(event_queue->queue);
	bd_mutex_unlock(event_queue->mutex);
	return result;
}

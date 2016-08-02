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

#ifndef INCLUDE_EVENT_QUEUE_H_
#define INCLUDE_EVENT_QUEUE_H_

#include "type/queue.h"
#include "event/event.h"
#include "system/mutex.h"
#include "system/cond.h"

typedef struct bd_event_queue {
	bd_queue_t queue;
	bd_mutex_t mutex;
	bd_cond_t cond;
} bd_event_queue, *bd_event_queue_t;

bd_event_queue_t bd_event_queue_create();
void bd_event_queue_destroy(bd_event_queue_t queue);

void bd_event_queue_push(bd_event_queue_t queue, bd_event_t event);
bd_event_t bd_event_queue_get(bd_event_queue_t queue);

#endif 

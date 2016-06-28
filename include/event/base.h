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


#ifndef BD_EVENT_H
#define BD_EVENT_H

#include <type/queue.h>
#include "type/object.h"
#include "type/type.h"
#include "component/component.h"

#define BD_EVENT_NUM_MAX	256

typedef enum bd_event_id {
    BD_EVENT_INVALID = -1,
	BD_EVENT_MAX = BD_EVENT_NUM_MAX,
} bd_event_id;

typedef struct bd_event {
    bd_object base;
    bd_event_id id;
    bd_object_t sender;
    bd_object_t target;
} bd_event;

typedef struct bd_event* bd_event_t;
typedef void(*bd_event_handler_t)(bd_event_t);

bd_event_t bd_event_create();
void bd_event_destroy(bd_event_t event);

void bd_event_send(bd_event_t ptr);

void bd_event_handle();

void bd_event_system_init();


#endif

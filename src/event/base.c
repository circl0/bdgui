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


#include "system/system.h"
#include "event/base.h"
#include "event/map.h"
#include "type/list.h"

static bd_queue_t bd_event_queue_get()
{
	static bd_queue_t event_queue = BD_NULL;
    if (event_queue == BD_NULL) {
        event_queue = bd_queue_create();
    }
    return event_queue;
}

static BD_INT bd_event_handler_run(BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	bd_event_handler_t handler = (bd_event_handler_t)e;
	if (handler == BD_NULL) {
		return 1;
	}
	handler((bd_event_t)data);
	return 1;
}

bd_event_t bd_event_create()
{
	bd_event_t event = (bd_event_t) bd_malloc(sizeof(bd_event));
	return event;
}

void bd_event_destroy(bd_event_t event)
{
	if (event == BD_NULL) {
		return;
	}
	bd_free(event);
}

void bd_event_send(bd_event_t ptr)
{
	bd_queue_t event_queue = bd_event_queue_get();
    if (event_queue == BD_NULL) {
        return;
    }
    bd_queue_push(event_queue, ptr);
}

void bd_event_handle()
{
	bd_queue_t event_queue = bd_event_queue_get();
	if (event_queue == BD_NULL) {
        return;
    }
    bd_event_t event = (bd_event_t) bd_queue_get(event_queue);
    if (event == BD_NULL) {
    	return;
    }
    bd_list_t list = bd_get_message_handlers(event->id, event->sender);
    bd_list_for_each(list, bd_event_handler_run, event);
    bd_free(event);
}

void bd_event_system_init()
{
	bd_main_loop();
	while(1) {
		bd_event_handle();
	}
}

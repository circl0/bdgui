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


#include "event/map.h"
#include "system/system.h"

typedef struct bd_sender {
	bd_object_t object;
	bd_list_t handlers;
} bd_sender, *bd_sender_t;

static bd_list_t bd_message_handler_map[BD_EVENT_NUM_MAX];

static BD_LONGINT bd_find_sender_by_object(const BD_HANDLE e, BD_HANDLE value)
{
	if (e == value) {
		return 0;
	}
	return 1;
}

static BD_LONGINT bd_find_handler_by_object(const BD_HANDLE e, BD_HANDLE value)
{
	if (((bd_sender_t)e)->object == (bd_object_t)value) {
		return 0;
	}
	return 1;
}

void bd_register_message_handler(bd_event_id id, bd_object_t object, bd_event_handler_t handler)
{
	bd_list_t handler_list = bd_message_handler_map[id];
	if (handler_list == BD_NULL) {
		handler_list = bd_list_create();
	}
	bd_sender_t sender = bd_list_search(handler_list, bd_find_sender_by_object, object);
	if (sender == BD_NULL) {
		sender = bd_malloc(sizeof(bd_sender));
		sender->object = object;
		sender->handlers = bd_list_create();
	}
	bd_list_push(sender->handlers, handler);
}

void bd_unregister_message_handler(bd_event_id id, bd_object_t object, bd_event_handler_t handler)
{
	bd_list_t handler_list = bd_message_handler_map[id];
	if (handler_list == BD_NULL) {
		return;
	}
	bd_sender_t sender = bd_list_search(handler_list, bd_find_sender_by_object, object);
	if (sender == BD_NULL) {
		return;
	}
	bd_list_remove(sender->handlers, bd_find_handler_by_object, handler);
}

bd_list_t bd_get_message_handlers(bd_event_id id, bd_object_t object)
{
	bd_list_t handler_list = bd_message_handler_map[id];
	if (handler_list == BD_NULL) {
		return BD_NULL;
	}
	bd_sender_t sender = bd_list_search(handler_list, bd_find_sender_by_object, object);
	if (sender == BD_NULL) {
		return BD_NULL;
	}
	return sender->handlers;

}

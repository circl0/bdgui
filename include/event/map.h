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


#ifndef INCLUDE_EVENT_MAP_H_
#define INCLUDE_EVENT_MAP_H_


#include "event/base.h"
#include "type/list.h"

void bd_register_message_handler(bd_event_id id, bd_object_t object, bd_event_handler_t handler);
void bd_unregister_message_handler(bd_event_id id, bd_object_t object, bd_event_handler_t handler);

bd_list_t bd_get_message_handlers(bd_event_id id, bd_object_t object);

#endif /* INCLUDE_EVENT_MAP_H_ */

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

#include "system/system.h"
#include "event/application.h"
#include "type/type.h"

static bd_application_t app = BD_NULL;

static BD_INT bd_application_event_queue_map_func(BD_HANDLE e, BD_INT location, BD_HANDLE data)
{
	bd_window_t window = (bd_window_t) e;
	bd_event_t event = (bd_event_t) data;
	if (window == BD_NULL || event == BD_NULL) {
		return 0;
	}
	window->handle_message(window, event);
	return 1;
}

static BD_HANDLE bd_application_run_func(BD_HANDLE data)
{
	bd_application_t app = (bd_application_t) data;
	if (app == BD_NULL) {
		return BD_NULL;
	}
	while (1) {
		bd_event_t event = bd_event_queue_get(app->event_queue);
		if (event != BD_NULL) {
			bd_list_for_each(app->window_list, bd_application_event_queue_map_func, event);
		}
		bd_free(event);
	}
	return BD_NULL;
}

void bd_application_run(bd_window_t main_window)
{
	app = (bd_application_t) bd_malloc(sizeof(bd_application));
	if (app == BD_NULL) {
		return;
	}
//	app->clazz->type = BD_TYPE_APPLICATION;
	app->event_queue = bd_event_queue_create();
	app->window_list = bd_list_create();
	bd_list_push(app->window_list, main_window);
	app->thread = bd_thread_create(bd_application_run_func, app);
	bd_main_loop();
}

void bd_application_send_event(bd_event_t event)
{
	if (app == BD_NULL) {
		return;
	}
	bd_event_queue_push(app->event_queue, event);
}

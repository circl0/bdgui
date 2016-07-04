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

#include "application/application.h"

static BD_HANDLE bd_application_run_func(BD_HANDLE data)
{
	bd_application_t app = (bd_application_t) data;
	if (app == BD_NULL) {
		return BD_NULL;
	}
	while (1) {
		bd_event_t event = bd_event_queue_get(app->event_queue);
		app->windows_mananger->handler_event(app->windows_mananger, event);
		bd_free(event);
	}
	return BD_NULL;
}

void bd_application_constructor(bd_application_t app)
{
	if (app == BD_NULL) {
		return;
	}
	app->windows_mananger = bd_windows_manager_create();
	app->thread = bd_thread_create(bd_application_run_func, app);
	app->event_queue = bd_event_queue_create();
}

void bd_application_destructor(bd_application_t app)
{
	if (app == BD_NULL) {
		return;
	}
	bd_event_queue_destroy(app->event_queue);
	bd_thread_destroy(app->thread);
	bd_windows_manager_destroy(app->windows_mananger);
}

void bd_application_run(bd_application_t app, bd_window_t main_window)
{
	if (app == BD_NULL) {
		return;
	}
	app->windows_mananger->add(app->windows_mananger, main_window);
	app->thread->start(app->thread, app);
	bd_main_loop();
}

void bd_application_send_event(bd_application_t app, bd_event_t event)
{
	if (app == BD_NULL) {
		return;
	}
	bd_event_queue_push(app->event_queue, event);
}

BD_CLASS_CONSTRUCTOR_START(bd_application)
BD_SUPER_CONSTRUCTOR(bd_object)
BD_CLASS_METHOD(constructor, bd_application_constructor)
BD_CLASS_METHOD(destructor, bd_application_destructor)
BD_CLASS_METHOD(run, bd_application_run)
BD_CLASS_METHOD(send_event, bd_application_send_event)
BD_CLASS_CONSTRUCTOR_END

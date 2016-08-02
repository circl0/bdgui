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

bd_application_t bd_application_create()
{
	bd_application_t app = bd_application_new();
	app->constructor(app);
	return app;
}

void bd_application_destroy(bd_application_t app)
{
	bd_application_delete(app);
}

void bd_application_constructor(bd_application_t app)
{
	app->bd_service = bd_system_service_get();
    app->bd_service->init(app->bd_service);

    bd_display_t display = app->bd_service->get_display(app->bd_service);
    bd_surface_t surface = bd_surface_create(display);
    app->windows_manager = bd_windows_manager_create(surface);
}

void bd_application_destructor(bd_application_t app)
{
	
}

void bd_application_run(bd_application_t app, bd_window_t window)
{
	app->windows_manager->add(app->windows_manager, window);
	app->bd_service->run(app->bd_service);
}

BD_CLASS_CONSTRUCTOR_START(bd_application)
BD_CLASS_METHOD(constructor, bd_application_constructor)
BD_CLASS_METHOD(destructor, bd_application_destructor)
BD_CLASS_METHOD(run, bd_application_run)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_application)
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

#ifndef INCLUDE_APPLICATION_APPLICATION_H_
#define INCLUDE_APPLICATION_APPLICATION_H_

#include "component/window.h"
#include "system/system.h"
#include "application/windows_manager.h"

BD_CLASS(bd_application) {
	BD_EXTENDS(bd_object);

	bd_system_service_t bd_service;
	bd_windows_manager_t windows_manager;

	void (*constructor)(bd_application_t app);
	void (*destructor)(bd_application_t app);	

	void (*run)(bd_application_t app, bd_window_t window);
};	

bd_application_t bd_application_create();
void bd_application_destroy(bd_application_t app);

#endif
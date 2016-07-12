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


#ifndef INCLUDE_EVENT_APPLICATION_H_
#define INCLUDE_EVENT_APPLICATION_H_

#include "application/windows_manager.h"
#include "system/thread.h"
#include "event/queue.h"
#include "component/window.h"
#include "type/object.h"

BD_CLASS(bd_application) {
	BD_EXTENDS(bd_object);

	bd_thread_t thread;
	bd_event_queue_t event_queue;
	bd_windows_manager_t windows_mananger;

	void (*constructor)(bd_application_t app);
	void (*destructor)(bd_application_t app);

	void (*run)(bd_application_t app, bd_window_t main_window);
	void (*send_event)(bd_application_t app, bd_event_t event);
};

#endif 

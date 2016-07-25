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


#ifndef BD_SYSTEM_H
#define BD_SYSTEM_H

#include "type/type.h"
#include "type/object.h"
#include "system/display.h"
#include "system/input.h"
#include "system/mutex.h"
#include "system/source.h"
#include "system/source_pool.h"
#include "system/thread.h"
#include "system/timer.h"

// memory
BD_HANDLE bd_malloc(BD_INT size);
void bd_free(BD_HANDLE handle);

BD_INTERFACE(bd_system_service) {

	void (*init)(bd_system_service_t service);
	void (*deinit)(bd_system_service_t service);
	void (*run)(bd_system_service_t service);

	bd_timer_t (*create_timer)(bd_system_service_t service, BD_INT id, BD_ULONG timeout);
	void (*destroy_timer)(bd_system_service_t service, bd_timer_t timer);
	void (*register_input)(bd_system_service_t service, const char* name, bd_input_type type);
	BD_ULONG (*get_tick_count)(bd_system_service_t service);

	bd_display_t (*get_display)(bd_system_service_t service);
};

bd_system_service_t bd_system_service_get();
void bd_system_service_destroy();

#endif

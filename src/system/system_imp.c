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


#include "system/system_imp.h"
#include "system/system.h"
#include "system/source_pool.h"
#include "application/windows_manager.h"
#include "utils/log.h"

static bd_system_service_imp_t service_imp = BD_NULL;

static void bd_source_pool_event_function(bd_source_t source)
{
	bd_event_t event = source->read_events(source);
	if (event == BD_NULL) {
		return;
	}
	bd_windows_manager_t manager = bd_windows_manager_get();
	if (event != BD_NULL && manager != BD_NULL) {
		manager->send_event(manager, event);
	}
}

static BD_HANDLE bd_main_loop(bd_source_pool_t pool)
{
	while (1) {
		pool->wait_for_events(pool, bd_source_pool_event_function);
	}
	return BD_NULL;
}

bd_system_service_t bd_system_service_get()
{
	if (service_imp == BD_NULL) {
		service_imp = bd_system_service_imp_new();
		service_imp->constructor(service_imp);
	}
	return BD_SUP(service_imp, bd_system_service);
}

void bd_system_service_destroy()
{
	if (service_imp == BD_NULL) {
		return;
	}
	bd_system_service_imp_delete(service_imp);
}

void bd_system_service_imp_constructor(bd_system_service_imp_t service)
{

}

void bd_system_service_imp_destructor(bd_system_service_imp_t service)
{

}

void bd_system_service_imp_init(bd_system_service_t service)
{
	// 1. init display
	if (service == BD_NULL) {
		return;
	}

	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);
    service_imp->display = bd_display_create();
    
    if (service_imp->display == BD_NULL) {
        bd_log("display_test", "display create failure");
        return;
    }
    service_imp->display->open(service_imp->display);
    // 2. init source
   	service_imp->source_pool = bd_source_pool_create(2);

   	service->register_input(service, "event0", BD_INPUT_MOUSE);
   	service->register_input(service, "event1", BD_INPUT_KEYBOARD);
}

void bd_system_service_imp_deinit(bd_system_service_t service)
{
	// 1. destroy source
	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);

	bd_source_pool_destroy(service_imp->source_pool);

	// 2. destroy display
	BD_INT err = service_imp->display->close(service_imp->display);

    if (err < 0) {
        bd_log("display_test", "display close failure");
        return;
    }

    bd_display_destroy(service_imp->display);
}

void bd_system_service_imp_run(bd_system_service_t service)
{
	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);
	bd_main_loop(service_imp->source_pool);
}

bd_timer_t bd_system_service_imp_create_timer(bd_system_service_t service, BD_INT id, BD_ULONG timeout)
{
	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);
	bd_source_t timer = BD_SUP(bd_timer_create(id, timeout), bd_source);
	timer->init(timer);
	service_imp->source_pool->push(service_imp->source_pool, timer);
}

void bd_system_service_imp_destroy_timer(bd_system_service_t service, bd_timer_t timer)
{
	
}

void bd_system_service_imp_register_input(bd_system_service_t service, const char* name, bd_input_type type)
{
	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);
	bd_source_t input = BD_SUP(bd_input_create(name, type), bd_source);
	input->init(input);
	service_imp->source_pool->push(service_imp->source_pool, input);
}

bd_display_t bd_system_service_imp_get_display(bd_system_service_t service)
{
	bd_system_service_imp_t service_imp = BD_SUB(service, bd_system_service, bd_system_service_imp);
	return service_imp->display;
}


BD_CLASS_CONSTRUCTOR_START(bd_system_service_imp)
BD_CLASS_METHOD(constructor, bd_system_service_imp_constructor)
BD_CLASS_METHOD(destructor, bd_system_service_imp_destructor)
BD_CLASS_METHOD(bd_system_service.init, bd_system_service_imp_init)
BD_CLASS_METHOD(bd_system_service.deinit, bd_system_service_imp_deinit)
BD_CLASS_METHOD(bd_system_service.run, bd_system_service_imp_run)
BD_CLASS_METHOD(bd_system_service.create_timer, bd_system_service_imp_create_timer)
BD_CLASS_METHOD(bd_system_service.destroy_timer, bd_system_service_imp_destroy_timer)
BD_CLASS_METHOD(bd_system_service.register_input, bd_system_service_imp_register_input)
BD_CLASS_METHOD(bd_system_service.get_display, bd_system_service_imp_get_display)
BD_CLASS_CONSTRUCTOR_END


BD_CLASS_DESTRUCTOR(bd_system_service_imp)
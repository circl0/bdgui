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


#include "component/window.h"
#include "utils/log.h"
#include "application/windows_manager.h"
#include "system/system.h"
#include "render/cairo/cairo_surface.h"

int main()
{
    bd_system_service_t service = bd_system_service_get();
    service->init(service);

    bd_display_t display = service->get_display(service);
    bd_cairo_surface_t surface = bd_cairo_surface_create(display);

    bd_windows_manager_t manager = bd_windows_manager_create(BD_SUP(surface, bd_surface));
    
    bd_window_t window1 = bd_window_new();
    window1->constructor(window1);
    // window1->set_title(window1, "BDGUI_1");
    window1->bd_component.set_x(&window1->bd_component, 10);
    window1->bd_component.set_y(&window1->bd_component, 10);
    window1->bd_component.set_width(&window1->bd_component, 200);
    window1->bd_component.set_height(&window1->bd_component, 100);
    manager->add(manager, window1);

    bd_window_t window2 = bd_window_new();
    // window2->set_title(window2, "BDGUI_2");
    window2->constructor(window2);
    window2->bd_component.set_x(&window2->bd_component, 50);
    window2->bd_component.set_y(&window2->bd_component, 50);
    window2->bd_component.set_width(&window2->bd_component, 200);
    window2->bd_component.set_height(&window2->bd_component, 100);
    manager->add(manager, window2);
    
    service->run(service);


    return 0;
}
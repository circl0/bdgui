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
#include "component/button.h"
#include "application/application.h"

int main()
{
	bd_application_t app = bd_application_create();
    
    bd_window_t window1 = bd_window_new();
    window1->constructor(window1, 1);
    // window1->set_title(window1, "BDGUI_1");
    window1->bd_component.set_x(&window1->bd_component, 10);
    window1->bd_component.set_y(&window1->bd_component, 10);
    window1->bd_component.set_width(&window1->bd_component, 200);
    window1->bd_component.set_height(&window1->bd_component, 100);

    // bd_button_t button = bd_button_new();
    // button->constructor(button, 3);
    // button->bd_component.set_x(&button->bd_component, 20);
    // button->bd_component.set_y(&button->bd_component, 20);
    // button->bd_component.set_width(&button->bd_component, 100);
    // button->bd_component.set_height(&button->bd_component, 100);
    // button->set_text(button, "Click");
    // button->set_text_size(button, 16);
    // bd_color c = {255, 0, 0};
    // button->set_text_color(button, c);
    // window1->add_child(window1, BD_SUP(button, bd_component));

    app->run(app, window1);

    // bd_window_t window2 = bd_window_new();
    // // window2->set_title(window2, "BDGUI_2");
    // window2->constructor(window2, 2);
    // window2->bd_component.set_x(&window2->bd_component, 50);
    // window2->bd_component.set_y(&window2->bd_component, 50);
    // window2->bd_component.set_width(&window2->bd_component, 200);
    // window2->bd_component.set_height(&window2->bd_component, 100);
    // manager->add(manager, window2);
    
    bd_application_destroy(app);


    return 0;
}
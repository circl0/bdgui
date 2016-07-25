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


// #include "system/display.h"
// #include "system/linux/display.h"
// #include "render/surface.h"
// #include "render/cairo/cairo_surface.h"
// #include "render/painter.h"
// #include "render/cairo/cairo_painter.h"
// #include "utils/log.h"

int main()
{   
    // // 1. init display
    // bd_linux_display_t linux_display = bd_linux_display_create();

    // bd_display_t display = BD_SUP(linux_display, bd_display);

    // if (display == BD_NULL) {
    //     bd_log("display_test", "display create failure");
    //     return -1;
    // }

    // BD_INT err = display->open(display);

    // if (err < 0) {
    //     bd_log("display_test", "display open failure");
    //     return -1;
    // }

    // // 2. make surface
    // bd_cairo_surface_t cairo_surface = bd_cairo_surface_create(display);
    // bd_surface_t surface = BD_SUP(cairo_surface, bd_surface);

    // display->start_paint(display);

    // // 3. get painter
    // bd_painter_t painter = surface->get_painter(surface);

    // // 4. do paint

    // // draw line
    // bd_color c1 = {255, 0, 0};
    // painter->set_color(painter, c1);
    // painter->set_line_width(painter, 6);
    // painter->draw_line(painter, 0, 0, 100, 100);

    // // draw circle && fill circle
    // bd_color c2 = {0, 0, 255};
    // painter->set_color(painter, c2);
    // painter->set_line_width(painter, 10);
    // painter->draw_circle(painter, 100, 100, 50);

    // bd_color c3 = {0, 255, 0};
    // painter->set_color(painter, c3);
    // painter->fill_circle(painter, 100, 100, 50 - 3);

    // // draw text
    // bd_color c4 = {255, 255, 255};
    // painter->set_font(painter, "Songti");
    // painter->set_font_size(painter, 24);
    // painter->draw_text(painter, 200, 200, "Shanghai");

    // // draw rect
    // bd_rect rect = {150, 150, 50, 50};
    // painter->draw_rect(painter, &rect);

    // display->finish_paint(display);

    // // 5. free
    // bd_cairo_surface_destroy(cairo_surface);

    // err = display->close(display);
    // if (err < 0) {
    //     bd_log("display_test", "display close failure");
    //     return -1;
    // }

    // bd_linux_display_destroy(linux_display);
    return 0;
}
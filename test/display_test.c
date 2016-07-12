#include "component/window.h"
#include "application/application.h"
#include "utils/log.h"

#include "system/display.h"

int main()
{
    bd_window_t window = bd_window_new();
    window->constructor(window);
    bd_application_t app = bd_application_new();
    app->constructor(app);
    app->run(app, window);

    bd_color c = {0, 0, 255};
    bd_open_display();
    bd_paint_start();
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            bd_paint_pixel(i, j, c);
        }
    }
    bd_paint_finish();

    bd_close_display();

    return 0;
}
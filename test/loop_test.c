#include "component/window.h"
#include "application/application.h"
#include "utils/log.h"

int main()
{
    bd_window_t window = bd_window_new();
    window->constructor(window);
    bd_application_t app = bd_application_new();
    app->constructor(app);
    app->run(app, window);
    return 0;
}
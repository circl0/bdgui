PROJECT(bdgui-lib)

# Source files definition
SET(SRC_LIB
  application/windows_manager.c
  application/cursor.c
  component/component.c
  component/window.c
  event/base.c
  event/events.c
  event/queue.c
  render/cairo/cairo_painter.c
  render/cairo/cairo_surface.c
  render/cairo/cairo_region.c
  system/system_imp.c
  system/input.c
  system/source.c
  system/source_pool.c
  system/timer.c
  system/display.c
  system/linux/display.c
  system/linux/framebuffer.c
  system/linux/input.c
  system/linux/mutex.c
  system/linux/source_pool.c
  system/linux/system.c
  system/linux/thread.c
  system/linux/timer.c
  system/linux/cond.c
  type/base.c
  type/object.c
  type/gdsl/list.c
  type/gdsl/queue.c
  utils/log.c
)

ADD_LIBRARY (
  bdgui
  ${SRC_LIB}
)
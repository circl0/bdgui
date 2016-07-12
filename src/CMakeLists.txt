PROJECT(bdgui-lib)

# Source files definition
SET(SRC_LIB
  application/application.c
  application/windows_manager.c
  component/component.c
  component/window.c
  event/base.c
  event/events.c
  event/map.c
  event/queue.c
  render/painter.c
  render/surface.c
  system/input.c
  system/source.c
  system/source_pool.c
  system/timer.c
  system/linux/display.c
  system/linux/framebuffer.c
  system/linux/input.c
  system/linux/mutex.c
  system/linux/source_pool.c
  system/linux/system.c
  system/linux/thread.c
  system/linux/timer.c
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
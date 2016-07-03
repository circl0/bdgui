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

#include "system/input.h"
#include "system/linux/input.h"
#include "system/system.h"
#include "type/object.h"
#include "event/events.h"
#include "utils/log.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/input.h>

#define INPUT_TAG "input"

static void bd_linux_input_dev_get_mouse_event(bd_linux_input_t input, bd_mouse_event_t event)
{
	struct input_event current_event;
	memset(&current_event, 0, sizeof(struct input_event));
	read(input->fd, &current_event, sizeof(struct input_event));
	if (input == BD_NULL || event == BD_NULL) {
		return;
	}
	bd_log("input", "name: %s, type: %d, code: %d, value: %d\n", input->bd_input.name, current_event.type, current_event.code, current_event.value);
}

static void bd_linux_input_dev_get_keyboard_event(bd_linux_input_t input, bd_keyboard_event_t event)
{
	struct input_event current_event;
	memset(&current_event, 0, sizeof(struct input_event));
	read(input->fd, &current_event, sizeof(struct input_event));
	if (input == BD_NULL || event == BD_NULL) {
		return;
	}
	bd_log("input", "name: %s, type: %d, code: %d, value: %d\n", input->bd_input.name, current_event.type, current_event.code, current_event.value);
}

static void bd_linux_input_dev_get_touch_event(bd_linux_input_t input, bd_touch_event_t event)
{

}

bd_input_t bd_input_create(const char* name, bd_input_type type)
{
	bd_linux_input_t linux_input = bd_linux_input_new();
	linux_input->constructor(linux_input, name, type);
	return BD_SUP(linux_input, bd_input);
}

void bd_input_destroy(bd_input_t input)
{
	if (input == BD_NULL) {
		return;
	}
	bd_linux_input_t linux_input = BD_SUB(input, bd_input, bd_linux_input);
	bd_linux_input_delete(linux_input);
}

void bd_linux_input_dev_constructor(bd_linux_input_t linux_input, const char* name, bd_input_type type)
{
	if (linux_input == BD_NULL) {
		return;
	}
	bd_input_t input = BD_SUP(linux_input, bd_input);
	input->constructor(input, type);
	strcpy(linux_input->bd_input.name, name);
}

void bd_linux_input_dev_destructor(bd_linux_input_t linux_input)
{
	if (linux_input == BD_NULL) {
		return;
	}
	bd_input_t input = BD_SUP(linux_input, bd_input);
	input->destructor(input);
}

BD_INT bd_linux_input_dev_open(bd_input_t input)
{
	if (input == BD_NULL) {
		return -1;
	}
	bd_linux_input_t linux_input = BD_SUB(input, bd_input, bd_linux_input);
	char path[255] = "/dev/input/";
	strcat(path, linux_input->bd_input.name);
	linux_input->fd = open(path, O_RDONLY);
	if (linux_input->fd < 0) {
		bd_log(INPUT_TAG, "input device open failure\n");
		return -1;
	}
	return 0;
}

BD_INT bd_linux_input_dev_close(bd_input_t input)
{
	if (input == BD_NULL) {
		return -1;
	}
	bd_linux_input_t linux_input = BD_SUB(input, bd_input, bd_linux_input);
	return close(linux_input->fd);
}

bd_event_t bd_linux_input_dev_read_event(bd_input_t input)
{
	if (input == BD_NULL) {
		return BD_NULL;
	}
	bd_linux_input_t linux_input = BD_SUB(input, bd_input, bd_linux_input);
	switch(input->type) {
	case BD_INPUT_MOUSE:
	{
		bd_mouse_event_t mouse_event = bd_mouse_event_new();
		mouse_event->constructor(mouse_event);
		bd_linux_input_dev_get_mouse_event(linux_input, mouse_event);
		return BD_SUP(mouse_event, bd_event);
	}
	case BD_INPUT_TOUCH:
	{
		bd_touch_event_t touch_event = bd_touch_event_new();
		touch_event->constructor(touch_event);
		bd_linux_input_dev_get_touch_event(linux_input, touch_event);
		return BD_SUP(touch_event, bd_event);
	}
	case BD_INPUT_KEYBOARD:
	{
		bd_keyboard_event_t keyboard_event = bd_keyboard_event_new();
		keyboard_event->constructor(keyboard_event);
		bd_linux_input_dev_get_keyboard_event(linux_input, keyboard_event);
		return BD_SUP(keyboard_event, bd_event);
	}
	default:
		return BD_NULL;
	}
}

BD_CLASS_CONSTRUCTOR_START(bd_linux_input)
BD_SUPER_CONSTRUCTOR(bd_input)
BD_CLASS_METHOD(bd_input.open, bd_linux_input_dev_open)
BD_CLASS_METHOD(bd_input.close, bd_linux_input_dev_close)
BD_CLASS_METHOD(bd_input.read, bd_linux_input_dev_read_event)
BD_CLASS_METHOD(constructor, bd_linux_input_dev_constructor)
BD_CLASS_METHOD(destructor, bd_linux_input_dev_destructor)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_linux_input)


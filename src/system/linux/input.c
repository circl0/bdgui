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

static BD_INT current_x = 0;
static BD_INT current_y = 0;

static bd_event_t bd_linux_input_dev_get_mouse_event(bd_linux_input_t input)
{
	struct input_event current_event;
	memset(&current_event, 0, sizeof(struct input_event));
	read(input->fd, &current_event, sizeof(struct input_event));
	if (input == BD_NULL) {
		return BD_NULL;
	}
	bd_log("input", "name: %s, type: %d, code: %d, value: %d\n", input->bd_input.name, current_event.type, current_event.code, current_event.value);
	if (current_event.type == 3) {
		bd_mouse_move_event_t mouse_move_event = bd_mouse_move_event_new();
		mouse_move_event->constructor(mouse_move_event);
		if (current_event.code == 0) {
			current_x = current_event.value / 128;
		}
		else if (current_event.code == 1) {
			current_y = current_event.value / 128;
		}
		mouse_move_event->x = current_x;
		mouse_move_event->y = current_y;

		return BD_SUP(mouse_move_event, bd_event);
	} 
	else if (current_event.type == 1) {
		bd_mouse_button_event_t mouse_button_event = bd_mouse_button_event_new();
		mouse_button_event->constructor(mouse_button_event);
		if (current_event.code == BTN_LEFT) {
			mouse_button_event->button = BD_MOUSE_BUTTON_LEFT;
		}
		else if (current_event.code == BTN_RIGHT) {
			mouse_button_event->button = BD_MOUSE_BUTTON_RIGHT;
		}
		else if (current_event.code == BTN_MIDDLE) {
			mouse_button_event->button = BD_MOUSE_BUTTON_WHEEL;
		}

		if (current_event.value == 1) {
			mouse_button_event->action = BD_MOUSE_BUTTON_DOWN;
		}
		else if (current_event.value == 0) {
			mouse_button_event->action = BD_MOUSE_BUTTON_UP;
		}

		mouse_button_event->x = current_x;
		mouse_button_event->y = current_y;
		return BD_SUP(mouse_button_event, bd_event);
	}
	else {
		return BD_NULL;
	}
}

static bd_event_t bd_linux_input_dev_get_keyboard_event(bd_linux_input_t input)
{
	struct input_event current_event;
	memset(&current_event, 0, sizeof(struct input_event));
	read(input->fd, &current_event, sizeof(struct input_event));
	if (input == BD_NULL) {
		return BD_NULL;
	}
	bd_log("input", "name: %s, type: %d, code: %d, value: %d\n", input->bd_input.name, current_event.type, current_event.code, current_event.value);

	bd_keyboard_event_t keyboard_event = bd_keyboard_event_new();
	keyboard_event->constructor(keyboard_event);

	return BD_SUP(keyboard_event, bd_event);
}

static bd_event_t bd_linux_input_dev_get_touch_event(bd_linux_input_t input)
{
	return BD_NULL;
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
	bd_event_t event = BD_NULL;
	switch(input->type) {
	case BD_INPUT_MOUSE:
	{
		event = bd_linux_input_dev_get_mouse_event(linux_input);
		break;
	}
	case BD_INPUT_TOUCH:
	{
		event = bd_linux_input_dev_get_touch_event(linux_input);
		break;
	}
	case BD_INPUT_KEYBOARD:
	{
		event = bd_linux_input_dev_get_keyboard_event(linux_input);
		break;
	}
	default:
		break;
	}
	return event;
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


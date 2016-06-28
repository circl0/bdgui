/* bdgui - a kind of embedded gui system
　* Copyright (C) 2016  Allen Yuan
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
#include "system/system.h"
#include "utils/log.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/input.h>

#define INPUT_TAG "input"

struct bd_input_dev {
	bd_source base;
	BD_INT	fp;
	BD_CHAR file_name[255];
	bd_input_type type;

};

static void bd_input_dev_get_mouse_event(bd_input_dev_t dev, bd_mouse_event_t event)
{
	struct input_event current_event;
	memset(&current_event, 0, sizeof(struct input_event));
	read(dev->fp, &current_event, sizeof(struct input_event));
	if (dev == BD_NULL || event == BD_NULL) {
		return;
	}
	bd_log("input", "name: %s, type: %x, code: %x, value: %x\n", dev->file_name, current_event.type, current_event.code, current_event.value);
}

static void bd_input_dev_get_keyboard_event(bd_input_dev_t dev, bd_keyboard_event_t event)
{

}

static void bd_input_dev_get_touch_event(bd_input_dev_t dev, bd_touch_event_t event)
{

}

bd_input_dev_t bd_input_dev_create(const char* name, bd_source_pool_t pool)
{
	bd_input_dev_t dev = (bd_input_dev_t) bd_malloc(sizeof(bd_input_dev));
	if (dev == BD_NULL) {
		bd_log(INPUT_TAG, "input device create failure\n");
		return BD_NULL;
	}
	strcpy(dev->file_name, name);
	if (pool == BD_NULL) {
		bd_log(INPUT_TAG, "source pool is null\n");
		bd_free(dev);
		return BD_NULL;
	}
	dev->base.type = BD_SOURCE_INPUT;
	dev->type = BD_INPUT_MOUSE;
	bd_source_pool_push(pool, (bd_source_t)dev);
	return dev;
}

BD_INT bd_input_dev_open(bd_input_dev_t dev)
{
	char path[255] = "/dev/input/";
	strcat(path, dev->file_name);
	dev->fp = open(path, O_RDONLY);
	if (dev->fp < 0) {
		bd_log(INPUT_TAG, "input device open failure\n");
		return -1;
	}
	return 0;
}

BD_INT bd_input_dev_close(bd_input_dev_t dev, BD_UINT size)
{
	return close(dev->fp);
}

bd_event_t bd_input_dev_read_event(bd_input_dev_t dev)
{
	switch(dev->type) {
	case BD_INPUT_MOUSE:
	{
		bd_mouse_event_t mouse_event = bd_malloc(sizeof(bd_mouse_event));
		bd_input_dev_get_mouse_event(dev, mouse_event);
		return (bd_event_t)mouse_event;
	}
	case BD_INPUT_TOUCH:
	{
		bd_touch_event_t touch_event = bd_malloc(sizeof(bd_touch_event));
		bd_input_dev_get_touch_event(dev, touch_event);
		return (bd_event_t)touch_event;
	}
	case BD_INPUT_KEYBOARD:
	{
		bd_keyboard_event_t keyboard_event = bd_malloc(sizeof(bd_keyboard_event));
		bd_input_dev_get_keyboard_event(dev, keyboard_event);
		return (bd_event_t)keyboard_event;
	}
	default:
		return BD_NULL;
	}
}



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

#include "type/object.h"
#include "system/system.h"
#include "system/timer.h"
#include "system/linux/timer.h"
#include "system/source.h"
#include "event/event.h"
#include "utils/log.h"
#include <sys/timerfd.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static void bd_linux_timer_fd_set_timeout(BD_INT fd, BD_ULONG milliseconds)
{
	struct itimerspec timerspec;
	timerspec.it_value.tv_sec = milliseconds / 1000;
	timerspec.it_value.tv_nsec = (milliseconds % 1000) * 1000 * 1000;
	timerspec.it_interval.tv_sec = timerspec.it_value.tv_sec;
	timerspec.it_interval.tv_nsec = timerspec.it_value.tv_nsec;
	timerfd_settime(fd, CLOCK_MONOTONIC, &timerspec, BD_NULL);
}

bd_timer_t bd_timer_create(BD_INT id, BD_ULONG timeout)
{
	bd_linux_timer_t linux_timer = bd_linux_timer_new();
	linux_timer->constructor(linux_timer, id, timeout);
	return BD_SUP(linux_timer, bd_timer);
}

void bd_timer_destroy(bd_timer_t timer)
{
	if (timer == BD_NULL) {
		return;
	}
	bd_linux_timer_t linux_timer = BD_SUB(timer, bd_timer, bd_linux_timer);
	bd_linux_timer_delete(linux_timer);
}

void bd_linux_timer_constructor(bd_linux_timer_t self, BD_INT id, BD_ULONG milliseconds)
{
	if (self == BD_NULL) {
		return;
	}
	bd_timer_t timer = BD_SUP(self, bd_timer);
	timer->constructor(timer, id, milliseconds);
}

void bd_linux_timer_destructor(bd_linux_timer_t self)
{
	if (self == BD_NULL) {
		return;
	}
	bd_timer_t timer = BD_SUP(self, bd_timer);
	timer->destructor(timer);
}

BD_INT bd_linux_timer_start(bd_timer_t self)
{
	bd_linux_timer_t linux_timer = BD_SUB(self, bd_timer, bd_linux_timer);
	linux_timer->fd = timerfd_create(CLOCK_MONOTONIC, 0);
	bd_linux_timer_fd_set_timeout(linux_timer->fd, self->timeout);
	return 0;
}

BD_INT bd_linux_timer_stop(bd_timer_t self)
{
	return 0;
}

bd_event_t bd_linux_timer_read_event(bd_timer_t self)
{
	// bd_log("timer", "id: %d\n", self->id);
	uint64_t exp = 0;
	bd_linux_timer_t linux_timer = BD_SUB(self, bd_timer, bd_linux_timer);
	read(linux_timer->fd, &exp, sizeof(uint64_t));
	bd_timer_event_t event = bd_timer_event_new();
	event->constructor(event);
	event->id = self->id;
	return BD_SUP(event, bd_event);
}

BD_CLASS_CONSTRUCTOR_START(bd_linux_timer)
BD_SUPER_CONSTRUCTOR(bd_timer)
BD_CLASS_METHOD(constructor, bd_linux_timer_constructor)
BD_CLASS_METHOD(destructor, bd_linux_timer_destructor)
BD_CLASS_METHOD(bd_timer.start, bd_linux_timer_start)
BD_CLASS_METHOD(bd_timer.stop, bd_linux_timer_stop)
BD_CLASS_METHOD(bd_timer.read, bd_linux_timer_read_event)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_linux_timer)


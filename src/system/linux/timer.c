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

#include "system/system.h"
#include "system/timer.h"
#include "system/source.h"
#include <sys/timerfd.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

struct bd_timer {
	bd_source base;
	BD_UINT timeout;
};

static void bd_timer_fd_set_timeout(BD_INT fd, BD_UINT milliseconds)
{
	struct itimerspec timerspec;
	timerspec.it_value.tv_sec = milliseconds / 1000;
	timerspec.it_value.tv_nsec = (milliseconds % 1000) * 1000 * 1000;
	timerspec.it_interval.tv_sec = timerspec.it_value.tv_sec;
	timerspec.it_interval.tv_nsec = timerspec.it_value.tv_nsec;
	timerfd_settime(fd, CLOCK_MONOTONIC, 0, &timerspec);
}

bd_timer_t bd_timer_create(BD_UINT milliseconds)
{
	bd_timer_t timer = (bd_timer_t) bd_malloc(sizeof(bd_timer));
	if (timer == BD_NULL) {
		return BD_NULL;
	}
	timer->base.type = BD_SOURCE_TIMER;
	timer->base.fd = timerfd_create(CLOCK_MONOTONIC, 0);
	timer->timeout = milliseconds;
	bd_timer_fd_set_timeout(timer->base.fd, milliseconds);

	return timer;
}

void bd_timer_destroy(bd_timer_t timer)
{
	if (timer == BD_NULL) {
		return;
	}
	close(timer->base.fd);
	bd_free(timer);
}

void bd_timer_set_timeout(bd_timer_t timer, BD_UINT milliseconds)
{
	if (timer == BD_NULL) {
		return;
	}
	bd_timer_fd_set_timeout(timer->base.fd, milliseconds);
}


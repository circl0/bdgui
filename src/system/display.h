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


#ifndef INCLUDE_SYSTEM_DISPLAY_H_
#define INCLUDE_SYSTEM_DISPLAY_H_

#include "type/type.h"
#include "type/object.h"
#include "system/mutex.h"

BD_ABSTRACT_CLASS(bd_display) {
	BD_EXTENDS(bd_object);

	BD_UINT screen_width;
	BD_UINT screen_height;
	bd_color_type color_type;
	bd_mutex_t mutex;

	void (*constructor)(bd_display_t display);
	void (*destructor)(bd_display_t display);

	BD_UINT (*get_screen_width)(bd_display_t display);
	BD_UINT (*get_screen_height)(bd_display_t display);
	bd_color_type (*get_color_type)(bd_display_t display);

	BD_INT (*open)(bd_display_t display);
	BD_INT (*close)(bd_display_t display);
	void (*lock)(bd_display_t display);
	void (*unlock)(bd_display_t display);
	void (*flip)(bd_display_t display);
	BD_HANDLE (*get_buffer)(bd_display_t display);
};

bd_display_t bd_display_create();
void bd_display_destroy(bd_display_t display);


#endif /* INCLUDE_SYSTEM_DISPLAY_H_ */

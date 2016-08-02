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

#ifndef INCLUDE_SYSTEM_LINUX_DISPLAY_H_
#define INCLUDE_SYSTEM_LINUX_DISPLAY_H_

#include "system/linux/framebuffer.h"
 
BD_CLASS(bd_display_internal) {

	bd_fb_dev_t fb;

	void (*constructor)(bd_display_internal_t display);
	void (*destructor)(bd_display_internal_t display);

	BD_INT (*open)(bd_display_internal_t display);
	BD_INT (*close)(bd_display_internal_t display);
	void (*flip)(bd_display_internal_t display);
	BD_HANDLE (*get_buffer)(bd_display_internal_t display);

	BD_UINT (*get_width)(bd_display_internal_t display);
	BD_UINT (*get_height)(bd_display_internal_t display);
	bd_color_type (*get_color_type)(bd_display_internal_t display);

};

bd_display_internal_t bd_display_internal_create();
void bd_display_internal_destroy(bd_display_internal_t display);

#endif /* INCLUDE_SYSTEM_LINUX_DISPLAY_H_ */

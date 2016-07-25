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


#ifndef INCLUDE_SYSTEM_LINUX_FRAMEBUFFER_H_
#define INCLUDE_SYSTEM_LINUX_FRAMEBUFFER_H_

#include <linux/fb.h>
#include "type/type.h"

//#define HAVE_DOUBLE_BUFFER  1

typedef struct bd_fb_dev {
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    BD_UINT height;
    BD_UINT width;
    char* primary_buffer;
    char* back_buffer;
    BD_UINT screen_size;
    BD_INT fp;
} bd_fb_dev;

typedef bd_fb_dev* bd_fb_dev_t;

bd_fb_dev_t bd_fb_dev_create();
void bd_fb_dev_destroy(bd_fb_dev_t dev);

BD_INT bd_fb_dev_open(bd_fb_dev_t dev);
BD_INT bd_fb_dev_close(bd_fb_dev_t dev);

void bd_fb_dev_paint_pixel(bd_fb_dev_t dev, BD_UINT x, BD_UINT y,
							BD_UINT r, BD_UINT g, BD_UINT b);

void bd_fb_dev_flip(bd_fb_dev_t dev);


#endif /* INCLUDE_SYSTEM_LINUX_FRAMEBUFFER_H_ */

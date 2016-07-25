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


#include "system/linux/framebuffer.h"
#include "system/system.h"
#include "type/type.h"
#include "utils/log.h"

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define FB_TAG  "framebuffer"

bd_fb_dev_t bd_fb_dev_create()
{
	bd_fb_dev_t dev = bd_malloc(sizeof(bd_fb_dev));
	if (dev == BD_NULL) {
		return BD_NULL;
	}
	memset(dev, 0, sizeof(bd_fb_dev));
	return dev;
}

void bd_fb_dev_destroy(bd_fb_dev_t dev)
{
	if (dev == BD_NULL) {
		return;
	}
	bd_free(dev);
}

BD_INT bd_fb_dev_open(bd_fb_dev_t dev)
{
	if (dev == BD_NULL) {
		return -1;
	}
    dev->fp = open("/dev/fb0", O_RDWR);

    if (dev->fp == BD_NULL) {
        bd_log(FB_TAG, "Error: cannot open framebuffer device.\n");
        return -1;
    }
    bd_log(FB_TAG, "The framebuffer device was opened successfully.\n");

    if (ioctl(dev->fp, FBIOGET_FSCREENINFO, &dev->finfo)) {
    	bd_log(FB_TAG, "Error reading fixed information.\n");
        return -1;
    }

    // Get variable screen information
    if (ioctl(dev->fp, FBIOGET_VSCREENINFO, &dev->vinfo)) {
    	bd_log(FB_TAG, "Error reading variable information.\n");
        return -1;
    }

#ifdef HAVE_DOUBLE_BUFFER
    dev->vinfo.xres_virtual = dev->vinfo.xres;
    dev->vinfo.yres_virtual = 2 * dev->vinfo.yres;
    dev->vinfo.xoffset = 0;
    dev->vinfo.yoffset = 0;

    dev->width = dev->vinfo.xres;
    dev->height = dev->vinfo.yres;

    if (ioctl(dev->fp, FBIOPUT_VSCREENINFO, &dev->vinfo)) {
    	bd_log(FB_TAG, "Error putting variable information.\n");
        return -1;
    }

    BD_UINT screen_size = dev->width * dev->height * dev->vinfo.bits_per_pixel / 8;
    bd_log(FB_TAG, "screen_size: %d bits_per_pixel:%d\n", screen_size, dev->vinfo.bits_per_pixel);
    bd_log(FB_TAG, "red: %d green: %d blue: %d\n", screen_size, dev->vinfo.red.offset, dev->vinfo.green.offset, dev->vinfo.blue.offset);

    dev->primary_buffer = mmap(0, 2 * screen_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                       dev->fp, 0);
    if ((BD_INT)dev->primary_buffer == -1) {
    	bd_log(FB_TAG, "Error: failed to map framebuffer device to memory.\n");
        return -1;
    }
    dev->back_buffer = dev->primary_buffer + screen_size;
    dev->screen_size = screen_size;
    memset(dev->primary_buffer, 0, 2 * screen_size);

    return 0;

#else

    dev->width = dev->vinfo.xres;
    dev->height = dev->vinfo.yres;

    BD_UINT screen_size = dev->width * dev->height * dev->vinfo.bits_per_pixel / 8;
    bd_log(FB_TAG, "screen_size: %d bits_per_pixel:%d\n", screen_size, dev->vinfo.bits_per_pixel);
    bd_log(FB_TAG, "red: %d green: %d blue: %d\n", screen_size, dev->vinfo.red.offset, dev->vinfo.green.offset, dev->vinfo.blue.offset);
    dev->primary_buffer = mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                       dev->fp, 0);
    if ((BD_INT)dev->primary_buffer == -1) {
    	bd_log(FB_TAG, "Error: failed to map framebuffer device to memory.\n");
        return -1;
    }
    dev->back_buffer = bd_malloc(screen_size);
    dev->screen_size = screen_size;

    memset(dev->primary_buffer, 0, screen_size);
    memset(dev->back_buffer, 0, screen_size);

    return 0;

#endif
}

BD_INT bd_fb_dev_close(bd_fb_dev_t dev)
{
#ifdef HAVE_DOUBLE_BUFFER
	void* buffer = dev->primary_buffer < dev->back_buffer ? dev->primary_buffer : dev->back_buffer;

	if (munmap(buffer, 2 * dev->screen_size) < 0) {
    	bd_log(FB_TAG, "Error munmap.\n");
    	return -1;
    }
#else
	if (munmap(dev->primary_buffer, dev->screen_size) < 0) {
    	bd_log(FB_TAG, "Error munmap.\n");
    	return -1;
    }
	bd_free(dev->back_buffer);
#endif
    if (close(dev->fp) < 0) {
    	bd_log(FB_TAG, "Error close.\n");
    	return -1;
    }
    return 0;
}

void bd_fb_dev_paint_pixel(bd_fb_dev_t dev, BD_UINT x, BD_UINT y,
							BD_UINT r, BD_UINT g, BD_UINT b)
{
	BD_UINT32 rgb888 = (r << 16) + (g << 8) + b;
    BD_ULONG location = (x + y * dev->width) * (dev->vinfo.bits_per_pixel / 8);

    *((BD_UINT16*)(dev->back_buffer + location)) = ((((rgb888) >> 19) & 0x1f) << 11) | ((((rgb888) >> 10) & 0x3f) << 5) |(((rgb888) >> 3) & 0x1f);
}

void bd_fb_dev_flip(bd_fb_dev_t dev)
{
#ifdef HAVE_DOUBLE_BUFFER
	void* temp = dev->primary_buffer;
	dev->primary_buffer = dev->back_buffer;
	dev->back_buffer = temp;

    if (ioctl(dev->fp, FBIOGET_VSCREENINFO, &dev->vinfo)) {
    	bd_log(FB_TAG, "Error reading variable information.\n");
        return;
    }
	dev->vinfo.yoffset = (dev->vinfo.yoffset == 0 ? dev->height : 0);
	ioctl(dev->fp, FBIOPAN_DISPLAY, &dev->vinfo);
#else
	memcpy(dev->primary_buffer, dev->back_buffer, dev->screen_size);
#endif
}

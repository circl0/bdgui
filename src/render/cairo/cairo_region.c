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
#include "render/region.h"
#include "render/cairo/cairo_region.h"

bd_cairo_region_t bd_cairo_region_create(bd_rect_t rect)
{
    bd_cairo_region_t cairo_region = bd_cairo_region_new();
    cairo_region->constructor(cairo_region, rect);
    return cairo_region;
}

void bd_cairo_region_destroy(bd_cairo_region_t cairo_region)
{
    bd_cairo_region_delete(cairo_region);
}

void bd_cario_region_constructor(bd_cairo_region_t cairo_region, bd_rect_t rect)
{
    cairo_rectangle_int_t cairo_rect;
    cairo_rect.x = rect->x;
    cairo_rect.y = rect->y;
    cairo_rect.width = rect->width;
    cairo_rect.height = rect->height;
    cairo_region->cr = cairo_region_create_rectangle(&cairo_rect);
}

void bd_cario_region_destructor(bd_cairo_region_t cairo_region)
{
    cairo_region_destroy(cairo_region->cr);
}

BD_INT bd_cario_region_get_rectangle_num(bd_region_t region)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    return cairo_region_num_rectangles(cairo_region->cr);
}

void bd_cario_region_get_rectangle(bd_region_t region, BD_INT num, bd_rect_t rect)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    cairo_rectangle_int_t cairo_rect;
    cairo_region_get_rectangle(cairo_region->cr, num, &cairo_rect);
    rect->x = cairo_rect.x;
    rect->y = cairo_rect.y;
    rect->width = cairo_rect.width;
    rect->height = cairo_rect.height;
}

void bd_cario_region_substract(bd_region_t region, bd_rect_t rect)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    cairo_rectangle_int_t cairo_rect;
    cairo_rect.x = rect->x;
    cairo_rect.y = rect->y;
    cairo_rect.width = rect->width;
    cairo_rect.height = rect->height;
    cairo_region_subtract_rectangle(cairo_region->cr, &cairo_rect);
}

void bd_cario_region_add(bd_region_t region, bd_rect_t rect)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    cairo_rectangle_int_t cairo_rect;
    cairo_rect.x = rect->x;
    cairo_rect.y = rect->y;
    cairo_rect.width = rect->width;
    cairo_rect.height = rect->height;
    cairo_region_union_rectangle(cairo_region->cr, &cairo_rect);
}

BD_INT bd_cario_region_equal(bd_region_t region, bd_region_t other)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    bd_cairo_region_t other_cairo_region = BD_SUB(other, bd_region, bd_cairo_region);
    return cairo_region_equal(cairo_region, other_cairo_region);
}

BD_INT bd_cario_region_contains(bd_region_t region, bd_rect_t rect)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    cairo_rectangle_int_t cairo_rect;
    cairo_rect.x = rect->x;
    cairo_rect.y = rect->y;
    cairo_rect.width = rect->width;
    cairo_rect.height = rect->height;
    cairo_region_overlap_t ol = cairo_region_contains_rectangle(cairo_region->cr, &cairo_rect);
    if (ol == CAIRO_REGION_OVERLAP_OUT) {
        return 0;
    }
    return 1;
}

BD_INT bd_cario_region_contains_point(bd_region_t region, BD_INT x, BD_INT y)
{
    bd_cairo_region_t cairo_region = BD_SUB(region, bd_region, bd_cairo_region);
    return cairo_region_contains_point(cairo_region->cr, x, y);
}

BD_CLASS_CONSTRUCTOR_START(bd_cairo_region)
BD_CLASS_METHOD(constructor, bd_cario_region_constructor)
BD_CLASS_METHOD(destructor, bd_cario_region_destructor)
BD_CLASS_METHOD(bd_region.get_rectangle_num, bd_cario_region_get_rectangle_num)
BD_CLASS_METHOD(bd_region.get_rectangle, bd_cario_region_get_rectangle)
BD_CLASS_METHOD(bd_region.add, bd_cario_region_add)
BD_CLASS_METHOD(bd_region.substract, bd_cario_region_substract)
BD_CLASS_METHOD(bd_region.equal, bd_cario_region_equal)
BD_CLASS_METHOD(bd_region.contains, bd_cario_region_contains)
BD_CLASS_METHOD(bd_region.contains_point, bd_cario_region_contains_point)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_cairo_region)
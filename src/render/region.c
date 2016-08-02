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

#include "render/region.h"

bd_region_t bd_region_create()
{
	bd_region_t region = bd_region_new();
	region->constructor(region);
	return region;
}

bd_region_t bd_region_create_by_rect(bd_rect_t rect)
{
	bd_region_t region = bd_region_new();
	region->constructor2(region, rect);
	return region;
}

void bd_region_destroy(bd_region_t region)
{
	bd_region_delete(region);
}

void bd_region_constructor(bd_region_t region)
{
	region->region_internal = bd_region_internal_create();
}

void bd_region_constructor2(bd_region_t region, bd_rect_t rect)
{
	region->region_internal = bd_region_internal_create_by_rect(rect);
}

void bd_region_destructor(bd_region_t region)
{
	bd_region_internal_destroy(region->region_internal);
}

BD_INT bd_region_get_rectangle_num(bd_region_t region)
{
	return region->region_internal->get_rectangle_num(region->region_internal);
}

void bd_region_get_rectangle(bd_region_t region, BD_INT num, bd_rect_t rect)
{
	region->region_internal->get_rectangle(region->region_internal, num , rect);
}

void bd_region_substract(bd_region_t region, bd_rect_t rect)
{
	region->region_internal->substract(region->region_internal, rect);
}

void bd_region_add(bd_region_t region, bd_rect_t rect)
{
	region->region_internal->add(region->region_internal, rect);
}

void bd_region_substract_region(bd_region_t region, bd_region_t other)
{
	region->region_internal->substract_region(region->region_internal, other->region_internal);
}

BD_INT bd_region_equal(bd_region_t region, bd_region_t other)
{
	return region->region_internal->equal(region->region_internal, other->region_internal);
}

BD_INT bd_region_contains(bd_region_t region, bd_rect_t rect)
{
	return region->region_internal->contains(region->region_internal, rect);
}

BD_INT bd_region_contains_point(bd_region_t region, BD_INT x, BD_INT y)
{
	return region->region_internal->contains_point(region->region_internal, x, y);
}


BD_CLASS_CONSTRUCTOR_START(bd_region)
BD_CLASS_METHOD(constructor, bd_region_constructor)
BD_CLASS_METHOD(constructor2, bd_region_constructor2)
BD_CLASS_METHOD(destructor, bd_region_destructor)
BD_CLASS_METHOD(get_rectangle_num, bd_region_get_rectangle_num)
BD_CLASS_METHOD(get_rectangle, bd_region_get_rectangle)
BD_CLASS_METHOD(add, bd_region_add)
BD_CLASS_METHOD(substract, bd_region_substract)
BD_CLASS_METHOD(substract_region, bd_region_substract_region)
BD_CLASS_METHOD(equal, bd_region_equal)
BD_CLASS_METHOD(contains, bd_region_contains)
BD_CLASS_METHOD(contains_point, bd_region_contains_point)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_region)
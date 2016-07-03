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


#ifdef WITH_GDSL

#include <gdsl/gdsl_types.h>
#include <gdsl/gdsl_list.h>
#include "type/list.h"
#include "system/system.h"

bd_list_t bd_list_create()
{
	return gdsl_list_alloc("", BD_NULL, BD_NULL);
}

void bd_list_destroy(bd_list_t list)
{
	gdsl_list_free(list);
}

void bd_list_push(bd_list_t list, BD_HANDLE data)
{
	gdsl_list_insert_tail(list, data);
}

BD_HANDLE bd_list_first(bd_list_t list)
{
	return gdsl_list_get_head(list);
}


void bd_list_for_each(bd_list_t list, bd_map_func func, BD_HANDLE data)
{
	gdsl_list_map_forward(list, func, data);
}

BD_HANDLE bd_list_search(bd_list_t list, bd_compare_func func, BD_HANDLE value)
{
	return gdsl_list_search(list, func, value);
}

BD_HANDLE bd_list_remove(bd_list_t list, bd_compare_func func, BD_HANDLE value)
{
	return gdsl_list_delete(list, func, value);
}

#endif


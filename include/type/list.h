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


#ifndef BD_LIST_H
#define BD_LIST_H

#include "type/type.h"

#ifdef WITH_GDSL
#include <gdsl/gdsl_list.h>
typedef gdsl_list_t bd_list_t;
#endif


bd_list_t bd_list_create();
void bd_list_destroy(bd_list_t list);

void bd_list_push(bd_list_t list, BD_HANDLE data);
BD_HANDLE bd_list_get(bd_list_t list);

BD_HANDLE bd_list_first(bd_list_t list);

BD_HANDLE bd_list_remove(bd_list_t list, BD_LONGINT(*compare)(const BD_HANDLE, BD_HANDLE), BD_HANDLE value);
void bd_list_for_each(bd_list_t list, BD_INT(*map)(BD_HANDLE, BD_INT, BD_HANDLE), BD_HANDLE data);
BD_HANDLE bd_list_search(bd_list_t list, BD_LONGINT(*compare)(const BD_HANDLE, BD_HANDLE), BD_HANDLE value);

#endif

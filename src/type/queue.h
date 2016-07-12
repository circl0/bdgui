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


#ifndef INCLUDE_TYPE_QUEUE_H_
#define INCLUDE_TYPE_QUEUE_H_

#include "type/type.h"

#include <gdsl/gdsl_queue.h>
typedef gdsl_queue_t bd_queue_t;

bd_queue_t bd_queue_create();
void bd_queue_destroy(bd_queue_t queue);

void bd_queue_push(bd_queue_t queue, BD_HANDLE data);
BD_HANDLE bd_queue_get(bd_queue_t queue);

#endif /* INCLUDE_TYPE_QUEUE_H_ */

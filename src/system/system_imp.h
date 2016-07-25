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


#ifndef BD_SYSTEM_IMP_H
#define BD_SYSTEM_IMP_H

#include "type/type.h"
#include "system/system.h"

BD_CLASS(bd_system_service_imp) {
	BD_IMPLEMENTS(bd_system_service);

	bd_display_t display;
	bd_source_pool_t source_pool;

	void (*constructor)(bd_system_service_imp_t service_imp);
	void (*destructor)(bd_system_service_imp_t service_imp);


};

#endif
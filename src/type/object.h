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


#ifndef BD_OBJECT_H
#define BD_OBJECT_H

#include "type/type.h"
#include "type/base.h"
#include <stdarg.h>


#define BD_CLASS 								CLASS
#define BD_ABSTRACT_CLASS 						ABS_CLASS
#define BD_INTERFACE 							INTERFACE

#define BD_EXTENDS								EXTENDS
#define BD_IMPLEMENTS							IMPLEMENTS

#define BD_CLASS_CONSTRUCTOR_START				CTOR
#define BD_CLASS_CONSTRUCTOR_END				END_CTOR

#define BD_ABSTRACT_CLASS_CONSTRUCTOR_START 	ABS_CTOR
#define BD_ABSTRACT_CLASS_CONSTRUCTOR_END 		END_ABS_CTOR

#define BD_SUPER_CONSTRUCTOR 					SUPER_CTOR

#define BD_CLASS_DESTRUCTOR_START				DTOR
#define BD_CLASS_DESTRUCTOR_END					END_DTOR

#define BD_SUP									SUPER_PTR
#define BD_SUB									SUB_PTR
#define BD_SUB2									SUB_PTR_2

#define BD_CLASS_METHOD 						FUNCTION_SETTING

#define BD_CLASS_DESTRUCTOR(class)				\
	BD_CLASS_DESTRUCTOR_START(class) \
	cthis->destructor(cthis); \
	return 1;\
	BD_CLASS_CONSTRUCTOR_END


BD_CLASS(bd_object) {
	void (*to_string)(bd_object_t o, char* str, BD_UINT size);

};

#endif

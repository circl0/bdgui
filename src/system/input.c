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

#include "system/source.h"
#include "system/input.h"

#include <string.h>

bd_input_t bd_input_create(const char* name, bd_input_type type)
{
	bd_input_t input = bd_input_new();
	input->constructor(input, name, type);
	return input;
}

void bd_input_destroy(bd_input_t input)
{
	bd_input_delete(input);
}

void bd_input_constructor(bd_input_t input, const char* name, bd_input_type type)
{
	if (input == BD_NULL) {
		return;
	}

	bd_source_t source = BD_SUP(input, bd_source);
	source->constructor(source, BD_SOURCE_INPUT);

	input->type = type;
	input->name = bd_malloc(strlen(name) + 1);
	strcpy(input->name, name);
	input->input_internal = bd_input_internal_create();
}

void bd_input_destructor(bd_input_t input)
{
	if (input == BD_NULL) {
		return;
	}

	bd_input_internal_destroy(input->input_internal);
	bd_free(input->name);

	bd_source_t source = BD_SUP(input, bd_source);
	source->destructor(source);
}

BD_INT bd_input_init(bd_source_t source)
{
	bd_input_t input = BD_SUB(source, bd_source, bd_input);
	return input->input_internal->open(input->input_internal, input->name);
}

BD_INT bd_input_deinit(bd_source_t source)
{
	bd_input_t input = BD_SUB(source, bd_source, bd_input);
	return input->input_internal->close(input->input_internal);
}

bd_event_t bd_input_read_events(bd_source_t source)
{
	bd_input_t input = BD_SUB(source, bd_source, bd_input);
	return input->input_internal->read(input->input_internal, input->type);
}

BD_CLASS_CONSTRUCTOR_START(bd_input)
BD_SUPER_CONSTRUCTOR(bd_source)
BD_CLASS_METHOD(bd_source.init, bd_input_init)
BD_CLASS_METHOD(bd_source.deinit, bd_input_init)
BD_CLASS_METHOD(bd_source.read_events, bd_input_read_events)
BD_CLASS_METHOD(constructor, bd_input_constructor)
BD_CLASS_METHOD(destructor, bd_input_destructor)
BD_CLASS_CONSTRUCTOR_END

BD_CLASS_DESTRUCTOR(bd_input)
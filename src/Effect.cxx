/*
	Darkroom is an open-source photography tool.
	Copyright (C) 2017  Guy Sherman

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	Contact the author via https://github.com/guysherman
*/


// C++ Standard Headers

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers
#include "Effect.h"

namespace darkroom
{
	Effect::Effect(uint32_t vs, uint32_t fs, uint32_t program) : vs(vs), fs(fs), program(program)
	{
		
		
		
	}

	Effect::~Effect()
	{

	}

	uint32_t Effect::GetProgram()
	{
		return program;
	}
}

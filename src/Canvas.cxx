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
#include <cstring>
#include "Canvas.h"


namespace darkroom
{
	Canvas::Canvas(float w, float h) : sizeDirty(true)
	{
		size[0] = w;
		size[1] = h;
	}

	Canvas::~Canvas()
	{

	}

	float *Canvas::GetSize()
	{
		return (float*) size;
	}

	void Canvas::SetSize(float w, float h)
	{
		size[0] = w;
		size[1] = h;
		sizeDirty = true;
	}

	bool Canvas::GetSizeDirty()
	{
		return sizeDirty;
	}

	void Canvas::setupVertices()
	{
		float verts[20] = { 0.0f,       0.0f, 0.0f, 0.0f, 0.0f,
					 		0.0f,    size[1], 0.0f, 0.0f, 1.0f,
							size[0], size[1], 0.0f, 1.0f, 1.0f,
				 	 		size[0],    0.0f, 0.0f, 1.0f, 0.0f};
		memcpy(&this->vertices, verts, 30 * sizeof(float));

		unsigned int inds[6] = { 0, 1, 2, 2, 3, 0 };
		memcpy(&this->indices, inds, 6 * sizeof(int));
		sizeDirty = false;
	}

	float *Canvas::GetVertices()
	{
		if (sizeDirty)
		{
			setupVertices();
		}
		return vertices;
	}

	unsigned int *Canvas::GetIndices()
	{
		if (sizeDirty)
		{
			setupVertices();
		}
		return indices;
	}


}

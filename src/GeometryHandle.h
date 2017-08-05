#ifndef __GEOMETRYHANDLE_H__
#define __GEOMETRYHANDLE_H__
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
#include <cstdint>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers



namespace darkroom
{
	struct GeometryInfo
	{
		float *positions;
		float *colors;
		float *texCoords;
		uint32_t *indices;
		uint32_t numVertices;
		uint32_t numIndices;
	};
	
	class GeometryHandle
	{
	public:
		GeometryHandle(uint32_t vao, uint32_t posBuf, uint32_t colBuf, uint32_t tcBuf, uint32_t idxBuf, uint32_t numIndices);
		virtual ~GeometryHandle();
		
		const uint32_t GetVao() const;
		const uint32_t GetPositionBuffer() const;
		const uint32_t GetColorBuffer() const;
		const uint32_t GetTexCoordBuffer() const;
		const uint32_t GetIndexBuffer() const;
		const uint32_t GetNumIndices() const;
	
	protected:
		uint32_t vao;
		uint32_t posBuf;
		uint32_t colBuf;
		uint32_t tcBuf;
		uint32_t idxBuf;
		uint32_t numIndices;
	};
}

#endif // __GEOMETRYHANDLE_H__
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
#include "GeometryHandle.h"

namespace darkroom
{
	GeometryHandle::GeometryHandle(
		uint32_t vao, 
		uint32_t posBuf, 
		uint32_t colBuf, 
		uint32_t tcBuf, 
		uint32_t idxBuf, 
		uint32_t numIndices,
		uint32_t textureHandleId) :
		vao(vao),
		posBuf(posBuf),
		colBuf(colBuf),
		tcBuf(tcBuf),
		idxBuf(idxBuf),
		numIndices(numIndices),
		textureHandleId(textureHandleId)
	{

	}

	GeometryHandle::~GeometryHandle()
	{
		// Ought to delete the buffers here or something.
	}
	
	const uint32_t GeometryHandle::GetVao() const
	{
		return vao;
	}

	const uint32_t GeometryHandle::GetPositionBuffer() const
	{
		return posBuf;
	}

	const uint32_t GeometryHandle::GetColorBuffer() const
	{
		return colBuf;
	}

	const uint32_t GeometryHandle::GetTexCoordBuffer() const
	{
		return tcBuf;
	}

	const uint32_t GeometryHandle::GetIndexBuffer() const
	{
		return idxBuf;
	}

	const uint32_t GeometryHandle::GetNumIndices() const
	{
		return numIndices;
	}

	const uint32_t GeometryHandle::GetTextureHandleId() const
	{
		return textureHandleId;
	}

	void GeometryHandle::SetTextureHandleId(uint32_t textureHandleId)
	{
		this->textureHandleId = textureHandleId;
	}

}

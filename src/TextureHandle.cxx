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

#include "TextureHandle.h"

namespace darkroom
{
	TextureHandle::TextureHandle(
		uint32_t texture,
		uint32_t textureUnit,
		uint32_t target,
		uint32_t internalFormat,
		uint32_t format,
		uint32_t type,
		uint32_t wrapS,
		uint32_t wrapT,
		uint32_t magFilter,
		uint32_t minFilter,
		float maxAniso) 
	: texture(texture),
	textureUnit(textureUnit),
	target(target),
	internalFormat(internalFormat),
	format(format),
	type(type),
	wrapS(wrapS),
	wrapT(wrapT),
	magFilter(magFilter),
	minFilter(minFilter),
	maxAniso(maxAniso)
	{
		
	}

	TextureHandle::~TextureHandle()
	{

	}

	uint32_t TextureHandle::GetTexture() const
	{
		return texture;
	}

	uint32_t TextureHandle::GetTextureUnit() const
	{
		return textureUnit;
	}

	uint32_t TextureHandle::GetTarget() const
	{
		return target;
	}

	uint32_t TextureHandle::GetInternalFormat() const
	{
		return internalFormat;
	}

	uint32_t TextureHandle::GetFormat() const
	{
		return format;
	}

	uint32_t TextureHandle::GetType() const
	{
		return type;
	}

	uint32_t TextureHandle::GetWrapS() const
	{
		return wrapS;
	}

	void TextureHandle::SetWrapS(uint32_t wrapS)
	{
		this->wrapS = wrapS;
	}
	
	uint32_t TextureHandle::GetWrapT() const
	{
		return wrapT;
	}

	void TextureHandle::SetWrapT(uint32_t wrapT)
	{
		this->wrapT = wrapT;
	}

	uint32_t TextureHandle::GetMagFilter() const
	{
		return magFilter;
	}

	void TextureHandle::SetMagFilter(uint32_t magFilter)
	{
		this->magFilter = magFilter;
	}

	uint32_t TextureHandle::GetMinFilter() const
	{
		return minFilter;
	}

	void TextureHandle::SetMinFilter(uint32_t minFilter)
	{
		this->minFilter = minFilter;
	}

	float TextureHandle::GetMaxAniso() const
	{
		return maxAniso;
	}

	void TextureHandle::SetMaxAniso(float maxAniso)
	{
		this->maxAniso = maxAniso;
	}
}

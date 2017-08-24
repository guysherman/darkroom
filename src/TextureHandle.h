#ifndef __TEXTUREHANDLE_H__
#define __TEXTUREHANDLE_H__
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
	class TextureHandle
	{
	public:
		TextureHandle(
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
			float maxAniso);
		virtual ~TextureHandle();

		uint32_t GetTexture() const;
		uint32_t GetTextureUnit() const;
		uint32_t GetTarget() const;
		uint32_t GetInternalFormat() const;
		uint32_t GetFormat() const;
		uint32_t GetType() const;

		uint32_t GetWrapS() const;
		void SetWrapS(uint32_t wrapS);

		uint32_t GetWrapT() const;
		void SetWrapT(uint32_t wrapT);

		uint32_t GetMagFilter() const;
		void SetMagFilter(uint32_t magFilter);

		uint32_t GetMinFilter() const;
		void SetMinFilter(uint32_t minFilter);
		
		float GetMaxAniso() const;
		void SetMaxAniso(float maxAniso);

	
	private:
		uint32_t texture;
		uint32_t textureUnit;
		uint32_t target;
		uint32_t internalFormat;
		uint32_t format;
		uint32_t type;
		uint32_t wrapS;
		uint32_t wrapT;
		uint32_t magFilter;
		uint32_t minFilter;
		float maxAniso;
	};
}

#endif // __TEXTUREHANDLE_H__
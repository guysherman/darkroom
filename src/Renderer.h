#ifndef __RENDERER_H__
#define __RENDERER_H__
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


#include <GL/glew.h>
#include <GLFW/glfw3.h>
// C++ Standard Headers
#include <memory>
#include <string>
#include <vector>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers
#include "Effect.h"


namespace darkroom
{
	struct GeometryInfo;
	class GeometryHandle;
	class TextureHandle;
	
	enum TextureUnit
	{
		Unit0 = GL_TEXTURE0
	};

	enum TextureFormat
	{
		RGBA = GL_RGBA
	};

	enum TextureType
	{
		UBYTE = GL_UNSIGNED_BYTE
	};

	class Renderer
	{
	public:
		Renderer(GLFWwindow *window);
		virtual ~Renderer();

		void Init();
		void BeginFrame();
		void EndFrame();

		void Draw(GeometryHandle *geometryHandle, Effect *effect, TextureHandle *texture, float *mvp);
		void TrashGeometryHandle(std::unique_ptr<GeometryHandle> geometryHandle);
		

		std::unique_ptr<GeometryHandle> CreateGeometryHandle(GeometryInfo& geometryInfo);
		std::unique_ptr<Effect> CreateEffect(std::string vsPath, std::string fsPath);
		std::unique_ptr<TextureHandle> GenerateTexture2D(uint32_t textureUnit, uint32_t format, uint32_t type, uint32_t width, uint32_t height, const unsigned char* data);

		void FreeGeometryHandle(GeometryHandle *handle);

		uint32_t GetGlTextureUnit(uint32_t textureUnit);
		

	private:
		void EmptyTrash();
		
		GLFWwindow *window;
		std::vector< std::unique_ptr<GeometryHandle> > trashedGeometry;
	};
}

#endif // __RENDERER_H__

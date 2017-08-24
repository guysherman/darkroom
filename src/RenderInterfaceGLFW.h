#ifndef __RENDERINTERFACEGLFW_H__
#define __RENDERINTERFACEGLFW_H__
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
#include <map>
#include <memory>
#include <cstdint>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <Rocket/Core/RenderInterface.h>

// GTK Headers


// Our Headers
#include "Renderer.h"
#include "Effect.h"



namespace darkroom
{
	class GeometryHandle;
	class TextureHandle;

	class RocketGLFWRenderer : public Rocket::Core::RenderInterface
	{
	public:
		RocketGLFWRenderer();
		virtual ~RocketGLFWRenderer();

		/// Sets the window
		void SetWindow(GLFWwindow* window);
		void SetRenderer(std::shared_ptr<darkroom::Renderer> renderer);

		/// Returns the currently assigned window
		GLFWwindow *GetWindow();

		/// Resizes the viewport automatically
		void Resize();

		/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
		virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

		/// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
		virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

		/// Called by Rocket when it wants to render application-compiled geometry.
		virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		/// Called by Rocket when it wants to release application-compiled geometry.
		virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/// Called by Rocket when it wants to enable or disable scissoring to clip content.
		virtual void EnableScissorRegion(bool enable);
		/// Called by Rocket when it wants to change the scissor region.
		virtual void SetScissorRegion(int x, int y, int width, int height);

		/// Called by Rocket when a texture is required by the library.
		virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
		virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		/// Called by Rocket when a loaded texture is no longer required.
		virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	private:
		GLFWwindow* window;
		std::weak_ptr<Renderer> renderer;
		std::unique_ptr<Effect> effect;
		uint32_t nextGeometryHandleId;
		uint32_t nextTextureId;
		std::map< int, std::unique_ptr< GeometryHandle > > compiledGeometryHandles;
		std::map< int, std::unique_ptr< TextureHandle > > textureHandles;
		//RocketGLFWRenderer *rocketRenderer;
	};
}

#endif // __RENDERINTERFACEGLFW_H__
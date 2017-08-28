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
#include <iostream>
#include <sstream>
#include <cstddef>
#include <cstring>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <Rocket/Core/Core.h>
#include <tga.h>

// GTK Headers


// Our Headers
#include "RenderInterfaceGLFW.h"
#include "linmath.h"
#include "GeometryHandle.h"
#include "TextureHandle.h"
#include "pngutils.h"
#include "TgaImage.h"

namespace darkroom
{
	
	RocketGLFWRenderer::RocketGLFWRenderer()
	{
		nextGeometryHandleId = 1;
		nextTextureId = 1;
	}

	RocketGLFWRenderer::~RocketGLFWRenderer()
	{

	}

	void RocketGLFWRenderer::SetWindow(GLFWwindow *window)
	{
		this->window = window;
	}

	GLFWwindow *RocketGLFWRenderer::GetWindow()
	{
		return this->window;
	}

	void RocketGLFWRenderer::SetRenderer(std::shared_ptr<Renderer> renderer)
	{
		this->renderer = renderer;
		auto eff = renderer->CreateEffect("assets/basic_vs.glsl", "assets/basic_fs.glsl");
		effect = std::move(eff);

		unsigned char pixels[] =
		{
			239, 233, 1, 255, 239, 233, 1, 255,
			239, 233, 1, 255, 239, 233, 1, 255
		};

		auto tx = renderer->GenerateTexture2D(Unit0, RGBA, UBYTE, 2, 2, &pixels[0]);
		textureHandles.insert(std::make_pair(0, std::move(tx)));

	}

	

	void RocketGLFWRenderer::Resize()
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
	}

	void RocketGLFWRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
	{
		
		
		float *positions = new float[num_vertices * 2];
		float *colors = new float[num_vertices * 4];
		float *texCoords = new float[num_vertices * 2];
		uint32_t *uindices = new uint32_t[num_indices];

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		mat4x4 m;
		mat4x4_identity(m);

		mat4x4_translate(m, translation.x, translation.y, 0.0f);

		mat4x4 p;
		mat4x4_ortho(p, 0, width, height, 0, 0, 1000);

		mat4x4 mvp;		
		mat4x4_mul(mvp, p, m);

		for (int i = 0; i < num_vertices; ++i) 
		{
			int ix = i * 2;
			int iy = ix + 1;

			positions[ix] = vertices[i].position.x;
			positions[iy] = vertices[i].position.y;
			texCoords[ix] = vertices[i].tex_coord.x;
			texCoords[iy] = vertices[i].tex_coord.y;

			int ir = i * 4;
			int ig = ir + 1;
			int ib = ig + 1;
			int ia = ib + 1;

			colors[ir] = vertices[i].colour.red / 255.0f;
			colors[ig] = vertices[i].colour.green / 255.0f;
			colors[ib] = vertices[i].colour.blue / 255.0f;
			colors[ia] = vertices[i].colour.alpha / 255.0f;
		}

		for (int j = 0; j < num_indices; ++j)
		{
			uindices[j] = (uint32_t)indices[j];
		}

		GeometryInfo gi;
		gi.positions = &positions[0];
		gi.colors = &colors[0];
		gi.texCoords = &texCoords[0];
		gi.indices = uindices;
		gi.numVertices = num_vertices;
		gi.numIndices = num_indices;

		std::shared_ptr<Renderer> renderRef = renderer.lock();
		auto gh = renderRef->CreateGeometryHandle(gi);

		auto tx = textureHandles.find((uint32_t)texture);
		if (tx != textureHandles.begin() && tx != textureHandles.end())
		{
			renderRef->Draw(gh.get(), effect.get(), tx->second.get(), (float *)m);
			renderRef->TrashGeometryHandle(std::move(gh));
		}

		

		// TODO: translation
		// TODO: texture

		delete[] positions;
		delete[] colors;
		delete[] texCoords;
		delete[] uindices;



	}

	/// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
    Rocket::Core::CompiledGeometryHandle RocketGLFWRenderer::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
	{
		float *positions = new float[num_vertices * 2];
		float *colors = new float[num_vertices * 4];
		float *texCoords = new float[num_vertices * 2];
		uint32_t *uindices = new uint32_t[num_indices];

		for (int i = 0; i < num_vertices; ++i) 
		{
			int ix = i * 2;
			int iy = ix + 1;

			positions[ix] = vertices[i].position.x;
			positions[iy] = vertices[i].position.y;
			texCoords[ix] = vertices[i].tex_coord.x;
			texCoords[iy] = vertices[i].tex_coord.y;

			int ir = i * 4;
			int ig = ir + 1;
			int ib = ig + 1;
			int ia = ib + 1;

			colors[ir] = vertices[i].colour.red / 255.0f;
			colors[ig] = vertices[i].colour.green / 255.0f;
			colors[ib] = vertices[i].colour.blue / 255.0f;
			colors[ia] = vertices[i].colour.alpha / 255.0f;
		}

		for (int j = 0; j < num_indices; ++j)
		{
			uindices[j] = (uint32_t)indices[j];
		}

		GeometryInfo gi;
		gi.positions = &positions[0];
		gi.colors = &colors[0];
		gi.texCoords = &texCoords[0];
		gi.indices = uindices;
		gi.numVertices = num_vertices;
		gi.numIndices = num_indices;

		std::shared_ptr<Renderer> renderRef = renderer.lock();
		auto gh = renderRef->CreateGeometryHandle(gi);
		gh->SetTextureHandleId((uint32_t)texture);
		uint32_t id = nextGeometryHandleId++;

		compiledGeometryHandles.insert(std::make_pair(id, std::move(gh)));

		// TODO: translation
		// TODO: texture

		delete[] positions;
		delete[] colors;
		delete[] texCoords;
		delete[] uindices;

		return (Rocket::Core::CompiledGeometryHandle)id;
	}

	/// Called by Rocket when it wants to render application-compiled geometry.
	void RocketGLFWRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		mat4x4 m;
		mat4x4_identity(m);

		mat4x4_translate(m, translation.x, translation.y, 0.0f);

		mat4x4 p;
		mat4x4_ortho(p, 0, width, height, 0, 0, 1000);

		mat4x4 mvp;		
		mat4x4_mul(mvp, p, m);
		
		auto it = compiledGeometryHandles.find((uint32_t)geometry);
		if (it != compiledGeometryHandles.end())
		{
			//std::cout << "Rendering with texture: " << it->second.get()->GetTextureHandleId() << std::endl;
			
			auto tx = textureHandles.find(it->second.get()->GetTextureHandleId());
			if (tx != textureHandles.end())
			{
				std::shared_ptr<Renderer> renderRef = renderer.lock();
				renderRef->Draw(it->second.get(), effect.get(), tx->second.get(), (float *)mvp);
			}
			else
			{
				std::cout << "Couldn't find texture: " << it->second.get()->GetTextureHandleId() << std::endl;
				std::shared_ptr<Renderer> renderRef = renderer.lock();
				renderRef->Draw(it->second.get(), effect.get(), nullptr, (float *)mvp);
			}
			
			
		}
		else 
		{
			std::cout << "Couldn't find geometry: " << (int)geometry;
		}
	}

	/// Called by Rocket when it wants to release application-compiled geometry.
	void RocketGLFWRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
	{
		auto it = compiledGeometryHandles.find((uint32_t)geometry);
		if (it != compiledGeometryHandles.begin() 
			&& it != compiledGeometryHandles.end())
		{
			std::shared_ptr<Renderer> renderRef = renderer.lock();
			renderRef->TrashGeometryHandle(std::move(it->second));
			compiledGeometryHandles.erase(it);
		}
	}

	/// Called by Rocket when it wants to enable or disable scissoring to clip content.
	void RocketGLFWRenderer::EnableScissorRegion(bool enable)
	{
		if (enable)
		{
			glEnable(GL_SCISSOR_TEST);
		}
		else
		{
			glDisable(GL_SCISSOR_TEST);
		}
		
	}
	
	/// Called by Rocket when it wants to change the scissor region.
	void RocketGLFWRenderer::SetScissorRegion(int x, int y, int width, int height)
	{
		int wWidth, wHeight;
		glfwGetFramebufferSize(window, &wWidth, &wHeight);
		glScissor(x, wHeight - (y + height), width, height);
	}

	// Called by Rocket when a texture is required by the library.
	bool RocketGLFWRenderer::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
	{
		Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
		Rocket::Core::FileHandle file_handle = file_interface->Open(source);
		if (file_handle == NULL)
			return false;

		file_interface->Seek(file_handle, 0, SEEK_END);
		size_t buffer_size = file_interface->Tell(file_handle);
		file_interface->Seek(file_handle, 0, SEEK_SET);
		
		std::vector<unsigned char> buffer;
		buffer.reserve(buffer_size);
		buffer.resize(buffer_size, '\0');
		file_interface->Read(&buffer[0], buffer_size, file_handle);
		file_interface->Close(file_handle);
		
		
		TgaImage image(buffer);
		const unsigned char *imageData = image.GetData();
		int imageWidth = image.GetWidth();
		int imageHeight = image.GetHeight();

		std::shared_ptr<Renderer> renderRef = renderer.lock();
		std::unique_ptr<TextureHandle> th;
		if (imageData != nullptr)
		{
			unsigned char orientation = image.GetVerticalOrientation();
			if (orientation == 0)
			{
				unsigned char *flipped = (unsigned char*) malloc(sizeof(unsigned char) * imageWidth * imageHeight * 4);
				for(int row = imageHeight - 1; row >= 0; --row)
				{
					size_t stride = imageWidth * 4;
					int destRow = (imageHeight - 1) - row;
					memcpy(&flipped[destRow * stride], &imageData[row * stride], stride);
				}

				th = renderRef->GenerateTexture2D(Unit0, RGBA, UBYTE, imageWidth, imageHeight, flipped);
			}
		}
		else
		{
			th = renderRef->GenerateTexture2D(Unit0, RGBA, UBYTE, imageWidth, imageHeight, imageData);
			
		}
		
		uint32_t id = nextTextureId++;
		

		std::cout << "Just generated texture: " << id << std::endl;

		textureHandles.insert(std::make_pair(id, std::move(th)));
		
		std::stringstream fname;
 
		fname << "out-" << id << ".png";

		writeImage(fname.str().c_str(), imageWidth, imageHeight, imageData, "Out");
		
		texture_handle = (Rocket::Core::TextureHandle)id;
		texture_dimensions.x = imageWidth;
		texture_dimensions.y = imageHeight;

		// texture_handle = (Rocket::Core::TextureHandle)0;
		// texture_dimensions.x = 1;
		// texture_dimensions.y = 1;


		return true;
	}
	
	/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
	bool RocketGLFWRenderer::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
	{
		
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		
		// // set the maximum!
		// glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso );
		
		std::shared_ptr<Renderer> renderRef = renderer.lock();
		auto th = renderRef->GenerateTexture2D(Unit0, RGBA, UBYTE, source_dimensions.x, source_dimensions.y, source);
		uint32_t id = nextTextureId++;

		std::cout << "Just generated texture: " << id << std::endl;

		textureHandles.insert(std::make_pair(id, std::move(th)));
		
		
		
		texture_handle = (Rocket::Core::TextureHandle)id;
		
		std::stringstream fname;
		fname << "out-" << id << ".png";


		writeImage(fname.str().c_str(), source_dimensions.x, source_dimensions.y, source, "Out");

		return true;
	}
	
	/// Called by Rocket when a loaded texture is no longer required.
	void RocketGLFWRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
	{
		return;
	}

}

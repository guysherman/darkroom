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
#include <iostream>

// C Standard Headers
#include <cstdio>

// Boost Headers

// 3rd Party Headers
#include "linmath.h"

// GTK Headers


// Our Headers
#include "File.h"
#include "Renderer.h"
#include "GeometryHandle.h"
#include "TextureHandle.h"
#include "Effect.h"

void APIENTRY openglCallbackFunction(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
										   const void* userParam){
	
	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: "<< message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: "<<id << std::endl;
	std::cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;
std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}


namespace darkroom
{
	Renderer::Renderer(GLFWwindow *window) : window(window)
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Init()
	{
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		glewInit();

		const GLubyte *renderer;
		const GLubyte *version;

		/* get version info */
		renderer = glGetString( GL_RENDERER ); /* get renderer string */
		version = glGetString( GL_VERSION );	 /* version as a string */
		printf( "Renderer: %s\n", renderer );
		printf( "OpenGL version supported %s\n", version );

		if(glDebugMessageCallback){
			std::cout << "Register OpenGL debug callback " << std::endl;
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openglCallbackFunction, nullptr);
			GLuint unusedIds = 0;
			glDebugMessageControl(GL_DONT_CARE,
				GL_DONT_CARE,
				GL_DONT_CARE,
				0,
				&unusedIds,
				true);
		}
	}

	std::unique_ptr<GeometryHandle> Renderer::CreateGeometryHandle(GeometryInfo& geometryInfo)
	{
		GLuint posBuffer;
		GLuint colBuffer;
		GLuint tcBuffer;
		GLuint idxBuffer;

		GLuint vao;

		glGenBuffers(1, &posBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glBufferData(GL_ARRAY_BUFFER, geometryInfo.numVertices * 3 * sizeof( GLfloat ), geometryInfo.positions, GL_STATIC_DRAW);

		glGenBuffers(1, &colBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
		glBufferData(GL_ARRAY_BUFFER, geometryInfo.numVertices * 3 * sizeof( GLfloat ), geometryInfo.colors, GL_STATIC_DRAW);

		glGenBuffers(1, &tcBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tcBuffer);
		glBufferData(GL_ARRAY_BUFFER, geometryInfo.numVertices * 2 * sizeof( GLfloat ), geometryInfo.texCoords, GL_STATIC_DRAW);

		glGenBuffers(1, &idxBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, idxBuffer);
		glBufferData(GL_ARRAY_BUFFER, geometryInfo.numIndices * sizeof( GLuint ), geometryInfo.indices, GL_STATIC_DRAW);

		glGenVertexArrays( 1, &vao );
		glBindVertexArray( vao );

		glEnableVertexAttribArray( 0 );
		glEnableVertexAttribArray( 1 );
		glEnableVertexAttribArray( 2 );

		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL );

		glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
		glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL );

		glBindBuffer(GL_ARRAY_BUFFER, tcBuffer);
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idxBuffer );

		auto result = std::unique_ptr<GeometryHandle>(new GeometryHandle(vao, posBuffer, colBuffer, tcBuffer, idxBuffer, geometryInfo.numIndices, 0));
		return result;
	}

	std::unique_ptr<Effect> Renderer::CreateEffect(std::string vsPath, std::string fsPath)
	{
		std::string vsSource = File::ReadAllText(vsPath);
		const char *vsSrc = vsSource.c_str();
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vsSrc, NULL);
		glCompileShader(vs);

		std::string fsSource = File::ReadAllText(fsPath);
		const char *fsSrc = fsSource.c_str();
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fsSrc, NULL);
		glCompileShader(fs);

		GLuint shader_program = glCreateProgram();
		glAttachShader( shader_program, fs );
		glAttachShader( shader_program, vs );
		glLinkProgram( shader_program );

		auto effect = std::unique_ptr<Effect>(new Effect(vs, fs, shader_program));
		return effect;
	}

	std::unique_ptr<TextureHandle> Renderer::GenerateTexture2D(
		uint32_t textureUnit,
		uint32_t format,
		uint32_t type,
		uint32_t width,
		uint32_t height,
		const unsigned char* data)
	{
		GLuint tex;
		
		glGenTextures( 1, &tex );
		glActiveTexture( GetGlTextureUnit(textureUnit) );
		glBindTexture( GL_TEXTURE_2D, tex );
		glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
		glGenerateMipmap( GL_TEXTURE_2D );
		GLfloat max_aniso = 0.0f;
		glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso );

		auto texture = std::unique_ptr<TextureHandle>(new TextureHandle(
			tex,
			textureUnit,
			GL_TEXTURE_2D,
			format,
			format,
			type,
			GL_CLAMP_TO_EDGE,
			GL_CLAMP_TO_EDGE,
			GL_LINEAR,
			GL_LINEAR_MIPMAP_LINEAR,
			max_aniso
		));

		return texture;
	}

	uint32_t Renderer::GetGlTextureUnit(uint32_t textureUnit)
	{
		switch(textureUnit)
		{
			default:
				return GL_TEXTURE0;
		}
	}

	void Renderer::BeginFrame()
	{
		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::EndFrame()
	{
		glfwSwapBuffers( window );
		EmptyTrash();
	}

	void Renderer::EmptyTrash()
	{
		for (auto it = trashedGeometry.begin(); it != trashedGeometry.end(); ++it)
		{
			auto gh = it->get();
			FreeGeometryHandle(gh);
		}
		
		trashedGeometry.clear();
	}

	void Renderer::Draw(GeometryHandle *geometryHandle, Effect *effect, TextureHandle *texture, float *mvp)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		
		int matrix_location = glGetUniformLocation (effect->GetProgram(), "matrix");
		
		glViewport(0, 0, width, height);
		glUseProgram( effect->GetProgram() );
	
		
	
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, (const GLfloat*) mvp);
		glBindVertexArray(geometryHandle->GetVao());

		if (texture != nullptr)
		{
			glActiveTexture( GetGlTextureUnit(texture->GetTextureUnit()) );
			glBindTexture( GL_TEXTURE_2D, texture->GetTexture() );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->GetWrapS() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->GetWrapT() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->GetMagFilter() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->GetMinFilter() );
			
			// // set the maximum!
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, texture->GetMaxAniso() );
		} 
		else
		{
			std::cout << "Couldn't bind texture" << std::endl;
		}

		

		glDrawElements( GL_TRIANGLES, geometryHandle->GetNumIndices(), GL_UNSIGNED_INT, (void*)0  );
	}

	void Renderer::TrashGeometryHandle(std::unique_ptr<GeometryHandle> geometryHandle)
	{
		trashedGeometry.push_back(std::move(geometryHandle));
	}
	
	void Renderer::FreeGeometryHandle(GeometryHandle *handle)
	{
		GLuint vao = handle->GetVao();
		glDeleteVertexArrays(1, &vao);

		GLuint posBuf = handle->GetPositionBuffer();
		glDeleteBuffers(1, &posBuf);

		GLuint colBuf = handle->GetColorBuffer();
		glDeleteBuffers(1, &colBuf);

		GLuint tcBuf = handle->GetTexCoordBuffer();
		glDeleteBuffers(1, &tcBuf);

		GLuint idxBuf = handle->GetIndexBuffer();
		glDeleteBuffers(1, &idxBuf);
	}

	
}

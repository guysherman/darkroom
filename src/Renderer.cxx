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
#include "Effect.h"

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
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL );

		glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
		glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL );

		glBindBuffer(GL_ARRAY_BUFFER, tcBuffer);
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idxBuffer );

		auto result = std::unique_ptr<GeometryHandle>(new GeometryHandle(vao, posBuffer, colBuffer, tcBuffer, idxBuffer, geometryInfo.numIndices));
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

	// std::shared_ptr<CanvasView> Renderer::CreateCanvasView(std::shared_ptr<Canvas> canvas)
	// {

	// 	int width, height;
	// 	glfwGetFramebufferSize(window, &width, &height);

	// 	std::string vsSource = File::ReadAllText("assets/basic_vs.glsl");
	// 	std::string fsSource = File::ReadAllText("assets/basic_fs.glsl");
	// 	const char *srcVs = vsSource.c_str();
	// 	const char *srcFs = fsSource.c_str();

	// 	glfwMakeContextCurrent(window);

	// 	GLuint vbo;
	// 	float *vertices = canvas->GetVertices();
	// 	glGenBuffers( 1, &vbo );
	// 	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	// 	glBufferData( GL_ARRAY_BUFFER, 30 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

	// 	GLuint ibo;
	// 	unsigned int *indices = canvas->GetIndices();
	// 	glGenBuffers( 1, &ibo );
	// 	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
	// 	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof( GLuint ), indices, GL_STATIC_DRAW );

	// 	GLuint vao;
	// 	glGenVertexArrays( 1, &vao );
	// 	glBindVertexArray( vao );

	// 	glEnableVertexAttribArray( 0 );
	// 	glEnableVertexAttribArray( 1 );

	// 	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	// 	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL );
	// 	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 2) );
	// 	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );

	// 	/* GL shader objects for vertex and fragment shader [components] */
	// 	GLuint vs, fs;
	// 	/* GL shader programme object [combined, to link] */
	// 	GLuint shader_programme;

	// 	vs = glCreateShader( GL_VERTEX_SHADER );
	// 	glShaderSource( vs, 1, &srcVs, NULL );
	// 	glCompileShader( vs );

	// 	fs = glCreateShader( GL_FRAGMENT_SHADER );
	// 	glShaderSource( fs, 1, &srcFs, NULL );
	// 	glCompileShader( fs );

	// 	shader_programme = glCreateProgram();
	// 	glAttachShader( shader_programme, fs );
	// 	glAttachShader( shader_programme, vs );
	// 	glLinkProgram( shader_programme );

	// 	std::shared_ptr<CanvasView> result(new CanvasView(canvas, width, height, vao, vbo, ibo, vs, fs, shader_programme));
	// 	return result;
	// }

	void Renderer::BeginFrame()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void Renderer::EndFrame()
	{
		glfwSwapBuffers( window );
	}

	void Renderer::Draw(GeometryHandle *geometryHandle, Effect *effect)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		mat4x4 m;
		int matrix_location = glGetUniformLocation (effect->GetProgram(), "matrix");
		
		glViewport(0, 0, width, height);
		glUseProgram( effect->GetProgram() );
	
		mat4x4_identity(m);
	
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, (const GLfloat*) m);
		glBindVertexArray(geometryHandle->GetVao());

		glDrawElements( GL_TRIANGLES, geometryHandle->GetNumIndices(), GL_UNSIGNED_INT, (void*)0  );
	}
}

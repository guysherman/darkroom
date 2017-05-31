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


// GTK Headers


// Our Headers
#include "File.h"
#include "Renderer.h"
#include "Canvas.h"
#include "CanvasView.h"

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

	std::shared_ptr<CanvasView> Renderer::CreateCanvasView(std::shared_ptr<Canvas> canvas)
	{

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		std::string vsSource = File::ReadAllText("assets/basic_vs.glsl");
		std::string fsSource = File::ReadAllText("assets/basic_fs.glsl");
		const char *srcVs = vsSource.c_str();
		const char *srcFs = fsSource.c_str();

		glfwMakeContextCurrent(window);

		GLuint vbo;
		float *vertices = canvas->GetVertices();
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, 30 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

		GLuint vao;
		glGenVertexArrays( 1, &vao );
		glBindVertexArray( vao );

		glEnableVertexAttribArray( 0 );
		glEnableVertexAttribArray( 1 );

		glBindBuffer( GL_ARRAY_BUFFER, vbo );

		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 2) );

		/* GL shader objects for vertex and fragment shader [components] */
		GLuint vs, fs;
		/* GL shader programme object [combined, to link] */
		GLuint shader_programme;

		vs = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vs, 1, &srcVs, NULL );
		glCompileShader( vs );

		fs = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fs, 1, &srcFs, NULL );
		glCompileShader( fs );

		shader_programme = glCreateProgram();
		glAttachShader( shader_programme, fs );
		glAttachShader( shader_programme, vs );
		glLinkProgram( shader_programme );

		std::shared_ptr<CanvasView> result(new CanvasView(canvas, width, height, vao, vbo, vs, fs, shader_programme));
		return result;
	}

	void Renderer::Draw(CanvasView &canvasView)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		canvasView.SetScreenSize(width, height);


		mat4x4 m, mvp;
		int matrix_location = glGetUniformLocation (canvasView.GetProgram(), "matrix");

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glViewport(0, 0, width, height);
		glUseProgram( canvasView.GetProgram() );

		mat4x4 &p = canvasView.GetProjectionMatrix();
		mat4x4_identity(m);
		mat4x4_mul(mvp, p, m);
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, (const GLfloat*) mvp);
		glBindVertexArray( canvasView.GetVao() );

		glDrawArrays( GL_TRIANGLES, 0, 6 );

		glfwSwapBuffers( window );

	}
}

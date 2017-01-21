// Darkroom is an open-source photography tool.
// Copyright (C) 2017  Guy Sherman
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Contact the author via https://github.com/guysherman
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include "linmath.h"
#include "Canvas.h"
#include "CanvasView.h"

static void error_callback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main() {
	GLFWwindow *window = NULL;
	const GLubyte *renderer;
	const GLubyte *version;
	GLuint vao;
	GLuint vbo;


	GLfloat verts[] = { 0.0f,       0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
						0.0f,    1024.0f, 0.0f, 1.0f, 1.0f, 1.0f,
						1280.0f,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
						0.0f,    1024.0f, 0.0f, 1.0f, 1.0f, 1.0f,
 						1280.0f, 1024.0f, 0.0f, 1.0f, 1.0f, 1.0f,
 						1280.0f,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char *srcVs = "#version 410\n"
								"layout (location = 0) in vec3 vp;"
								"layout (location = 1) in vec2 tc;"
								"uniform mat4 matrix;"
								"void main () {"
								"	gl_Position = matrix * vec4 (vp, 1.0);"
								"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char *srcFs = "#version 410\n"
								"out vec4 frag_colour;"
								"void main () {"
								"	frag_colour = vec4 (1.0, 1.0, 1.0, 1.0);"
								"}";
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme;

	glfwSetErrorCallback(error_callback);

	/* start GL context and O/S window using the GLFW helper library */
	if ( !glfwInit() ) {
		fprintf( stderr, "ERROR: could not start GLFW3\n" );
		return 1;
	}

#ifndef WIN32
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#endif

	window = glfwCreateWindow( 1280, 1024, "Darkroom", NULL, NULL );
	if ( !window ) {
		fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
		glfwTerminate();
		return 1;
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent( window );

	glewExperimental = GL_TRUE;
	glewInit();

	/* get version info */
	renderer = glGetString( GL_RENDERER ); /* get renderer string */
	version = glGetString( GL_VERSION );	 /* version as a string */
	printf( "Renderer: %s\n", renderer );
	printf( "OpenGL version supported %s\n", version );

	std::shared_ptr<darkroom::Canvas> canvas = std::shared_ptr<darkroom::Canvas>(
		new darkroom::Canvas(1280.0f, 1024.0f));
	darkroom::CanvasView canvasView(canvas, 1280.0f, 1024.0f);

	float* vertices = canvas->GetVertices();

	glEnable( GL_DEPTH_TEST );

	glDepthFunc( GL_LESS );

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, 36 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 2) );

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



	mat4x4& matrix = canvasView.GetProjectionMatrix();

	int matrix_location = glGetUniformLocation (shader_programme, "matrix");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, (GLfloat *) matrix);



	GLenum err = 0;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}


	while ( !glfwWindowShouldClose( window ) ) {

		float ratio;
		int width, height;
		mat4x4 m, mvp;
		glfwGetFramebufferSize(window, &width, &height);
		canvasView.SetScreenSize(width, height);
		ratio = width / (float) height;

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glViewport(0, 0, width, height);
		glUseProgram( shader_programme );

		mat4x4 &p = canvasView.GetProjectionMatrix();
		mat4x4_identity(m);
		mat4x4_mul(mvp, p, m);
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, (const GLfloat*) mvp);
		glBindVertexArray( vao );

		glDrawArrays( GL_TRIANGLES, 0, 6 );
		glfwPollEvents();
		glfwSwapBuffers( window );
	}

	glfwTerminate();
	return 0;
}

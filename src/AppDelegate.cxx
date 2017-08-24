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
#include <cstdint>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include "linmath.h"
#include <Rocket/Core.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>


// GTK Headers


// Our Headers


#include "AppDelegate.h"
#include "Renderer.h"
#include "GeometryHandle.h"
#include "TextureHandle.h"
#include "RenderInterfaceGLFW.h"
#include "SystemInterfaceGLFW.h"
#include "ShellFileInterface.h"



namespace darkroom
{
	AppDelegate *AppDelegate::instance = nullptr;

	static void error_callback(int error, const char* description)
	{
		std::cerr << "Error: " << description << std::endl;
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		// 	glfwSetWindowShouldClose(window, GLFW_TRUE);
		if (nullptr != AppDelegate::instance)
		{
			AppDelegate::instance->KeyEvent(window, key, scancode, action, mods);
		}
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (nullptr != AppDelegate::instance)
		{
			AppDelegate::instance->MouseButtonEvent(window, button, action, mods);
		}
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if(nullptr != AppDelegate::instance)
		{
			AppDelegate::instance->MousePositionEvent(window, xpos, ypos);
		}
	}

	static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
	{
		if (nullptr != AppDelegate::instance)
		{
			AppDelegate::instance->ScrollEvent(window, xoffset, yoffset);
		}
	}

	AppDelegate::AppDelegate(int width, int height)
	{
		glfwSetErrorCallback(error_callback);
		/* start GL context and O/S window using the GLFW helper library */
		if ( !glfwInit() ) {
			std::cerr << "ERROR: could not start GLFW3" << std::endl;
			exit(EXIT_FAILURE);
		}

	#ifndef WIN32
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	#endif

		window = glfwCreateWindow( width, height, "Darkroom", NULL, NULL );
		if ( !window ) {
			fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetScrollCallback(window, scroll_callback);

		renderer = std::shared_ptr<Renderer>(new Renderer(window));
		renderer->Init();
		rocketRenderer = std::shared_ptr<RocketGLFWRenderer>(new RocketGLFWRenderer());
		rocketRenderer->SetWindow(window);
		rocketRenderer->SetRenderer(renderer);

		systemInterface = std::shared_ptr<RocketGLFWSystemInterface>(new RocketGLFWSystemInterface());
		fileInterface = std::shared_ptr<ShellFileInterface>(new ShellFileInterface("./assets/"));

		Rocket::Core::SetFileInterface(fileInterface.get());
		Rocket::Core::SetRenderInterface(rocketRenderer.get());
		Rocket::Core::SetSystemInterface(systemInterface.get());

		

		lastMousePos[0] = lastMousePos[1] = 0.0f;
		lastScrollPos[0] = lastScrollPos[1] = 0.0f;
	}

	AppDelegate::~AppDelegate()
	{

	}

	void AppDelegate::KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

	}

	void AppDelegate::MouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

	}

	void AppDelegate::MousePositionEvent(GLFWwindow *window, double xpos, double ypos)
	{
		// vec2 to = {(float)xpos, (float)ypos};

		lastMousePos[0] = xpos;
		lastMousePos[1] = ypos;
	}

	void AppDelegate::ScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
	{
		// vec2 to = {(float)xoffset * SCROLL_SENSITIVITY, (float)yoffset * SCROLL_SENSITIVITY};

		lastScrollPos[0] = xoffset;
		lastScrollPos[1] = yoffset;
	}

	void AppDelegate::Run()
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		
		float points[] = 
		{
			  0.0f,  100.0f,
			100.0f,  100.0f, 
			100.0f,    0.0f,
			  0.0f,    0.0f
		};

		float colors[] = 
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};

		float texCoords[] = 
		{
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		uint32_t indices[] = 
		{
			0, 3, 2,
			0, 2, 1
		};

		unsigned char pixels[] =
		{
			255, 255, 255, 0, 255, 255, 255, 255,
			255, 255, 255, 255, 255, 255, 255, 0
		};


		GeometryInfo gi;
		gi.positions = &points[0];
		gi.colors = &colors[0];
		gi.texCoords = &texCoords[0];
		gi.indices = &indices[0];
		gi.numVertices = 4;
		gi.numIndices = 6;

		
		auto tx = renderer->GenerateTexture2D(Unit0, RGBA, UBYTE, 2, 2, &pixels[0]);

		auto gh = renderer->CreateGeometryHandle(gi);
		auto gh2 = renderer->CreateGeometryHandle(gi);
		auto gh3 = renderer->CreateGeometryHandle(gi);
		auto gh4 = renderer->CreateGeometryHandle(gi);

		auto effect = renderer->CreateEffect("assets/basic_vs.glsl", "assets/basic_fs.glsl");
		
		if(!Rocket::Core::Initialise())
		{
			return;
		}

		Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
		Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
		Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
		Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

		Rocket::Core::Context *Context = Rocket::Core::CreateContext("default",
		Rocket::Core::Vector2i(width, height));

		Rocket::Debugger::Initialise(Context);

		Rocket::Core::ElementDocument *Document = Context->LoadDocument("demo.rml");

		if(Document)
		{
			Document->Show();
			Document->RemoveReference();
			fprintf(stdout, "\nDocument loaded");
		}
		else
		{
			fprintf(stdout, "\nDocument is NULL");
		}
		
		while ( !glfwWindowShouldClose( window ) )
		{
			
			glfwGetFramebufferSize(window, &width, &height);

			
			mat4x4 m;
			mat4x4 p;
			mat4x4 mvp;
			
			


			renderer->BeginFrame();

			mat4x4_identity(m);
			mat4x4_translate(m, 100.0f, 100.0f, 0.0f);
			mat4x4_ortho(p, 0, width, height, 0, 0, 1000);
			mat4x4_mul(mvp, p, m);
			renderer->Draw(gh.get(), effect.get(), tx.get(), (float *)mvp);
			mat4x4_identity(m);
			mat4x4_translate(m, 400.0f, 100.0f, 0.0f);
			mat4x4_ortho(p, 0, width, height, 0, 0, 1000);
			mat4x4_mul(mvp, p, m);
			renderer->Draw(gh2.get(), effect.get(), tx.get(), (float *)mvp);
			mat4x4_identity(m);
			mat4x4_translate(m, 800.0f, 100.0f, 0.0f);
			mat4x4_ortho(p, 0, width, height, 0, 0, 1000);
			mat4x4_mul(mvp, p, m);
			renderer->Draw(gh3.get(), effect.get(), tx.get(), (float *)mvp);
			mat4x4_identity(m);
			mat4x4_translate(m, 1200.0f, 100.0f, 0.0f);
			mat4x4_ortho(p, 0, width, height, 0, 0, 1000);
			mat4x4_mul(mvp, p, m);
			renderer->Draw(gh4.get(), effect.get(), tx.get(), (float *)mvp);


			Context->Render();
		
			glfwWaitEventsTimeout(0.016);
			renderer->EndFrame();
			//glfwPollEvents();
		}
	}

}

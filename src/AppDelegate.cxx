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
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include "linmath.h"

// GTK Headers


// Our Headers


#include "AppDelegate.h"
#include "Renderer.h"
#include "Canvas.h"
#include "CanvasView.h"

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
		canvas = std::shared_ptr<Canvas>(new Canvas(1280.0f, 1024.0f));
		canvasView = renderer->CreateCanvasView(canvas);
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

		canvasView->KeyEvent(window, key, scancode, action, mods);
	}

	void AppDelegate::MouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (canvasView->ScreenPointIsInView(xpos, ypos))
		{
			canvasView->MouseButton(window, button, action, mods);
		}
	}

	void AppDelegate::MousePositionEvent(GLFWwindow *window, double xpos, double ypos)
	{
		vec2 to = {(float)xpos, (float)ypos};
		if (canvasView->ScreenPointIsInView(xpos, ypos))
		{
			canvasView->MouseMoved(window, lastMousePos, to);
		}

		lastMousePos[0] = xpos;
		lastMousePos[1] = ypos;
	}

	void AppDelegate::ScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
	{
		vec2 to = {(float)xoffset * SCROLL_SENSITIVITY, (float)yoffset * SCROLL_SENSITIVITY};
		canvasView->Scrolled(window, lastScrollPos, to);

		lastScrollPos[0] = xoffset;
		lastScrollPos[1] = yoffset;
	}

	void AppDelegate::Run()
	{
		while ( !glfwWindowShouldClose( window ) )
		{
			renderer->BeginFrame();
			renderer->Draw(*canvasView);
		
			glfwWaitEventsTimeout(0.016);
			renderer->EndFrame();
			//glfwPollEvents();
		}
	}

}

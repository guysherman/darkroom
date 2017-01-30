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
#include <memory>
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
// GTK Headers


// Our Headers



#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

namespace darkroom
{
	class Renderer;
	class Canvas;
	class CanvasView;
	class AppDelegate
	{
	public:
		AppDelegate(int width, int height);
		virtual ~AppDelegate();

		void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		void MousePositionEvent(GLFWwindow* window, double xpos, double ypos);
		void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

		void Run();

		static AppDelegate *instance;

	private:
		GLFWwindow* window;
		std::shared_ptr<Renderer> renderer;
		std::shared_ptr<Canvas> canvas;
		std::shared_ptr<CanvasView> canvasView;
		vec2 lastMousePos;



	};


}


#endif //__APPDELEGATE_H__

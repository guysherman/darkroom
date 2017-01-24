#ifndef __CANVASVIEW_H__
#define __CANVASVIEW_H__

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
// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers


#include "linmath.h"
#include "Canvas.h"

namespace darkroom
{
	class CanvasView
	{
	public:
		CanvasView(
			std::shared_ptr<Canvas> canvas,
			float screenWidth,
			float screenHeight,
			GLuint vao,
			GLuint vbo,
			GLuint vs,
			GLuint fs,
			GLuint program);
		~CanvasView();

		float GetZoom();
		void SetZoom(float zoom);

		float* GetPan();
		void SetPan(vec2 pan);

		void SetScreenSize(float width, float height);


		mat4x4& GetProjectionMatrix();

		GLuint GetVao();
		GLuint GetProgram();


	private:
		void setupProjection();


		float zoom;
		vec2 pan;
		vec2 screenSize;
		mat4x4 projection;
		
		GLuint vao;
		GLuint vbo;
		GLuint vs;
		GLuint fs;
		GLuint program;
		std::shared_ptr<Canvas> canvas;
	};
}

#endif //__CANVASVIEW_H__

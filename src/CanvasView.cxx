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


// GTK Headers


// Our Headers
#include <cstring>
#include "CanvasView.h"

namespace darkroom
{
	CanvasView::CanvasView(std::shared_ptr<Canvas> canvas,
	float screenWidth,
	float screenHeight,
	GLuint vao,
	GLuint vbo,
	GLuint vs,
	GLuint fs,
	GLuint program) : zoom(1.0f), canvas(canvas)
	{
		pan[0] = 0.0f;
		pan[1] = 0.0f;
		screenSize[0] = screenWidth;
		screenSize[1] = screenHeight;
		this->vao = vao;
		this->vbo = vbo;
		this->vs = vs;
		this->fs = fs;
		this->program = program;
		handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		normalCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		setupProjection();
	}

	CanvasView::~CanvasView()
	{
		glfwDestroyCursor(handCursor);
		glfwDestroyCursor(normalCursor);
	}

	float CanvasView::GetZoom()
	{
		return zoom;
	}

	void CanvasView::SetZoom(float zoom)
	{
		this->zoom = zoom;
		setupProjection();
	}

	float* CanvasView::GetPan()
	{
		return pan;
	}

	void CanvasView::SetPan(vec2 pan)
	{
		this->pan[0] = pan[0];
		this->pan[1] = pan[1];
		setupProjection();
	}

	void CanvasView::SetScreenSize(float width, float height)
	{
		this->screenSize[0] = width;
		this->screenSize[1] = height;
		setupProjection();
	}

	mat4x4& CanvasView::GetProjectionMatrix()
	{
		return projection;
	}

	void CanvasView::setupProjection()
	{
		float* size = canvas->GetSize();
		float hcw = size[0] / 2.0f;
		float hch = size[1] / 2.0f;
		float hw = screenSize[0] / (2.0f);
		float hh = screenSize[1] / (2.0f);

		float screenAspectRatio = screenSize[0] / screenSize[1];
		float canvasAspectRatio = size[0] / size[1];

		float l = 0.0f, r = 0.0f, b = 0.0f, t = 0.0f,n = 0.0f,f = 0.0f;

		if ( canvasAspectRatio < screenAspectRatio )
		{
			//l = ( hch * screenAspectRatio ) * ( 1 - zoom ) + pan[0];
			l = (hch * canvasAspectRatio) - (hch * screenAspectRatio * zoom) + pan[0];
			//r = ( hch * screenAspectRatio ) * ( 1 + zoom ) + pan[0];
			r = (hch * canvasAspectRatio) + (hch * screenAspectRatio * zoom) + pan[0];
			b = hch * ( 1 - zoom ) + pan[1];
			t = hch * ( 1 + zoom ) + pan[1];
			n = 0.0f;
			f = 1.0f;
		}
		else 
		{
			l = hcw * ( 1 - zoom ) + pan[0];
			r = hcw * ( 1 + zoom ) + pan[0];
			//b = ( hcw / screenAspectRatio ) * ( 1 - zoom ) + pan[1];
			b = (hcw / canvasAspectRatio) - ((hcw * zoom) / screenAspectRatio) + pan[1];
			//t = ( hcw / screenAspectRatio ) * ( 1 + zoom ) + pan[1];
			t = (hcw / canvasAspectRatio) + ((hcw * zoom) / screenAspectRatio) + pan[1];
			n = 0.0f;
			f = 1.0f;
		}

		

		mat4x4_ortho(projection, l, r, b, t, n, f);
	}

	GLuint CanvasView::GetProgram()
	{
		return program;
	}

	GLuint CanvasView::GetVao()
	{
		return vao;
	}

	bool CanvasView::ScreenPointIsInView(double xpos, double ypos)
	{
		// TODO: at some point, this will have constrained size/position,
		// in which case we'll need some logic here
		return true;
	}

	bool CanvasView::MouseMoved(GLFWwindow *window, vec2 from, vec2 to)
	{
		if (mouseMode == MouseMode::Pan)
		{
			vec2 move;
			vec2 newPan;
			vec2_sub(move, to, from);
			move[0] = move[0] * -1.0f;
			vec2_add(newPan, pan, move);
			pan[0] = newPan[0];
			pan[1] = newPan[1];

			std::cout << "move: " << move[0] << ", " << move[1] << "; " << "from: " << from[0] << ", " << from[1] << "; " << "to: " << to[0] << ", " << to[1] << ";" << std::endl;
			return true;
		}


		return false;
	}

	bool CanvasView::MouseButton(GLFWwindow *window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && (mods & GLFW_MOD_ALT))
		{
			mouseMode = MouseMode::Pan;
			glfwSetCursor(window, handCursor);
			return true;
		}
		else
		{
			// TODO: this will be a bug eventually. Individual components should not decide the
			// cursor, they should ask for a cursor, and only the one who returns true should get it.
			glfwSetCursor(window, normalCursor);
			mouseMode = MouseMode::None;
		}

		return false;
	}

	bool CanvasView::Scrolled(GLFWwindow *window, vec2 from, vec2 to)
	{
		vec2 move;
		vec2_sub(move, to, from);
		std::cout << "move: " << move[0] << ", " << move[1] << "; " << "from: " << from[0] << ", " << from[1] << "; " << "to: " << to[0] << ", " << to[1] << ";" << std::endl;
		
		float newZoom = zoom + to[1];
		
		if (newZoom >= 0 && newZoom <= 1)
		{
			SetZoom(newZoom);
			return true;
		}
		return false;
	}

	bool CanvasView::KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		if (key == GLFW_KEY_H && action == GLFW_PRESS && (mods & GLFW_MOD_ALT))
		{
			if (!isViewCentred())
			{
				centreView();
				return true;
			}
			else if (!isZoomedToFit()) 
			{
				resetZoom();
				return true;
			}
		}
		
		return false;
		
	}

	bool CanvasView::isViewCentred()
	{
		return 0.0f == pan[0] && 0.0f == pan[1];
	}

	void CanvasView::centreView()
	{
		vec2 newPan = {0.0f, 0.0f};
		SetPan(newPan);
	}

	bool CanvasView::isZoomedToFit()
	{
		return 1.0f == zoom;
	}

	void CanvasView::resetZoom()
	{
		SetZoom(1.0f);
	}



}

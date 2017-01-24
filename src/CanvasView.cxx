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
		setupProjection();
	}

	CanvasView::~CanvasView()
	{

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
		float hw = screenSize[0] / 2.0f;
		float hh = screenSize[1] / 2.0f;

		float l = hcw + pan[0] - hw;
		float r = hcw + pan[0] + hw;
		float b = hch + pan[1] - hh;
		float t = hch + pan[1] + hh;
		float n = 0.0f;
		float f = 1.0f;

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


}

#include "CanvasView.h"

namespace darkroom
{
	CanvasView::CanvasView(std::shared_ptr<Canvas> canvas, float screenWidth, float screenHeight) : zoom(1.0f), canvas(canvas)
	{
		pan[0] = 0.0f;
		pan[1] = 0.0f;
		screenSize[0] = screenWidth;
		screenSize[1] = screenHeight;
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
}

#ifndef __CANVASVIEW_H__
#define __CANVASVIEW_H__

#include <memory>
#include "linmath.h"
#include "Canvas.h"

namespace darkroom
{
	class CanvasView
	{
	public:
		CanvasView(std::shared_ptr<Canvas> canvas, float screenWidth, float screenHeight);
		~CanvasView();

		float GetZoom();
		void SetZoom(float zoom);

		float* GetPan();
		void SetPan(vec2 pan);

		void SetScreenSize(float width, float height);

		mat4x4& GetProjectionMatrix();


	private:
		void setupProjection();

		float zoom;
		vec2 pan;
		vec2 screenSize;
		mat4x4 projection;
		std::shared_ptr<Canvas> canvas;
	};
}

#endif //__CANVASVIEW_H__

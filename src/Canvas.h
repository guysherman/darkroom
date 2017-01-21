#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "linmath.h"

namespace darkroom
{
	class Canvas
	{
	public:
		Canvas(float w, float h);
		~Canvas();

		float *GetSize();
		void SetSize(float w, float h);
		float *GetVertices();

	private:
		vec2 size;
		float vertices[30];
	};
}

#endif //__CANVAS_H__

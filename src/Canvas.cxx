#include <cstring>
#include "Canvas.h"


namespace darkroom
{
	Canvas::Canvas(float w, float h)
	{
		size[0] = w;
		size[1] = h;
		float verts[30] = { 0.0f,       0.0f, 0.0f, 0.0f, 0.0f,
					 		0.0f,    size[1], 0.0f, 0.0f, 1.0f,
				 	 		size[0],    0.0f, 0.0f, 1.0f, 0.0f,
					 		0.0f,    size[1], 0.0f, 0.0f, 1.0f,
			 		 		size[0], size[1], 0.0f, 1.0f, 1.0f,
			 		 		size[0], 	 0.0f, 0.0f, 1.0f, 0.0f};
		memcpy(&this->vertices, verts, 30 * sizeof(float));
	}

	Canvas::~Canvas()
	{

	}

	float *Canvas::GetSize()
	{
		return (float*) size;
	}

	void Canvas::SetSize(float w, float h)
	{
		size[0] = w;
		size[1] = h;
		float verts[30] = { 0.0f,       0.0f, 0.0f, 0.0f, 0.0f,
					 		0.0f,    size[1], 0.0f, 0.0f, 1.0f,
				 	 		size[0],    0.0f, 0.0f, 1.0f, 0.0f,
					 		0.0f,    size[1], 0.0f, 0.0f, 1.0f,
			 		 		size[0], size[1], 0.0f, 1.0f, 1.0f,
			 		 		size[0], 	 0.0f, 0.0f, 1.0f, 0.0f};
		memcpy(&this->vertices, verts, 30 * sizeof(float));
	}

	float *Canvas::GetVertices()
	{
		return vertices;
	}


}

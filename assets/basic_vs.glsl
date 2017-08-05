#version 410
layout (location = 0) in vec2 vp;
layout (location = 1) in vec4 col;
layout (location = 2) in vec2 tc;
uniform mat4 matrix;
void main () {
	gl_Position = matrix * vec4 (vp, 0.0, 1.0);
}

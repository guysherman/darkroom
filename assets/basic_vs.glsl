#version 410
layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 tc;
uniform mat4 matrix;
void main () {
	gl_Position = matrix * vec4 (vp, 1.0);
}

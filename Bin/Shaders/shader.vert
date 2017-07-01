#version 400

in vec3 Pos;

uniform mat4 transform;

void main(void)
{
	vec4 newPos = vec4(Pos, 1.f);
	newPos = newPos * transform;
	gl_Position = vec4(newPos.xyz, 1.0f);
}
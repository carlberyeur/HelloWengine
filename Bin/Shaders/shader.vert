#version 400

in vec3 Pos;

uniform mat3 hej;

void main(void)
{
	vec3 newPos = Pos * hej;
	gl_Position = vec4(newPos, 1.0f);
}
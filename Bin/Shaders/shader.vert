#version 400

in vec4 Pos;
in vec4 Norm;
in vec4 Tangent;
in vec4 Bitangent;
in vec2 uv;

uniform mat4 transform;

void main(void)
{
	vec4 newPos = vec4(Pos.xyz, 1.f);
	newPos = newPos * transform;
	gl_Position = vec4(newPos.xyz, 1.0f);
}
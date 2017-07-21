#version 400

in vec2 fragUV;
out vec4 outputColor;

uniform sampler2D albedo;

void main(void)
{
	outputColor = texture(albedo, fragUV);
	//outputColor = vec4(0.5f, 1.f, 0.f, 1.f);
}

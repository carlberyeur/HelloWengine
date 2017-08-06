#version 400

in vec2 fragUV;
out vec4 outputColor;

uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D rmao;
uniform sampler2D emissive;

void main(void)
{
	vec4 albedoColor = texture(albedo, fragUV);
	vec4 normalColor = texture(normal, fragUV);
	vec4 rmaoColor = texture(rmao, fragUV);
	vec4 emissiveColor = texture(emissive, fragUV);
	
	outputColor = albedoColor;
	outputColor.a = albedoColor.a;
}

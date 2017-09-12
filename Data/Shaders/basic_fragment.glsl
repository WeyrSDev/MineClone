#version 330 core
in vec2 TexCoord;
in float light;

out vec4 color;

uniform sampler2D uTexture;
uniform float alpha;


void main()
{
	color = vec4(vec3(texture(uTexture, TexCoord)), alpha) * light;
}

#version 330 core
in vec2 TexCoord;
in float light;

out vec4 color;

uniform sampler2D uTexture;


void main()
{
	color = texture(uTexture, TexCoord) * light;
}

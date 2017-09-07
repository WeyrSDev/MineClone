#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in float light;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transformMatrix;

void main()
{
	gl_Position = transformMatrix * vec4(pos, 1.0);
	TexCoord = texCoord;
}

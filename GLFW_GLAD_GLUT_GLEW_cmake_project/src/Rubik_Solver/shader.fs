#version 400 core
in vec3 fColor;
in vec2 TexCoord;

out vec4 Color;

uniform sampler2D texture1;

void main()
{
    Color = texture(texture1, TexCoord) * vec4(fColor, 1.0);
}

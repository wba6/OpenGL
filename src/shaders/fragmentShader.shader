#version 330 core
out vec4 FragColor;
in vec3 ourColorPass;
in vec2 TexCord;
uniform sampler2D ourTexture;
void main()
{
    FragColor = texture(ourTexture, TexCord) * vec4(ourColorPass, 1.0f);
}
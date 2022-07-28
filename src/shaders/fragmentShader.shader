#version 330 core
out vec4 FragColor;
in vec3 ourColorPass;
in vec2 TexCord;
uniform sampler2D ourTexture;
uniform sampler2D texture2;
void main()
{
    FragColor = mix(texture(ourTexture, TexCord), texture(texture2, TexCord), 0.3) * vec4(ourColorPass, 1.0f);
}
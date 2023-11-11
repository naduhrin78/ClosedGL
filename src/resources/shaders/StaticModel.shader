#Shader Vertex
#version 330 core

out vec2 v_Texture;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * position;
    v_Texture = texture;
}

#Shader Fragment
#version 330 core

out vec4 color;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

in vec2 v_Texture;
uniform Material material;

void main()
{
    color = texture(material.texture_diffuse1, v_Texture);
}
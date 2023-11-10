#Shader Vertex
#version 330 core

out vec2 v_Texture;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;
layout(location = 5) in ivec4 boneIds; 
layout(location = 6) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = position;
            break;
        }

        vec4 localPosition = finalBonesMatrices[boneIds[i]] * position;
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * normal;
    }

    gl_Position = projection * view * model * totalPosition;
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
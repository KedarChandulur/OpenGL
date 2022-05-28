#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec3 modelPosition;
layout(location = 1) in vec2 modelTexCoords;

out vec2 fragTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   fragTexCoords = modelTexCoords;
   gl_Position = projection * view * model * vec4(modelPosition, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 modelColor;

in vec2 fragTexCoords;

uniform sampler2D texture1;

void main()
{
    modelColor = texture(texture1, fragTexCoords);
}
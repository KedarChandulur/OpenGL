#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec4 lightPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * lightPosition;
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 lightColor;

void main()
{
    lightColor = vec4(1.0);
}
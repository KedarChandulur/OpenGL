#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec3 modelPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(modelPosition, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = vec4(0.04, 0.28, 0.26, 1.0);
}
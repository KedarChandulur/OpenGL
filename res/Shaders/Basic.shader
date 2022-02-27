#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * position;
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	color = vec4(lightColor * objectColor, 1.0);
};
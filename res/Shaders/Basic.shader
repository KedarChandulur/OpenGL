#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
//layout(location = 2) in vec3 a_Color;

out vec2 v_TexCoord;
//out vec3 v_Color;

//uniform mat4 u_MVP;
//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * position;
   //gl_Position = u_MVP * transform * position;
   v_TexCoord = texCoord;
   //v_Color = a_Color;
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

//in vec3 v_Color;

void main()
{
   vec4 texColor = mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.3);
   color = texColor;
   //color = v_Color;
};
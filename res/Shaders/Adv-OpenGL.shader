#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec3 modelPosition;
layout(location = 1) in vec2 modelTexCoords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   texCoords = modelTexCoords;
   gl_Position = projection * view * model * vec4(modelPosition, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, texCoords);
	if (texColor.a < 0.1)
		discard;
	fragColor = texColor;
}

//float near = 0.1;
//float far = 100.0;
//
//float LinearizeDepth(float depth)
//{
//	float z = depth * 2.0 - 1.0; // back to NDC
//	return (2.0 * near * far) / (far + near - z * (far - near));
//}
//
//void main()
//{
//	float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far to get depth in range [0,1] for visualization purpose.
//	fragColor = vec4(vec3(depth), 1.0);
//}
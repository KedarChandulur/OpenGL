#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 fragPosition;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   //Multiplying model and position for World space calculation.
   fragPosition = vec3(model * vec4(position, 1.0));
   //Need to add transpose and inverse calls on CPU side in future.
   fragNormal = mat3(transpose(inverse(model))) * normal;
   gl_Position = projection * view * model * vec4(position, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//Ambient light calculation.
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse light calculation.
	vec3 frag_N_Normalized = normalize(fragNormal);
	vec3 lightDirectionNormalized = normalize(lightPos - fragPosition);
	float diffuseImpact = max(dot(frag_N_Normalized, lightDirectionNormalized), 0.0);
	vec3 diffuse = diffuseImpact * lightColor;

	//Specular light calculation.
	float specularStrength = 0.5;
	vec3 viewDirection = normalize(viewPos - fragPosition);
	vec3 reflectionDirection = reflect(-lightDirectionNormalized, frag_N_Normalized);
	float specularComponent = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
	vec3 specular = specularStrength * specularComponent * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0);
};
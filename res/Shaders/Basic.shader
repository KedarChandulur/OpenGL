#shader vertex
//#version 410 core
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   //Multiplying model and position for World space calculation.
   fragPosition = vec3(model * vec4(position, 1.0));
   //Need to add transpose and inverse calls on CPU side in future.
   fragNormal = mat3(transpose(inverse(model))) * normal;
   fragTexCoords = texCoords;

   gl_Position = projection * view * model * vec4(position, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 color;

struct Material
{	
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
};

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//Ambient light calculation.
	vec3 ambient = light.ambient * texture(material.diffuse, fragTexCoords).rgb;

	//Diffuse light calculation.
	vec3 Normal = normalize(fragNormal);
	vec3 lightDirection = normalize(light.position - fragPosition);
	float diffuseImpact = max(dot(Normal, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diffuseImpact * texture(material.diffuse, fragTexCoords).rgb;

	//Specular light calculation.
	vec3 viewDirection = normalize(viewPos - fragPosition);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specularComponent = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (specularComponent * material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
};
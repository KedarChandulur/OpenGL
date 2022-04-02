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
   //gl_Position = projection * view * vec4(position, 1.0);
};

#shader fragment
//#version 410 core
#version 330 core

layout(location = 0) out vec4 color;

struct Material
{	
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
};

#define NO_O_POINT_LIGHTS 4

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NO_O_POINT_LIGHTS];
uniform SpotLight spotLight;

//Light function declarations
vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main()
{
	//Properties
	vec3 Normal = normalize(fragNormal);
	vec3 viewDirection = normalize(viewPos - fragPosition);

	//DirectionalLight
	vec3 result = CalculateDirectionalLight(directionalLight, Normal, viewDirection);
	
	//PointLight
	for (int i = 0; i < NO_O_POINT_LIGHTS; i++)
		result += CalculatePointLight(pointLights[i], Normal, fragPosition, viewDirection);

	//SpotLight
	result += CalculateSpotLight(spotLight, Normal, fragPosition, viewDirection);

	color = vec4(result, 1.0);
};

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-directionalLight.direction);

	//diffuse impact.
	float diffuseImpact = max(dot(normal, lightDirection), 0.0);

	//Specular impact.
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	vec3 ambient = directionalLight.ambient * vec3(texture(material.diffuse, fragTexCoords));
	vec3 diffuse = directionalLight.diffuse * diffuseImpact * vec3(texture(material.diffuse, fragTexCoords));
	vec3 specular = directionalLight.specular * specularImpact * vec3(texture(material.specular, fragTexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
	vec3 lightDirection = normalize(pointLight.position - fragPosition);

	//diffuse impact
	float diffuseImpact = max(dot(normal, lightDirection), 0.0);

	//specular impact
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	//Attenuation
	float distance = length(pointLight.position - fragPosition);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, fragTexCoords));
	vec3 diffuse = pointLight.diffuse * diffuseImpact * vec3(texture(material.diffuse, fragTexCoords));
	vec3 specular = pointLight.specular * specularImpact * vec3(texture(material.specular, fragTexCoords));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
	vec3 lightDirection = normalize(spotLight.position - fragPosition);

	//diffuse impact
	float diffuseImpact = max(dot(normal, lightDirection), 0.0);

	//specular impact
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	//Attenuation
	float distance = length(spotLight.position - fragPosition);
	float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

	//spotlight intensity
	float theta = dot(lightDirection, normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, fragTexCoords));
	vec3 diffuse = spotLight.diffuse * diffuseImpact * vec3(texture(material.diffuse, fragTexCoords));
	vec3 specular = spotLight.specular * specularImpact * vec3(texture(material.specular, fragTexCoords));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}
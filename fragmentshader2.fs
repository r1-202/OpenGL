#version 330 core
out vec4 FragColor;

uniform vec3 viewPos;

struct Material
{
	sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};
struct Light
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};
  
uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main()
{
	vec4 color;
	float distance = length(light.position-FragPos);
	float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);
	attenuation = 1.0;
	

	//flashlight
	vec3 lightDir = normalize(light.position-FragPos);
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff-light.outerCutOff;
	float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);
	//ambient component
	vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords))*light.ambient;
	ambient=ambient*intensity;
	//ambient = ambient*attenuation;
	//diffuse component
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse =light.diffuse*diff*vec3(texture(material.texture_diffuse1,TexCoords));
	diffuse = diffuse*intensity;
	//diffuse = diffuse*attenuation;
	//specular component
	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = light.specular*(spec*vec3(texture(material.texture_specular1, TexCoords)));
	specular = specular*intensity;
	//specular = specular*attenuation;

		vec3 result = ambient+diffuse+specular;
		FragColor = vec4(result,1.0);
}
#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec3 Normal;
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

vec4 pointLight()
{

	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 0.5;
	float b = 0.3;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.25f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.55f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 12);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) + texture(tex1, texCoord)) * lightColor * (diffuse * inten + ambient + specular * inten);
}

vec4 direcLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) + texture(tex1, texCoord) +  texture(tex2, texCoord) + texture(tex3, texCoord)) * (diffuse + ambient + specular) * lightColor;
	//return texture(tex2, texCoord) * (diffuse + ambient + specular) * lightColor;
	//return texture(tex0, texCoord) + texture(tex1, texCoord) + texture(tex2, texCoord) * (diffuse + ambient + specular) * lightColor;

}

vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f,-1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) + texture(tex1, texCoord)) * (diffuse * inten + ambient + specular * inten)  * lightColor;

}

void main()
{


	FragColor = direcLight();
	//FragColor = texture(tex0, texCoord)* lightColor * (diffuse + ambient + specular);
	//FragColor = texture(tex1, texCoord) * lightColor * (diffuse + ambient + specular);

}
#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform float shininess;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

void main() {
  // Calculate the lighting values of the fragment using the supplied textures.
  vec3 diffVal = texture(diffuseTexture, texCoords).xyz;
  vec3 specVal = texture(specularTexture, texCoords).xyz;

  // Calculate any direction vectors needed for lighting.
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 lightDirReflect = reflect(-lightDir, normal);
  vec3 viewDir = normalize(viewPos - fragPos);

  // Calculate the diffuse component.
  float d = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = lightColor * diffVal * d;

  // Calculate the specular component.
  float s = pow(max(dot(viewDir, lightDirReflect), 0.0), shininess);
  vec3 specular = lightColor * specVal * s;

  // Combine each component.
  fragColor = vec4(diffuse + specular, 1.0);
}
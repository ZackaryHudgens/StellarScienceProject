#version 330 core

// Vertex attributes
layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoords;

// Instance attributes
layout (location = 4) in mat4 aMatrix;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
  normal = normalize(mat3(aMatrix) * aNormal);
  texCoords = aTexCoords;

  // Calculate the fragment position in world space.
  fragPos = vec3(aMatrix * vec4(aPosition, 1.0));

  gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}
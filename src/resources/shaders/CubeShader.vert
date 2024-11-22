#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 3) in vec2 aTexCoords;
layout (location = 4) in mat4 aMatrix;

out vec2 texCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
  texCoords = aTexCoords;

  gl_Position = projectionMatrix * viewMatrix * aMatrix * vec4(aPosition, 1.0);
}
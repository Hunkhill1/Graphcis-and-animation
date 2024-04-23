#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec4 color;

uniform mat4 xyzwMultipliers;

void main()
{
    gl_Position = xyzwMultipliers * vec4(vPosition, 1.0f);
    color = vec4( vColor, 1.0 );
}

#version 460 core

layout (location = 0) in vec3 vPos;
out vec3 color;

uniform mat4 transformations;
uniform float time;

void main()
{
    const vec3 axis = vec3(0.0, 1.0, 0.0);
    vec3 delta = vec3(0.0, 0.0, 0.0);
    const float amp = 0.2;
    //вычисление значения для цветовых координат
    delta += amp * sin(time);

    gl_Position = transformations * vec4(vPos, 1.0);

    color = delta;
}

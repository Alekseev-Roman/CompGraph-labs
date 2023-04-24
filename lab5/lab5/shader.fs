#version 460 core

in vec3 color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(
        clamp(0.4 + color.x, 0.0, 1.0),
        clamp(0.1 + color.y, 0.0, 1.0),
        clamp(0.4 + color.z, 0.0, 1.0),
        1.0
    );
}

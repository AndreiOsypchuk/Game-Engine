@vertex
#version 460
layout (location = 0) in vec3 v_Pos;
void main()
{
    gl_Position = vec4(v_Pos, 1.0f);
}

@fragment
#version 460
out vec4 f_Color;
void main()
{
    f_Color = vec4(0.3f, 0.5f, 0.6f, 1.0f);
}

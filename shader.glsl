@vertex
#version 460
layout (location = 0) in vec3 v_Pos;
layout (location = 1) in vec3 v_Col;

out vec3 f_Col;

void main()
{
    gl_Position = vec4(v_Pos, 1.0f);
    f_Col = v_Col;
}

@fragment
#version 460
in vec3 f_Col;
out vec4 f_Color;
void main()
{
    f_Color = vec4(0.3f, 0.5f, 0.6f, 1.0f);
    //f_Color = vec4(f_Col, 1.0f);
}

#include <GameEngine>
#include <glad/glad.h>

class TestLayer : public GE::Layer
{
    public:

        enum Type {
            PROGRAM,
            FRAGMENT,
            VERTEX
        };

        void OnAttach()
        {

            

            float vertices[] = {
                0.0f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f
            };

            const char* vertSource = "#version 460\n"
                "layout(location=0) in vec3 Pos;\n"
                "void main() {\n"
                "   gl_Position = vec4(Pos, 1.0f);\n"
                "}\n";

            const char* fragSource = "#version 460\n"
                "out vec4 Color;\n"
                "void main() {\n"
                "   Color = vec4(0.5f, 0.4f, 0.6f, 1.0f);\n"
                "}\n";


            uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertSource, nullptr);
            glCompileShader(vertexShader);
            ErrorCheck(vertexShader, VERTEX);

            uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragSource, nullptr);
            glCompileShader(fragmentShader);
            ErrorCheck(fragmentShader, FRAGMENT);

            m_Program = glCreateProgram();
            glAttachShader(m_Program, vertexShader);
            glAttachShader(m_Program, fragmentShader);
            glLinkProgram(m_Program);
            ErrorCheck(m_Program, PROGRAM);


                

            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            glGenBuffers(1, &m_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
            glEnableVertexAttribArray(0);

        }

        void ErrorCheck(uint32_t thing, Type type)
        {
            int success;
            char infoLog[512];

            switch(type)
            {
                case PROGRAM:
                    {
                        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
                        if(!success)
                        {
                            glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
                            GE_ERR("PROGRAM\n{0}", infoLog);
                        }
                        break;
                    }
                default:
                    {
                        glGetShaderiv(thing, GL_COMPILE_STATUS, &success);
                        if(!success)
                        {
                            glGetShaderInfoLog(thing, 512, nullptr, infoLog);
                            GE_ERR("{0}\n{1}", "SHADER", infoLog);
                            break;
                        }
                    }
            }
        }

        void OnEvent(GE::Event& e) override
        {
        }

        void OnUpdate(float time) override
        {
            glUseProgram(m_Program);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

    public:

        uint32_t m_VAO;
        uint32_t m_VBO;
        uint32_t m_Program;

};

class Example : public GE::Application
{
    public:
        Example() {
            GE_INFO("Is Running");
            PushLayer(new TestLayer);

        };

        ~Example() {};
};

GE::Application* GE::CreateApplication()
{
    return new Example();
}

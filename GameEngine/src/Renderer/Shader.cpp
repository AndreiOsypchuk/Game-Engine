#include "pch.h"
#include "Shader.h"
#include <glad/glad.h>

#include <fstream>

namespace GE
{
    Shader::Shader(const char* shaderSource)
    {
        std::fstream shaderFile(shaderSource);

        
        if(shaderFile.is_open())
        {
            std::string line;
            std::stringstream vertStream;
            std::stringstream fragStream;

            bool isVertex;

            while(std::getline(shaderFile, line))
            {
                if(line == "@vertex")
                {
                    isVertex = true;
                    continue;
                }
                if(line == "@fragment")
                {
                    isVertex = false;
                    continue;
                }

                if(isVertex)
                {
                    vertStream << line << "\n";
                }
                else
                {
                    fragStream << line << "\n";
                }

            }
            std::string vertString = vertStream.str();
            std::string fragString = fragStream.str();

            const char* vertSource = vertString.c_str();
            const char* fragSource = fragString.c_str();

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
        } else {
            GE_CORE_ERR("Unable open file at path: \"{0}\"", shaderSource);
        }




    }

    void Shader::ErrorCheck(uint32_t id, Type type)
    {
        int success;
        char infoLog[512];
        switch(type)
        {
            case PROGRAM:
                {
                    glGetProgramiv(id, GL_LINK_STATUS, &success);
                    if(!success)
                    {
                        glGetProgramInfoLog(id, 512, nullptr, infoLog);
                        GE_CORE_ERR("{0}\n{1}", type, infoLog);
                        std::cout << infoLog << std::endl;
                    }
                    break;
                }
            default:
                {
                    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                    if(!success)
                    {
                        glGetShaderInfoLog(id, 512, nullptr, infoLog);
                        GE_CORE_ERR("{0}\n{1}", type, infoLog);
                        std::cout << infoLog << std::endl;
                    }
                }
        }
    };

    void Shader::Use()
    {
        glUseProgram(m_Program);
    }
}


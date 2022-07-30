#pragma once

namespace GE
{ 
    enum Type
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    class Shader
    {
        public:
            Shader(const char* shaderSource);
            void Use();

        public:
            uint32_t m_Program;

        private:
            void ErrorCheck(uint32_t id, Type type);
    };
}

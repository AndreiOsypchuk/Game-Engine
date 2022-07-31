#pragma once

namespace GE
{
    enum class VertexDataType
    {
        Float,
        Float2,
        Float3,
        Float4,
    };

    uint32_t VertexDataLength(VertexDataType type);
    uint32_t VertexDataSize(VertexDataType type);

    struct VertexBufferObject
    {
        VertexArrayBuffer(void* data)
            : m_Data(data) {};
        void* m_Data;
        uint32_t m_ID;
    };

    struct Vertex
    {

        Vertex(VertexDataType type, const char* name)
            : m_Type(type), 
            m_Name(name), 
            m_Length(VertexDataLength(type)),
            m_Size(VertexDataSize(type))
        {};
        VertexDataType m_Type;
        uint32_t m_Length;
        uint32_t m_Size;
        const char* m_Name;
    };

    class VertexSpec
    {
        public:
            VertexSpec(VertexBufferObject vbo, std::initializer_list<Vertex> l);
            void Bind();
            void Unbind();
            void GenAttrib();
        public:
            uint32_t m_ID;
            std::vector<Vertex> m_VertexSpecList;
            unsigned int m_Size;
    };
}

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

    class VertexBufferObject
    {
        public:
            VertexBufferObject(void* data, int size)
                : m_Data(data), m_Size(size) {};
            uint32_t m_ID;
            void* m_Data;
            int m_Size;
        public:
            void Bind();
    };

    class VertexIndexObject
    {
        public:
            VertexIndexObject(void* data, int size)
                : m_Data(data), m_Size(size) {};
            uint32_t m_ID;
            void* m_Data;
            int m_Size;
        public:
            void Bind();
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
            VertexSpec(std::initializer_list<Vertex> l);
            void Bind();
            void Unbind();
            void GenAttributes();
            void AttachVertexBuffer(std::shared_ptr<VertexBufferObject> vbo);
            void AttachIndexBuffer(std::shared_ptr<VertexIndexObject> vio);
        public:
            uint32_t m_ID;
            std::shared_ptr<VertexBufferObject> m_VBO;
            std::shared_ptr<VertexIndexObject> m_VIO;
            std::vector<Vertex> m_VertexSpecList;
            unsigned int m_Stride;
    };
}

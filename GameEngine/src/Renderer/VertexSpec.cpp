#include "pch.h"
#include "VertexSpec.h"
#include <glad/glad.h>

namespace GE
{
    uint32_t VertexDataLength(VertexDataType type)
    {
        switch(type)
        {
            case VertexDataType::Float:     return 1;
            case VertexDataType::Float2:    return 2;
            case VertexDataType::Float3:    return 3;
            case VertexDataType::Float4:    return 4;
        }

        GE_CORE_ERR("Unknown data type was supplied to a vertex ");

        return 0;
    }

    uint32_t VertexDataSize(VertexDataType type)
    {
        switch(type)
        {
            case VertexDataType::Float:     return 1 * sizeof(float);
            case VertexDataType::Float2:    return 2 * sizeof(float);
            case VertexDataType::Float3:    return 3 * sizeof(float);
            case VertexDataType::Float4:    return 4 * sizeof(float);
        }

        GE_CORE_ERR("Unknown data type was supplied to a vertex ");

        return 0;
    }


    void VertexBufferObject::Bind()
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW);
    }

    

    VertexSpec::VertexSpec(VertexBufferObject vbo, std::initializer_list<Vertex> l)
        : m_VertexSpecList(l), m_Stride(0), m_VBO(vbo)
    {
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);

        m_VBO.Bind();

        for(auto vertex : m_VertexSpecList)
            m_Stride += vertex.m_Size;
    };


    void VertexSpec::GenAttrib()
    {
        int i = 0;
        unsigned int offset_pointer = 0;
        for(auto vertex : m_VertexSpecList)
        {
            glVertexAttribPointer(i, vertex.m_Length, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(intptr_t)offset_pointer);
            glEnableVertexAttribArray(i);
            offset_pointer += vertex.m_Size;
            i++;
        }
    }

           
}

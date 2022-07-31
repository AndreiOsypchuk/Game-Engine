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
        
    

    VertexSpec::VertexSpec(std::initializer_list<Vertex> l)
        : m_VertexSpecList(l), m_Size(0)
    {
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);
        for(auto vertex : m_VertexSpecList)
            m_Size += vertex.m_Size;
    };


    void VertexSpec::GenAttrib()
    {
        int i = 0;
        unsigned int stride = 0;
        for(auto vertex : m_VertexSpecList)
        {
            glVertexAttribPointer(i, vertex.m_Length, GL_FLOAT, GL_FALSE, m_Size, (const void*)(stride * sizeof(float)));
            glEnableVertexAttribArray(i);
            stride += vertex.m_Length;
            i++;
        }
    }

           
}

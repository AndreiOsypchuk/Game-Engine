#include "pch.h"
#include "Layer.h"

namespace GE
{


    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }
    
    void LayerStack::Push(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::Pop(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
        if(it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex++;
        }
    }
}

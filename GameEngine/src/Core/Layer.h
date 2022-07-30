#pragma once

#include "Event.h"

namespace GE
{
    class Layer
    {
        public:
            Layer() = default;
            virtual void OnAttach() {};
            virtual void OnEvent(Event& e) {};
            virtual void OnDetach() {};
            virtual void OnUpdate(float time) {};
            virtual ~Layer() = default;
    };


    class LayerStack
    {
        public:

            LayerStack() = default;
            ~LayerStack();

        public:

            void Push(Layer* layer);
            void Pop(Layer* layer);

            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }
            std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
            std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

            
        public:
            std::vector<Layer*> m_Layers;
            int m_LayerInsertIndex = 0;
    };

}

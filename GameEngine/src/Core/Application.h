#pragma once
#include <memory>
#include "Window.h"
#include "Layer.h"
namespace GE 
{
    class Application 
    {
        public:
            Application();
            virtual ~Application();
            void Run();
            void EventHandler(Event&);

            void PushLayer(Layer* layer);

            bool OnClose(WindowClosed&);
            bool OnResize(WindowResized&);
            bool OnFocus(WindowFocused&);

        protected:
            std::shared_ptr<Window> m_Window;
            LayerStack m_LayerStack;
        private:
            bool m_Running;
            static Application* s_Instance;
            
    };


    Application* CreateApplication();           // This is defined by the client
}

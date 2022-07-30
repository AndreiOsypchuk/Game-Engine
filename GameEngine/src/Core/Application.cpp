#include "pch.h"
#include "Window.h"
#include "Application.h"
#include "Event.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace GE 
{
    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        Logger::Init();
        m_Window = std::make_shared<Window>(800, 600, "Application");
        m_Window->SetEventHandler(BIND_EVENT_FN(EventHandler));
        m_Running = true;
        s_Instance = this;
    }

    Application::~Application()
    {
    }

    // this is passed to the window as a handler for all the events
    // it will resieve all events and dispatch them

    void Application::EventHandler(Event& e)
    {
        // create a dispatcher
        EventDispatcher dispatcher(e);

        // dispatch events
        dispatcher.Dispatch<WindowClosed>(BIND_EVENT_FN(OnClose));



        for(auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if(e.m_IsHandled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Run()
    {
        GE_CORE_INFO("Is Running...");

        while(m_Running)
        {
            m_Window->Begin();
            {
                for(auto layer : m_LayerStack)
                    layer->OnUpdate(m_Window->GetTime());

            }
            m_Window->End();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        layer->OnAttach();
        m_LayerStack.Push(layer);
    }

    bool Application::OnClose(WindowClosed& e)
    {
        GE_CORE_INFO(e);
        m_Running = false;
        return true;
    }

    bool Application::OnResize(WindowResized& e)
    {
        GE_CORE_TRACE(e);
        return true;
    }

    bool Application::OnFocus(WindowFocused& e)
    {
        GE_CORE_INFO(e);
        return true;
    }
}



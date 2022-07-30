#include "pch.h"
#include <glad/glad.h>
#include "Event.h"
#include "Window.h"


namespace GE
{

#define getWindowPropsPointer(x) (WindowProps*)glfwGetWindowUserPointer(window);

    Window::Window(float width, float height, const char* title)
        : m_Props(WindowProps(width, height, title))
    {
        if(!glfwInit())
        {
            GE_CORE_ERR("GLFW DID NOT INIT");
        } else {
            GE_CORE_TRACE("GLFW init");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title, nullptr, nullptr);

        if(!m_Window)
        {
            GE_CORE_ERR("Window is null");
        } else {
            GE_CORE_TRACE("Window created");
        }

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Props);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            GE_CORE_ERR("Glad did not init");
        } else {
            GE_CORE_TRACE("Glad init");
        }

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowProps* props = getWindowPropsPointer(window);
            WindowClosed e;
            props->eventHandler(e);
            props->isOpen = false;
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int x, int y) {
            WindowProps* props = (WindowProps*)glfwGetWindowUserPointer(window);
            WindowResized e(x, y);
            props->Width = x;
            props->Height = y;
            glViewport(0, 0, x, y);
            props->eventHandler(e);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowProps* props = (WindowProps*)glfwGetWindowUserPointer(window);
            if(focused)
            {
                WindowFocused e;
                props->eventHandler(e);
            }
            else
            {
                WindowUnfocused e;
                props->eventHandler(e);
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int pressed, int mods) {
            WindowProps* props = (WindowProps*)glfwGetWindowUserPointer(window);
            if(pressed)
            {
                MouseButtonPressed e(button, mods);
                props->eventHandler(e);
            }
            else
            {
                MouseButtonReleased e(button, mods);
                props->eventHandler(e);
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
            WindowProps* props = getWindowPropsPointer(window);
            MouseMoved e(x, y);
            props->eventHandler(e);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowProps* props = getWindowPropsPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressed e(key, false);
                    props->eventHandler(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressed e(key, true);
                    props->eventHandler(e);
                    break;
                }
                default:
                {
                    KeyReleased e(key);
                    props->eventHandler(e);
                    break;
                }
            }
                
            
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
            WindowProps* props = getWindowPropsPointer(window);
            CharTyped e(c);
            props->eventHandler(e);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y) {
            WindowProps* props = getWindowPropsPointer(window);
            MouseScrolled e(x, y);
            props->eventHandler(e);
        }); 
    }

    void Window::Begin()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Window::End()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    float Window::GetAspectRatio() const
    {
        return m_Props.Width / m_Props.Height;
    }

    float Window::GetWidth() const
    {
        return m_Props.Width;
    }

    float Window::GetHeight() const
    {
        return m_Props.Height;
    }

    bool Window::IsOpen() const
    {
        return m_Props.isOpen;
    }

    void Window::SetEventHandler(const EventHandlerFn& fn)
    {
        m_Props.eventHandler = fn;
    }

    float Window::GetTime()
    {
        return glfwGetTime();
    }
}


#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "Event.h"
#include <functional>
namespace GE 
{
    class Window
    {
        public:
            // typedef void (*EventHandlerFn)(Event&);
            using EventHandlerFn = std::function<void(Event& e)>;

            Window(float, float, const char*);

            void Begin();
            void End();

            float GetAspectRatio() const;
            float GetWidth() const;
            float GetHeight() const;
            float GetTime();
            bool IsOpen() const;
            void SetEventHandler(const EventHandlerFn& eventHandler);

        public:

            

        private:


            struct WindowProps
            {
                WindowProps(float w = 800.0f, float h = 700.0f, const char* title = "New window")
                    : Width(w), Height(h), Title(title), isOpen(true) {}
                float Width, Height;
                const char* Title;
                bool isOpen;
                EventHandlerFn eventHandler;
            };

            WindowProps m_Props;

            GLFWwindow* m_Window;
    };
}

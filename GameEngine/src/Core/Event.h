#pragma once
#include "pch.h"

namespace GE 
{
    enum class EventType 
    {
        WINDOW_CLOSED,
        WINDOW_RESIZED,
        WINDOW_FOCUSED,
        WINDOW_UNFOCUSED,

        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,
        MOUSE_MOVED,
        MOUSE_SCROLLED,

        KEY_PRESSED,
        KEY_RELEASED,
        CHAR_TYPED
    };

    enum EventCategory : char
    {
        APPLICATION_EVENT       = 1 << 0,   // Start, Load ...
        WINDOW_EVENT            = 1 << 1,   // Resize, Minimize ...
        MOUSE_EVENT             = 1 << 2,   // Click, Move
        KEYBOARD_EVENT          = 1 << 3,   // Press, Release ..
    };

    #define EVENT_TYPE(type) \
        static EventType GetStaticEventType() { return EventType::type; } \
        EventType GetEventType() const override { return GetStaticEventType();} \
        const char* GetEventName() const override { return #type; }

    #define EVENT_CATEGORY(category) \
        virtual char GetEventCategory() const override { return category; }


    class Event
    {
        public:
            bool m_IsHandled = false;
        public:
            Event() = default;
            virtual ~Event() = default;
            
            virtual const char* GetEventName() const = 0;
            virtual char GetEventCategory() const = 0;
            virtual EventType GetEventType() const = 0;
            
            virtual std::string ToString() const 
            {
                return GetEventName();
            };
    };


    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }


    class EventDispatcher
    {
        public:
            EventDispatcher(Event& e)
                : m_Event(e) {}
        public:

            template<typename E, typename F>
            bool Dispatch(const F& fn)
            {

                if(m_Event.GetEventType() == E::GetStaticEventType())
                {
                    m_Event.m_IsHandled |= fn(static_cast<E&>(m_Event));
                    return true;
                }

                return false;
            }

        private:
            Event& m_Event;
    };

    /*
     * ================================================================= 
     * =============================== EVENTS ==========================
     * =================================================================
     *
    */
    
    enum ModKeys
    {
        NONE = 0,
        GE_SHIFT    = 1 << 0,
        GE_CTRL     = 1 << 1,
        GE_ALT      = 1 << 2,
        GE_SUPER    = 1 << 3
    };

    // WINDOW EVENTS

    class WindowClosed : public Event
    {
        public:
            EVENT_TYPE(WINDOW_CLOSED);
            EVENT_CATEGORY(WINDOW_EVENT);
        public:
            WindowClosed() = default;

    };


    class WindowFocused : public Event
    {
        public:
            EVENT_TYPE(WINDOW_FOCUSED);
            EVENT_CATEGORY(WINDOW_EVENT);
        public:
            WindowFocused() = default;
    };

    
    class WindowUnfocused : public Event
    {
        public:
            EVENT_TYPE(WINDOW_UNFOCUSED);
            EVENT_CATEGORY(WINDOW_EVENT);
        public:
            WindowUnfocused() = default;
    };


    class WindowResized : public Event
    {
        public:
            EVENT_TYPE(WINDOW_RESIZED);
            EVENT_CATEGORY(WINDOW_EVENT);
        public:
            WindowResized( int x, int y)
                : m_Width(x), m_Height(y) {};
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - " << m_Width << "/" << m_Height << "/" << (float)m_Width / (float)m_Height;
                return ss.str();
            }

            int m_Width;
            int m_Height;
    };

    // MOUSE EVENTS

    class MouseButtonEvent : public Event
    {
        public:
            MouseButtonEvent(int button, int mod = NONE)
                : m_Button(button), m_ModKeys(mod) {};
            int GetButton() const { return m_Button; };
            int GetModKeys() const { return m_ModKeys; };
            int m_Button;
            int m_ModKeys;

    };

    class MouseButtonPressed : public MouseButtonEvent
    {
        public:
            EVENT_TYPE(MOUSE_BUTTON_PRESSED);
            EVENT_CATEGORY(MOUSE_EVENT);
        public:
            MouseButtonPressed(int button, char mod)
                : MouseButtonEvent(button, mod) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Button << ", " << m_ModKeys << "]";
                return ss.str();
            }
    };

    class MouseButtonReleased : public MouseButtonEvent
    {
        public:
            EVENT_TYPE(MOUSE_BUTTON_RELEASED);
            EVENT_CATEGORY(MOUSE_EVENT);
        public:
            MouseButtonReleased(int button, int mod)
                : MouseButtonEvent(button, mod) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Button << ", " << m_ModKeys << "]";
                return ss.str();
            }
    };

    class MouseMoved : public Event
    {
        public:
            EVENT_TYPE(MOUSE_MOVED);
            EVENT_CATEGORY(MOUSE_EVENT);
        public:
            MouseMoved(double x, double y)
                : m_Xpos(x), m_Ypos(y) {}

            double GetX() const
            {
                return m_Xpos;
            }

            double GetY() const
            {
                return m_Ypos;
            }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Xpos << "/" << m_Ypos << "]";
                return ss.str();
            }

        private:
            double m_Xpos;
            double m_Ypos;
    };


    class MouseScrolled : public Event
    {
        public:
            EVENT_TYPE(MOUSE_SCROLLED);
            EVENT_CATEGORY(MOUSE_EVENT);
        public:
            MouseScrolled(double x, double y)
                : m_Xoffset(x), m_Yoffset(y) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Xoffset << " : " << m_Yoffset << "]";
                return ss.str();
            }

        private:
            double m_Xoffset;
            double m_Yoffset;
    };


    // KEYBOARD

    class KeyboardEvent : public Event
    {
        public:
            KeyboardEvent(int button)
                : m_Button(button) {}
            int getButton() const { return m_Button; };
        public:
            int m_Button;
    };


    class KeyPressed : public KeyboardEvent
    {
        public:
            EVENT_TYPE(KEY_PRESSED);
            EVENT_CATEGORY(KEYBOARD_EVENT);
        public:
            KeyPressed(int button, bool held)
                : KeyboardEvent(button), m_Held(held) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Button << ", " << m_Held << "]";
                return ss.str();
            }
        protected:
            bool m_Held;
    };

    class KeyReleased : public KeyboardEvent
    {
        public:
            EVENT_TYPE(KEY_RELEASED);
            EVENT_CATEGORY(KEYBOARD_EVENT);
        public:
            KeyReleased(int button)
                : KeyboardEvent(button) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Button << "]";
                return ss.str();
            }
    };

    class CharTyped : public Event
    {
        public:
            EVENT_TYPE(CHAR_TYPED);
            EVENT_CATEGORY(KEYBOARD_EVENT);
        public:
            CharTyped(unsigned int c)
                : m_Character(c) {}
            
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << GetEventName() << " - [" << m_Character << " : " << (char)m_Character << "]";
                return ss.str();
            }
        protected:
            unsigned int m_Character;
    };
}

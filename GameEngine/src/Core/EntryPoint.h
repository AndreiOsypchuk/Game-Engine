#pragma once
#include "Core/Application.h"
extern GE::Application* GE::CreateApplication();
int main()
{
    auto app = GE::CreateApplication();
    app->Run();
    delete app;
}

workspace "GameEngine"
    configurations {"Debug", "Release"}
    architecture "x86_64"
    startproject "Example"

    include "GameEngine/deps/GLFW"
    include "GameEngine/deps/glad"
    include "GameEngine/deps/spdlog"

    depdirs = {}
    depdirs["GLFW"] = "%{wks.location}/GameEngine/deps/GLFW/include"
    depdirs["glad"] = "%{wks.location}/GameEngine/deps/glad/include"
    depdirs["glm"] = "%{wks.location}/GameEngine/deps/glm"
    depdirs["spdlog"] = "%{wks.location}/GameEngine/deps/spdlog/include"
    depdirs["GameEngine"] = "%{wks.location}/GameEngine/src"

    include "GameEngine"
    include "Example"

project "GameEngine"
        language "C++"
        kind "StaticLib"
        cppdialect "C++17"
        staticruntime "on"

        pchheader "pch.h"
        pchsource "%{prj.location}/pch.cpp"

        targetdir ("%{wks.location}/bin/%{prj.name}_%{cfg.buildcfg}")
        objdir ("%{wks.location}/bin-int/%{prj.name}_%{cfg.buildcfg}")

        files {
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/src/**.h"
        }

        defines {
            "GLFW_INCLUDE_NONE"
        }

        includedirs {
            "%{depdirs.GameEngine}",
            "%{depdirs.GLFW}",
            "%{depdirs.glad}",
            "%{depdirs.glm}",
            "%{depdirs.spdlog}",
        }

        links {
            'X11',
            'dl',
            'pthread',
            'GLFW',
            'glad',
            'spdlog'
        }

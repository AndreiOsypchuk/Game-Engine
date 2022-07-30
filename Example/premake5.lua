project "Example"
        language "C++"
        cppdialect "C++17"
        kind "ConsoleApp"
        staticruntime "on"

        targetdir ("%{wks.location}/bin/%{prj.name}_%{cfg.buildcfg}")
        objdir ("%{wks.location}/bin-int/%{prj.name}_%{cfg.buildcfg}")

        files {
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/src/**.h"
        }

        defines {
            "GLFW_INCLUDE_NONE"
        }


        includedirs(depdirs)
        links {
            "GameEngine",
            'GLFW',
            'glad',
            'spdlog'
        }

        filter "system:linux"
            links {
                'X11',
                'dl',
                'pthread',
            }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

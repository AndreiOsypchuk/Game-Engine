project "glad"
    configurations {"Debug", "Release"}
    language "C"
    kind "StaticLib"

    targetdir ("bin/%{prj.name}_%{cfg.buildcfg}")
    objdir ("bin-int/%{prj.name}_%{cfg.buildcfg}")
    
    includedirs {
        "include"
    }

    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
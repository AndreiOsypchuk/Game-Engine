project "GLFW"
    configurations {"Debug", "Release"}
    language "C"
    kind "StaticLib"

    targetdir ("bin/%{prj.name}_%{cfg.buildcfg}")
    objdir ("bin-int/%{prj.name}_%{cfg.buildcfg}")

    files {                    
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",   
    
        "src/context.c",       
        "src/egl_context.c",   
        "src/glx_context.c",   
    
        "src/init.c",          
        "src/input.c",         
        "src/vulkan.c",        
        "src/monitor.c",       
        "src/platform.c",      
        "src/window.c",        
      
        "src/null_init.c",     
        "src/null_joystick.c", 
        "src/null_monitor.c",  
        "src/null_window.c"    
        
    }   
        
    defines {
        "_GLFW_X11"            
    }   
        
    filter "system:linux"      
        files {
            "src/posix_module.c",           
            "src/posix_poll.c",
            "src/posix_thread.c",           
            "src/posix_time.c",
            "src/osmesa_context.c",         
    
            "src/x11_init.c",  
            "src/x11_monitor.c",            
            "src/x11_platform.h",           
            "src/x11_window.c",
            "src/xkb_unicode.c",            
        
            "src/linux_joystick.c"          
        }



-------------------------------------------------------------------------

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

    -------------------------------------------------------------------

    project "spdlog"
    configurations {"Debug", "Release"}
    language "C++"
    kind "StaticLib"
    staticruntime "On"

    targetdir ("bin/%{prj.name}_%{cfg.buildcfg}")
    objdir ("bin-int/%{prj.name}_%{cfg.buildcfg}")

    includedirs {"include"}
    defines {
        "SPDLOG_COMPILED_LIB"
    }
    files {
        "src/async.cpp",
        "src/cfg.cpp",
        "src/color_sinks.cpp",
        "src/file_sinks.cpp",
        "src/fmt.cpp",
        "src/spdlog.cpp",
        "src/stdout_sinks.cpp"
    }

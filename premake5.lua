workspace "OpenGL-Sandbox"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }
    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "OpenGL-Sandbox/vendor/glfw"
    include "OpenGL-Sandbox/vendor/Glad"
group ""

project "OpenGL-Sandbox"
    language "c++"
    cppdialect "c++17"
    kind "ConsoleApp"
	staticruntime "on"
    location "OpenGL-Sandbox"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor",
        "%{prj.name}/vendor/glfw/include",
        "%{prj.name}/vendor/Glad/include"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

    filter "configurations:Release"
    runtime "Release"
    optimize "on"




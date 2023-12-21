workspace "OpenGL-Sandbox"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }
    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "OpenGL-Sandbox/vendor/glfw"
    include "OpenGL-Sandbox/vendor/Glad"
    include "OpenGL-Sandbox/vendor/imgui"
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
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
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
        "%{prj.name}/vendor/Glad/include",
        "%{prj.name}/vendor/glm",
        "%{prj.name}/vendor/stb_image",
        "%{prj.name}/vendor/imgui"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

    filter "configurations:Release"
    runtime "Release"
    optimize "on"




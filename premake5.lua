workspace "StudioSimGroup2"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/ext/**.h",
		"%{prj.name}/ext/**.c",
		"%{prj.name}/ext/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
		"%{prj.name}/ext"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WINDOWS_PLATFORM",
            "ENGINE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        optimize "On"    

project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"

        targetdir ("bin/".. outputdir .. "/%{prj.name}")
        objdir ("bin-int/".. outputdir .. "/%{prj.name}")
    
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Engine/src"
        }

        links
        {
            "Engine"
        }

        filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
            "WINDOWS_PLATFORM"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

workspace "Sleepy Engine"
    architecture "x64"
    startproject "Game"

    configurations
    {
        "DebugOGL",
		"DebugD3D11",
        "ReleaseOGL",
		"ReleaseD3D11"
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
		"%{prj.name}/ext/**.hpp",
		"%{prj.name}/ext/**.cpp"
    }
	
	links
	{
		"OpenAL32.lib",
		"ImGui"
	}

    includedirs
    {
        "%{prj.name}/src",
		"%{prj.name}/ext",
		"%{wks.location}/Imgui/src",
		"%{wks.location}/Imgui/ext"
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

    filter "configurations:DebugOGL"
        defines "ENGINE_DEBUG_OGL"
        symbols "On"
		excludes
		{
			"%{prj.name}/src/Backend/D3D11/**.h",
			"%{prj.name}/src/Backend/D3D11/**.cpp"
		}
		
		libdirs
		{
			"%{prj.name}/ext/OpenAL-Soft/Debug"
		}

	filter "configurations:DebugD3D11"
        defines "ENGINE_DEBUG_D3D11"
        symbols "On"
		excludes
		{
			"%{prj.name}/src/Backend/OGL/**.h",
			"%{prj.name}/src/Backend/OGL/**.cpp"
		}
		
		libdirs
		{
			"%{prj.name}/ext/OpenAL-Soft/Debug"
		}

    filter "configurations:ReleaseOGL"
        defines "ENGINE_RELEASE_OGL"
        optimize "On"
		excludes
		{
			"%{prj.name}/src/Backend/D3D11/**.h",
			"%{prj.name}/src/Backend/D3D11/**.cpp"
		}		
		
		libdirs
		{
			"%{prj.name}/ext/OpenAL-Soft/Release"
		}
	
	filter "configurations:ReleaseD3D11"
        defines "ENGINE_RELEASE_D3D11"
        optimize "On"
		excludes
		{
			"%{prj.name}/src/Backend/OGL/**.h",
			"%{prj.name}/src/Backend/OGL/**.cpp"
		}		    
		
		libdirs
		{
			"%{prj.name}/ext/OpenAL-Soft/Release"
		}
		
project "ImGui"
    location "ImGui"
    kind "StaticLib"
    language "C++"
	buildoptions "/MTd"
	
	files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	includedirs
	{
		"%{wks.location}/Engine/ext/"
	}

    filter "configurations:DebugOGL"
		excludes
		{
			"%{prj.name}/src/D3D11/**.h",
			"%{prj.name}/src/D3D11/**.cpp"
		}

	filter "configurations:DebugD3D11"
		excludes
		{
			"%{prj.name}/src/OpenGL/**.h",
			"%{prj.name}/src/OpenGL/**.cpp"
		}

    filter "configurations:ReleaseOGL"
		excludes
		{
			"%{prj.name}/src/D3D11/**.h",
			"%{prj.name}/src/D3D11/**.cpp"
		}		
	
	filter "configurations:ReleaseD3D11"
		excludes
		{
			"%{prj.name}/src/OpenGL/**.h",
			"%{prj.name}/src/OpenGL/**.cpp"
		}		    

		
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
		defines "ENGINE_DEBUG_OGL"
		symbols "On"

	filter "configurations:Debug"
		defines "ENGINE_DEBUG_D3D11"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE_OGL"
		optimize "On"
		
	filter "configurations:Release"
		defines "ENGINE_RELEASE_D3D11"
		optimize "On"

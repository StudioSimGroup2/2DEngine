workspace "Sleepy Engine"
    architecture "x64"
    startproject "Game"
	cppdialect "C++17"

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
		"ImGui",
		"TinyXML"
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
		runtime "Debug"
		excludes
		{
			"%{prj.name}/src/Backend/D3D11/**.h",
			"%{prj.name}/src/Backend/D3D11/**.cpp"
		}
		
		libdirs
		{
			"%{prj.name}/lib/OpenAL/DBG"
		}

	filter "configurations:DebugD3D11"
        defines "ENGINE_DEBUG_D3D11"
        symbols "On"
		runtime "Debug"
		excludes
		{
			"%{prj.name}/src/Backend/OGL/**.h",
			"%{prj.name}/src/Backend/OGL/**.cpp"
		}
		
		libdirs
		{
			"%{prj.name}/lib/OpenAL/DBG"
		}

    filter "configurations:ReleaseOGL"
        defines "ENGINE_RELEASE_OGL"
        optimize "On"
		runtime "Release"
		excludes
		{
			"%{prj.name}/src/Backend/D3D11/**.h",
			"%{prj.name}/src/Backend/D3D11/**.cpp"
		}		
		
		libdirs
		{
			"%{prj.name}/lib/OpenAL/RLS"
		}
	
	filter "configurations:ReleaseD3D11"
        defines "ENGINE_RELEASE_D3D11"
        optimize "On"
		runtime "Release"
		excludes
		{
			"%{prj.name}/src/Backend/OGL/**.h",
			"%{prj.name}/src/Backend/OGL/**.cpp"
		}		    
		
		libdirs
		{
			"%{prj.name}/lib/OpenAL/RLS"
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
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/ext/**.h",
		"%{prj.name}/ext/**.c",
        "%{prj.name}/ext/**.cpp"
    }

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

	includedirs
	{
		"%{wks.location}/Engine/ext/"
	}

    filter "configurations:DebugOGL"
	    defines "ENGINE_DEBUG_OGL"
        symbols "On"
		runtime "Debug"
		excludes
		{
			"%{prj.name}/src/D3D11/**.h",
			"%{prj.name}/src/D3D11/**.cpp"
		}

	filter "configurations:DebugD3D11"
	    defines "ENGINE_DEBUG_D3D11"
        symbols "On"
		runtime "Debug"
		excludes
		{
			"%{prj.name}/src/OpenGL/**.h",
			"%{prj.name}/src/OpenGL/**.cpp"
		}

    filter "configurations:ReleaseOGL"
	    defines "ENGINE_RELEASE_OGL"
        optimize "On"
		runtime "Release"
		excludes
		{
			"%{prj.name}/src/D3D11/**.h",
			"%{prj.name}/src/D3D11/**.cpp"
		}		
	
	filter "configurations:ReleaseD3D11"
	    defines "ENGINE_RELEASE_D3D11"
        optimize "On"
		runtime "Release"
		excludes
		{
			"%{prj.name}/src/OpenGL/**.h",
			"%{prj.name}/src/OpenGL/**.cpp"
		}		 

project "TinyXML"
    location "TinyXML"
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
	    defines "ENGINE_DEBUG_OGL"
        symbols "On"
		runtime "Debug"

	filter "configurations:DebugD3D11"
	    defines "ENGINE_DEBUG_D3D11"
        symbols "On"
		runtime "Debug"

    filter "configurations:ReleaseOGL"
	    defines "ENGINE_RELEASE_OGL"
        optimize "On"
		runtime "Release"
	
	filter "configurations:ReleaseD3D11"
	    defines "ENGINE_RELEASE_D3D11"
        optimize "On"
		runtime "Release"

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
            "Engine/src",
			"Engine/ext"
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

	filter "configurations:DebugOGL"
		defines "ENGINE_DEBUG_OGL"
		runtime "Debug"
		symbols "On"

	filter "configurations:DebugD3D11"
		defines "ENGINE_DEBUG_D3D11"
		runtime "Debug"
		symbols "On"

	filter "configurations:ReleaseOGL"
		defines "ENGINE_RELEASE_OGL"
		runtime "Release"
		optimize "On"
		
	filter "configurations:ReleaseD3D11"
		defines "ENGINE_RELEASE_D3D11"
		runtime "Release"
		optimize "On"

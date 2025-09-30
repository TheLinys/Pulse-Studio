project "GLM"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	warnings "off"

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries-Intermediates/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"**.h",
		"**.hpp",
		"**.cpp",
		"**inl"
	}

	includedirs
	{
		""
	}

	defines
	{
		"GLM_ENABLE_EXPERIMENTAL",
		"GLM_FORCE_XYZW"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
			"**.h",
			"**.hpp",
			"**.cpp",
			"**inl"
		}

	filter "system:macosx"
		pic "On"

		files
		{
			"**.h",
			"**.hpp",
			"**.cpp",
			"**inl"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"**.h",
			"**.hpp",
			"**.cpp",
			"**inl"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"
project "Freetype"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	warnings "off"

    targetdir ("../../../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../../../Binaries-Intermediates/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "**.c",
        "**.cpp",
        "**.h",
		"**.md",
		"**.dsp",
		"**.list"
    }

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
            "**.c",
            "**.cpp",
            "**.h",
			"**.md",
			"**.dsp",
			"**.list"
		}

	filter "system:macosx"
		pic "On"

		files
		{
            "**.c",
            "**.cpp",
            "**.h",
			"**.md",
			"**.dsp",
			"**.list"
		}
	filter "system:windows"
		systemversion "latest"

		files
		{
            "**.c",
            "**.cpp",
            "**.h",
			"**.md",
			"**.dsp",
			"**.list"
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